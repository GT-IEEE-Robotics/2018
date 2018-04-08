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
Sheet 2 4
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
L DualMotorController_Signal J4
U 1 1 5AC8852E
P 3500 5350
AR Path="/5AC8802A/5AC8852E" Ref="J4"  Part="1" 
AR Path="/5ACA5F87/5AC8852E" Ref="J?"  Part="1" 
AR Path="/5ACB9F03/5AC8852E" Ref="J10"  Part="1" 
AR Path="/5ACC6682/5AC8852E" Ref="J16"  Part="1" 
F 0 "J4" H 3500 5700 50  0000 C CNN
F 1 "DualMotorController_SIG" V 3300 5400 50  0000 C CNN
F 2 "MotorCapeComponents:Pin_Header_Latched_1x05" H 3150 5350 50  0001 C CNN
F 3 "" H 3150 5350 50  0001 C CNN
	1    3500 5350
	0    -1   -1   0   
$EndComp
Text HLabel 3400 1700 3    60   Input ~ 0
Motor_PWR
Text HLabel 3500 1700 3    60   Input ~ 0
Motor_GND
Text HLabel 3650 5100 1    60   Input ~ 0
GND
Text HLabel 4250 2150 0    60   Input ~ 0
GND
Text HLabel 2700 2150 2    60   Input ~ 0
GND
Text HLabel 2700 2250 2    60   Input ~ 0
5V_PWR
Text HLabel 3250 5100 1    60   Input ~ 0
M1_DIR
Text HLabel 3350 5100 1    60   Input ~ 0
M1_SPD
Text HLabel 3550 5100 1    60   Input ~ 0
M2_SPD
Text HLabel 3450 5100 1    60   Input ~ 0
M2_DIR
$Comp
L DualMotorController_Power J2
U 1 1 5AC89C0C
P 3450 1450
AR Path="/5AC8802A/5AC89C0C" Ref="J2"  Part="1" 
AR Path="/5ACA5F87/5AC89C0C" Ref="J?"  Part="1" 
AR Path="/5ACB9F03/5AC89C0C" Ref="J8"  Part="1" 
AR Path="/5ACC6682/5AC89C0C" Ref="J14"  Part="1" 
F 0 "J2" H 3450 1800 50  0000 C CNN
F 1 "DualMotorController_PWR" V 3650 1450 50  0000 C CNN
F 2 "Connectors_Phoenix:PhoenixContact_MSTBA-G_06x5.08mm_Angled" H 3350 1450 50  0001 C CNN
F 3 "" H 3350 1450 50  0001 C CNN
	1    3450 1450
	0    -1   -1   0   
$EndComp
$Comp
L MotorConnector J1
U 1 1 5AC89F1B
P 2350 2200
AR Path="/5AC8802A/5AC89F1B" Ref="J1"  Part="1" 
AR Path="/5ACA5F87/5AC89F1B" Ref="J?"  Part="1" 
AR Path="/5ACB9F03/5AC89F1B" Ref="J6"  Part="1" 
AR Path="/5ACC6682/5AC89F1B" Ref="J13"  Part="1" 
F 0 "J1" H 2350 2550 50  0000 C CNN
F 1 "Motor1" V 2700 2200 50  0000 C CNN
F 2 "MotorCapeComponents:Pin_Header_Latched_1x06" H 2150 2200 50  0001 C CNN
F 3 "" H 2150 2200 50  0001 C CNN
	1    2350 2200
	-1   0    0    -1  
$EndComp
$Comp
L MotorConnector J5
U 1 1 5AC89F69
P 4600 2200
AR Path="/5AC8802A/5AC89F69" Ref="J5"  Part="1" 
AR Path="/5ACA5F87/5AC89F69" Ref="J?"  Part="1" 
AR Path="/5ACB9F03/5AC89F69" Ref="J12"  Part="1" 
AR Path="/5ACC6682/5AC89F69" Ref="J17"  Part="1" 
F 0 "J5" H 4600 2550 50  0000 C CNN
F 1 "Motor2" V 4950 2200 50  0000 C CNN
F 2 "MotorCapeComponents:Pin_Header_Latched_1x06" H 4400 2200 50  0001 C CNN
F 3 "" H 4400 2200 50  0001 C CNN
	1    4600 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1700 3600 1950
Wire Wire Line
	3600 1950 4250 1950
Text HLabel 4250 2250 0    60   Input ~ 0
5V_PWR
Text HLabel 3200 4050 3    60   Input ~ 0
M1_ENC_A
Text HLabel 3300 4050 3    60   Input ~ 0
M1_ENC_B
Text HLabel 3600 4050 3    60   Input ~ 0
M2_ENC_A
Text HLabel 3700 4050 3    60   Input ~ 0
M2_ENC_B
Text HLabel 3400 2750 1    60   Input ~ 0
5V_PWR
Text HLabel 3500 4050 3    60   Input ~ 0
GND
Text HLabel 3500 2750 1    60   Input ~ 0
GND
Text HLabel 3400 4050 3    60   Input ~ 0
3v3_PWR
Wire Wire Line
	3200 2750 3200 2350
Wire Wire Line
	3200 2350 2700 2350
Wire Wire Line
	2700 2450 3300 2450
Wire Wire Line
	3300 2450 3300 2750
Wire Wire Line
	3600 2750 3600 2350
Wire Wire Line
	3600 2350 4250 2350
Wire Wire Line
	3700 2750 3700 2450
Wire Wire Line
	3700 2450 4250 2450
$Comp
L SPARKFUN_LOGIC_LEVEL_CONVERTER B?
U 1 1 5AC8C87A
P 3500 3400
AR Path="/5AC8C87A" Ref="B?"  Part="1" 
AR Path="/5AC8802A/5AC8C87A" Ref="B1"  Part="1" 
AR Path="/5ACC6682/5AC8C87A" Ref="B3"  Part="1" 
AR Path="/5ACB9F03/5AC8C87A" Ref="B2"  Part="1" 
F 0 "B1" H 2950 3850 45  0000 L BNN
F 1 "SPARKFUN_LOGIC_LEVEL_CONVERTER" H 2950 3000 45  0000 L BNN
F 2 "Sparkfun_Boards:SPARKFUN_LOGIC_LEVEL_CONVERTER" H 3500 3850 20  0001 C CNN
F 3 "" H 3500 3400 60  0001 C CNN
F 4 "XXX-00000" H 3500 3900 60  0000 C CNN "Field4"
	1    3500 3400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3300 1700 3300 1950
Wire Wire Line
	3300 1950 2700 1950
Text HLabel 2700 2050 2    60   Input ~ 0
Motor_GND
Text HLabel 3200 1700 0    60   Input ~ 0
Motor_GND
Text HLabel 3700 1700 2    60   Input ~ 0
Motor_GND
Text HLabel 4250 2050 0    60   Input ~ 0
Motor_GND
$EndSCHEMATC
