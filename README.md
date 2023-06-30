# Purejet_Limiter

This repository contains hardware a hardware design and software for a rev limiter for Ditech / Purejet Scooter.

![Rev Limiter](https://raw.githubusercontent.com/runtime429/Purejet_Limiter/main/img/DBZ_v2.png)

principal author: Kevin Sucker

--------------------

# Intro

I am working on a rev limiter project utilizing the ATmega328P-AU microcontroller, similar to the Arduino Uno board. The purpose of this rev limiter is to simulate a lower value of the actual throttle valve, effectively restricting the engine's speed. It is designed to be inserted between the throttle and the ECU (Engine Control Unit).

To maximize the PWM (Pulse Width Modulation) output speed of the ATmega328P, I have opted for a 20 MHz quartz crystal, surpassing the standard 16 MHz crystal used in the Arduino Uno board.

In order to adjust the RPM limit, I have incorporated a teach button, allowing for easy customization of the rev limiter's speed threshold.

I have implemented a bypass feature that can disable the RPM limit when necessary. This can be achieved by using a cheap 433MHz remote control, such as the one available on AliExpress (http://aliexpress.com/item/1005003558907008.html), or by integrating a switch into the system.



# 3D printable housing

![Front View](https://raw.githubusercontent.com/runtime429/Purejet_Limiter/main/img/Housing.png)

![Back](https://raw.githubusercontent.com/runtime429/Purejet_Limiter/main/img/Back.png)

# Etching the board and PCB assembly

Thanks to [Tobias Link on Youtube](https://youtu.be/-L1i9SnYGaU) for his excellent Tutorial!

Checkout [Build_PCB.md](https://github.com/runtime429/Purejet_Limiter/blob/main/PCB_make/Build_PCB.md)

![4](https://raw.githubusercontent.com/runtime429/Purejet_Limiter/main/PCB_make/IMG_20230628_184607.jpg)

# How to flash the Board

- Add the [MiniCore](https://github.com/MCUdude/MiniCore) to your Arduino IDE
- Tools -> Bootloader -> No Bootloader
        -> Clock -> external 20Mhz
- Choose your ISP Programmer
- Download the [RCSwitch](https://github.com/sui77/rc-switch)-library from the arduino library manager
- Connect to the ISP Pins on the Board
- Burn Bootloader to set the Fuse-Bits
- Upload Sketch Using Programmer
- Press any key of your 433MHz remote
- You can read the value of yor 433MHz signal on the TX Uart pin (Baud 115200), I copiet the Signal from a [cheep 433MHz wireless socket remote](https://github.com/runtime429/Purejet_Limiter/blob/main/img/433_remote.png)
- Change the value of the "const int valRcSig", in my case to 21777
- Repload Sketch Using Programmer

# Limiter Installation on Scooter How-To

![Connector](https://raw.githubusercontent.com/runtime429/Purejet_Limiter/main/wiring/ECU_Connector.png)

![Pin Description](https://raw.githubusercontent.com/runtime429/Purejet_Limiter/main/wiring/Pin_Description_Board.png)

![Wiring](https://raw.githubusercontent.com/runtime429/Purejet_Limiter/main/wiring/Wire_Piaggio.png)


# Set up the Rev Limiter
