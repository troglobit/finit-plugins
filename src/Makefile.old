# Contributed plugins for Finit          -*-Makefile-*-
#
# This file has no copyright, it is released in the public domain.  Each
# plugin, however, is copyright the respective author, and they are all
# licensed under the same MIT licese as Finit, due to runtime linking.
#

prefix   ?= /usr/local

PLUGINS   = chronyd.so
SRCS      = $(PLUGINS:.so=.c)
OBJS      = $(PLUGINS:.so=.o)
DEPS      = $(PLUGINS:.so=.d)
CPPFLAGS += -I$(prefix)/include/finit
CFLAGS   += -W -Wall -Wextra -Wno-unused-parameter -fPIC
LDFLAGS  += -shared

all: Makefile $(PLUGINS)

$(PLUGINS): Makefile

%.o: %.c
	+@$(CC) $(CFLAGS) $(CPPFLAGS) -MD -MP -c -o $@ $<

%.so: %.o
	+@$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

install:
	@install -d $(prefix)/lib/finit/plugins
	@for plugin in $(PLUGINS); do
		install -c -m 0644 $plugin $(prefix)/lib/finit/plugins/
	done

clean:
	@$(RM) $(OBJS) $(PLUGINS)

distclean: clean
	@$(RM) DEADJOE core *.map *~ *.d *.o *.so

.PHONY: all install clean distclean

-include $(DEPS)
