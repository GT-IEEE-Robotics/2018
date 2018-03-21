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
Sheet 1 11
Title "Pi_Cape"
Date ""
Rev ""
Comp "Gatech IEEE Hardware Team"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Raspberry_Pi_2_3 U1
U 1 1 5A988C03
P 7000 3550
F 0 "U1" H 7700 2300 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 6600 4450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x20" H 8000 4800 50  0001 C CNN
F 3 "" H 7050 3400 50  0001 C CNN
	1    7000 3550
	1    0    0    -1  
$EndComp
Text GLabel 7900 2750 2    60   Input ~ 0
I2C1_SCL
Text GLabel 7900 2650 2    60   Input ~ 0
I2C1_SDA
Text GLabel 2600 3900 2    60   Input ~ 0
GND
Wire Wire Line
	2500 3800 2500 4000
$Comp
L Earth #PWR01
U 1 1 5A989305
P 2500 4000
F 0 "#PWR01" H 2500 3750 50  0001 C CNN
F 1 "Earth" H 2500 3850 50  0001 C CNN
F 2 "" H 2500 4000 50  0000 C CNN
F 3 "" H 2500 4000 50  0000 C CNN
	1    2500 4000
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 5A9893C7
P 2500 3800
F 0 "#FLG02" H 2500 3895 50  0001 C CNN
F 1 "PWR_FLAG" H 2500 3980 50  0000 C CNN
F 2 "" H 2500 3800 50  0000 C CNN
F 3 "" H 2500 3800 50  0000 C CNN
	1    2500 3800
	1    0    0    -1  
$EndComp
Text GLabel 7100 2250 1    60   Input ~ 0
Vin
Wire Wire Line
	2200 3900 2600 3900
Connection ~ 2500 3900
$Comp
L PWR_FLAG #FLG03
U 1 1 5A98A6CF
P 2500 3350
F 0 "#FLG03" H 2500 3445 50  0001 C CNN
F 1 "PWR_FLAG" H 2500 3530 50  0000 C CNN
F 2 "" H 2500 3350 50  0000 C CNN
F 3 "" H 2500 3350 50  0000 C CNN
	1    2500 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2500 2900 2500 3350
NoConn ~ 6900 2250
Text GLabel 6800 2250 1    60   Input ~ 0
5V_PWR_IN
NoConn ~ 6100 2850
NoConn ~ 6100 3150
NoConn ~ 6100 3250
NoConn ~ 6100 3350
NoConn ~ 6100 3850
NoConn ~ 7900 3050
NoConn ~ 7900 3150
NoConn ~ 7900 3950
NoConn ~ 7200 2250
NoConn ~ 6700 4850
NoConn ~ 6800 4850
NoConn ~ 6900 4850
NoConn ~ 7000 4850
NoConn ~ 7100 4850
NoConn ~ 7200 4850
NoConn ~ 7300 4850
Text GLabel 2600 3200 2    60   Input ~ 0
5V_PWR_IN
$Comp
L +5V #PWR04
U 1 1 5AAB4385
P 2500 2900
F 0 "#PWR04" H 2500 2750 50  0001 C CNN
F 1 "+5V" H 2500 3040 50  0000 C CNN
F 2 "" H 2500 2900 50  0000 C CNN
F 3 "" H 2500 2900 50  0000 C CNN
	1    2500 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 3200 2600 3200
