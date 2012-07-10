EESchema Schematic File Version 2  date 10/07/2012 11:17:02
LIBS:power
LIBS:device
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
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
LIBS:contrib
LIBS:valves
LIBS:Arduino
LIBS:arduino_shieldsNCL
LIBS:o_analog
LIBS:Shield FSK-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "10 jul 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1950 1950 2050 1950
Wire Wire Line
	3250 1850 3250 1950
Wire Wire Line
	3850 1450 3750 1450
Wire Wire Line
	6400 3000 6500 3000
Wire Wire Line
	2850 4200 2850 4000
Wire Wire Line
	2600 4550 2600 4650
Wire Wire Line
	2600 3650 2600 4050
Connection ~ 2600 3850
Wire Wire Line
	3100 3850 3100 3700
Wire Wire Line
	3100 3700 4600 3700
Wire Wire Line
	6300 3800 6400 3800
Wire Wire Line
	6650 4000 6450 4000
Wire Wire Line
	6450 4000 6450 4100
Wire Wire Line
	6450 4100 6300 4100
Connection ~ 3450 4350
Wire Wire Line
	3600 4350 3450 4350
Wire Wire Line
	4100 4350 4550 4350
Wire Wire Line
	4550 4350 4550 4200
Wire Wire Line
	4550 4200 4600 4200
Wire Wire Line
	4100 4150 4550 4150
Wire Wire Line
	4550 4150 4550 4100
Wire Wire Line
	4550 4100 4600 4100
Wire Wire Line
	4600 4000 4550 4000
Wire Wire Line
	4200 3850 4450 3850
Connection ~ 4450 3800
Wire Wire Line
	4450 3850 4450 3800
Wire Wire Line
	6450 3900 6300 3900
Wire Wire Line
	4400 3800 4600 3800
Wire Wire Line
	4600 3500 4350 3500
Wire Wire Line
	3400 3600 4600 3600
Wire Wire Line
	3800 3850 3700 3850
Wire Wire Line
	4600 3900 4150 3900
Wire Wire Line
	4150 3900 4150 4000
Wire Wire Line
	3600 4150 3450 4150
Wire Wire Line
	3450 4150 3450 4500
Wire Wire Line
	6600 4200 6300 4200
Wire Wire Line
	7050 4000 7200 4000
Wire Wire Line
	6900 3800 6900 3700
Wire Wire Line
	6900 3700 6300 3700
Wire Wire Line
	2850 4000 2600 4000
Connection ~ 2600 4000
Wire Wire Line
	2600 3050 2600 3150
Wire Wire Line
	2850 4600 2600 4600
Connection ~ 2600 4600
Wire Wire Line
	4500 2200 4400 2200
Wire Wire Line
	3250 3300 3250 3400
Wire Wire Line
	4500 2400 4400 2400
Wire Wire Line
	2750 1450 2650 1450
Wire Wire Line
	1950 1750 2050 1750
$Comp
L GND #PWR01
U 1 1 4FFBED7B
P 2050 1950
F 0 "#PWR01" H 2050 1950 30  0001 C CNN
F 1 "GND" H 2050 1880 30  0001 C CNN
	1    2050 1950
	0    -1   -1   0   
$EndComp
$Comp
L +BATT #PWR02
U 1 1 4FFBED73
P 2050 1750
F 0 "#PWR02" H 2050 1700 20  0001 C CNN
F 1 "+BATT" H 2050 1850 30  0000 C CNN
	1    2050 1750
	0    1    1    0   
$EndComp
$Comp
L CONN_2 P2
U 1 1 4FFBED61
P 1600 1850
F 0 "P2" V 1550 1850 40  0000 C CNN
F 1 "CONN_2" V 1650 1850 40  0000 C CNN
	1    1600 1850
	-1   0    0    1   
$EndComp
$Comp
L +BATT #PWR03
U 1 1 4FFBED15
P 2650 1450
F 0 "#PWR03" H 2650 1400 20  0001 C CNN
F 1 "+BATT" H 2650 1550 30  0000 C CNN
	1    2650 1450
	0    -1   -1   0   
$EndComp
$Comp
L +BATT #PWR04
U 1 1 4FFBED10
P 4400 2400
F 0 "#PWR04" H 4400 2350 20  0001 C CNN
F 1 "+BATT" H 4400 2500 30  0000 C CNN
	1    4400 2400
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR05
U 1 1 4FFBE854
P 3850 1450
F 0 "#PWR05" H 3850 1550 30  0001 C CNN
F 1 "VCC" H 3850 1550 30  0000 C CNN
	1    3850 1450
	0    1    1    0   
$EndComp
$Comp
L GND #PWR06
U 1 1 4FFBE773
P 3250 1950
F 0 "#PWR06" H 3250 1950 30  0001 C CNN
F 1 "GND" H 3250 1880 30  0001 C CNN
	1    3250 1950
	1    0    0    -1  
$EndComp
$Comp
L LM7810 U2
U 1 1 4FFBE6BF
P 3250 1550
F 0 "U2" H 3250 1800 60  0000 C CNN
F 1 "LM7810" H 3560 1300 60  0000 C CNN
	1    3250 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 4F6DEC1B
P 3250 3300
F 0 "#PWR07" H 3250 3300 30  0001 C CNN
F 1 "GND" H 3250 3230 30  0001 C CNN
	1    3250 3300
	-1   0    0    1   
