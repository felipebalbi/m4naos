## Introduction

MiKey is a fully Free (as in **speech**) implementation of a USB HID Keyboard
Class controller on top of an STM32L05x device.

## Motivation

I've always wanted a desktop computer running 100% Free Software. Now that
[Coreboot][1]/[Libreboot][2] have good support for some recent HW running
without any firmware blobs, I feel like the Keyboard is the next natural step.

## Contributors

The traditional github process:

1. Fork
1. Hack
1. Test
1. Send pull request

## Coding Style

We're using the Linux Kernel's style, mainly because I like it and my GNU Emacs
is already configured properly.

Note that we're not aligning argument list to the opening parenthesis, we're
just adding two tabs after the line break.

### Note for contributors

The project will only accept GPL v3+ contributions. Please don't send any code
unless you agree with the terms of GPL v3+.

## License

The code is licensed as GPL v3+

[1]: http://www.coreboot.org/
[2]: https://libreboot.org/
