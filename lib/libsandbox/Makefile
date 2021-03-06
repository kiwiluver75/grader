################################################################################
# The Sandbox Libraries Makefile                                               #
#                                                                              #
# Copyright (C) 2004-2009, 2011 LIU Yu, pineapple.liu@gmail.com                #
# All rights reserved.                                                         #
#                                                                              #
# Redistribution and use in source and binary forms, with or without           #
# modification, are permitted provided that the following conditions are met:  #
#                                                                              #
# 1. Redistributions of source code must retain the above copyright notice,    #
#    this list of conditions and the following disclaimer.                     #
#                                                                              #
# 2. Redistributions in binary form must reproduce the above copyright notice, #
#    this list of conditions and the following disclaimer in the documentation #
#    and/or other materials provided with the distribution.                    #
#                                                                              #
# 3. Neither the name of the author(s) nor the names of its contributors may   #
#    be used to endorse or promote products derived from this software without #
#    specific prior written permission.                                        #
#                                                                              #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  #
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    #
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   #
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE     #
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          #
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         #
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     #
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      #
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      #
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   #
# POSSIBILITY OF SUCH DAMAGE.                                                  #
################################################################################

PREFIX ?= /usr/local
LIBRARY = sandbox
VERSION = 0.3.3
RELEASE = rc3

AR = /usr/bin/ar rcs
AWK = gawk
LN = ln -s -f
TAR = /bin/tar
MKDIR = /bin/mkdir -p
INSTALL = /usr/bin/install -c -D
INSTALL_DATA = ${INSTALL} -m 644 -D

# build options
CC = gcc
CFLAGS = -Wall -g0 -O3 -ansi -std=gnu99 -fPIC -pthread -Isrc -D SANDBOX  -D NDEBUG -U DEBUG
LDFLAGS =  -shared
LIBS = -lrt 

# buid sources and targets
$(LIBRARY)_hdr = src/platform.h src/sandbox.h src/symbols.h src/config.h
$(LIBRARY)_src = src/platform.c src/sandbox.c src/symbols.c
$(LIBRARY)_obj = $($(LIBRARY)_src:.c=.o)
$(LIBRARY)_sdist = $($(LIBRARY)_hdr:config.h=config.h.in) \
                   $($(LIBRARY)_src:symbols.c=symbols.awk) \
                   $(LIBRARY).spec Makefile.in Doxyfile configure install-sh \
                   README COPYING CHANGES
$(LIBRARY)_bdist = lib$(LIBRARY).so lib$(LIBRARY).so.$(VERSION) lib$(LIBRARY).a

# build branches
.PHONY: all clean sdist install

all: $($(LIBRARY)_bdist) src/$(LIBRARY).h

$($(LIBRARY)_obj): $($(LIBRARY)_hdr) $($(LIBRARY)_src) Makefile

lib$(LIBRARY).so : lib$(LIBRARY).so.$(VERSION)
	$(LN) lib$(LIBRARY).so.$(VERSION) lib$(LIBRARY).so

lib$(LIBRARY).so.$(VERSION) : $($(LIBRARY)_obj)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(@) $($(LIBRARY)_obj)

lib$(LIBRARY).a: $($(LIBRARY)_obj)
	$(AR) $(@) $($(LIBRARY)_obj)

$(PREFIX) dist:
	$(MKDIR) $(@)

clean:
	rm -f src/symbols.c src/config.h config.log config.status Makefile
	rm -f $($(LIBRARY)_obj) $($(LIBRARY)_bdist)

sdist: dist $($(LIBRARY)_sdist)
	$(TAR) --dereference -czf dist/lib$(LIBRARY)-$(VERSION).tar.gz $($(LIBRARY)_sdist)
	rm -rf dist/lib$(LIBRARY)-$(VERSION)
	$(MKDIR) dist/lib$(LIBRARY)-$(VERSION)
	$(TAR) -C dist/lib$(LIBRARY)-$(VERSION) -xzf dist/lib$(LIBRARY)-$(VERSION).tar.gz
	$(TAR) -C dist -czvf dist/lib$(LIBRARY)-$(VERSION).tar.gz lib$(LIBRARY)-$(VERSION)
	rm -rf dist/lib$(LIBRARY)-$(VERSION)

install: $(PREFIX) $($(LIBRARY)_bdist) src/$(LIBRARY).h
	$(INSTALL_DATA) src/$(LIBRARY).h $(PREFIX)/include/$(LIBRARY).h
	$(INSTALL_DATA) lib$(LIBRARY).a $(PREFIX)/lib/lib$(LIBRARY).a
	$(INSTALL) lib$(LIBRARY).so.$(VERSION) $(PREFIX)/lib/lib$(LIBRARY).so.$(VERSION)
	$(LN) lib$(LIBRARY).so.$(VERSION) $(PREFIX)/lib/lib$(LIBRARY).so

Makefile: Makefile.in
	./config.status

src/config.h: src/config.h.in
	./config.status

config.status: configure
	./config.status --recheck

%.c: %.awk
	$(AWK) -f $(<) $($(LIBRARY)_hdr) $($(LIBRARY)_src) > $(@)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(@) $(<)

