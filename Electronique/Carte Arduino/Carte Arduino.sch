EESchema Schematic File Version 2  date 13/12/2011 07:36:52
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
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Arduino
LIBS:Carte Arduino-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "13 dec 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 5400 4050
NoConn ~ 5300 4050
NoConn ~ 4350 4050
NoConn ~ 4250 4050
Wire Wire Line
	7850 6650 7750 6650
Wire Wire Line
	5200 4550 5200 4700
Wire Wire Line
	4150 4550 4150 4700
Wire Wire Line
	5400 3950 5400 4050
Wire Wire Line
	5200 3950 5200 4050
Wire Wire Line
	5000 3950 5000 4050
Wire Wire Line
	4350 3950 4350 4050
Wire Wire Line
	4150 3950 4150 4050
Wire Wire Line
	3950 3950 3950 4050
Wire Wire Line
	7750 6550 7850 6550
Wire Wire Line
	9550 6350 9650 6350
Wire Wire Line
	9550 6450 9650 6450
Wire Wire Line
	7850 5900 7750 5900
Wire Wire Line
	5950 6400 5950 6500
Wire Wire Line
	5750 6400 5750 6500
Wire Wire Line
	5550 6400 5550 6500
Wire Wire Line
	5150 6400 5150 6500
Wire Wire Line
	4950 6400 4950 6500
Wire Wire Line
	4750 6400 4750 6500
Wire Wire Line
	4550 6400 4550 6500
Wire Wire Line
	4150 6400 4150 6500
Wire Wire Line
	3950 6400 3950 6500
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
Wire Wire Line
	3850 6400 3850 6500
Wire Wire Line
	4050 6400 4050 6500
Wire Wire Line
	4450 6400 4450 6500
Wire Wire Line
	4650 6400 4650 6500
Wire Wire Line
	4850 6400 4850 6500
Wire Wire Line
	5050 6400 5050 6500
Wire Wire Line
	5450 6400 5450 6500
Wire Wire Line
	5650 6400 5650 6500
Wire Wire Line
	5850 6400 5850 6500
Wire Wire Line
	6050 6400 6050 6500
Wire Wire Line
	6150 6400 6150 6500
Wire Wire Line
	9550 6500 9650 6500
Wire Wire Line
	9550 6400 9650 6400
Wire Wire Line
	7850 6500 7750 6500
Wire Wire Line
	3850 3950 3850 4050
Wire Wire Line
	4050 3950 4050 4050
Wire Wire Line
	4250 3950 4250 4050
Wire Wire Line
	4900 3950 4900 4050
Wire Wire Line
	5100 3950 5100 4050
Wire Wire Line
	5300 3950 5300 4050
Wire Wire Line
	7850 6600 7750 6600
Text Label 7750 6650 2    60   ~ 0
Arduino - CH4
Text Label 7750 6600 2    60   ~ 0
Arduino - CO2
Text Label 5200 4700 3    60   ~ 0
Arduino - CH4
$Comp
L R R?
U 1 1 4EE6F1CD
P 5200 4300
F 0 "R?" V 5280 4300 50  0000 C CNN
F 1 "R" V 5200 4300 50  0000 C CNN
	1    5200 4300
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4EE6F1C1
P 4150 4300
F 0 "R?" V 4230 4300 50  0000 C CNN
F 1 "R" V 4150 4300 50  0000 C CNN
	1    4150 4300
	1    0    0    -1  
$EndComp
Text Label 4150 4700 3    60   ~ 0
Arduino - CO2
$Comp
L +5V #PWR?
U 1 1 4EE6F1B0
P 5100 4050
F 0 "#PWR?" H 5100 4140 20  0001 C CNN
F 1 "+5V" H 5100 4140 30  0000 C CNN
	1    5100 4050
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR?
U 1 1 4EE6F1A6
P 4050 4050
F 0 "#PWR?" H 4050 4140 20  0001 C CNN
F 1 "+5V" H 4050 4140 30  0000 C CNN
	1    4050 4050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 4EE6F197
P 5000 4050
F 0 "#PWR?" H 5000 4050 30  0001 C CNN
F 1 "GND" H 5000 3980 30  0001 C CNN
	1    5000 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4EE6F192
