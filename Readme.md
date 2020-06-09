### tree — tree listing of filesystem paths.

A program to print tree formated directory listings.  The program
uses box drawing characters drawn from utf-8 character set (but
an option allows you to use plain ASCII characters).  It allows a
lot of options to show different properties of the files (i-node
number, permissions, like the option `-l` for `ls(1)` command)

To build the program, just run

```
$ make
```
and then, as root, run
```
# make install
```
(The program installs under `/usr/local` by default), but you can
specify a different path with
```
# make prefix=/path/to/location install
```
You can use different options, just read the `Makefile` to tweak
it.

This program has been written to show the use of filesystem
related system calls.  Just compile it an enjoy a different
layout for your directory listings.

This program was suggested to me by a friend who told me about
the lack of a `TREE.EXE` command in unix.
