# Makefile -- build script for tree program.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Sun Jun  7 10:27:52 EEST 2020
# Copyright: (C) 2020 Luis Colorado.  All rights reserved.
# License: BSD.

targets          = tree
toclean          = $(targets)
all_srcs         =

prefix          ?= $(HOME)
bindir          ?= $(prefix)/bin
own             ?= `id -u`
grp             ?= `id -g`
xmod            ?= 755
fmod            ?= 644

RM              ?= rm -f

tree_deps        =
tree_objs        = tree.o process.o stinfo.o prmod.o help.o \
                    timeinfo.o
tree_libs        =
tree_ldfl        =
toclean         += $(tree_objs)
all_srcs        += $(tree_objs:.o=.c)

all: $(targets)
clean:
	$(RM) $(toclean)
depend:
	mkdep $(all_srcs)
install: $(targets)
	$(INSTALL) -o $(own) -g $(grp) -m $(xmod) tree $(bindir)/tree
deinstall:
	$(RM) $(bindir)/tree

tree: $(tree_deps) $(tree_objs)
	$(CC) -o $@ $(LDFLAGS) $($@_ldfl) $($@_objs) $($@_libs)
