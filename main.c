/**
 * Copyright (c) 2019 Joshua Inscoe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */



#include <unistd.h>

#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rot.h"



#define DEFAULT_SHIFT       3


#define XSTR( x )           STR( x )
#define  STR( x )           # x

#define ROT_VERSION_STRING  XSTR( ROT_VERSION_MAJOR ) "." XSTR( ROT_VERSION_MINOR ) "." XSTR( ROT_VERSION_MICRO )

static const char* _version = "rot v" ROT_VERSION_STRING "\n";

static const char* _usage =
    "Usage: %s [OPTIONS] [STRING] [...]\n"                                  \
    "\n"                                                                    \
    "Options:\n"                                                            \
    "  -h, --help     Show this help menu and exit.\n"                      \
    "  -V, --version  Show the version and exit.\n"                         \
    "  -a             Print all possible rotations one after the other.\n"  \
    "  -s SHIFT       Specify the shift value [default: %d].\n"             \
    ;



static void _vers(FILE* stream)
{
    fprintf(stream, _version);

    return;
}

static void _help(FILE* stream, const char* progname)
{
    fprintf(stream, _usage, progname, DEFAULT_SHIFT);

    return;
}



static char* _combine_argv(int argc, char* const argv[], int start)
{
    static const char* argvsep = " ";

    char* s = NULL;

    size_t length = 0;
    size_t offset = 0;

    size_t n;

    int i;

    if (start < argc)
    {
        for (i = start; i < argc; ++i)
        {
            length += strlen(argv[i]);
            length += 1;
        }

        length += 1;

        s = (char*)malloc(sizeof(char) * length);
        if (!s)
        {
            fprintf(stderr, "error: malloc() [size=%zu]: %s\n", length, strerror(errno));

            exit(1);
        }

        for (i = start; i < argc; ++i)
        {
            n = strlen(argv[i]);

            memcpy(s + offset, argv[i], n);
            offset += n;
            memcpy(s + offset, argvsep, 1);
            offset += 1;
        }

        offset -= 1;

        s[offset] = '\n';
        offset += 1;
        s[offset] = '\0';
    }

    return s;
}


static char* _read_next_input(int delim)
{
    static char*  s = NULL;
    static size_t n = 0;

    if (getdelim(&s, &n, delim, stdin) < 0)
    {
        if (feof(stdin))
        {
            free(s);
        }
        else
        {
            fprintf(stderr, "error: getdelim() [delim=%d]: %s\n", delim, strerror(errno));

            exit(1);
        }

        return NULL;
    }

    return s;
}



int main(int argc, char* const argv[])
{
    int o_all = 0;

    long shift = DEFAULT_SHIFT;

    while (1)
    {
        static struct option long_options[] =
        {
            { "help"    , no_argument , NULL , 'h' },
            { "version" , no_argument , NULL , 'V' },
            { NULL      , 0           , NULL ,  0  }
        };

        int c = getopt_long(argc, argv, "hVas:", long_options, NULL);
        if (c < 0)
        {
            break;
        }

        char* endptr = NULL;

        switch (c)
        {
            case '?':
                _help(stderr, argv[0]);

                exit(1);

            case 'h':
                _help(stdout, argv[0]);

                exit(0);

            case 'V':
                _vers(stdout);

                exit(0);

            case 'a':
                o_all = 1;

                break;

            case 's':
                errno = 0;
                shift = strtol(optarg, &endptr, 10);
                if (errno)
                {
                    fprintf(stderr, "error: Invalid shift value\n");
                    exit(1);
                }
                if (*endptr != '\0')
                {
                    fprintf(stderr, "error: Invalid shift value\n");
                    exit(1);
                }

                if (shift <   0)
                {
                    shift %= 26;
                    shift += 26;
                }
                if (shift >= 26)
                {
                    shift %= 26;
                }

                break;

            default:
                assert("Unhandled option case" && 0);

                exit(1);
        }
    }

    char* data = NULL;

    int delim;

    int i;
    int n;

    if (optind < argc)
    {
        while (1)
        {
            data = _combine_argv(argc, argv, optind);
            if (!data)
            {
                break;
            }

            if (o_all)
            {
                i = 26 - 1;
                n = 1;
            }
            else
            {
                i = 1;
                n = shift ;
            }

            while (i-- > 0)
            {
                printf("%s", rot(data, n));
            }

            if (data)
            {
                free(data);
            }

            break;
        }
    }
    else
    {
        if (isatty(0))
        {
            delim = '\n';
        }
        else
        {
            delim =  EOF;
        }

        while (1)
        {
            data = _read_next_input(delim);
            if (!data)
            {
                break;
            }

            if (o_all)
            {
                i = 26 - 1;
                n = 1;
            }
            else
            {
                i = 1;
                n = shift ;
            }

            while (i-- > 0)
            {
                printf("%s", rot(data, n));
            }
        }
    }

    return 0;
}
