Custom firmware for the Game and Watch: Super Mario Bros. console.


[![Click to play demo](https://thumbs.gfycat.com/UntriedMajesticAfricancivet-mobile.jpg)](https://gfycat.com/untriedmajesticafricancivet)


# What is this?
This repo contains custom code as well as a patching utility to add additional
functionality to the stock Game and Watch firmware. This is the only custom firmware that allows you to run both the stock firmware as well as retro-go without soldering a higher capacity flash chip!


# Features
* Works correctly with [retro-go](https://github.com/kbeckmann/game-and-watch-retro-go) in internal flash bank 2.
* Press button combination (`LEFT` + `GAME`) to launch retro-go from internal flash bank 2.
* Configurable sleep timeout.
* Configurable hard-reset timeout.
* Ability to store the enitre firmware in internal flash! No external flash required!
* Reduced external flash firmware size `--slim`; reduced from 1,048,576 bytes to just **180,224** bytes
    * Removed the "Mario Song" easter egg.
    * Removed the 5 sleeping illustrations.
    * LZMA compressed SMB2 ROM and Clock graphic tiles.
    * Move Clock graphic tiles to internal flash. 
* An even further stripped version `--clock-only` that further reduces extflash size to just **139,264** bytes. Uses all the techniques described in `slim` plus:
    * Removed SMB2 ROM.
    * Set retro-go macro to just `GAME`.
* Migrate the external firmware to internal firmware by utilizing an undocumented extra 128KB of internal flash with the option `--extended`.

# Usage
Place your `internal_flash_backup.bin` and `flash_backup.bin` in the root of this
repo. To extract these from your gnw system, see the [game and watch backup repo](https://github.com/ghidraninja/game-and-watch-backup)

Install python dependencies (>=python3.6 required) via:

```
pip3 install -r requirements.txt
```

Download STM32 Driver files:

```
make download_sdk
```

To just build and flash, you can just run `make flash`, however it's a bit finicky. You'll probably have better success running:

```
make flash_patched_ext
make flash_patched_int
```

The default programmer interface is `stlink`, you can chose a different interface via the `ADAPTER` variable. For example, `ADAPTER=rpi`.

I recommend pressing the power button at the same time you press enter. Note that the same configuration parameters have to be passed to each `make` command.

For additional configuration options, run `make help`.


### Retro Go
Since most people are going to be using this with retro-go, use the minimum amount of external storage, and don't care about the sleeping images or the mario song easter egg, here are the recommend commands:

```
# in this repo
make clean
make PATCH_PARAMS="--slim --extended --no-save" flash_patched_int

# in the retro-go repo; this assumes you have the stock 1MB flashchip
# NOTE: MUST have the patched openocd installed:
#         https://github.com/kbeckmann/ubuntu-openocd-git-builder
make clean
make -j8 EXTFLASH_SIZE=868352 EXTFLASH_OFFSET=180224 INTFLASH_BANK=2 flash
```

# Advanced usage
Other potentially useful make targets:

```
make clean
make patch  # Generates the patched bin at build/internal_flash_patched.bin, but doesn't flash
make flash_stock_int
make flash_stock_ext
make flash_patch_int
make flash_patch_ext
```

# TODO
* Figure out safe place in RAM to store global/static variables. The current
  configuration described in the linker file is unsafe, but currently we have
  no global/static variables.
* Custom sprites for clock.

# Development
Main stages to developing a feature:
1. Find a place to take control in the stock rom (usually function calls).
2. Add the stock function and its address to `Core/Inc/stock_firmware.h`.
3. Implement your own function, possibly in `Core/Src/main.c`. There's a good chance your custom function will call the function in (2). You will also probably have to add `-Wl,--undefined=my_custom_function` to `LDFLAGS` in the Makefile so that it doesn't get optimized out as unreachable code.
4. Add a patch definition to `patches/patches.py`.

# Journal
This is my first time ever developing patches for a closed source binary. [I documented my journey in hopes that it helps other people](docs/journal.md). If you have any recommendations, tips, tricks, or anything like that, please leave a github issue and I'll update the documentation!



# Acknowledgement

Thanks to the community that made this possible! This repo was built with the help of others. Repos referenced during the development of this project:

* [game-and-watch-retro-go](https://github.com/kbeckmann/game-and-watch-retro-go) by [kbeckmann](https://github.com/kbeckmann)
* [game-and-watch-backup](https://github.com/ghidraninja/game-and-watch-backup) by [ghidraninja](https://github.com/ghidraninja)
* [game-and-watch-base](https://github.com/ghidraninja/game-and-watch-base) by [ghidraninja](https://github.com/ghidraninja)
* [game-and-watch-decrypt](https://github.com/GMMan/game-and-watch-decrypt) by [GMMan](https://github.com/GMMan)
* [game-and-watch-drawing-song-re](https://github.com/jaames/game-and-watch-drawing-song-re/) by [jaames](https://github.com/jaames)

I would also like to thank the [stacksmashing discord](https://discord.gg/zBN3ex8v4p) for all the help (special shoutout to @cyanic)!
