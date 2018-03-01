EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:Pi_cape_devices
LIBS:PI_Cape-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X05 J5
U 1 1 5A963D10
P 3900 1800
F 0 "J5" H 3900 2100 50  0000 C CNN
F 1 "Dist_Sensor_FR" V 4000 1800 50  0000 C CNN
F 2 "" H 3900 1800 50  0001 C CNN
F 3 "" H 3900 1800 50  0001 C CNN
	1    3900 1800
	0    -1   1    0   
$EndComp
$Comp
L CONN_01X05 J7
U 1 1 5A964137
P 4400 2300
F 0 "J7" H 4400 2600 50  0000 C CNN
F 1 "Dist_Sensor_RF" V 4500 2300 50  0000 C CNN
F 2 "" H 4400 2300 50  0001 C CNN
F 3 "" H 4400 2300 50  0001 C CNN
	1    4400 2300
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X05 J3
U 1 1 5A9645AF
P 3200 1800
F 0 "J3" H 3200 2100 50  0000 C CNN
F 1 "Dist_Sensor_FL" V 3300 1800 50  0000 C CNN
F 2 "" H 3200 1800 50  0001 C CNN
F 3 "" H 3200 1800 50  0001 C CNN
	1    3200 1800
	0    -1   1    0   
$EndComp
$Comp
L CONN_01X05 J1
U 1 1 5A9645EE
P 2700 2300
F 0 "J1" H 2700 2600 50  0000 C CNN
F 1 "Dist_Sensor_LF" V 2800 2300 50  0000 C CNN
F 2 "" H 2700 2300 50  0001 C CNN
F 3 "" H 2700 2300 50  0001 C CNN
	1    2700 2300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X05 J6
U 1 1 5A964719
P 3900 3500
F 0 "J6" H 3900 3800 50  0000 C CNN
F 1 "Dist_Sensor_BR" V 4000 3500 50  0000 C CNN
F 2 "" H 3900 3500 50  0001 C CNN
F 3 "" H 3900 3500 50  0001 C CNN
	1    3900 3500
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X05 J4
U 1 1 5A964776
P 3200 3500
F 0 "J4" H 3200 3800 50  0000 C CNN
F 1 "Dist_Sensor_BL" V 3300 3500 50  0000 C CNN
F 2 "" H 3200 3500 50  0001 C CNN
F 3 "" H 3200 3500 50  0001 C CNN
	1    3200 3500
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X05 J8
U 1 1 5A9647B4
P 4400 3000
F 0 "J8" H 4400 3300 50  0000 C CNN
F 1 "Dist_Sensor_RB" V 4500 3000 50  0000 C CNN
F 2 "" H 4400 3000 50  0001 C CNN
F 3 "" H 4400 3000 50  0001 C CNN
	1    4400 3000
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X05 J2
U 1 1 5A9647F9
P 2700 3000
F 0 "J2" H 2700 3300 50  0000 C CNN
F 1 "Dist_Sensor_LB" V 2800 3000 50  0000 C CNN
F 2 "" H 2700 3000 50  0001 C CNN
F 3 "" H 2700 3000 50  0001 C CNN
	1    2700 3000
	1    0    0    -1  
