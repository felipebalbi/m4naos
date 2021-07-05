![Build](https://github.com/felipebalbi/m4naos/workflows/CMake/badge.svg)

# Introduction

m4naOS is a fully Free (as in **speech**) implementation of a toy
microkernel to run on a STM32F405RG device.

# Motivation

The original motivation of the project was to develop a open source
firmware for USB and/or PS/2 keyboards, but as it turns out, the
project took a life of its own and I changed scope towards a small
RTOS for Cortex-M4F STM32F405RG.

Even though I'm developing and testing only on an Olimex H405 board
sporting a STM32F405RG, it shouldn't be too hard to port it to other
Cortex-M devices, don't quote me on that, though.

# Coding Style

We're using the Linux Kernel's style, mainly because I like it and my
GNU Emacs is already configured properly.

Note that we're not aligning argument list to the opening parenthesis,
we're just adding two tabs after the line break.

## Note for contributors

The project will only accept GPL v3+ contributions. Please don't send
any code unless you agree with the terms of GPL v3+.

# License

The code is licensed as GPL v3+
