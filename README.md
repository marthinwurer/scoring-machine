# An Arduino Scoring Machine
This is a scoring machine built using an Arduino Uno (ATMega328P-PU). 
It works pretty great, and we've used it at club practices for a few weeks, and had no issues.

Epee works 100%. Foil works 100%. Saber needs whipover and better timing, so 75%. 

Main code needs a good refactor, but it works!

# Instructions

follow https://github.com/arduino-cmake/Arduino-CMake-NG/wiki/Installation

We need the new arduino toolkit

```
git clone git@github.com:arduino-cmake/Arduino-CMake-NG.git

```

Do not install avrdude from the repos, we need the one in the arduino toolkit.
This gets pulled in automatically by arduino-cmake.

```
sudo cp -r ~/Downloads/arduino-1.8.10 /usr/share
```
