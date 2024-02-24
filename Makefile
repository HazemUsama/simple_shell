CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -g -std=gnu89
SRCDIR=./
BUILDDIR=./build
TARGET=hsh
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
	rm -f $(TARGET)

force: clean all

.PHONY: all clean force

