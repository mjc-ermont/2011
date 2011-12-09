EESchema Schematic File Version 2  date 09/12/2011 07:44:42
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
LIBS:Carte Arduino-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
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
	5550 3450 5550 3600
Wire Wire Line
	5750 2850 5750 3000
Wire Wire Line
	5750 3000 6100 3000
Wire Wire Line
	6100 3000 6100 2850
Wire Wire Line
	5550 2850 5550 2950
$Comp
L R R?
U 1 1 4EE1ADE8
P 5550 3200
F 0 "R?" V 5630 3200 50  0000 C CNN
F 1 "R" V 5550 3200 50  0000 C CNN
	1    5550 3200
	1    0    0    -1  
$EndComp
Text Label 5550 3600 3    60   ~ 0
Arduino - Température
$Comp
L CONN_2 P?
U 1 1 4EE1AD34
P 5650 2500
F 0 "P?" V 5600 2500 40  0000 C CNN
F 1 "CONN_2" V 5700 2500 40  0000 C CNN
	1    5650 2500
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR?
U 1 1 4EE0BB2B
P 6100 2850
F 0 "#PWR?" H 6100 2940 20  0001 C CNN
F 1 "+5V" H 6100 2940 30  0000 C CNN
	1    6100 2850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
