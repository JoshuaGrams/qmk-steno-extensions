EcoSteno
===

![EcoSteno](https://nolltronics.com/wp-content/uploads/2021/04/Noll-Steno-Front-Angle.jpg)

* Keyboard Maintainer: [Nathan Olivares](https://github.com/nkotech)
* Hardware Supported: EcoSteno v1.0.1X
* Hardware Availability: [Nolltronics](https://nolltronics.com/product/ecosteno)

Make example for this keyboard (after setting up your build environment):

    make noll/ecosteno:default

Flashing example for this keyboard:

    dfu-util.exe -d 1eaf:0003 -a 2 -D "noll_ecosteno_default.bin"

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs). You might still need more info (WIP)
