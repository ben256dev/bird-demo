# raylib 2D example

This project uses `pkg-config` to resolve raylib (no vendored dependency).
It also auto-checks `/tmp/raylib-install/lib/pkgconfig` in this environment.

## Build
```bash
make
```

## Run
```bash
make run
```

## Requirement check
```bash
PKG_CONFIG_PATH=/tmp/raylib-install/lib/pkgconfig:$PKG_CONFIG_PATH pkg-config --modversion raylib
```

If that command fails, raylib is not installed globally for your user environment.
