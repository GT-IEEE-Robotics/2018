EESchema Schematic File Version 2
LIBS:MotorCape-rescue
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:MotorCapeComponents
LIBS:arduino
LIBS:DueShieldComponents
LIBS:SparkFun-Aesthetics
LIBS:SparkFun-Batteries
LIBS:SparkFun-Boards
LIBS:SparkFun-Capacitors
LIBS:SparkFun-Clocks
LIBS:SparkFun-Coils
LIBS:SparkFun-Connectors
LIBS:SparkFun-DiscreteSemi
LIBS:SparkFun-Displays
LIBS:SparkFun-Electromechanical
LIBS:SparkFun-Fuses
LIBS:SparkFun-GPS
LIBS:SparkFun-Hardware
LIBS:SparkFun-IC-Amplifiers
LIBS:SparkFun-IC-Comms
LIBS:SparkFun-IC-Conversion
LIBS:SparkFun-IC-Logic
LIBS:SparkFun-IC-Memory
LIBS:SparkFun-IC-Microcontroller
LIBS:SparkFun-IC-Power
LIBS:SparkFun-IC-Special-Function
LIBS:SparkFun-Jumpers
LIBS:SparkFun-LED
LIBS:SparkFun-PowerSymbols
LIBS:SparkFun-Resistors
LIBS:SparkFun-RF
LIBS:SparkFun-Sensors
LIBS:SparkFun-Switches
LIBS:MotorCape-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 7000 6950 0    60   ~ 0
MOTOR_PWR=12V\nfor motors:\n1 - 12V (red)       3 - encoder gnd(green)       5 - encoder A (yellow)\n2 - Gnd (black)     4 - encoder Vcc(5V)(blue)    6 - encoder B (white)\n
$Comp
L Conn_01x02 J7
U 1 1 59FC44BE
P 4550 2450
F 0 "J7" H 4550 2250 50  0000 C CNN
F 1 "i2c bus connector" H 4600 2600 50  0000 C CNN
F 2 "MotorCapeComponents:Pin_Header_Latched_1x02" H 4550 2450 50  0001 C CNN
F 3 "" H 4550 2450 50  0001 C CNN
	1    4550 2450
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x03 J11
U 1 1 5A0ED002
P 4600 4150
F 0 "J11" H 4600 3950 50  0000 C CNN
F 1 "flag_wheel servo" H 4550 4350 50  0000 C CNN
F 2 "MotorCapeComponents:Pin_Header_Latched_1x03" H 4600 4150 50  0001 C CNN
F 3 "" H 4600 4150 50  0001 C CNN
	1    4600 4150
	-1   0    0    -1  
$EndComp
NoConn ~ 6350 4000
NoConn ~ 6450 4000
NoConn ~ 6550 4000
NoConn ~ 6650 4000
NoConn ~ 6750 4000
NoConn ~ 6850 4000
NoConn ~ 6950 4000
NoConn ~ 7050 4000
NoConn ~ 7150 4000
NoConn ~ 7250 4000
NoConn ~ 7350 4000
NoConn ~ 7450 4000
NoConn ~ 7550 4000
NoConn ~ 7650 4000
NoConn ~ 9550 4000
NoConn ~ 9650 4000
NoConn ~ 9750 4000
NoConn ~ 9850 4000
NoConn ~ 9950 4000
NoConn ~ 6350 1400
NoConn ~ 6450 1400
NoConn ~ 6550 1400
NoConn ~ 6850 1400
NoConn ~ 6950 1400
NoConn ~ 7050 1400
NoConn ~ 7150 1400
NoConn ~ 7450 1400
NoConn ~ 7550 1400
NoConn ~ 7750 1400
NoConn ~ 9750 1400
NoConn ~ 9850 1400
NoConn ~ 7850 1400
NoConn ~ 7950 1400
NoConn ~ 8050 1400
NoConn ~ 8150 1400
NoConn ~ 8250 1400
NoConn ~ 8350 1400
NoConn ~ 8450 1400
NoConn ~ 8550 1400
NoConn ~ 8650 1400
NoConn ~ 8750 1400
NoConn ~ 8850 1400
NoConn ~ 8950 1400
NoConn ~ 9050 1400
NoConn ~ 9150 1400
NoConn ~ 9350 1400
NoConn ~ 9450 1400
NoConn ~ 10450 1400
NoConn ~ 10350 1400
NoConn ~ 10250 1400
NoConn ~ 10150 1400
NoConn ~ 10050 1400
NoConn ~ 9950 1400
Text GLabel 4800 2450 2    60   Input ~ 0
SCL
Text GLabel 4800 2550 2    60   Input ~ 0
SDA
Text GLabel 9550 1400 1    60   Input ~ 0
SCL
Text GLabel 9650 1400 1    60   Input ~ 0
SDA
NoConn ~ 11100 2750
NoConn ~ 11100 2850
Text GLabel 1250 3000 0    60   Input ~ 0
MOTOR_PWR
$Comp
L Fuse F1
U 1 1 5A6C2616
P 3350 1200
F 0 "F1" V 3430 1200 50  0000 C CNN
F 1 "Fuse" V 3275 1200 50  0000 C CNN
F 2 "MotorCapeComponents:Fuseholder_horizontal_inline_1_25x0_25_inch" V 3280 1200 50  0001 C CNN
F 3 "" H 3350 1200 50  0001 C CNN
	1    3350 1200
	0    1    -1   0   
