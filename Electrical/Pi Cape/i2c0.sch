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
Sheet 3 11
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
L CONN_01X05 J?
U 1 1 5AAB57E4
P 2850 1350
AR Path="/5AAB5523/5AAB57E4" Ref="J?"  Part="1" 
AR Path="/5AAB7920/5AAB6396/5AAB57E4" Ref="J1"  Part="1" 
AR Path="/5AAB7920/5AAB6799/5AAB57E4" Ref="J2"  Part="1" 
AR Path="/5AAB7920/5AAB6BB2/5AAB57E4" Ref="J3"  Part="1" 
AR Path="/5AAB7920/5AAB6BB7/5AAB57E4" Ref="J4"  Part="1" 
AR Path="/5AAB9EF4/5AAB6396/5AAB57E4" Ref="J5"  Part="1" 
AR Path="/5AAB9EF4/5AAB6799/5AAB57E4" Ref="J6"  Part="1" 
AR Path="/5AAB9EF4/5AAB6BB2/5AAB57E4" Ref="J7"  Part="1" 
AR Path="/5AAB9EF4/5AAB6BB7/5AAB57E4" Ref="J8"  Part="1" 
F 0 "J7" H 2850 1650 50  0000 C CNN
F 1 "Dist_Sensor" V 2950 1350 50  0000 C CNN
F 2 "Pi Cape Footprints:Pin_Header_Latched_1x05" H 2850 1350 50  0001 C CNN
F 3 "" H 2850 1350 50  0001 C CNN
	1    2850 1350
	0    -1   -1   0   
$EndComp
Text HLabel 2850 1550 3    60   Input ~ 0
~EN~
Text HLabel 2950 1550 3    60   Input ~ 0
SCL
Text HLabel 3050 1550 3    60   Input ~ 0
SDA
Text HLabel 2650 1550 3    60   Input ~ 0
Vin
Text HLabel 2750 1550 3    60   Input ~ 0
Gnd
$EndSCHEMATC
