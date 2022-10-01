---
title: Enhanced Terminator Aerial Hunter-Killer (HK)
layout: splash
header:
  overlay_image: /assets/images/t800-hk.jpg
  overlay_filter: 0.66
  actions:
    - label: "<i class='fas fa-download'></i> Instructions"
      url: "#parts"
    - label: "<i class='fab fa-github'></i> View on GitHub"
      url: "https://github.com/jsware/t800-hk"
excerpt: >
  A modification to Pegasus Hobbies Aerial HK Machine using LEDs, servos and
  remote control. Programmed with Arduino Nano, IR Remote and DFPlayer Pro.
gallery:
  - url: /assets/images/hk-cover2.jpg
    image_path: /assets/images/hk-cover2.jpg
    alt: "Support Strut Removal"
    title: "Cut away the support structure to make room for the thruster servos."
  - url: /assets/images/hk-cover1.jpg
    image_path: /assets/images/hk-cover1.jpg
    alt: "Support Strut Removal"
    title: "Cut away the support structure to make room for the thruster servos."
  - url: /assets/images/hk-thrust.jpg
    image_path: /assets/images/hk-thrust.jpg
    alt: "Thruster Servos"
    title: "Fit the thruster servos back-to-back."
  - url: /assets/images/hk-lights.jpg
    image_path: /assets/images/hk-lights.jpg
    alt: "Search and Landing Lights"
    title: "Wire in search and landing lights."
  - url: /assets/images/hk-underside.jpg
    image_path: /assets/images/hk-underside.jpg
    alt: "HK Underside"
    title: "Cut a small hole in the bottom to feed through the wires."
  - url: /assets/images/cabling.jpg
    image_path: /assets/images/cabling.jpg
    alt: "Ground Cables"
    title: "Lay tail lights and feed the wires through the bottom of the HK"
gallery2:
  - url: /assets/images/chrome.jpg
    image_path: /assets/images/chrome.jpg
    alt: "Chrome Paint"
    title: "Spray-paint the body of the model."
  - url: /assets/images/tail-lights.jpg
    image_path: /assets/images/tail-lights.jpg
    alt: "Tail Lights"
    title: "Feed miniature tail light LEDs into the tail-wings."
  - url: /assets/images/search-fire.jpg
    image_path: /assets/images/search-fire.jpg
    alt: "Search & Fire"
    title: "The search lights, landing lights and tail lights all wired in."
  - url: /assets/images/plasma-gun.jpg
    image_path: /assets/images/plasma-gun.jpg
    alt: "Plasma Gun"
    title: "Run the plasma gun wires up the plasma gun sides."
  - url: /assets/images/mounted-arduino.jpg
    image_path: /assets/images/mounted-arduino.jpg
    alt: "Arduino Nano"
    title: "Wire up the servos and lights to check your solering."
  - url: /assets/images/wired-up.jpg
    image_path: /assets/images/wired-up.jpg
    alt: "All Wired Up"
    title: "Connect up the DFPlayer, Speaker and IR remote control sensor."
gallery3:
  - url: /assets/images/base-front.jpg
    image_path: /assets/images/base-front.jpg
    alt: "Build a Base Mount (Front)"
    title: "Build a Lego base mount for the Tilt & turn servos and control unit (front view)."
  - url: /assets/images/base-back.jpg
    image_path: /assets/images/base-back.jpg
    alt: "Build a Base Mount (Rear)"
    title: "Build a Lego base mount for the Tilt & turn servos and control unit (rear view)."
  - url: /assets/images/base-right.jpg
    image_path: /assets/images/base-right.jpg
    alt: "Build a Base (Right)"
    title: "Build a Lego base mount for the Tilt & turn servos and control unit (right view)."
  - url: /assets/images/base-left.jpg
    image_path: /assets/images/base-left.jpg
    alt: "Build a Base Mount (Left)"
    title: "Build a Lego base mount for the Tilt & turn servos and control unit (left view)."
  - url: /assets/images/base-closeup.jpg
    image_path: /assets/images/base-closeup.jpg
    alt: "Tilt Servo Bracket"
    title: "Use three right-angle brackets holding the tilt servo."
  - url: /assets/images/base-cabling.jpg
    image_path: /assets/images/base-cabling.jpg
    alt: "Tidy Cabling"
    title: "Keep the cables tidy avoids them catching when the model turns."
