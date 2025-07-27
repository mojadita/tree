# Makefile -- build script for tree program.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Sun Jun  7 10:27:52 EEST 2020
# Copyright: (C) 2020 Luis Colorado.  All rights reserved.
# License: BSD.

targets          = tree
toclean          = $(targets)
all_srcs         =

prefix          ?= /usr/local
exec_prefix     ?= $(prefix)
bindir          ?= $(prefix)/bin
rootdatadir     ?= $(prefix)
datadir         ?= $(rootdatadir)/share
mandir          ?= $(rootdatadir)/man
man1dir         ?= $(mandir)/man1

OS              != uname -o

OWN-FreeBSD      = root
GRP-FreeBSD      = wheel
OWN-GNU/Linux    = bin
GRP-GNU/Linux    = bin

own             ?= $(OWN-$(OS))
grp             ?= $(GRP-$(OS))
xmod            ?= 755
fmod            ?= 644
dmod            ?= 755

manpg            = tree.1.gz
toclean         += $(manpg)

RM              ?= rm -f
INSTALL			?= /usr/bin/install

tree_deps        =
tree_objs        = tree.o process.o stinfo.o prmod.o help.o \
                    timeinfo.o pwinfo.o link.o
tree_libs        =
tree_ldfl        =
toclean         += $(tree_objs)
all_srcs        += $(tree_objs:.o=.c)

.SUFFIXES: .1 .1.gz

all: $(targets)
clean:
	$(RM) $(toclean)
depend:
	mkdep $(all_srcs)

install: $(bindir)/tree $(man1dir)/$(manpg)

$(bindir)/tree: tree $(bindir)
	-$(INSTALL) -o $(own) -g $(grp) -m $(xmod) tree $@
$(man1dir)/$(manpg): $(manpg) $(man1dir)
	-$(INSTALL) -o $(own) -g $(grp) -m $(fmod) $(manpg) $(man1dir)/$(manpg)

$(bindir) $(man1dir):
	-$(INSTALL) -o $(own) -g $(grp) -m $(dmod) -d $@

deinstall:
	-$(RM) $(bindir)/tree
	-$(RM) $(man1dir)/$(manpg)

tree: $(tree_deps) $(tree_objs)
	$(CC) -o $@ $(LDFLAGS) $($@_ldfl) $($@_objs) $($@_libs)

.1.1.gz:
	gzip <$< >$@
