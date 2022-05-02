---
title: Enhanced Terminator Aerial Hunter-Killer (HK)
layout: splash
header:
  overlay_image: /assets/images/t800-hk.jpg
  overlay_filter: 0.66
  actions:
    - label: "<i class='fas fa-download'></i> Instructions"
      url: "#instructions"
    - label: "<i class='fab fa-github'></i> View on GitHub"
      url: "https://github.com/jsware/t800-hk"
excerpt: >
  A modification to Pegasus Hobbies Aerial HK Machine using LEDs, servos and
  remote control. Programmed with Arduino Nano, IR Remote and DFPlayer Pro.
---
# Pegasus Hobbies Future War Aerial HK Machine
An modification for Pegasus Hobbies Future War Aerial HK Machine. The model is a 1/32 scale model kit. Modified with LEDs in the tail, landing lights, search lights and plasma gun. Added servos to control the VTOL jets and a modified base (built with lego) to control pan and tilt of the model.

{% include video id="6yDIxSZvYxw" provider="youtube" %}

## Instructions

First some parts:

* An Arduino Nano. I used one from [Ebay](https://www.ebay.co.uk/itm/Nano-V3-0-Arduino-ATmega328-5V-16MHz-CH340-UNSOLDERED-HEADERS-UK-Stock-/323825474433) but also ran some tests using an official one from somewhere like [The PI Hut](https://thepihut.com/products/arduino-nano) which is *much more expensive* (but has pins soldered).
* DFPlayer Pro MP3 Card. I used this one from [The PI Hut](https://thepihut.com/products/fermion-dfplayer-pro-a-mini-mp3-player-with-on-board-128mb-storage-breakout).
* An 8W 3-ohm speaker.
* [IR Receiver Module](https://arduinomodules.info/ky-022-infrared-receiver-module/) and controller.
* Mini [multicolor LEDs](https://www.amazon.co.uk/dp/B08DKL7Z8Y) for the tail. These need to be very small (model railway lamps and lights size) to fit into the tail wing cavity.
* Super-bright white LEDs for landing and search lights.
* Purple LED for the plasma gun.
* Some resistors to protect each eyes from full voltage. The Arduino puts 5v to each IO pin which is too much for red LEDs which require about [1.8-2.1v](https://www.digikey.co.uk/en/resources/conversion-calculators/conversion-calculator-led-series-resistor).
* Some AWG 24 wiring to connect things together. Either [multi-core](https://www.amazon.co.uk/dp/B07TT69PPV/) or [solid core](https://www.amazon.co.uk/gp/product/B08BZKVVH2/). These options provide much more than required, depending on your needs.
* Mail and female Dupont conntectors.

You will also need a soldering iron and some solder to connect things together. A [crimping tool](https://www.amazon.co.uk/dp/B07QNPZDTW) to create the connector cables.