gallery4:
  - url: /assets/images/base-top.jpg
    image_path: /assets/images/base-top.jpg
    alt: "Base Unit Top"
    title: "Build the top of the base unit."
  - url: /assets/images/base-mold.jpg
    image_path: /assets/images/base-mold.jpg
    alt: "Original Base Duplication"
    title: "Duplicate the original base using mold-making silicon and resin."
  - url: /assets/images/base-lights.jpg
    image_path: /assets/images/base-lights.jpg
    alt: "Base Lights Routing"
    title: "Routing the base lights so the base unit fits round model stand."
  - url: /assets/images/base-open1.jpg
    image_path: /assets/images/base-open1.jpg
    alt: "Base Opening"
    title: "Allow the top of the base unit to open with cabling near the hinge."
  - url: /assets/images/base-open2.jpg
    image_path: /assets/images/base-open2.jpg
    alt: "Base Opening"
    title: "Open the top of the base unit makes for easier fitting round the stand struts."
  - url: /assets/images/all-put-together.jpg
    image_path: /assets/images/all-put-together.jpg
    alt: "Everything Assembled"
    title: "With everything assembled, the base mount is hidden inside the base unit."
---
# Pegasus Hobbies Future War Aerial HK Machine
A modification for the Pegasus Hobbies Future War Aerial HK Machine. The model is a 1/32 scale model kit available from a [number of locations](https://www.google.com/search?q=pegasus+aerial+hk+machine). Modified with LEDs in the tail, landing lights, search lights and plasma gun. Added servos to control the VTOL jets and a modified base (built with Lego) to control turn and tilt of the model.

{% include video id="eI-JwoG87fo" provider="youtube" %}

## Parts

First some parts. None of the makes suggested here are endorsements. You should do your own research and buy what you feel is best.

* An Arduino Nano. I used one from [Ebay](https://www.ebay.co.uk/itm/Nano-V3-0-Arduino-ATmega328-5V-16MHz-CH340-UNSOLDERED-HEADERS-UK-Stock-/323825474433) but also ran some tests using an official one from somewhere like [The PI Hut](https://thepihut.com/products/arduino-nano) which is *much more expensive* (but has pins soldered).
* Three KY66 micro-servos (two for the thrusters and one to control the tilt). I bought a pack of 10 from [Longrunner](https://www.amazon.co.uk/dp/B072J59PKZ/) on Amazon.
* One MG90S to control the turn. One with metal gears as it takes the weight of the model. There are lots of poor quality MG90S fakes around, so don't go for a cheap one. I used these from [Amazon](https://www.amazon.co.uk/yusvwkj-Coreless-Airplane-Helicopter-Arduino/dp/B09TSTD9G5).
* DFPlayer Pro MP3 Card. I used this one from [The PI Hut](https://thepihut.com/products/fermion-dfplayer-pro-a-mini-mp3-player-with-on-board-128mb-storage-breakout). On the schematic below, it says DF Player Mini, because I could not find the DFPlayer Pro schematic.
* An LM2596 DC-to-DC Buck Convertor [such as this](https://www.ebay.co.uk/itm/193591375232) example to step down a power adapter voltage to 5V DC and to provide enough current to drive the Arduino, servos, bright LEDs and periferal devices.
* Associated 5A DC Power Connector [like this example](https://www.amazon.co.uk/gp/product/B089DXQDS9/).
* An 8W 3-ohm speaker. For example [this one from ebay](https://www.ebay.co.uk/itm/224097819811).
* [IR Receiver Module](https://arduinomodules.info/ky-022-infrared-receiver-module/) and controller.
* Mini [multicolor LEDs](https://www.amazon.co.uk/dp/B08DKL7Z8Y) for the tail. These need to be very small (model railway lamps and lights size) to fit into the tail wing cavity.
* Super-bright white LEDs for landing and search lights [like this example](https://www.ebay.co.uk/itm/265095846318).
* Purple LED [like these from EBay](https://www.ebay.co.uk/sch/i.html?_nkw=3mm+flat+top+purple+leds) for the plasma gun.
* Some resistors to protect each LED from full voltage. The Arduino puts 5v to each IO pin which is too much for LEDs which require about [1.8-2.1v](https://www.digikey.co.uk/en/resources/conversion-calculators/conversion-calculator-led-series-resistor). I used 100 and 150 ohm (see the schematic).
* Some AWG 24 wiring to connect things together. Either [multi-core](https://www.amazon.co.uk/dp/B07TT69PPV/) or [solid core](https://www.amazon.co.uk/gp/product/B08BZKVVH2/). These options provide much more than required, depending on your needs. I used solid core (stays as bent) within the HK and flexible core in the drop down to the base.
* Heat shrink tubing [such as this](https://www.amazon.co.uk/gp/product/B08N5246YB) I used from Amazon.
* A PCB Prototype board [such as this example](https://www.amazon.co.uk/gp/product/B091F7Z3MV)
* Mail and female Dupont connectors.

You will also need a soldering iron and some solder to connect things together. A [crimping tool](https://www.amazon.co.uk/dp/B07QNPZDTW) to create the connector cables. Hot glue and glue sticks. I used [this one](https://www.hobbycraft.co.uk/black-mini-hot-melt-glue-gun/6389691000.html) from Hobby Craft.

## Circuit Schematic

{% include figure image_path="/assets/images/circuit.jpg" alt="Circuit" caption="The circuit schematic" %}

## Assembly

This is how I fitted the internals to the main body. See the pictures below for visuals.

1. Before fitting the servos, some cutting of struts in the main body is required to make room.
1. Slowly cut the struts down and check if the servo sits in line with the thrusters.
1. Once aligned, glue the two KY66 servos back-to-back to control the thrusters, glued in place in the model body.
1. Then fit the search and landing lights.
1. Cut a hole in the bottom of the model to feed wires through to the base.
1. I layed wires to the tail lights (using just LEDs to prove wiring prior to using the miniature LEDs into the tail wings later)

{% include gallery caption="Fitting out interior of HK" %}

At this point I painted the model chrome, but you may prefer to paint at the end as there's some handling of the model.

Lay the tail lights into the tail wings so they shine through the clear tail light ends. I recommend connecting up and testing everything works before glueing everything together (I speak from experience).

{% include gallery id="gallery2" caption="Connecting up DFPlayer, speaker and IR sensor " %}

For the plasma gun, fix the purple LED with it's anode & cathode down the length of the gun and use heat shrink tubing to secure in place. It doesn't show once spray-painted silver.

From the last two pictures, you can see how the cabling comes down from the model into the base electronics and how the peripherals are linked to the base electronics also. There are more pictures of the cabling later.

## Mounting

Once you have everything connected up, it's time to mount the model on a stand. I used Lego because you can build it to fit yor needs (and I had some old lego left over from my childhood). Other options might be suitable. With Lego I had to modify some parts so they held the turn servo securely in place (a [ladder](https://www.bricklink.com/v2/catalog/catalogitem.page?P=4175) with the rungs filed flat).

My first version didn't have the rotate servo underneath and used arms to turn the main shaft. See the design on [BrickLink](https://www.bricklink.com/v3/studio/design.page?idModel=320370). There was some wobble when turning the model back and forth.

After some experimentation, I built a base around the MG90S turn servo with flat tiles on top. The servo horn was glued to a [plate with a hole](https://www.bricklink.com/v2/catalog/catalogitem.page?P=711) (with some filing of the underside). The hole so the screw can hold the horn onto the servo. I then layed the tilt servo flat (to minimise height) using some [90 degree brackets](https://www.bricklink.com/v2/catalog/catalogitem.page?P=3956#T=C) and a [Technical Lego](https://www.bricklink.com/v2/catalog/catalogitem.page?P=3703) strut up to the model (bound with black tape in the pictures).

{% include gallery id="gallery3" caption="Building the base mounting out of Lego" %}

You can see the two (white) right angle brackets facing away from each other and the other grey right angle bracket attached to the strut (partially covered with the black tape in the picture).

This Lego all fits in the base unit of my model and is hot-glued down to keep it still. The remote control sensor protrudes at the front and the power socket out the back. You would need to build your base mount to fit your base unit.

To stop the cables interfering with the turn motion, I hot-glued the circuit boards onto a platform with space underneath to route power and signal cables underneath. The one unconnected black ground wire is for the red and blue lights on the top of the base unit.

To make the top of the base unit, I duplicated the original base using mold making silicone and resin. Once cured, I cut it so it fits round the stand and tilt struts upto the model. I laid the red and blue base unit lights, hot-glued on the underside with the cables crossing at the back of the underside (near a hinge made from black tape).

{% include gallery id="gallery4" caption="Building the top of the base unit" %}

Putting everything together hides the base mount in the base unit. With some painting, decals and model railway gravel, the Terminator Aerial Hunter-Killer enhancements are complete.

{% include video id="nFd6Pr7X_5A" provider="youtube" %}
