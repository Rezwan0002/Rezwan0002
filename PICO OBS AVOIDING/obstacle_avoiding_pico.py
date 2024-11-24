from machine import Pin, PWM
import time

# Initialize the servo motor
servo = PWM(Pin(16))  # Servo pin set to 12
servo.freq(50)

# Initialize the ultrasonic sensor pins
Trig = Pin(18, Pin.OUT)  # Trig pin set to 10
Echo = Pin(19, Pin.IN)   # Echo pin set to 11

# Motor driver pins (L298N connections)
ENA = PWM(Pin(14))  # Enable pin A set to 6
IN1 = Pin(9, Pin.OUT)  # Input pin 1 set to 2
IN2 = Pin(8, Pin.OUT)  # Input pin 2 set to 3
IN3 = Pin(7, Pin.OUT)  # Input pin 3 set to 4
IN4 = Pin(6, Pin.OUT)  # Input pin 4 set to 5
ENB = PWM(Pin(15))  # Enable pin B set to 7

ENA.freq(1000)
ENB.freq(1000)

# Adjusted speed for lower power consumption and better response
speed = 30000  # Speed of the robot (lower for safer operation)

def forward():
    ENA.duty_u16(speed)
    IN1.value(0)
    IN2.value(1)
    ENB.duty_u16(speed)
    IN3.value(1)
    IN4.value(0)
    print("Moving Forward")

def backward():
    ENA.duty_u16(speed)
    IN1.value(1)
    IN2.value(0)
    ENB.duty_u16(speed)
    IN3.value(0)
    IN4.value(1)
    print("Moving Backward")

def left():
    ENA.duty_u16(speed)
    IN1.value(1)
    IN2.value(0)
    ENB.duty_u16(speed)
    IN3.value(1)
    IN4.value(0)
    print("Turning Left")

def right():
    ENA.duty_u16(speed)
    IN1.value(0)
    IN2.value(1)
    ENB.duty_u16(speed)
    IN3.value(0)
    IN4.value(1)
    print("Turning Right")

def stop():
    ENA.duty_u16(0)
    IN1.value(0)
    IN2.value(0)
    ENB.duty_u16(0)
    IN3.value(0)
    IN4.value(0)
    print("Stopped")

# Function to get the distance from the ultrasonic sensor
def distance():
    Trig.value(0)
    time.sleep_us(2)
    Trig.value(1)
    time.sleep_us(10)
    Trig.value(0)
    
    while Echo.value() == 0:
        low = time.ticks_us()
    
    while Echo.value() == 1:
        high = time.ticks_us()
    
    t = high - low
    cm = t / 29 / 2  # Convert time to cm
    print(f"Measured distance: {cm:.2f} cm")
    return cm

def servo_left():
    servo.duty_u16(7500)  # Move servo to the left
    print("Servo moved left")

def servo_right():
    servo.duty_u16(1800)  # Move servo to the right
    print("Servo moved right")

def servo_start():
    servo.duty_u16(4800)  # Center the servo
    print("Servo centered")

while True:
    dis = distance()
    
    if dis < 15:  # Obstacle detected within 15 cm
        stop()
        time.sleep(0.5)
        
        # Backward for a short time before turning
        backward()
        time.sleep(1)  # Reverse for second
        stop()
        time.sleep(0.5)
        
        # Scan to the left
        servo_left()
        time.sleep(0.2)  # Wait for the servo to move
        left_dis = distance()  # Measure left distance
        print("Left Distance:", left_dis)
        
        # Center the servo
        servo_start()
        time.sleep(0.2)  # Centering time
        
        # Scan to the right
        servo_right()
        time.sleep(0.2)  # Wait for the servo to move
        right_dis = distance()  # Measure right distance
        print("Right Distance:", right_dis)
        
        # Center the servo back
        servo_start()
        time.sleep(0.3)  # Centering time

        # Decision making based on distance readings
        if left_dis > right_dis:
            print("Decision: Turn Left")
            left()  # Turn left
            time.sleep(0.5)
        else:
            print("Decision: Turn Right")
            right()  # Turn right
            time.sleep(0.5)
        
        stop()  # Stop after turning
        time.sleep(0.5)  # Wait before moving again
        
    else:
        forward()  # No obstacles, move forward
        time.sleep(0.1)  # Short delay for forward movement