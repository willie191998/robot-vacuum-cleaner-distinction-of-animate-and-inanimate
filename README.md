# robot vacuum cleaner distinction of animate and inanimate obstacles
This code is designed for an Arduino UNO microcontroller and is part of a project to construct a robot vacuum. The vacuum operates using the S-path navigation algorithm and features motion detection using PIR sensors and limit switches/touch sensors. It's equipped with two TT DC motors for movement and separate motors for vacuuming and sweeping. Additional components include a buzzer, LED, and the AFMotor library for L293D motor driver control.

This code is a simplified form of the later advanced code I had to build, this time using an MPU5060 IC. This was done because the robot being two-wheel could not move on a straight line because of inaccuracies in the motors so they don't make the same amount of turn per second. An MPU5060 sensor is a multi-axis acceleration detector using an internal accelerometer and gyroscopes. It detects the turn of the vacuum cleaner in the Z axis and makes adjustments in the turn of the movement motors to counter this turn. The result is that the vacuum cleaner moves in a straight line.

I uploaded the simple algorithm here to start with if you want the advanced algorithm using an MPU sensor then email me at anoruewilson@gmail.com
see the project at Instructables  https://www.instructables.com/Making-a-Robot-Vacuum-Cleaner-Follow-the-S-path-Al/
