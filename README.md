# BearRescue

## BearRescue_Gauntlet.ino

Main file where the brains of the project lies. It meshes together all the components.

## BearRescue_HackPublisher.hpp

Library provided by HAcK mentor team to have network connectivity and to manage a server connection with a remote device.

## BearRescue_Melody.hpp

Personal library that manages collections of Notes so that they can played asynchronously thus removing the need to add delays for alarms.

## BearRescue_Note.hpp

Personal library that manages a single note and its properties (pitch and duration) and stores them in a bitfield to offload memory requirements.

## BearRescue_Secrets.hpp

This file is not tracked and has the definition of two variables that hold the SSID and password of the network used to communicate.

## BearRescue_SoundList.hpp

Declarations of tunes used in this project using the Note library.

## BearRescue_Ultrasonic.hpp

Libary that manages and fascilitates the use of an ultrasonic sensor. Allows selecting your preferred unit and it defaults to centimeters.

## Notes or Issues Encountered

Issues where numerous but we dealt with them as they came since their source came from both the circuitry and code in equal parts. A non comprehensive list includes:

1. Being unable to upload code to the ESP32 because I was using the wrong cable (cable used did not have a data line).
2. Some sensors not working because some pins caused compatibiity issues with another ones.
3. Code that worked fine in the Arduino Nano was failing to work when uploaded to the ESP32
4. I was not getting activity on the web server because I was on the wrong network. Also the password provided at first had a lookalike character that Visual Studio Code managed to catch and warn me about.
5. When I removed the delay of two seconds the server connection failed, I assume because it was getting overloaded. I added instead a half a second delay which give a reasonable amount of data without sacrificing continuity of data.
6. Switch button being added to play a victory song did not work, and to avoid wasting valuable time on the last hours we decided to do away with it.
