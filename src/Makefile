LIB:=libupnplog.so
CFLAGS:=-Wall -fPIC -shared
LDFLAGS:=-lsqlite3
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
	
clean:
	$(RM) $(LIB)
