# Purejet_Limiter

This repository contains hardware a hardware design and software for a rev limiter for Ditech / Purejet Scooter.

![Rev Limiter](https://raw.githubusercontent.com/runtime429/Purejet_Limiter/main/img/DBZ_v2.png)

principal author: Kevin Sucker

--------------------

# Documentation

The rev limiter based on the ATmega328P like the Arduino Uno Board. For use the fastest PWM Output wich is possible with the ATmega328P i choosed a 20 MHz quartz (Arduino uses 16 MHz).

The rev limiter works by simulating a lower value of the real throttle valve. The rev limiter is built between the throttle and the ECU

How much the rev limiter should limit the speed can be set using a teach button.

The RPM limit can be bypassed using for example a cheap 433MHz remote control (http://aliexpress.com/item/1005003558907008.html) or a Switch.





