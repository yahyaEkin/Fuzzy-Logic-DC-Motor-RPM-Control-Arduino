# Fuzzy-Logic-DC-Motor-RPM-Control-Arduino
Controlling DC motor rpm with mamdani type fuzzy inference system designed in MATLAB and implemented to Arduino with using look-up table. 

# This project involves using mamdani type fuzzy inference system to control DC motor's RPM. This project involves these steps:
1- Generating a fuzzy inference system  with using MATLAB's Fuzzy Logic Toolbox.
2- Exporting the fuzzy inference system **(in our case it is Mamdan3.fis)** and convert it to look-up table using fuzztoard_v1.m .
3- Loading that array to Arduino Nano's program memory. 
4- Generating a feedback loop with IR sensor. 
5- Uploading the code to Arduino Nano. 
**The Arduino code is fuzz_to_arduino_dc_motor_rpm_control.ino**

## 1) Purpose: 
The RPM control of DC motor is fundamental concept used in the field of where electric 
motors are used, as an obvious example, electric cars. But how we can sure about that when we 
press the accelerator pedal in our car, the rpm of the motor is approaching our desired RPM 
value. To be sure about that, Mamdani type-1 fuzzy logic control system can be used. To control 
the motor, we need two linguistic variables as RPM Error and Change of RPM Error. The 
definitions of both are: 

*RPM Error = Desired RPM – Measured Motor RPM.* 
*Change of RPM Error = RPM Error – Previous RPM Error.* 
The output linguistic variable is Fuzzy Output PWM, which is defined as: 
*Fuzzy Output PWM = Output PWM – Previous Output PWM.* 

To perform the motor control simple Arduino setup is designed. This setup consists of 
IR Receiver, which is used to measure the motor RPM, 12V DC motor, Potentiometer to 
define desired RPM value, DC motor driver and Arduino Nano Board. 



