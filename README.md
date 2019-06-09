# arduino_proj
Obstacle and edge detection using Arduino and motor shield

The robot has 2 ultrasonic sensors.
1 facing front to detect obstacles
1 facing down on an extension 1/2 ft long plate.

Obstacle detection sensor is mounted on the servo motor to detection obstacle in the way of robot body.
It does not cover 180\degree since its redundant. Sensor needs to detect obstacles
that will be in the way of robot and not the once around it.

The same code can be used for a robot with Maccunum wheels or normal wheels. Only the direction methods will need to be modified.

Chips and hardware : Arduino UNO, Motor shield, Maccunum wheels
