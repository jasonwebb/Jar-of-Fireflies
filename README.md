# Jar of Fireflies

Mason jars outfitted with LEDs and a small microcontroller programmed to mimic the behavior of fireflies caught on a warm summer night. A gentle tap on the glass catches the attention of a piezo element, startling the lights and causing them to rapidly flash for a moment before returning to their blissful natural state.

This is a modernized reinvention of the classic ["Jar of fireflies"](http://www.instructables.com/id/Jar-of-Fireflies/) project by Keso using the Arduino framework and the ATTiny85 microcontroller.

## Board features
* ATTiny85 microcontroller mounted with a DIP IC socket so it can be easily removed and reprogrammed externally using HLT's Arduino bootloader (see http://hlt.media.mit.edu/?p=1695).
  * Currently looking into adding an on-board ICSP interface for easier reprogramming. [See issue](https://github.com/jasonwebb/Jar-of-Fireflies/issues/1).
* Six charlieplexed LEDs (with the option to use SMD LEDs with fancy soldering).
* Piezo sensor to detect tapping for interaction.
* Multiple power input options including via a classic 2.1mm barrel jack, a 2-pin JST jack or 2-pin 0.1" screw terminal.
* Large hole contacts for alligator clips so multiple jars can be daisychained to a single power source.

## License
This work is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).

Use this project to learn, tinker and share with friends. Small commercial runs for workshops or other educational uses is completely cool, but please contact me if you'd like to mass produce this project for profit.

[![Creative Commons license](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-nc-sa/4.0/)