$EndComp
Text GLabel 3550 1200 2    60   Input ~ 0
MOTOR_PWR
$Comp
L CONN_01X02 P13
U 1 1 5A98ECA7
P 2850 1250
F 0 "P13" H 2850 1400 50  0000 C CNN
F 1 "battery_connector" V 2950 1250 50  0000 C CNN
F 2 "Connectors_Molex:Molex_Sabre_43160-XX02_02x7.49mm_Vertical_BoardLock" H 2850 1250 50  0001 C CNN
F 3 "" H 2850 1250 50  0000 C CNN
	1    2850 1250
	-1   0    0    -1  
$EndComp
NoConn ~ 7650 1500
$Comp
L CONN_01X04 P14
U 1 1 5AA1DD33
P 4550 3150
F 0 "P14" H 4550 2900 50  0000 C CNN
F 1 "Pi_Connector" H 4550 3400 50  0000 C CNN
F 2 "MotorCapeComponents:Pin_Header_Latched_1x04" H 4550 3150 50  0001 C CNN
F 3 "" H 4550 3150 50  0000 C CNN
	1    4550 3150
	-1   0    0    -1  
$EndComp
Text GLabel 4800 3200 2    60   Input ~ 0
Tx_To_Pi
Text GLabel 4800 3300 2    60   Input ~ 0
Rx_From_Pi
NoConn ~ 11100 2450
NoConn ~ 11100 2550
NoConn ~ 11100 2650
NoConn ~ 11100 2950
NoConn ~ 4300 5200
NoConn ~ 4300 5300
NoConn ~ 4300 5400
NoConn ~ 4300 5500
NoConn ~ 4300 5600
NoConn ~ 4300 5900
NoConn ~ 4300 6000
Text GLabel 6000 5700 2    60   Input ~ 0
SDA
Text GLabel 6000 5900 2    60   Input ~ 0
SCL
$Comp
L IMU U1
U 1 1 5ABDC0C0
P 4500 5150
F 0 "U1" H 4950 4200 60  0000 C CNN
F 1 "IMU" H 4950 5200 60  0000 C CNN
F 2 "MotorCapeComponents:IMU" H 4500 5150 60  0001 C CNN
F 3 "" H 4500 5150 60  0000 C CNN
	1    4500 5150
	1    0    0    -1  
