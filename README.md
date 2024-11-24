- 👋 Hi, I’m @Rezwan0002
- 👀 I’m interested in embedded systems,electronics,c/c++ programming.
- 🌱 I’m currently pursuing Electrical and Electronics Engineering pre final year.
- 💞️ I’m looking to collaborate on Embedded systems projects,c/c++ projects.
- 📫 reach me Mail-rezwanbasheer0002@gmail.com.
- ⚡ Fun fact:a problem a day keeps ur placement fear away 

Obstacle Avoiding Robot Using Raspberry Pi Pico
This project demonstrates an obstacle-avoiding robot using the Raspberry Pi Pico. The robot is programmed in MicroPython and optionally supports development in Arduino IDE. It features an ultrasonic sensor for detecting obstacles, a servo motor for wider sensing coverage, and autonomous movement capabilities.

Features
Obstacle Detection: Uses an ultrasonic sensor for real-time obstacle detection.
Servo Motor Integration: Rotates the ultrasonic sensor to scan the surroundings.
Autonomous Navigation: Adjusts motor speed and direction to avoid obstacles.
Reverse Functionality: Reverses when obstacles are too close.
Adjustable Speed: Configurable motor speed for better control.
Components Used
Raspberry Pi Pico
Ultrasonic Sensor (e.g., HC-SR04)
Servo Motor (e.g., SG90)
L298N Motor Driver
Gear Motors (x2)
Li-ion Batteries (3.7V x2)
Programming
The robot is programmed using MicroPython, and an additional option for programming in Arduino IDE is available for advanced users or alternative implementations.

How It Works
Servo Motor Functionality: The servo rotates the ultrasonic sensor to scan for obstacles across a wider range.
Obstacle Detection: The ultrasonic sensor measures distances and identifies nearby obstacles.
Decision Making:
If an obstacle is detected within a threshold, the robot stops, reverses, and turns.
The servo helps identify a clear direction for forward movement.
Motor Control: The L298N motor driver manages the movement of the gear motors.
Setup Instructions
Hardware Setup:

Attach the ultrasonic sensor to the servo motor.
Connect the servo motor and ultrasonic sensor to the Raspberry Pi Pico GPIO pins.
Wire the gear motors to the L298N motor driver.
Power the robot using two 3.7V Li-ion batteries.
Software Setup:

Use Thonny IDE to write and upload the Python script to the Raspberry Pi Pico.
Optionally, use Arduino IDE for an alternative implementation.
Future Enhancements
Optimize response time by adjusting the servo's scanning intervals.
Implement additional sensors for enhanced obstacle detection.
Add Bluetooth/WiFi functionality using the Raspberry Pi Pico W for remote control.