$EndComp
Text GLabel 3000 1600 1    60   Input ~ 0
Vin
Text GLabel 3100 1600 1    60   Input ~ 0
GND
Text GLabel 3200 1600 1    60   Input ~ 0
SHDN_FL
Text GLabel 3300 1600 1    60   Input ~ 0
SCL
Text GLabel 3400 1600 1    60   Input ~ 0
SDA
Text GLabel 3700 1600 1    60   Input ~ 0
Vin
Text GLabel 3800 1600 1    60   Input ~ 0
GND
Text GLabel 3900 1600 1    60   Input ~ 0
SHDN_FR
Text GLabel 4000 1600 1    60   Input ~ 0
SCL
Text GLabel 4100 1600 1    60   Input ~ 0
SDA
Text GLabel 4600 2100 2    60   Input ~ 0
Vin
Text GLabel 4600 2200 2    60   Input ~ 0
GND
Text GLabel 4600 2300 2    60   Input ~ 0
SHDN_RF
Text GLabel 4600 2400 2    60   Input ~ 0
SCL
Text GLabel 4600 2500 2    60   Input ~ 0
SDA
Text GLabel 2500 2100 0    60   Input ~ 0
Vin
Text GLabel 2500 2200 0    60   Input ~ 0
GND
Text GLabel 2500 2300 0    60   Input ~ 0
SHDN_LF
Text GLabel 2500 2400 0    60   Input ~ 0
SCL
Text GLabel 2500 2500 0    60   Input ~ 0
SDA
Text GLabel 2500 2800 0    60   Input ~ 0
Vin
Text GLabel 2500 2900 0    60   Input ~ 0
GND
Text GLabel 2500 3000 0    60   Input ~ 0
SHDN_LB
Text GLabel 2500 3100 0    60   Input ~ 0
SCL
Text GLabel 2500 3200 0    60   Input ~ 0
SDA
Text GLabel 4600 2800 2    60   Input ~ 0
Vin
Text GLabel 4600 2900 2    60   Input ~ 0
GND
Text GLabel 4600 3000 2    60   Input ~ 0
SHDN_RB
Text GLabel 4600 3100 2    60   Input ~ 0
SCL
Text GLabel 4600 3200 2    60   Input ~ 0
SDA
Text GLabel 3700 3700 3    60   Input ~ 0
Vin
Text GLabel 3800 3700 3    60   Input ~ 0
GND
Text GLabel 3900 3700 3    60   Input ~ 0
SHDN_BR
Text GLabel 4000 3700 3    60   Input ~ 0
SCL
Text GLabel 4100 3700 3    60   Input ~ 0
SDA
Text GLabel 3000 3700 3    60   Input ~ 0
Vin
Text GLabel 3100 3700 3    60   Input ~ 0
GND
Text GLabel 3200 3700 3    60   Input ~ 0
SHDN_BL
Text GLabel 3300 3700 3    60   Input ~ 0
SCL
Text GLabel 3400 3700 3    60   Input ~ 0
SDA
$Comp
L Raspberry_Pi_2_3 U1
U 1 1 5A988C03
P 6850 2400
F 0 "U1" H 7550 1150 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 6450 3300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x20" H 7850 3650 50  0001 C CNN
F 3 "" H 6900 2250 50  0001 C CNN
	1    6850 2400
	1    0    0    -1  
$EndComp
Text GLabel 7750 1600 2    60   Input ~ 0
SCL
Text GLabel 7750 1500 2    60   Input ~ 0
SDA
Text GLabel 950  1500 2    60   Input ~ 0
GND
Wire Wire Line
	850  1400 850  1600
$Comp
L Earth #PWR2
U 1 1 5A989305
P 850 1600
F 0 "#PWR2" H 850 1350 50  0001 C CNN
F 1 "Earth" H 850 1450 50  0001 C CNN
F 2 "" H 850 1600 50  0000 C CNN
F 3 "" H 850 1600 50  0000 C CNN
	1    850  1600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR1
U 1 1 5A98937C
P 850 750
F 0 "#PWR1" H 850 600 50  0001 C CNN
F 1 "+3.3V" H 850 890 50  0000 C CNN
F 2 "" H 850 750 50  0000 C CNN
F 3 "" H 850 750 50  0000 C CNN
	1    850  750 
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 5A9893C7
P 850 1400
F 0 "#FLG2" H 850 1495 50  0001 C CNN
F 1 "PWR_FLAG" H 850 1580 50  0000 C CNN
F 2 "" H 850 1400 50  0000 C CNN
F 3 "" H 850 1400 50  0000 C CNN
	1    850  1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3100 8600 3100
Wire Wire Line
	7750 3200 8600 3200
Text GLabel 7750 1700 2    60   Input ~ 0
SHDN_FL
Text GLabel 5950 1800 0    60   Input ~ 0
SHDN_FR
Text GLabel 5950 1900 0    60   Input ~ 0
SHDN_RF
Text GLabel 5950 2800 0    60   Input ~ 0
SHDN_RB
Text GLabel 5950 2300 0    60   Input ~ 0
SHDN_BR
Text GLabel 5950 2400 0    60   Input ~ 0
SHDN_BL
Text GLabel 5950 2500 0    60   Input ~ 0
SHDN_LB
Text GLabel 5950 2600 0    60   Input ~ 0
SHDN_LF
Text GLabel 950  850  2    60   Input ~ 0
Vin
Wire Wire Line
	950  1500 850  1500
Connection ~ 850  1500
$Comp
L PWR_FLAG #FLG1
U 1 1 5A98A6CF
P 850 950
F 0 "#FLG1" H 850 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 850 1130 50  0000 C CNN
F 2 "" H 850 950 50  0000 C CNN
F 3 "" H 850 950 50  0000 C CNN
	1    850  950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	850  750  850  950 
Wire Wire Line
	950  850  850  850 
Connection ~ 850  850 
$Comp
L +3.3V #PWR4
U 1 1 5A98C737
P 6950 1000
F 0 "#PWR4" H 6950 850 50  0001 C CNN
F 1 "+3.3V" H 6950 1140 50  0000 C CNN
F 2 "" H 6950 1000 50  0000 C CNN
F 3 "" H 6950 1000 50  0000 C CNN
	1    6950 1000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR6