$EndComp
Text GLabel 1250 3100 0    60   Input ~ 0
MOTOR_GND
Text GLabel 2550 2900 2    60   Input ~ 0
FrontLeft_DIR
Text GLabel 2550 3000 2    60   Input ~ 0
FrontLeft_SPD
Text GLabel 2550 3350 2    60   Input ~ 0
BackLeft_DIR
Text GLabel 2550 3450 2    60   Input ~ 0
BackLeft_SPD
Text GLabel 2550 3100 2    60   Input ~ 0
FrontLeft_ENC_A
Text GLabel 2550 3200 2    60   Input ~ 0
FrontLeft_ENC_B
Text GLabel 2550 3550 2    60   Input ~ 0
BackLeft_ENC_A
Text GLabel 2550 3650 2    60   Input ~ 0
BackLeft_ENC_B
Text GLabel 3550 1400 2    60   Input ~ 0
MOTOR_GND
$Sheet
S 1300 2800 1200 950 
U 5AC8802A
F0 "LeftMotors_levelshifted" 60
F1 "MotorsAndController.sch" 60
F2 "Motor_PWR" I L 1300 3000 60 
F3 "Motor_GND" I L 1300 3100 60 
F4 "GND" I L 1300 3550 60 
F5 "5V_PWR" I L 1300 3350 60 
F6 "M1_DIR" I R 2500 2900 60 
F7 "M1_SPD" I R 2500 3000 60 
F8 "M2_SPD" I R 2500 3450 60 
F9 "M2_DIR" I R 2500 3350 60 
F10 "M1_ENC_A" I R 2500 3100 60 
F11 "M1_ENC_B" I R 2500 3200 60 
F12 "M2_ENC_A" I R 2500 3550 60 
F13 "M2_ENC_B" I R 2500 3650 60 
F14 "3v3_PWR" I L 1300 3450 60 
$EndSheet
Text GLabel 1250 6450 0    60   Input ~ 0
MOTOR_PWR
Text GLabel 1250 6550 0    60   Input ~ 0
MOTOR_GND
Text GLabel 2550 6350 2    60   Input ~ 0
FlagWheel_DIR
Text GLabel 2550 6450 2    60   Input ~ 0
FlagWheel_SPD
Text GLabel 2550 6800 2    60   Input ~ 0
DrawBridge_DIR
Text GLabel 2550 6900 2    60   Input ~ 0
DrawBridge_SPD
Text GLabel 2550 6550 2    60   Input ~ 0
FlagWheel_ENC_A
Text GLabel 2550 6650 2    60   Input ~ 0
FlagWheel_ENC_B
Text GLabel 2550 7000 2    60   Input ~ 0
DrawBridge_ENC_A
Text GLabel 2550 7100 2    60   Input ~ 0
DrawBridge_ENC_B
$Sheet
S 1300 6250 1200 950 
U 5ACB9F03
F0 "TopMotors_levelshifted" 60
F1 "MotorsAndController.sch" 60
F2 "Motor_PWR" I L 1300 6450 60 
F3 "Motor_GND" I L 1300 6550 60 
F4 "GND" I L 1300 7000 60 
F5 "5V_PWR" I L 1300 6800 60 
F6 "M1_DIR" I R 2500 6350 60 
F7 "M1_SPD" I R 2500 6450 60 
F8 "M2_SPD" I R 2500 6900 60 
F9 "M2_DIR" I R 2500 6800 60 
F10 "M1_ENC_A" I R 2500 6550 60 
F11 "M1_ENC_B" I R 2500 6650 60 
F12 "M2_ENC_A" I R 2500 7000 60 
F13 "M2_ENC_B" I R 2500 7100 60 
F14 "3v3_PWR" I L 1300 6900 60 
$EndSheet
Text GLabel 1250 4800 0    60   Input ~ 0
MOTOR_PWR
Text GLabel 1250 4900 0    60   Input ~ 0
MOTOR_GND
Text GLabel 2550 4700 2    60   Input ~ 0
FrontRight_DIR
Text GLabel 2550 4800 2    60   Input ~ 0
FrontRight_SPD
Text GLabel 2550 5150 2    60   Input ~ 0
BackRight_DIR
Text GLabel 2550 5250 2    60   Input ~ 0
BackRight_SPD
Text GLabel 2550 4900 2    60   Input ~ 0
FrontRight_ENC_A
Text GLabel 2550 5000 2    60   Input ~ 0
FrontRight_ENC_B
Text GLabel 2550 5350 2    60   Input ~ 0
BackRight_ENC_A
Text GLabel 2550 5450 2    60   Input ~ 0
BackRight_ENC_B
$Sheet
S 1300 4600 1200 950 
U 5ACC6682
F0 "RightMotors_levelshifted" 60
F1 "MotorsAndController.sch" 60
F2 "Motor_PWR" I L 1300 4800 60 
F3 "Motor_GND" I L 1300 4900 60 
F4 "GND" I L 1300 5350 60 
F5 "5V_PWR" I L 1300 5150 60 
F6 "M1_DIR" I R 2500 4700 60 
F7 "M1_SPD" I R 2500 4800 60 
F8 "M2_SPD" I R 2500 5250 60 
F9 "M2_DIR" I R 2500 5150 60 
F10 "M1_ENC_A" I R 2500 4900 60 
F11 "M1_ENC_B" I R 2500 5000 60 
F12 "M2_ENC_A" I R 2500 5350 60 
F13 "M2_ENC_B" I R 2500 5450 60 
F14 "3v3_PWR" I L 1300 5250 60 
$EndSheet
Text GLabel 9450 4000 3    60   Input ~ 0
FrontLeft_DIR
Text GLabel 10650 4000 3    60   Input ~ 0
FrontLeft_SPD
Text GLabel 9150 4000 3    60   Input ~ 0
BackLeft_DIR
Text GLabel 10550 4000 3    60   Input ~ 0
BackLeft_SPD
Text GLabel 9350 4000 3    60   Input ~ 0
FrontLeft_ENC_A
Text GLabel 9250 4000 3    60   Input ~ 0
FrontLeft_ENC_B
Text GLabel 9050 4000 3    60   Input ~ 0
BackLeft_ENC_A
Text GLabel 8950 4000 3    60   Input ~ 0
BackLeft_ENC_B
Text GLabel 10450 4000 3    60   Input ~ 0
FrontRight_SPD
Text GLabel 10350 4000 3    60   Input ~ 0
BackRight_SPD
Text GLabel 8250 4000 3    60   Input ~ 0
FlagWheel_DIR
Text GLabel 10250 4000 3    60   Input ~ 0
FlagWheel_SPD
Text GLabel 7950 4000 3    60   Input ~ 0
DrawBridge_DIR
Text GLabel 10150 4000 3    60   Input ~ 0
DrawBridge_SPD
Text GLabel 8150 4000 3    60   Input ~ 0
FlagWheel_ENC_A
Text GLabel 8050 4000 3    60   Input ~ 0
FlagWheel_ENC_B
Text GLabel 7850 4000 3    60   Input ~ 0
DrawBridge_ENC_A
Text GLabel 7750 4000 3    60   Input ~ 0
DrawBridge_ENC_B
Text GLabel 8850 4000 3    60   Input ~ 0
FrontRight_DIR
Text GLabel 8750 4000 3    60   Input ~ 0
FrontRight_ENC_A
Text GLabel 8650 4000 3    60   Input ~ 0
FrontRight_ENC_B
Text GLabel 8550 4000 3    60   Input ~ 0
BackRight_DIR
Text GLabel 8450 4000 3    60   Input ~ 0
BackRight_ENC_A
Text GLabel 8350 4000 3    60   Input ~ 0
BackRight_ENC_B
Text GLabel 10050 4000 3    60   Input ~ 0
Servo_SPD
$Comp
L R R2
U 1 1 5ACFD3ED
P 5800 5900
F 0 "R2" V 5880 5900 50  0000 C CNN
F 1 "R" V 5800 5900 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 5730 5900 50  0001 C CNN
F 3 "" H 5800 5900 50  0001 C CNN
	1    5800 5900
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5ACFD510
P 5800 5700
F 0 "R1" V 5880 5700 50  0000 C CNN
F 1 "R" V 5800 5700 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 5730 5700 50  0001 C CNN
F 3 "" H 5800 5700 50  0001 C CNN
	1    5800 5700
	0    1    1    0   
