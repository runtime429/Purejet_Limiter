# Purejet_Limiter

This repository contains hardware a hardware design and software for a rev limiter for Ditech / Purejet Scooter.

![Rev Limiter](https://raw.github.com/...)

principal author: Kevin Sucker

--------------------

# Documentation

The rev limiter based on the ATmega328P like the Arduino Uno Board. For use the fastest PWM Output wich is possible with the ATmega328P i choosed a 20 MHz quatz (Arduino uses 16 MHz).

The rev limiter works by simulating a lower value of the real throttle valve.

How much the rev limiter should limit the speed can be set using a teach button.

The RPM limit can be bypassed using a 433MHz remote control or a Switch.



