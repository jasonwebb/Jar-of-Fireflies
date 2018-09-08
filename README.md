---
WARNING: This project is currently being updated. The board designs need to be physically prototyped, and the current firmware sketch is not guaranteed to work correctly with the latest board design. Use with caution!
---

# Jar of Fireflies

Mason jar outfitted with LEDs and a small microcontroller programmed to mimic the behavior of fireflies caught on a warm summer night. A gentle tap on the glass catches the attention of a piezo element, startling the lights and causing them to rapidly flash for a moment before returning to their blissful natural state.

An external sensor interface enables more complex interactions using both analog and digital sensors for properties like temperature, sound, light, distance/proximity, movement, tilt, biometrics, and much more.

This is a modernized reinvention of the classic ["Jar of fireflies"](http://www.instructables.com/id/Jar-of-Fireflies/) project by Keso using the Arduino framework and the ATTiny85 microcontroller.

## Features
* ATTiny85 microcontroller programmed with Arduino using the [HLT bootloader](http://hlt.media.mit.edu/?p=1695), mounted in a DIP IC socket for easy removal and replacement.
* Six charlieplexed through-hole LEDs, with the option to use SMD LEDs with fancy soldering.
* Large plated hole pairs for alligator clips so multiple jars can be daisy-chained to a single power source.
* Piezo sensor to detect tapping for interaction.
* Tactile button as an alternative to the piezo sensor for interaction.
* 3-pin interface for external sensors (both analog and digital) to enable more complex interactions.
* 2x3 pin ICSP interface for easier reprogramming.
* Multiple power input options including:
  * 3.5mm center-positive barrel jack for common wall supplies.
  * 2-pin JST-PH jack for battery packs.

## License
This work is licensed under the [Creative Commons BY-NC-SA (Attribution - NonCommercial - ShareAlike) 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).

[![Creative Commons license](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-nc-sa/4.0/)

This means that you are completely free to use and modify any of these files for personal and educational use (with a shout-out 🙂), but manufacturing, selling and marketing this project to mass markets for your own profit is prohibited. If this is something that you are interested in doing, please contact me about setting up a partnership!

This license is chosen mainly in an effort, however naive, to discourage low-quality "knock offs" from flooding the market, which can lead to frustration and lack of trust in consumers caused by poor documentation, support, and quality assurance - a concern that tends to be unique to open-source hardware.

I expressly and strongly approve of use of this project for conference badges/swag, soldering workshops, art projects, and other small-scale community and creative-oriented applications. Such applications are what motivate me to share these source files in the first place!