$EndComp
Text GLabel 10550 1400 1    60   Input ~ 0
Tx_To_Pi
Text GLabel 10650 1400 1    60   Input ~ 0
Rx_From_Pi
$Comp
L GND #PWR01
U 1 1 5ACBB0CF
P 1150 3550
F 0 "#PWR01" H 1150 3300 50  0001 C CNN
F 1 "GND" H 1150 3400 50  0000 C CNN
F 2 "" H 1150 3550 50  0001 C CNN
F 3 "" H 1150 3550 50  0001 C CNN
	1    1150 3550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR02
U 1 1 5ACBBBC2
P 1150 3350
F 0 "#PWR02" H 1150 3200 50  0001 C CNN
F 1 "+5V" H 1150 3490 50  0000 C CNN
F 2 "" H 1150 3350 50  0001 C CNN
F 3 "" H 1150 3350 50  0001 C CNN
	1    1150 3350
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR03
U 1 1 5ACBBE6A
P 950 3450
F 0 "#PWR03" H 950 3300 50  0001 C CNN
F 1 "+3.3V" H 950 3590 50  0000 C CNN
F 2 "" H 950 3450 50  0001 C CNN
F 3 "" H 950 3450 50  0001 C CNN
	1    950  3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5ACBEE75
P 1150 5350
F 0 "#PWR04" H 1150 5100 50  0001 C CNN
F 1 "GND" H 1150 5200 50  0000 C CNN
F 2 "" H 1150 5350 50  0001 C CNN
F 3 "" H 1150 5350 50  0001 C CNN
	1    1150 5350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 5ACBEE7B
