# Fuzzy-Logic-DC-Motor-RPM-Control-Arduino
Controlling DC motor rpm with mamdani type fuzzy inference system designed in MATLAB and implemented to Arduino with using look-up table. 

### This project involves using mamdani type fuzzy inference system to control DC motor's RPM. This project involves these steps:
- Generating a fuzzy inference system  with using MATLAB's Fuzzy Logic Toolbox.  
- Exporting the fuzzy inference system **(in our case it is Mamdan3.fis)** and convert it to look-up table using fuzztoard_v1.m .  
- Loading that array to Arduino Nano's program memory.   
- Generating a feedback loop with IR sensor.   
- Uploading the code to Arduino Nano.   
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
## 2) Fuzzy Logic Toolbox  
### Membership Functions  
The membership functions are influenced from (Freitas, Rameli, & EAK, 2017), but the range of the functions are adapted to our DC motor. The DC motor that used can deliver 1000 RPM at 12V according to its datasheet. Since we are using L298N Motor Driver, which has 2V voltage drop, our maximum output voltage is limited to 10V. The expected motor RPM at 10V is near 800 RPM. To verify that, motor RPM is measured against the rising PWM values which is used to drive the motor. The graph of motor curve is represented below.  
![dc_motor_rpm_curve](https://github.com/user-attachments/assets/745c4c0c-b8f3-4b9c-9e21-5d5282885a9b)  
To stay in safer limits, the motor RPM is limited to 600 RPM in membership functions. The input membership functions are represented below.  

![fuzzy_inference_system](https://github.com/user-attachments/assets/416f2661-b2e0-465e-8298-496cb9a53bcb)  

NL (Negative Low), NS (Negative Small), Z (Zero), PS (Positive Small), PL (Positive Large) ANL (Add Negative Large number), APS (Add Positive Small number),  ..etc.  

Detailed membership functions can be seen from **Mamdan3.fis**.  
### Rule Base  
Handwritten rule base is attached below. Detailed and clear version cen be seen from **Mamdan3.fis**.  

![rule_base](https://github.com/user-attachments/assets/fcb73b08-e293-4508-acd0-22354664241f)  
The rule base table will be replaced by excel version immediately. This rule base is als influenced from (Freitas, Rameli, & EAK, 2017), but the output rules are replaced with the inverse of the rules in order to fit our system.  

## 3) Generating Lookup Table  

To implement fuzzy logic control to Arduino platform, various libraries might be used to generate and evaluate fuzzy logic in the Arduino. However, in my approach I chose to use MATLAB’s Fuzzy Logic Toolbox as a fuzzy designer and use output of the fuzzy system as a lookup table in the Arduino. Within these 2 steps, anyone can export the output of any fuzzy system as a lookup table.  
### Generating Lookup Table in MATLAB  
To generate the lookup table, the evalfis (fis, input1, input2) function in MATLAB can be used to evaluate fuzzy inference system with given inputs as below. Anyone might wonder why we define arrays CE and E in a way that increments 20 value per step. The reason is the limited storage size of Arduino Nano. If we decide to use whole table which consists of 1200x1200 double array, the size will not fit the Arduino’s available space.  
![generating_lookup_table_from_fis](https://github.com/user-attachments/assets/2bdabbfc-d81c-4f5d-b571-1f9387d0f2f4)  
Another important note is that the resulting array should be stored in Arduino’s program memory, not in the SRAM as a global variable. The global variable space in Arduino is 2kB, but the program space is 30kB. The size of the lookup table should be arranged by considering remaining program space in the memory.  
### Convering MATLAB array to Arduino array    
![matlab_array_to_arduino_array](https://github.com/user-attachments/assets/3d65a5bf-4844-42f1-a2d6-acccf7aaf2ea)  
In this way, we generate Arduino compatible lookup table within minutes.  

## 4) Implementing Lookup Table in Arduino  
![lookup_table_arduino_picture](https://github.com/user-attachments/assets/1943f40c-449c-4245-adfd-647c271344b5)  

Here’s the portion of the lookup table in the Arduino. The important point is to add “PROGMEM” 
word after the array definition which tells the compiler to save this array into program memory. 
However, the program memory is only readable. To read a value from our stored array, this method 
can be used:  
*Out_PWM = pgm_read_word(&LookUpTable[selected_y][selected_x]);*  
The variables selected_y and selected_x defines the index values to reach the data in lookup 
table. Here’s how we define them:  
<img width="302" alt="image" src="https://github.com/user-attachments/assets/82c52a0a-887a-43a5-b7e0-e68223b088f3">  

Why we use rounded inputs is that: Since we resized our lookup table array, shortened it, we can 
not directly access to it using ordinary values. Because our inputs, rpm_error and change_of_rpm_error is changing continuously, not by incremented by 20. So, we need to use 
interpolation to reach our closest desired value in the lookup table. For instance, if our 
rpm_error is 585,  
*585/20 = 29.25*   
*Round(29.25) = 29*   
*29*20 = 580*  
To find which index value is corresponds to 580, the map() function of the Arduino is used. 
Let’s say 580 is the x’th input in our shortened lookup table, so in order to  access the output 
data according to 580, we use the index value x.  

## 5) Code Explanation  
Here’s the flowchart of the program.The program gets user input as desired RPM and 
fuzzy controller is used to reach the desired RPM and keep the motor on desired RPM. Full 
code is available on ino file. The main logic is taking the rpm data from the motor, calculate 
rpm error and rpm error change to use input for fuzzy inference system, obtain the response of 
the fuzzy system via lookup table, use the output control pwm to drive the motor and so on. 
There is a point shoul I note that the output PWM is not the output cames from the lookup table. 
Previously, I used that to drive the motor but motor stalls since most of the time the adjustments 
made from the fuzzy system is relatively small to drive the motor. After couple of hours of error 
checking and researching, I noticed that the output PWM value from the fuzzy inference 
represents the change in the output, not the output to drive the motor. So, I adjusted the code in 
that way, this is why we have separate variable to drive the motor as drivePWM and Out_PWM. 
Out_PWM is the PWM value comes from fuzzy inference. DrivePWM is the PWM value to 
drive motor. DrivePWM can be calculated as:  

<img width="383" alt="image" src="https://github.com/user-attachments/assets/48e16a5d-1952-4a93-905e-203933a5355d">   
  
## 6) Results  
The results are taken from the Arduino serial monitor and transferred to excel to 
process the data. The RPM and PWM graph of fuzzy controller is attached below.  

<img width="373" alt="image" src="https://github.com/user-attachments/assets/28204f16-f40b-4131-859b-df28f2b5caf7">  
From the graph above, the motor RPM and desired RPM can be tracked, also the error 
variables of our fuzzy system RPM error and change of RPM error can be observed. From this 
output, one can say that the fuzzy inference system’s fuzzy output PWM matches with change of 
rpm error. Also, the motor tracks the desired RPM with significant error margin. Although desired 
RPM and motor RPM aligns, there is an error gap occurred. The error is around -80 RPM. This 
error might be lowered by adjusting the rule base or input membership functions, or adding some 
rescaling operations to evaluate drive PWM, which is used to drive the motor.  

## References  
1. Belkhir, K. S. (2020). Simple Implementationof a FuzzyLogicSpeedController for a PMDC Motor witha LowCostArduino Mega. Departmentof ElectricalEngineering, Facultyof Technology, UniversityFerhat Abbas Setif1. Setif, Algeria. ksbelkhir@univ-setif.dz  
 2. Freitas, B. M., Rameli, M., & EAK, R. (2017). Implementationof MamdaniFuzzyLogicControl System on DC Motor SpeedController. Department of ElectricalEngineering, SepuluhNopember Instituteof Technology, Surabaya, Indonesia.  
 3. MATLAB. (2016, April 19). FuzzyInferenceSystem Walkthrough| FuzzyLogic, Part2 [Video]. YouTube. https://www.youtube.com/watch?v=r57CGLAzjZE




