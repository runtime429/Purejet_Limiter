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





