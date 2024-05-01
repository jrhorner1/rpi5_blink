# rpi5_lgpio_blink
Basic LED blink program in C for the Raspberry Pi 5 using libgpiod 2.1.1. Raspberry Pi OS ships with version 1.6.3 which is not compatible with this code.  

## Hardware setup

 * Raspberry Pi 5
 * 1 LED
 * 1 1k Resistor
 * Breadboard & Wires

The LED cathode ( - , short leg) is connected to ground and the anode ( + , long leg) is connected to GPIO 21 through the resistor. Ref. [pinout](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)

## Build

```bash
gcc -o blink blink.c -lgpiod
```

```
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
gpiodetect -v
```

Optionally build the documentation

```bash
sudo apt install doxygen graphviz
make doc
```