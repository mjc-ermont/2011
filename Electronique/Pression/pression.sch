EESchema Schematic File Version 1
LIBS:power,C:/Documents and Settings/atelier du bocage/Bureau/Robotique-MJC/Electronique/Librairies kiCAD/arduino_shieldsNCL,C:/Documents and Settings/atelier du bocage/Bureau/Robotique-MJC/Electronique/Librairies kiCAD/Arduino,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves
EELAYER 23  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "31 mar 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 6250 5950 0    60   ~
Entree temperature ext
Connection ~ 7750 5850
Wire Wire Line
	7150 5850 7750 5850
Wire Wire Line
	7750 5950 7750 5800
Wire Wire Line
	7750 6600 7750 6450
Wire Wire Line
	7750 5100 7750 5300
$Comp
L VCC #PWR?
U 1 1 4F772421
P 7750 5100
F 0 "#PWR?" H 7750 5200 30  0001 C C
F 1 "VCC" H 7750 5200 30  0000 C C
	1    7750 5100
	1    0    0    -1  
$EndComp
$Comp
L R CAPT_TEMP?
U 1 1 4F772420
P 7750 5550
F 0 "CAPT_TEMP?" V 7830 5550 50  0000 C C
F 1 "R" V 7750 5550 50  0001 C C
	1    7750 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4F77241F
P 7750 6600
F 0 "#PWR?" H 7750 6600 30  0001 C C
F 1 "GND" H 7750 6530 30  0001 C C
	1    7750 6600
	1    0    0    -1  
$EndComp
$Comp
L R 10k?
U 1 1 4F77241E
P 7750 6200
F 0 "10k?" V 7830 6200 50  0000 C C
F 1 "R" V 7750 6200 50  0001 C C
	1    7750 6200
	1    0    0    -1  
$EndComp
Text Label 4450 5950 0    60   ~
Entree temperature int
Connection ~ 6000 5850
Wire Wire Line
	5400 5850 6000 5850
Wire Wire Line
	6000 5950 6000 5800
Wire Wire Line
	4900 3550 4900 3600
Wire Wire Line
	7650 2850 7650 2800
Connection ~ 8600 3250
Wire Wire Line
	8600 3250 8600 4100
Wire Wire Line
	8600 4100 7500 4100
Connection ~ 6700 3350
Wire Wire Line
	6700 3350 6700 4100
Wire Wire Line
	6700 4100 7000 4100
Wire Wire Line
	5500 3700 5500 3150
Wire Wire Line
	5500 3700 4900 3700
Wire Wire Line
	4900 3700 4900 3900
Connection ~ 4300 3350
Wire Wire Line
	4300 3350 4300 4050
Wire Wire Line
	4300 4050 4650 4050
Wire Wire Line
	2350 2450 2350 3350
Wire Wire Line
	2350 3350 3500 3350
Wire Wire Line
	4000 3350 4500 3350
Wire Wire Line
	4500 3350 4500 3250
Wire Wire Line
	4300 2800 4300 2150
Wire Wire Line
	6050 1750 6550 1750
Wire Wire Line
	5400 2400 5400 2650
Wire Wire Line
	5550 1750 5400 1750
Wire Wire Line
	5400 1750 5400 1900
Wire Wire Line
	5250 2150 4800 2150
Wire Wire Line
	4000 2800 4500 2800
Wire Wire Line
	4500 2800 4500 3050
Connection ~ 4300 2800
Wire Wire Line
	2550 2450 2550 2800
Wire Wire Line
	2550 2800 3500 2800
Wire Wire Line
	2450 2600 2450 2450
Wire Wire Line
	2650 2450 2650 2600
Wire Wire Line
	5500 3150 7250 3150
Wire Wire Line
	6250 3700 6250 3350
Wire Wire Line
	6250 3350 7250 3350
Wire Wire Line
	9800 3250 8250 3250
Wire Wire Line
	4900 2700 4900 2750
Wire Wire Line
	7650 3650 7650 3700
Wire Wire Line
	6000 6600 6000 6450
Wire Wire Line
	6000 5100 6000 5300
$Comp
L VCC #PWR?
U 1 1 4F7723A7
P 6000 5100
F 0 "#PWR?" H 6000 5200 30  0001 C C
F 1 "VCC" H 6000 5200 30  0000 C C
	1    6000 5100
	1    0    0    -1  
$EndComp
$Comp
L R CAPT_TEMP
U 1 1 4F7722EB
P 6000 5550
F 0 "CAPT_TEMP" V 6080 5550 50  0000 C C
F 1 "R" V 6000 5550 50  0001 C C
	1    6000 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4F7722C3
P 6000 6600
F 0 "#PWR?" H 6000 6600 30  0001 C C
F 1 "GND" H 6000 6530 30  0001 C C
	1    6000 6600
	1    0    0    -1  
$EndComp
$Comp
L R 10k
U 1 1 4F7721E0
P 6000 6200
F 0 "10k" V 6080 6200 50  0000 C C
F 1 "R" V 6000 6200 50  0001 C C
	1    6000 6200
	1    0    0    -1  
