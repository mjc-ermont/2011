EESchema Schematic File Version 1
LIBS:power,C:/Documents and Settings/Robotik/Bureau/Robotique-MJC-2011/Electronique/Librairies kiCAD/xr2206,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "10 mar 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 6300 3500
NoConn ~ 6300 3600
Wire Wire Line
	6300 3700 6900 3700
Wire Wire Line
	6900 3700 6900 3800
Wire Wire Line
	7050 4000 7200 4000
Wire Wire Line
	6600 4200 6300 4200
Wire Wire Line
	3450 4500 3450 4150
Wire Wire Line
	3450 4150 3600 4150
Wire Wire Line
	4150 4000 4150 3900
Wire Wire Line
	4150 3900 4600 3900
Wire Wire Line
	3800 3850 3700 3850
Wire Wire Line
	3400 3600 4600 3600
Wire Wire Line
	4600 3500 4350 3500
Wire Wire Line
	4400 3800 4600 3800
Wire Wire Line
	6450 3900 6300 3900
Wire Wire Line
	4450 3800 4450 3850
Connection ~ 4450 3800
Wire Wire Line
	4450 3850 4200 3850
Wire Wire Line
	4600 4000 4550 4000
Wire Wire Line
	4600 4100 4550 4100
Wire Wire Line
	4550 4100 4550 4150
Wire Wire Line
	4550 4150 4100 4150
Wire Wire Line
	4600 4200 4550 4200
Wire Wire Line
	4550 4200 4550 4350
Wire Wire Line
	4550 4350 4100 4350
Wire Wire Line
	3600 4350 3450 4350
Connection ~ 3450 4350
Wire Wire Line
	6300 4100 6450 4100
Wire Wire Line
	6450 4100 6450 4000
Wire Wire Line
	6450 4000 6650 4000
Wire Wire Line
	6300 3800 6400 3800
$Comp
L R R?
U 1 1 4F5B7612
P 6650 3800
F 0 "R?" V 6730 3800 50  0000 C C
F 1 "R" V 6650 3800 50  0000 C C
	1    6650 3800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 4F5B75FB
P 7200 4000
F 0 "#PWR?" H 7200 4000 30  0001 C C
F 1 "GND" H 7200 3930 30  0001 C C
	1    7200 4000
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 4F5B75E2
P 6850 4000
F 0 "C?" H 6900 4100 50  0000 L C
F 1 "C" H 6900 3900 50  0000 L C
	1    6850 4000
	0    -1   -1   0   
$EndComp
NoConn ~ 6300 4000
Text Label 6600 4200 0    60   ~
Entree serie
$Comp
L GND #PWR?
U 1 1 4F5B733F
P 3450 4500
F 0 "#PWR?" H 3450 4500 30  0001 C C
F 1 "GND" H 3450 4430 30  0001 C C
	1    3450 4500
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4F5B7320
P 3850 4350
F 0 "R?" V 3930 4350 50  0000 C C
F 1 "R" V 3850 4350 50  0000 C C
	1    3850 4350
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4F5B7305
P 3850 4150
F 0 "R?" V 3930 4150 50  0000 C C
F 1 "R" V 3850 4150 50  0000 C C
	1    3850 4150
	0    1    1    0   
$EndComp
Text Label 3400 3600 0    60   ~
Sortie FSK
$Comp
L C C?
U 1 1 4F5B723C
P 4350 4000
F 0 "C?" H 4400 4100 50  0000 L C
F 1 "C" H 4400 3900 50  0000 L C
	1    4350 4000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 4F5B7223
P 3700 3850
F 0 "#PWR?" H 3700 3850 30  0001 C C
F 1 "GND" H 3700 3780 30  0001 C C
	1    3700 3850
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 4F5B720F
P 4000 3850
F 0 "C?" H 4050 3950 50  0000 L C
F 1 "C" H 4050 3750 50  0000 L C
	1    4000 3850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 4F5B70E7
P 4350 3500
F 0 "#PWR?" H 4350 3500 30  0001 C C
F 1 "GND" H 4350 3430 30  0001 C C
	1    4350 3500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 4F5B7069
P 6450 3900
F 0 "#PWR?" H 6450 3900 30  0001 C C
F 1 "GND" H 6450 3830 30  0001 C C
	1    6450 3900
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR?
U 1 1 4F5B7056
P 4400 3800
F 0 "#PWR?" H 4400 3900 30  0001 C C
F 1 "VCC" H 4400 3900 30  0000 C C
	1    4400 3800
	0    -1   -1   0   
$EndComp
$Comp
L XR2206 U?
U 1 1 4F5B704A
P 5400 3800
F 0 "U?" H 5400 3800 60  0000 C C
F 1 "XR2206" H 5400 3800 60  0000 C C
	1    5400 3800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