$EndComp
$Comp
L BNC P1
U 1 1 4F6DEBDE
P 3250 3600
F 0 "P1" H 3260 3720 60  0000 C CNN
F 1 "BNC" V 3360 3540 40  0000 C CNN
	1    3250 3600
	-1   0    0    1   
$EndComp
$Comp
L C C4
U 1 1 4F6DEA2A
P 6850 4000
F 0 "C4" H 6900 4100 50  0000 L CNN
F 1 "C" H 6900 3900 50  0000 L CNN
	1    6850 4000
	0    1    1    0   
$EndComp
$Comp
L C C1
U 1 1 4F6DEA20
P 2850 4400
F 0 "C1" H 2900 4500 50  0000 L CNN
F 1 "C" H 2900 4300 50  0000 L CNN
	1    2850 4400
	1    0    0    -1  
$EndComp
Text Label 6500 3000 0    60   ~ 0
Entree serie
$Comp
L GND #PWR08
U 1 1 4F6B897D
P 4400 2200
F 0 "#PWR08" H 4400 2200 30  0001 C CNN
F 1 "GND" H 4400 2130 30  0001 C CNN
	1    4400 2200
	0    1    1    0   
$EndComp
$Comp
L ARDUINO_SHIELD SHIELD1
U 1 1 4F6B8878
P 5450 2300
F 0 "SHIELD1" H 5100 3250 60  0000 C CNN
F 1 "ARDUINO_SHIELD" H 5500 1350 60  0000 C CNN
	1    5450 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 4F5B8724
P 2600 4650
F 0 "#PWR09" H 2600 4650 30  0001 C CNN
F 1 "GND" H 2600 4580 30  0001 C CNN
	1    2600 4650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR010
U 1 1 4F5B8719
P 2600 3050
F 0 "#PWR010" H 2600 3150 30  0001 C CNN
F 1 "VCC" H 2600 3150 30  0000 C CNN
	1    2600 3050
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4F5B870F
P 2600 4300
F 0 "R2" V 2680 4300 50  0000 C CNN
F 1 "R" V 2600 4300 50  0000 C CNN
	1    2600 4300
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4F5B8708
P 2600 3400
F 0 "R1" V 2680 3400 50  0000 C CNN
F 1 "R" V 2600 3400 50  0000 C CNN
	1    2600 3400
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 4F5B867D
P 2850 3850
F 0 "RV1" H 2850 3750 50  0000 C CNN
F 1 "POT" H 2850 3850 50  0000 C CNN
	1    2850 3850
	-1   0    0    1   
$EndComp
NoConn ~ 6300 3500
NoConn ~ 6300 3600
$Comp
L R R5
U 1 1 4F5B7612
P 6650 3800
F 0 "R5" V 6730 3800 50  0000 C CNN
F 1 "R" V 6650 3800 50  0000 C CNN
	1    6650 3800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 4F5B75FB
P 7200 4000
F 0 "#PWR011" H 7200 4000 30  0001 C CNN
F 1 "GND" H 7200 3930 30  0001 C CNN
	1    7200 4000
	0    -1   -1   0   
$EndComp
NoConn ~ 6300 4000
Text Label 6600 4200 0    60   ~ 0
Entree serie
$Comp
L GND #PWR012
U 1 1 4F5B733F
P 3450 4500
F 0 "#PWR012" H 3450 4500 30  0001 C CNN
F 1 "GND" H 3450 4430 30  0001 C CNN
	1    3450 4500
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4F5B7320
P 3850 4350
F 0 "R4" V 3930 4350 50  0000 C CNN
F 1 "R" V 3850 4350 50  0000 C CNN
	1    3850 4350
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 4F5B7305
P 3850 4150
F 0 "R3" V 3930 4150 50  0000 C CNN
F 1 "R" V 3850 4150 50  0000 C CNN
	1    3850 4150
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 4F5B723C
P 4350 4000
F 0 "C3" H 4400 4100 50  0000 L CNN
F 1 "C" H 4400 3900 50  0000 L CNN
	1    4350 4000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR013
U 1 1 4F5B7223
P 3700 3850
F 0 "#PWR013" H 3700 3850 30  0001 C CNN
F 1 "GND" H 3700 3780 30  0001 C CNN
	1    3700 3850
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 4F5B720F
P 4000 3850
F 0 "C2" H 4050 3950 50  0000 L CNN
F 1 "C" H 4050 3750 50  0000 L CNN
	1    4000 3850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR014
U 1 1 4F5B70E7
P 4350 3500
F 0 "#PWR014" H 4350 3500 30  0001 C CNN
F 1 "GND" H 4350 3430 30  0001 C CNN
	1    4350 3500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR015
U 1 1 4F5B7069
P 6450 3900
F 0 "#PWR015" H 6450 3900 30  0001 C CNN
F 1 "GND" H 6450 3830 30  0001 C CNN
	1    6450 3900
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR016
U 1 1 4F5B7056
P 4400 3800
F 0 "#PWR016" H 4400 3900 30  0001 C CNN
F 1 "VCC" H 4400 3900 30  0000 C CNN
	1    4400 3800
	0    -1   -1   0   
$EndComp
$Comp
L XR2206 U1
U 1 1 4F5B704A
P 5400 3800
F 0 "U1" H 5400 3800 60  0000 C CNN
F 1 "XR2206" H 5400 3800 60  0000 C CNN
	1    5400 3800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