U 1 1 5A98C981
P 8700 1700
F 0 "#PWR6" H 8700 1550 50  0001 C CNN
F 1 "+3.3V" H 8700 1840 50  0000 C CNN
F 2 "" H 8700 1700 50  0000 C CNN
F 3 "" H 8700 1700 50  0000 C CNN
	1    8700 1700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8700 1700 8950 1700
$Comp
L Earth #PWR3
U 1 1 5A98CCDE
P 6450 3800
F 0 "#PWR3" H 6450 3550 50  0001 C CNN
F 1 "Earth" H 6450 3650 50  0001 C CNN
F 2 "" H 6450 3800 50  0000 C CNN
F 3 "" H 6450 3800 50  0000 C CNN
	1    6450 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3700 6450 3800
$Comp
L Earth #PWR5
U 1 1 5A98CF68
P 8700 1600
F 0 "#PWR5" H 8700 1350 50  0001 C CNN
F 1 "Earth" H 8700 1450 50  0001 C CNN
F 2 "" H 8700 1600 50  0000 C CNN
F 3 "" H 8700 1600 50  0000 C CNN
	1    8700 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 1600 8950 1600
Text GLabel 8950 1800 0    60   Input ~ 0
MOSI
Text GLabel 8950 1900 0    60   Input ~ 0
SPI_SCL
Text GLabel 7750 2600 2    60   Input ~ 0
SPI_SCL
Text GLabel 7750 2500 2    60   Input ~ 0
MOSI
Text GLabel 7750 2400 2    60   Input ~ 0
MISO
Text GLabel 9750 2050 2    60   Input ~ 0
MISO
Text GLabel 9750 2150 2    60   Input ~ 0
MISO
Text GLabel 9750 1850 2    60   Input ~ 0
CS_M
Text GLabel 9750 1950 2    60   Input ~ 0
CS_AG
Text GLabel 7750 2200 2    60   Input ~ 0
CS_M
Text GLabel 7750 2300 2    60   Input ~ 0
CS_AG
NoConn ~ 9750 1350
NoConn ~ 9750 1450
NoConn ~ 9750 1550
NoConn ~ 9750 1650
NoConn ~ 9750 1750
Wire Wire Line
	6550 3700 6550 3750
Wire Wire Line
	6450 3750 7150 3750
Wire Wire Line
	7150 3750 7150 3700
Wire Wire Line
	7050 3700 7050 3750
Connection ~ 7050 3750
Wire Wire Line
	6950 3700 6950 3750
Connection ~ 6950 3750
Wire Wire Line
	6850 3700 6850 3750
Connection ~ 6850 3750
Wire Wire Line
	6750 3700 6750 3750
Connection ~ 6750 3750
Wire Wire Line
	6650 3700 6650 3750
Connection ~ 6650 3750
Connection ~ 6450 3750
Connection ~ 6550 3750
Wire Wire Line
	6950 1000 6950 1100
Wire Wire Line
	7050 1100 7050 1050
Wire Wire Line
	7050 1050 6950 1050
Connection ~ 6950 1050
NoConn ~ 6750 1100
$Comp
L IMU_LSM9DS1 IMU?
U 1 1 5A991F3D
P 9350 1750
F 0 "IMU?" H 9300 1250 50  0000 L CNN
F 1 "IMU_LSM9DS1" H 9100 2300 50  0000 L TNN
F 2 "" V 9400 1400 50  0000 L CNN
F 3 "" H 9350 1600 50  0000 C CNN
	1    9350 1750
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Interface P?
U 1 1 5A9921FD
P 8950 3050
F 0 "P?" H 8950 3300 50  0000 C CNN
F 1 "Arduino_Interface" V 9050 3050 50  0000 C CNN
F 2 "" H 8950 3050 50  0000 C CNN
F 3 "" H 8950 3050 50  0000 C CNN
	1    8950 3050
	1    0    0    -1  
$EndComp
$Comp
L Earth #PWR?
U 1 1 5A9924E9
P 8600 3000
F 0 "#PWR?" H 8600 2750 50  0001 C CNN
F 1 "Earth" H 8600 2850 50  0001 C CNN
F 2 "" H 8600 3000 50  0000 C CNN
F 3 "" H 8600 3000 50  0000 C CNN
	1    8600 3000
	0    1    1    0   
$EndComp
Text GLabel 8600 2900 0    60   Input ~ 0
5V_PWR_IN
Text GLabel 6650 1100 1    60   Input ~ 0
5V_PWR_IN
$EndSCHEMATC
