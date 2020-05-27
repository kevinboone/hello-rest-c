NAME    := hello-rest-c
VERSION := 0.1a
CC      :=  gcc
LIBS    := -lmicrohttpd -lpthread ${EXTRA_LIBS} 
TARGET	:= $(NAME)
SOURCES := $(shell find src/ -type f -name *.c)
OBJECTS := $(patsubst src/%,build/%,$(SOURCES:.c=.o))
DEPS	:= $(OBJECTS:.o=.deps)
DESTDIR := /
PREFIX  := /usr
BINDIR  := $(DESTDIR)/$(PREFIX)/bin
SHARE   := $(DESTDIR)/$(PREFIX)/share/$(TARGET)
CFLAGS  := -O3 -fpie -fpic -Wall -Werror -DNAME=\"$(NAME)\" -DVERSION=\"$(VERSION)\" -DSHARE=\"$(SHARE)\" -DPREFIX=\"$(PREFIX)\" -I include ${EXTRA_CFLAGS} -ffunction-sections -fdata-sections
LDFLAGS := -s -pie -Wl,--gc-sections   ${EXTRA_LDFLAGS}

$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) 

build/%.o: src/%.c
	@mkdir -p build/
	$(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo "  Cleaning..."; $(RM) -r build/ $(TARGET) 

install: $(TARGET)
	mkdir -p $(DESTDIR)/$(PREFIX) $(DESTDIR)/$(BINDIR) $(DESTDIR)/$(MANDIR)
	strip $(TARGET)
	install -m 755 $(TARGET) $(DESTDIR)/${BINDIR}

-include $(DEPS)

.PHONY: clean