P 1150 5150
F 0 "#PWR05" H 1150 5000 50  0001 C CNN
F 1 "+5V" H 1150 5290 50  0000 C CNN
F 2 "" H 1150 5150 50  0001 C CNN
F 3 "" H 1150 5150 50  0001 C CNN
	1    1150 5150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR06
U 1 1 5ACBEE81
P 950 5250
F 0 "#PWR06" H 950 5100 50  0001 C CNN
F 1 "+3.3V" H 950 5390 50  0000 C CNN
F 2 "" H 950 5250 50  0001 C CNN
F 3 "" H 950 5250 50  0001 C CNN
	1    950  5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5ACC0E28
P 1150 7000
F 0 "#PWR07" H 1150 6750 50  0001 C CNN
F 1 "GND" H 1150 6850 50  0000 C CNN
F 2 "" H 1150 7000 50  0001 C CNN
F 3 "" H 1150 7000 50  0001 C CNN
	1    1150 7000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR08
U 1 1 5ACC0E2E
P 1150 6800
F 0 "#PWR08" H 1150 6650 50  0001 C CNN
F 1 "+5V" H 1150 6940 50  0000 C CNN
F 2 "" H 1150 6800 50  0001 C CNN
F 3 "" H 1150 6800 50  0001 C CNN
	1    1150 6800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR09
U 1 1 5ACC0E34
P 950 6900
F 0 "#PWR09" H 950 6750 50  0001 C CNN
F 1 "+3.3V" H 950 7040 50  0000 C CNN
F 2 "" H 950 6900 50  0001 C CNN
F 3 "" H 950 6900 50  0001 C CNN
	1    950  6900
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR010
U 1 1 5ACCCA3A
P 4100 5700
F 0 "#PWR010" H 4100 5550 50  0001 C CNN
F 1 "+3.3V" H 4100 5840 50  0000 C CNN
F 2 "" H 4100 5700 50  0001 C CNN
F 3 "" H 4100 5700 50  0001 C CNN
	1    4100 5700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 5ACCD4EB
P 5900 5500
F 0 "#PWR011" H 5900 5350 50  0001 C CNN
F 1 "+3.3V" H 5900 5640 50  0000 C CNN
F 2 "" H 5900 5500 50  0001 C CNN
F 3 "" H 5900 5500 50  0001 C CNN
	1    5900 5500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5ACCD775
P 5700 5500
F 0 "#PWR012" H 5700 5250 50  0001 C CNN
F 1 "GND" H 5700 5350 50  0000 C CNN
F 2 "" H 5700 5500 50  0001 C CNN
F 3 "" H 5700 5500 50  0001 C CNN
	1    5700 5500
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR013
U 1 1 5ACD7342
P 5100 4150
F 0 "#PWR013" H 5100 4000 50  0001 C CNN
F 1 "+5V" H 5100 4290 50  0000 C CNN
F 2 "" H 5100 4150 50  0001 C CNN
F 3 "" H 5100 4150 50  0001 C CNN
	1    5100 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5ACD7452
