CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -std=c99

TARGET := raylib_2d
SRC := main.c

PKG_PATH_FALLBACK := /tmp/raylib-install/lib/pkgconfig
PKG_ENV := PKG_CONFIG_PATH=$(PKG_PATH_FALLBACK):$$PKG_CONFIG_PATH

RAYLIB_CFLAGS := $(shell $(PKG_ENV) pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS := $(shell $(PKG_ENV) pkg-config --libs raylib 2>/dev/null)

ifeq ($(strip $(RAYLIB_CFLAGS)$(RAYLIB_LIBS)),)
  $(error raylib not found via pkg-config. Install globally or provide /tmp/raylib-install/lib/pkgconfig/raylib.pc)
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) -o $@ $(SRC) $(RAYLIB_LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
