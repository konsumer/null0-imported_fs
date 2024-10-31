The idea here is that the host wasm imports `PNTR_LOAD_FILE`/`PNTR_SAVE_FILE` from it's host, so it can share fs with cart.

I am using [xmake](https://xmake.io/).

```
# set platform to wasm
xmake config -p wasm

# set platform to native (if you build for wasm)
xmake config -p macosx/windows/linux

# build for current platform
xmake

# run a webserver to checkout wasm build
npx -y live-server
```