Connection ~ 2500 3200
Text GLabel 6100 4250 0    60   Input ~ 0
I2C0_SDA
Text GLabel 6100 4350 0    60   Input ~ 0
I2C0_SCL
$Sheet
S 3950 2950 600  500 
U 5AAB7920
F0 "I2C0_Front&Back_Sensors" 60
F1 "i2c0_sensors.sch" 60
F2 "~EN_2~" I R 4550 3250 60 
F3 "~EN_3~" I R 4550 3350 60 
F4 "~EN_0~" I R 4550 3050 60 
F5 "~EN_1~" I R 4550 3150 60 
F6 "SDA" I L 3950 3050 60 
F7 "SCL" I L 3950 3150 60 
F8 "Vin" I L 3950 3250 60 
F9 "Gnd" I L 3950 3350 60 
$EndSheet
$Sheet
S 3950 3750 600  500 
U 5AAB9EF4
F0 "I2C1_Left&Right_Sensors" 60
F1 "i2c0_sensors.sch" 60
F2 "~EN_2~" I R 4550 4050 60 
F3 "~EN_3~" I R 4550 4150 60 
F4 "~EN_0~" I R 4550 3850 60 
F5 "~EN_1~" I R 4550 3950 60 
F6 "SDA" I L 3950 3850 60 
F7 "SCL" I L 3950 3950 60 
F8 "Vin" I L 3950 4050 60 
F9 "Gnd" I L 3950 4150 60 
$EndSheet
Text GLabel 3950 3050 0    60   Input ~ 0
I2C0_SDA
Text GLabel 3950 3150 0    60   Input ~ 0
I2C0_SCL
Text GLabel 3950 3950 0    60   Input ~ 0
I2C1_SCL
Text GLabel 3950 3850 0    60   Input ~ 0
I2C1_SDA
Text GLabel 4550 3250 2    60   Input ~ 0
nEN_BL
Text GLabel 4550 3150 2    60   Input ~ 0
nEN_FR
Text GLabel 4550 3350 2    60   Input ~ 0
nEN_BR
Text GLabel 4550 3050 2    60   Input ~ 0
nEN_FL
Text GLabel 4550 3850 2    60   Input ~ 0
nEN_LF
Text GLabel 4550 3950 2    60   Input ~ 0
nEN_LB
Text GLabel 4550 4050 2    60   Input ~ 0
nEN_RF
Text GLabel 4550 4150 2    60   Input ~ 0
nEN_RB
Text GLabel 7900 2850 2    60   Input ~ 0
nEN_FL
Text GLabel 6100 2950 0    60   Input ~ 0
nEN_FR
Text GLabel 6100 3050 0    60   Input ~ 0
nEN_BL
Text GLabel 6100 3450 0    60   Input ~ 0
nEN_BR
Text GLabel 6100 3550 0    60   Input ~ 0
nEN_LF
Text GLabel 6100 3650 0    60   Input ~ 0
nEN_LB
Text GLabel 6100 3750 0    60   Input ~ 0
nEN_RF
Text GLabel 6100 3950 0    60   Input ~ 0
nEN_RB
NoConn ~ 7900 3350
NoConn ~ 7900 3450
NoConn ~ 7900 3550
NoConn ~ 7900 3650
NoConn ~ 7900 3750
$Comp
L CONN_01X02 P2
U 1 1 5AABF366
P 2000 3350
F 0 "P2" H 2000 3500 50  0000 C CNN
F 1 "5V_PWR_FROM_REGULATOR" V 2100 3350 50  0000 C CNN
F 2 "Pi Cape Footprints:Pin_Header_Latched_1x02" H 2000 3350 50  0001 C CNN
F 3 "" H 2000 3350 50  0000 C CNN
	1    2000 3350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2200 3300 2200 3200
Wire Wire Line
	2200 3400 2200 3900
Text GLabel 3950 4050 0    60   Input ~ 0
Vin
Text GLabel 3950 3250 0    60   Input ~ 0
Vin
Text GLabel 6600 4850 3    60   Input ~ 0
GND
Text GLabel 3950 4150 0    60   Input ~ 0
GND
Text GLabel 3950 3350 0    60   Input ~ 0
GND
NoConn ~ 7900 4050
Wire Wire Line
	8300 4250 7900 4250
Wire Wire Line
	7900 4350 8300 4350
Text GLabel 8300 4150 0    60   Input ~ 0
GND
$Comp
L Arduino_Interface P1
U 1 1 5AB07671
P 8550 4250
F 0 "P1" H 8550 4450 50  0000 C CNN
F 1 "Arduino_Interface" V 8650 4250 50  0000 C CNN
F 2 "Pi Cape Footprints:Pin_Header_Latched_1x03" H 8550 4250 50  0001 C CNN
F 3 "" H 8550 4250 50  0000 C CNN
	1    8550 4250
	1    0    0    -1  
$EndComp
$Comp
L 7-segment_LED U2
U 1 1 5AB1C163
P 9250 3400
F 0 "U2" H 9250 2650 60  0000 C CNN
F 1 "7-segment_LED" H 9250 2800 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 9150 3200 60  0001 C CNN
F 3 "" H 9150 3200 60  0000 C CNN
	1    9250 3400
	0    -1   -1   0   
$EndComp
Text GLabel 9300 3200 0    60   Input ~ 0
GND
Text GLabel 9300 3350 0    60   Input ~ 0
5V_PWR_IN
Text GLabel 9300 3050 0    60   Input ~ 0
Vin
Text GLabel 9300 3650 0    60   Input ~ 0
I2C1_SDA
Text GLabel 9300 3500 0    60   Input ~ 0
I2C1_SCL
$EndSCHEMATC
