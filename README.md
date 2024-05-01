# rpi5_blink
Basic LED blink program in C and Python for the Raspberry Pi 5.

## Hardware setup

 * Raspberry Pi 5
 * 1 LED
 * 1 1k Resistor
 * Breadboard & Wires

The LED cathode ( - , short leg) is connected to ground and the anode ( + , long leg) is connected to GPIO 21 through the resistor. Ref. [pinout](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)

## Python

This doesn't seem to care which version of libgpiod is installed. 

```bash
python3 blink.py
```

## C

Raspberry Pi OS ships with libgpiod 1.6.3 and this program was written for libgpiod 2.1.1 which is not available from the repositories yet. Please see the instructions below for building libgpiod from source.

```bash
gcc -o blink blink.c -lgpiod
```

```bash
jrhorner@raspberrypi5:~/blink $ gcc -o blink blink.c -lgpiod
jrhorner@raspberrypi5:~/blink $ ./blink 
Libgpiod version 2.1.1
jrhorner@raspberrypi5:~/blink $ uname -a
Linux raspberrypi5 6.6.28+rpt-rpi-2712 #1 SMP PREEMPT Debian 1:6.6.28-1+rpt1 (2024-04-22) aarch64 GNU/Linux
```

## libgpiod-2.1.1 

Build instructions for [libgpiod 2.1.1](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git) on [Raspberry Pi OS x64 Lite](https://downloads.raspberrypi.com/raspios_lite_arm64/images/raspios_lite_arm64-2024-03-15/).

```bash
sudo apt install autoconf autoconf-archive help2man libtool
curl -O https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/snapshot/libgpiod-2.1.1.tar.gz
tar xzf libgpiod-2.1.1.tar.gz
cd libgpiod-2.1.1
mkdir m4
./autogen.sh --enable-tools=yes --prefix=/usr
make
sudo make install
```

Verify the version

```bash
jrhorner@raspberrypi5:~ $ gpiodetect -v
gpiodetect (libgpiod) v2.1.1
Copyright (C) 2017-2023 Bartosz Golaszewski
License: GPL-2.0-or-later
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

jrhorner@raspberrypi5:~ $ gpiodetect
gpiochip0 [gpio-brcmstb@107d508500] (32 lines)
gpiochip1 [gpio-brcmstb@107d508520] (4 lines)
gpiochip2 [gpio-brcmstb@107d517c00] (17 lines)
gpiochip3 [gpio-brcmstb@107d517c20] (6 lines)
gpiochip4 [pinctrl-rp1] (54 lines)
```

Optionally build the documentation and examples

```bash
sudo apt install doxygen graphviz
make doc
```