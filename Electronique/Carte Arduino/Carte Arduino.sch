EESchema Schematic File Version 1
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves
EELAYER 23  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "9 dec 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	2100 5350 2100 5500
Wire Wire Line
	2100 4750 2100 4850
Wire Wire Line
	2300 4850 2300 4750
Wire Wire Line
	1900 4850 1900 4750
Wire Wire Line
	1700 4750 1700 4850
Wire Wire Line
	1700 5350 1700 5500
$Comp
L +5V #PWR?
U 1 1 4EE364FB
P 2300 4850
F 0 "#PWR?" H 2300 4940 20  0001 C C
F 1 "+5V" H 2300 4940 30  0000 C C
	1    2300 4850
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P?
U 1 1 4EE364FA
P 2200 4400
F 0 "P?" V 2150 4400 40  0000 C C
F 1 "CONN_2" V 2250 4400 40  0000 C C
	1    2200 4400
	0    -1   -1   0   
$EndComp
Text Label 2100 5500 3    60   ~
Arduino - Pression exterieure
$Comp
L R R?
U 1 1 4EE364F9
P 2100 5100
F 0 "R?" V 2180 5100 50  0000 C C
F 1 "R" V 2100 5100 50  0000 C C
	1    2100 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4EE364F8
P 1700 5100
F 0 "R?" V 1780 5100 50  0000 C C
F 1 "R" V 1700 5100 50  0000 C C
	1    1700 5100
	1    0    0    -1  
$EndComp
Text Label 1700 5500 3    60   ~
Arduino - Temperature exterieure
$Comp
L CONN_2 P?
U 1 1 4EE364F7
P 1800 4400
F 0 "P?" V 1750 4400 40  0000 C C
F 1 "CONN_2" V 1850 4400 40  0000 C C
	1    1800 4400
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR?
U 1 1 4EE364F6
P 1900 4850
F 0 "#PWR?" H 1900 4940 20  0001 C C
F 1 "+5V" H 1900 4940 30  0000 C C
	1    1900 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	1300 5350 1300 5500
Wire Wire Line
	1300 4750 1300 4850
Wire Wire Line
	1500 4850 1500 4750
Wire Wire Line
	1100 4850 1100 4750
Wire Wire Line
	900  4750 900  4850
Wire Wire Line
	900  5350 900  5500
$Comp
L +5V #PWR?
U 1 1 4EE22ACD
P 1500 4850
F 0 "#PWR?" H 1500 4940 20  0001 C C
F 1 "+5V" H 1500 4940 30  0000 C C
	1    1500 4850
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P?
U 1 1 4EE22ACC
P 1400 4400
F 0 "P?" V 1350 4400 40  0000 C C
F 1 "CONN_2" V 1450 4400 40  0000 C C
	1    1400 4400
	0    -1   -1   0   
$EndComp
Text Label 1300 5500 3    60   ~
Arduino - Pression interieure
$Comp
L R R?
U 1 1 4EE22ACB
P 1300 5100
F 0 "R?" V 1380 5100 50  0000 C C
F 1 "R" V 1300 5100 50  0000 C C
	1    1300 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4EE1ADE8
P 900 5100
F 0 "R?" V 980 5100 50  0000 C C
F 1 "R" V 900 5100 50  0000 C C
	1    900  5100
	1    0    0    -1  
$EndComp
Text Label 900  5500 3    60   ~
Arduino - Temperature interieure
$Comp
L CONN_2 P?
U 1 1 4EE1AD34
P 1000 4400
F 0 "P?" V 950 4400 40  0000 C C
F 1 "CONN_2" V 1050 4400 40  0000 C C
	1    1000 4400
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR?
U 1 1 4EE0BB2B
P 1100 4850
F 0 "#PWR?" H 1100 4940 20  0001 C C
F 1 "+5V" H 1100 4940 30  0000 C C
	1    1100 4850
	-1   0    0    1   
$EndComp
$EndSCHEMATC