P 5100 4250
F 0 "#PWR014" H 5100 4000 50  0001 C CNN
F 1 "GND" H 5100 4100 50  0000 C CNN
F 2 "" H 5100 4250 50  0001 C CNN
F 3 "" H 5100 4250 50  0001 C CNN
	1    5100 4250
	1    0    0    -1  
$EndComp
Text GLabel 5050 3900 2    60   Input ~ 0
Servo_SPD
Wire Wire Line
	3050 1200 3200 1200
Wire Wire Line
	4100 5700 4300 5700
Wire Wire Line
	4300 5800 4250 5800
Wire Wire Line
	4250 5800 4250 5700
Connection ~ 4250 5700
Wire Wire Line
	3050 1300 3050 1400
Wire Wire Line
	3050 1400 3550 1400
Wire Wire Line
	3550 1200 3500 1200
Wire Wire Line
	1150 3350 1300 3350
Wire Wire Line
	950  3450 1300 3450
Wire Wire Line
	1150 3550 1300 3550
Wire Wire Line
	1150 5150 1300 5150
Wire Wire Line
	950  5250 1300 5250
Wire Wire Line
	1150 5350 1300 5350
Wire Wire Line
	1150 6800 1300 6800
Wire Wire Line
	950  6900 1300 6900
Wire Wire Line
	1150 7000 1300 7000
Wire Wire Line
	1250 6450 1300 6450
Wire Wire Line
	1300 6550 1250 6550
Wire Wire Line
	2550 6350 2500 6350
Wire Wire Line
	2550 6450 2500 6450
Wire Wire Line
	2550 6550 2500 6550
Wire Wire Line
	2500 6650 2550 6650
Wire Wire Line
	2550 6800 2500 6800
Wire Wire Line
	2500 6900 2550 6900
Wire Wire Line
	2550 7000 2500 7000
Wire Wire Line
	2500 7100 2550 7100
Wire Wire Line
	2550 4700 2500 4700
Wire Wire Line
	2500 4800 2550 4800
Wire Wire Line
	2550 4900 2500 4900
Wire Wire Line
	2500 5000 2550 5000
Wire Wire Line
	2550 5150 2500 5150
Wire Wire Line
	2500 5250 2550 5250
Wire Wire Line
	2550 5350 2500 5350
Wire Wire Line
	2500 5450 2550 5450
Wire Wire Line
	2550 2900 2500 2900
Wire Wire Line
	2500 3000 2550 3000
Wire Wire Line
	2550 3100 2500 3100
Wire Wire Line
	2500 3200 2550 3200
Wire Wire Line
	2550 3350 2500 3350
Wire Wire Line
	2500 3450 2550 3450
Wire Wire Line
	2550 3550 2500 3550
Wire Wire Line
	2500 3650 2550 3650
Wire Wire Line
	1250 3000 1300 3000
Wire Wire Line
	1300 3100 1250 3100
Wire Wire Line
	1250 4800 1300 4800
Wire Wire Line
	1250 4900 1300 4900
Wire Wire Line
	4750 3000 5000 3000
Wire Wire Line
	4800 3100 4750 3100
Wire Wire Line
	4750 3200 4800 3200
Wire Wire Line
	4800 3300 4750 3300
Wire Wire Line
	4800 2450 4750 2450
Wire Wire Line
	4750 2550 4800 2550
Wire Wire Line
	5700 5500 5600 5500
Wire Wire Line
	5900 5500 5900 5600
Wire Wire Line
	5900 5600 5600 5600
Wire Wire Line
	5650 5700 5600 5700
Wire Wire Line
	5600 5800 5650 5800
Wire Wire Line
	5650 5800 5650 5900
Wire Wire Line
	6000 5700 5950 5700
Wire Wire Line
	6000 5900 5950 5900
Wire Wire Line
	5050 3900 5000 3900
Wire Wire Line
	5000 3900 5000 4050
Wire Wire Line
	5000 4050 4800 4050
Wire Wire Line
	4800 4150 5100 4150
Wire Wire Line
	5100 4250 4800 4250
