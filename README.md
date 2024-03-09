# mc

## overview

mc is a c++ command-line interface application for managing audio input devices on windows. 
the program allows users to toggle the mute/unmute status of specific audio input devices and provides a convenient list of available devices.

## features

- **toggle microphone mute/unmute:** control the mute state of a particular audio input device from the command line.
- **list audio input devices:** display a list of available audio input devices along with their mute status.

## table of contents

- [usage](#usage)
  - [commands](#commands)
  - [examples](#examples)
- [dependencies](#dependencies)
- [build instructions](#build-instructions)
- [license](#license)

## usage

### commands

- **list devices:**
  ```bash
  mc.exe --list
  ```

- **toggle microphone state:**
  ```bash
  mc.exe -d <device_index> -m   # mute
  mc.exe -d <device_index> -u   # unmute
  ```

### examples

- mute microphone on device with index 1:
  ```bash
  mc.exe -d 1 -m
  ```

## dependencies

- windows multimedia api
- cxxopts (for command-line option parsing)

## build instructions

1. clone the repository
2. open the project in visual studio
3. build the project

## license

this project is licensed under the mit license - see the [license](license) file for details.