$EndComp
$Comp
L VSS GND
U 1 1 4F77206F
P 6250 4200
F 0 "GND" H 6250 4130 30  0000 C C
F 1 "VSS" H 6250 4130 30  0001 C C
	1    6250 4200
	1    0    0    -1  
$EndComp
$Comp
L ARDUINO_SHIELD SHIELD?
U 1 1 4F771FE6
P 2700 4950
F 0 "SHIELD?" H 2350 5900 60  0000 C C
F 1 "ARDUINO_SHIELD" H 2750 4000 60  0000 C C
	1    2700 4950
	1    0    0    -1  
$EndComp
Text Label 9800 3250 0    60   ~
Entree pression
$Comp
L GND #PWR01
U 1 1 4F5B9537
P 4900 3600
F 0 "#PWR01" H 4900 3600 30  0001 C C
F 1 "GND" H 4900 3530 30  0001 C C
	1    4900 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 4F5B952E
P 7650 3700
F 0 "#PWR02" H 7650 3700 30  0001 C C
F 1 "GND" H 7650 3630 30  0001 C C
	1    7650 3700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 4F5B9527
P 7650 2800
F 0 "#PWR03" H 7650 2890 20  0001 C C
F 1 "+5V" H 7650 2890 30  0000 C C
	1    7650 2800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 4F5B9507
P 4900 2700
F 0 "#PWR04" H 4900 2790 20  0001 C C
F 1 "+5V" H 4900 2790 30  0000 C C
	1    4900 2700
	1    0    0    -1  
$EndComp
$Comp
L POT POT2
U 1 1 4F5B7225
P 7250 4100
F 0 "POT2" H 7250 4000 50  0000 C C
F 1 "20k" H 7250 4100 50  0000 C C
	1    7250 4100
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 4F5B721F
P 6250 3950
F 0 "R6" V 6330 3950 50  0000 C C
F 1 "10k" V 6250 3950 50  0000 C C
	1    6250 3950
	1    0    0    -1  
$EndComp
$Comp
L LM324 U1
U 2 1 4F5B71F2
P 7750 3250
F 0 "U1" H 7800 3450 60  0000 C C
F 1 "LM324" H 7900 3050 50  0000 C C
	2    7750 3250
	1    0    0    -1  
$EndComp
$Comp
L POT POT1
U 1 1 4F5B719D
P 4900 4050
F 0 "POT1" H 4900 3950 50  0000 C C
F 1 "1M" H 4900 4050 50  0000 C C
	1    4900 4050
	1    0    0    -1  
$EndComp
$Comp
L VCC +9V05
U 1 1 4F5B711C
P 2450 2600
F 0 "+9V05" H 2450 2700 30  0000 C C
F 1 "VCC" H 2450 2700 30  0001 C C
	1    2450 2600
	1    0    0    1   
$EndComp
$Comp
L GND GND06
U 1 1 4F5B7118
P 2650 2600
F 0 "GND06" H 2650 2500 30  0000 C C
F 1 "GND" H 2650 2530 30  0001 C C
	1    2650 2600
	1    0    0    -1  
$EndComp
$Comp
L POT POT3
U 1 1 4F5B6F5B
P 5400 2150
F 0 "POT3" H 5400 2050 50  0000 C C
F 1 "4.7k" H 5400 2150 50  0000 C C
	1    5400 2150
	0    -1   -1   0   
$EndComp
$Comp
L VCC +9V07
U 1 1 4F5B6F1F
P 6550 1750
F 0 "+9V07" V 6550 1900 30  0000 C C
F 1 "VCC" H 6550 1850 30  0001 C C
	1    6550 1750
	0    1    1    0   
$EndComp
$Comp
L GND GND08
U 1 1 4F5B6F0A
P 5400 2650
F 0 "GND08" H 5400 2575 30  0000 C C
F 1 "GND" H 5400 2580 30  0001 C C
	1    5400 2650
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4F5B6EB9
P 5800 1750
F 0 "R5" V 5880 1750 50  0000 C C
F 1 "1.5k" V 5800 1750 50  0000 C C
	1    5800 1750
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 4F5B6EB2
P 4550 2150
F 0 "R3" V 4630 2150 50  0000 C C
F 1 "680k" V 4550 2150 50  0000 C C
	1    4550 2150
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 4F5B6DD4
P 3750 3350
F 0 "R2" V 3830 3350 50  0000 C C
F 1 "3.3k" V 3750 3350 50  0000 C C
	1    3750 3350
	0    1    1    0   
$EndComp
$Comp
L LM324 U1
U 1 1 4F5B6DB5
P 5000 3150
F 0 "U1" H 5050 3350 60  0000 C C
F 1 "LM324" H 5150 2950 50  0000 C C
	1    5000 3150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4F5B6CE2
P 3750 2800
F 0 "R1" V 3830 2800 50  0000 C C
F 1 "4.7k" V 3750 2800 50  0000 C C
	1    3750 2800
	0    1    1    0   
$EndComp
$Comp
L CONN_4 MPX~2200AP1
U 1 1 4F5B6C04
P 2500 2100
F 0 "MPX 2200AP1" V 2450 2100 50  0000 C C
F 1 "CONN_4" V 2550 2100 50  0000 C C
	1    2500 2100
	0    1    -1   0   
$EndComp
$EndSCHEMATC