$Comp
L +3.3V #PWR015
U 1 1 5ACE6F1B
P 6900 1200
F 0 "#PWR015" H 6900 1050 50  0001 C CNN
F 1 "+3.3V" H 6900 1340 50  0000 C CNN
F 2 "" H 6900 1200 50  0001 C CNN
F 3 "" H 6900 1200 50  0001 C CNN
	1    6900 1200
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR016
U 1 1 5ACECB70
P 6650 1200
F 0 "#PWR016" H 6650 1050 50  0001 C CNN
F 1 "+5V" H 6650 1340 50  0000 C CNN
F 2 "" H 6650 1200 50  0001 C CNN
F 3 "" H 6650 1200 50  0001 C CNN
	1    6650 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1400 6650 1200
Wire Wire Line
	6900 1200 6750 1200
Wire Wire Line
	6750 1200 6750 1400
$Comp
L +5V #PWR017
U 1 1 5ACEE5B5
P 5000 3000
F 0 "#PWR017" H 5000 2850 50  0001 C CNN
F 1 "+5V" H 5000 3140 50  0000 C CNN
F 2 "" H 5000 3000 50  0001 C CNN
F 3 "" H 5000 3000 50  0001 C CNN
	1    5000 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5ACEEEF3
P 5350 3050
F 0 "#PWR018" H 5350 2800 50  0001 C CNN
F 1 "GND" H 5350 2900 50  0000 C CNN
F 2 "" H 5350 3050 50  0001 C CNN
F 3 "" H 5350 3050 50  0001 C CNN
	1    5350 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3050 4800 3050
Wire Wire Line
	4800 3050 4800 3100
$Comp
L GND #PWR019
U 1 1 5ACF22E4
P 3500 1550
F 0 "#PWR019" H 3500 1300 50  0001 C CNN
F 1 "GND" H 3500 1400 50  0000 C CNN
F 2 "" H 3500 1550 50  0001 C CNN
F 3 "" H 3500 1550 50  0001 C CNN
	1    3500 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1550 3500 1400
Connection ~ 3500 1400
Wire Wire Line
	3100 1050 3100 1200
Connection ~ 3100 1200
Wire Wire Line
	1550 1300 1550 1200
$Comp
L PWR_FLAG #FLG020
U 1 1 5AD0C3B9
P 1550 1300
F 0 "#FLG020" H 1550 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 1550 1450 50  0000 C CNN
F 2 "" H 1550 1300 50  0001 C CNN
F 3 "" H 1550 1300 50  0001 C CNN
	1    1550 1300
	-1   0    0    1   
$EndComp
$Comp
L +12V #PWR021
U 1 1 5AD0C6D0
P 3100 1050
F 0 "#PWR021" H 3100 900 50  0001 C CNN
F 1 "+12V" H 3100 1190 50  0000 C CNN
F 2 "" H 3100 1050 50  0001 C CNN
F 3 "" H 3100 1050 50  0001 C CNN
	1    3100 1050
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR022
U 1 1 5AD0DF58
P 1550 1200
F 0 "#PWR022" H 1550 1050 50  0001 C CNN
F 1 "+12V" H 1550 1340 50  0000 C CNN
F 2 "" H 1550 1200 50  0001 C CNN
F 3 "" H 1550 1200 50  0001 C CNN
	1    1550 1200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5AD14C85
P 7400 1150
F 0 "#PWR023" H 7400 900 50  0001 C CNN
F 1 "GND" H 7400 1000 50  0000 C CNN
F 2 "" H 7400 1150 50  0001 C CNN
F 3 "" H 7400 1150 50  0001 C CNN
	1    7400 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 1150 7250 1150
Wire Wire Line
	7250 1150 7250 1400
$Comp
L Arduino_Due_Shield ARD1
U 1 1 5AC90C45
P 8500 2700
F 0 "ARD1" V 8600 2700 60  0000 C CNN
F 1 "Arduino_Due_Shield" V 8400 2700 60  0000 C CNN
F 2 "MotorCapeComponents:Arduino_Due_Shield" H 9200 5450 60  0001 C CNN
F 3 "" H 9200 5450 60  0001 C CNN
	1    8500 2700
	0    1    1    0   
$EndComp
$EndSCHEMATC