P 3950 4050
F 0 "#PWR?" H 3950 4050 30  0001 C CNN
F 1 "GND" H 3950 3980 30  0001 C CNN
	1    3950 4050
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 4EE6F18C
P 4900 4050
F 0 "#PWR?" H 4900 4140 20  0001 C CNN
F 1 "+5V" H 4900 4140 30  0000 C CNN
	1    4900 4050
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR?
U 1 1 4EE6F184
P 3850 4050
F 0 "#PWR?" H 3850 4140 20  0001 C CNN
F 1 "+5V" H 3850 4140 30  0000 C CNN
	1    3850 4050
	-1   0    0    1   
$EndComp
Text Notes 4800 3350 0    60   ~ 0
Capteur de CH4
Text Notes 3750 3350 0    60   ~ 0
Capteur de CO2
$Comp
L CONN_6 P?
U 1 1 4EE66058
P 5150 3600
F 0 "P?" V 5100 3600 60  0000 C CNN
F 1 "CONN_6" V 5200 3600 60  0000 C CNN
	1    5150 3600
	0    -1   -1   0   
$EndComp
$Comp
L CONN_6 P?
U 1 1 4EE66049
P 4100 3600
F 0 "P?" V 4050 3600 60  0000 C CNN
F 1 "CONN_6" V 4150 3600 60  0000 C CNN
	1    4100 3600
	0    -1   -1   0   
$EndComp
NoConn ~ 5950 6500
NoConn ~ 5850 6500
NoConn ~ 5750 6500
NoConn ~ 5650 6500
Text Label 6150 6500 3    60   ~ 0
Arduino - SCL
Text Label 6050 6500 3    60   ~ 0
Arduino - SDA
$Comp
L +5V #PWR?
U 1 1 4EE6592F
P 5550 6500
F 0 "#PWR?" H 5550 6590 20  0001 C CNN
F 1 "+5V" H 5550 6590 30  0000 C CNN
	1    5550 6500
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 4EE65926
P 5450 6500
F 0 "#PWR?" H 5450 6500 30  0001 C CNN
F 1 "GND" H 5450 6430 30  0001 C CNN
	1    5450 6500
	1    0    0    -1  
$EndComp
Text Notes 8550 5750 0    60   ~ 0
Arduino
Text Label 7750 6550 2    60   ~ 0
Arduino - SCL
Text Label 7750 6500 2    60   ~ 0
Arduino - SDA
Text Label 7750 5900 2    60   ~ 0
Modulateur
Text Label 9650 6350 0    60   ~ 0
Arduino - Temperature interieure
Text Label 9650 6400 0    60   ~ 0
Arduino - Temperature exterieure
Text Label 9650 6450 0    60   ~ 0
Arduino - Pression interieure
Text Label 9650 6500 0    60   ~ 0
Arduino - Pression exterieure
$Comp
L ARDUINO_MINI U?
U 1 1 4EE489A2
P 8650 6300
F 0 "U?" H 8650 6300 60  0000 C CNN
F 1 "ARDUINO_MINI" H 8650 6300 60  0000 C CNN
	1    8650 6300
	1    0    0    -1  
$EndComp
Text Notes 1850 4200 1    60   ~ 0
Capteur temperature exterieure
Text Notes 2250 4200 1    60   ~ 0
Capteur pression exterieure
Text Notes 1450 4200 1    60   ~ 0
Capteur pression interieure
Text Notes 1050 4200 1    60   ~ 0
Capteur temperature interieure
Text Notes 5450 5850 0    60   ~ 0
Accelerometre
$Comp
L CONN_8 P?
U 1 1 4EE37ED4
P 5800 6050
F 0 "P?" V 5750 6050 60  0000 C CNN
F 1 "CONN_8" V 5850 6050 60  0000 C CNN
	1    5800 6050
	0    -1   -1   0   
$EndComp
Text Notes 4550 5850 0    60   ~ 0
Gyroscope
Text Notes 3500 5850 0    60   ~ 0
Capteur Humidite
NoConn ~ 5050 6500
NoConn ~ 4950 6500
$Comp
L GND #PWR01
U 1 1 4EE37BF2
P 5150 6500
F 0 "#PWR01" H 5150 6500 30  0001 C CNN
F 1 "GND" H 5150 6430 30  0001 C CNN
	1    5150 6500
	1    0    0    -1  
$EndComp
NoConn ~ 4850 6500
NoConn ~ 4750 6500
Text Label 4650 6500 3    60   ~ 0
Arduino - SDA
Text Label 4550 6500 3    60   ~ 0
Arduino - SCL
$Comp
L +5V #PWR02
U 1 1 4EE37B76
P 4450 6500
F 0 "#PWR02" H 4450 6590 20  0001 C CNN
F 1 "+5V" H 4450 6590 30  0000 C CNN
	1    4450 6500
	-1   0    0    1   
