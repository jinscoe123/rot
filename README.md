# Rot

A small program to perform a rotation cipher on some given text.

### Installation

```
$ make
$ make install
```

### Usage

Display the help menu.

```
$ rot --help
Usage: rot [OPTIONS] [STRING] [...]

Options:
  -h, --help     Show this help menu and exit.
  -V, --version  Show the version and exit.
  -a             Print all possible rotations one after the other.
  -s SHIFT       Specify the shift value [default: 3].
$
```

Get the ROT13 of a string from the command line.

```
$ rot -s 13 Hello, world!
Uryyb, jbeyq!
$
```

Negative shifts work too!

```
$ rot -s -13 Hello, world!
Uryyb, jbeyq!
$
```

Get all the possible rotations of a given string.

```
$ rot -a The quick brown fox jumped over the lazy dog.
Uif rvjdl cspxo gpy kvnqfe pwfs uif mbaz eph.
Vjg swkem dtqyp hqz lworgf qxgt vjg ncba fqi.
Wkh txlfn eurzq ira mxpshg ryhu wkh odcb grj.
Xli uymgo fvsar jsb nyqtih sziv xli pedc hsk.
Ymj vznhp gwtbs ktc ozruji tajw ymj qfed itl.
Znk waoiq hxuct lud pasvkj ubkx znk rgfe jum.
Aol xbpjr iyvdu mve qbtwlk vcly aol shgf kvn.
Bpm ycqks jzwev nwf rcuxml wdmz bpm tihg lwo.
Cqn zdrlt kaxfw oxg sdvynm xena cqn ujih mxp.
Dro aesmu lbygx pyh tewzon yfob dro vkji nyq.
Esp bftnv mczhy qzi ufxapo zgpc esp wlkj ozr.
Ftq cguow ndaiz raj vgybqp ahqd ftq xmlk pas.
Gur dhvpx oebja sbk whzcrq bire gur ynml qbt.
Hvs eiwqy pfckb tcl xiadsr cjsf hvs zonm rcu.
Iwt fjxrz qgdlc udm yjbets dktg iwt apon sdv.
Jxu gkysa rhemd ven zkcfut eluh jxu bqpo tew.
Kyv hlztb sifne wfo aldgvu fmvi kyv crqp ufx.
Lzw imauc tjgof xgp bmehwv gnwj lzw dsrq vgy.
Max jnbvd ukhpg yhq cnfixw hoxk max etsr whz.
Nby kocwe vliqh zir dogjyx ipyl nby futs xia.
Ocz lpdxf wmjri ajs ephkzy jqzm ocz gvut yjb.
Pda mqeyg xnksj bkt fqilaz kran pda hwvu zkc.
Qeb nrfzh yoltk clu grjmba lsbo qeb ixwv ald.
Rfc osgai zpmul dmv hskncb mtcp rfc jyxw bme.
Sgd pthbj aqnvm enw itlodc nudq sgd kzyx cnf.
$
```

If you prefer, you can pass input in via `stdin`.

```
$ echo Hello, world! | rot -s 13
Uryyb, jbeyq!
$
```

Or there's even an interactive mode.

```
$ rot -s 13
In interactive mode, strings are ROT-ed line-by-line.
Va vagrenpgvir zbqr, fgevatf ner EBG-rq yvar-ol-yvar.
To exit, just hit ^D.
Gb rkvg, whfg uvg ^Q.
$
```
