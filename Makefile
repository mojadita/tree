# Makefile -- build script for tree program.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Sun Jun  7 10:27:52 EEST 2020
# Copyright: (C) 2020 Luis Colorado.  All rights reserved.
# License: BSD.

targets          = tree
toclean          = $(targets)
all_srcs         =

prefix          ?= ${HOME}
bindir          ?= $(prefix)/bin
mandir          ?= $(prefix)/man
man1dir         ?= $(mandir)/man1
own             ?= `id -u`
grp             ?= `id -g`
xmod            ?= 755
fmod            ?= 644
dmod            ?= 755
manpg            = tree.1.gz
toclean         += $(manpg)

RM              ?= rm -f

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
install: $(targets) $(manpg) $(bindir) $(man1dir)
	-$(INSTALL) -o $(own) -g $(grp) -m $(xmod) tree $(bindir)/tree
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