$EndComp
$Comp
L CONN_8 P?
U 1 1 4EE37B01
P 4800 6050
F 0 "P?" V 4750 6050 60  0000 C CNN
F 1 "CONN_8" V 4850 6050 60  0000 C CNN
	1    4800 6050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR03
U 1 1 4EE3788C
P 3950 6500
F 0 "#PWR03" H 3950 6500 30  0001 C CNN
F 1 "GND" H 3950 6430 30  0001 C CNN
	1    3950 6500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 4EE3787E
P 4050 6500
F 0 "#PWR04" H 4050 6590 20  0001 C CNN
F 1 "+5V" H 4050 6590 30  0000 C CNN
	1    4050 6500
	-1   0    0    1   
$EndComp
Text Label 4150 6500 3    60   ~ 0
Arduino - SCL
Text Label 3850 6500 3    60   ~ 0
Arduino - SDA
$Comp
L CONN_4 P?
U 1 1 4EE37809
P 4000 6050
F 0 "P?" V 3950 6050 50  0000 C CNN
F 1 "CONN_4" V 4050 6050 50  0000 C CNN
	1    4000 6050
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR05
U 1 1 4EE364FB
P 2300 4850
F 0 "#PWR05" H 2300 4940 20  0001 C CNN
F 1 "+5V" H 2300 4940 30  0000 C CNN
	1    2300 4850
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P?
U 1 1 4EE364FA
P 2200 4400
F 0 "P?" V 2150 4400 40  0000 C CNN
F 1 "CONN_2" V 2250 4400 40  0000 C CNN
	1    2200 4400
	0    -1   -1   0   
$EndComp
Text Label 2100 5500 3    60   ~ 0
Arduino - Pression exterieure
$Comp
L R R?
U 1 1 4EE364F9
P 2100 5100
F 0 "R?" V 2180 5100 50  0000 C CNN
F 1 "R" V 2100 5100 50  0000 C CNN
	1    2100 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4EE364F8
P 1700 5100
F 0 "R?" V 1780 5100 50  0000 C CNN
F 1 "R" V 1700 5100 50  0000 C CNN
	1    1700 5100
	1    0    0    -1  
$EndComp
Text Label 1700 5500 3    60   ~ 0
Arduino - Temperature exterieure
$Comp
L CONN_2 P?
U 1 1 4EE364F7
P 1800 4400
F 0 "P?" V 1750 4400 40  0000 C CNN
F 1 "CONN_2" V 1850 4400 40  0000 C CNN
	1    1800 4400
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR06
U 1 1 4EE364F6
P 1900 4850
F 0 "#PWR06" H 1900 4940 20  0001 C CNN
F 1 "+5V" H 1900 4940 30  0000 C CNN
	1    1900 4850
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR07
U 1 1 4EE22ACD
P 1500 4850
F 0 "#PWR07" H 1500 4940 20  0001 C CNN
F 1 "+5V" H 1500 4940 30  0000 C CNN
	1    1500 4850
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P?
U 1 1 4EE22ACC
P 1400 4400
F 0 "P?" V 1350 4400 40  0000 C CNN
F 1 "CONN_2" V 1450 4400 40  0000 C CNN
	1    1400 4400
	0    -1   -1   0   
$EndComp
Text Label 1300 5500 3    60   ~ 0
Arduino - Pression interieure
$Comp
L R R?
U 1 1 4EE22ACB
P 1300 5100
F 0 "R?" V 1380 5100 50  0000 C CNN
F 1 "R" V 1300 5100 50  0000 C CNN
	1    1300 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4EE1ADE8
P 900 5100
F 0 "R?" V 980 5100 50  0000 C CNN
F 1 "R" V 900 5100 50  0000 C CNN
	1    900  5100
	1    0    0    -1  
$EndComp
Text Label 900  5500 3    60   ~ 0
Arduino - Temperature interieure
$Comp
L CONN_2 P?
U 1 1 4EE1AD34
P 1000 4400
F 0 "P?" V 950 4400 40  0000 C CNN
F 1 "CONN_2" V 1050 4400 40  0000 C CNN
	1    1000 4400
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR08
U 1 1 4EE0BB2B
P 1100 4850
F 0 "#PWR08" H 1100 4940 20  0001 C CNN
F 1 "+5V" H 1100 4940 30  0000 C CNN
	1    1100 4850
	-1   0    0    1   
$EndComp
$EndSCHEMATC
