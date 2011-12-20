/*
*
*		GPSSK
*		GPS Starter Kit
*		Setup, Diagnostics, And Data Monitor
*		For The
*		Trimble ASCII Interface Protocol (TAIP)
*
*		Trimble Navigation
*		645 N. Mary Ave
*		Sunnyvale, CA 94088
*		Copyright 1992
*
*
*		TAIP Message Encoding/Decoding Source Code
*		----------------------------------------------------------------
*		TAIP.C contains 'C' source code for encoding and decoding TAIP
*		messages.  There is no warranty of any kind on this software.
*		It is provided only as an example of TAIP message processing.
*		Use it at your own risk.
*
*		Author: Jim Reynolds
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sio.h"						/* Serial I/O */

#ifndef FALSE
#define FALSE		0					/* Boolean flags for False */
#define TRUE		(!FALSE)			/*   and True */
#endif

#define VERSION		"1.00"

/*
*	Unit Conversions
*/
#define M2F			3.2808				/* Meters to Feet */
#define MILES2FT	5280.0				/* Miles to Feet */
#define F2M			(1.0/M2F)			/* Feet to Meters */
#define HRS2SEC		3600.0				/* Hours to Seconds */
#define MPH2MPS		((MILES2FT*F2M)/HRS2SEC)	/* Miles/hour to meters/sec */
#define MPS2MPH		(1.0/MPH2MPS) 	/* meters/sec to Miles/hour */
#define PI			3.1415926535898		/* PI */
#define D2R			(PI/180.0)			/* Degrees to radians */
#define R2D			(180.0/PI)			/* Radians to Degrees */

typedef unsigned char	/* define "byte" as an unsigned character */
	byte;

/*
*	POS.fix_type
*/
#define POS_FIX_A2		0		/* Autonomous 2D Fix */
#define POS_FIX_A3		1		/* Autonomous 3D Fix */
#define POS_FIX_D2		2		/* Differential 2D Fix */
#define POS_FIX_D3		3		/* Differential 3D Fix */
#define POS_FIX_UNK		4		/* Unknown source for Fix */
#define POS_FIX_DR		6		/* Dead-Reckoned Fix */
#define POS_FIX_DDR		8		/* Degraded Dead-Reckoned Fix */

/*
*	POS.fix_age
*/
#define POS_AGE_NEW		2		/* Position is "new" (less than 10 sec old) */
#define POS_AGE_OLD		1		/* Position is "old" (10 sec old or more) */
#define POS_AGE_UNK		0		/* Position is of unknown age */

#define TAIP_ID_LEN		4		/* Length of a TAIP ID */
#define POS_MSG_LEN		80		/* Maximum length of AM message text field */

#define BUFSIZ			512		/* Serial port manager buffer size (bytes) */

/*
*	TAIP message delimeters
*/
#define TAIP_START		'>'		/* All TAIP messages begin with a '>' */
#define TAIP_END		'<'		/* All TAIP messages end with a '<' */

/*
*	TAIP decoder's standard TAIP position structure
*	This structure is used by TAIP messages CP, PV, AM, and LN.
*	Some fields will not be filled.
*/
typedef struct {
	char
		id [3],				/* ID of TAIP message that filled TAIP_POS */
		alarm_code,			/* Alarm code from the AM message */
		msg [POS_MSG_LEN+1];	/* Message from the AM message */
	int
		fix_type,			/* Fix type, see #define POS_FIX_XXX above */
		fix_age,			/* Fix age, see #define POS_AGE_XXX above */
		nsvs,				/* Quantity of satellites used in position */
		svs [4],			/* List of satellites used in position */
		iodes [4];			/* satellite's IODEs */
	double
		time,				/* GPS time of position */
		lat,				/* latitude in radians */
		lon,				/* longtiude in radians */
		alt,				/* altitude in meters */
		cog,				/* course over ground in radians from north */
		sog,				/* speed over ground in meters/second */
		vs;					/* vertical speed in meters/second */
} TAIP_POS;

/*	AL message structure */
typedef struct {
	int
		fix_type,			/* Fix type, see #define POS_FIX_XXX above */
		fix_age;			/* Fix age, see #define POS_AGE_XXX above */
	double
		time,				/* GPS time of position */
		alt,				/* altitude in meters */
		vspd;				/* vertical speed in meters/second */
} TAIP_AL;

/*
*	Decoder's standard TAIP port parameters structure
*	This structure is used by TAIP messages AP, PT
*/
typedef struct {
	int
		baud,				/* baud rate */
		data_bits,			/* quantity of data bits */
		stop_bits,			/* quantity of stop bits */
		parity,				/* parity */
		port;				/* port */
} TAIP_PORT;

/*	RM message structure */
typedef struct {
	int
		id_flag,			/* ID_FLAG, send ID with messages */
		cs_flag,			/* CS_FLAG, send checksums with messages */
		ec_flag,			/* EC_FLAG, echo Set commands */
		fr_flag;			/* FR_FLAG, enable Frequency reporting */
} TAIP_RM;

/*	IP message structure */
typedef struct {
	int
		lat_deg,			/* Initial latitude in degrees */
		lon_deg;			/* Initial longitude in degrees */
	long
		alt;				/* Initial altitude in meters */
} TAIP_IP;

/*	VR message structure */
#define VR_NAME_LEN		40		/* Maximum length of product name */
#define VR_VERS_LEN		4		/* Length of version */
#define VR_REL_LEN		8		/* Length of date */
typedef struct {
	char
		name [VR_NAME_LEN+1],		/* Product name */
		vers [VR_VERS_LEN+1],		/* Version */
		rel_date [VR_REL_LEN+1];	/* Release date */
} TAIP_VR;

/*	ID message structure */
typedef struct {
	char
		id [TAIP_ID_LEN+1];			/* GPS receiver's ID */
} TAIP_ID;

/*	ST message structure */
typedef struct {
	int
		codes [5];					/* 5 status codes */
} TAIP_ST;

/*	TM message structure */
typedef struct {
	int
		yr, mo, dy,					/* year, month, day */
		hr, mn, sc, ms,				/* hour, minute, second, millisecond */
		gpsutc,						/* GPS to UTC time offset in seconds */
		gpsutc_valid,				/* is gpsutc valid? */
		fix_type,					/* Fix type, see #define POS_FIX_XXX */
		n_sv;						/* Quantity of satellites */
} TAIP_TM;

/*	X1 message structure */
typedef struct {
	int
		msg,						/*	Sub-Message ID */
		odom_sta,					/*	Odometer Status */
		gyro_sta;					/*	Gyro Status */
	long
		odom_sf;					/*	Odometer Scale Factor */
	double
		gyro_rate_bias,				/*	Gyro rate bias */
		gyro_lsf,					/*	Gyro left scale factor */
		gyro_rsf;					/*	Gyro right scale factor */
} TAIP_X1;

/*
*	union of all supported TAIP messages used for parser to
*	displayer data transfer
*/
typedef union {
	TAIP_POS pos;
	TAIP_AL al;
	TAIP_PORT port;
	TAIP_RM rm;
	TAIP_IP ip;
	TAIP_VR vr;
	TAIP_ID id;
	TAIP_ST st;
	TAIP_TM tm;
	TAIP_X1 x1;
} TAIP_DATA;

char
	*fix_type_str[] = {"GPS-2D", "GPS-3D", "DGPS-2D",
		"DGPS-3D", "Unknown", "Unknown", "DR",
		"Unknown", "Deg-DR", "Unknown"},
	*fix_age_str [] = {"N/A", "Old", "New"},
	*parity_str [] = {"None", "Odd", "Even"};

#define NMSGS		(sizeof (msgs) / sizeof (MSG))

typedef struct {
	char
		*id;
	void
		(*parse_f)(),
		(*disp_f)();
} MSG;

/*****************************************************************************
*	Function Prototypes
*****************************************************************************/
double
	antof (byte *, int);
int
	antoi (char *, int),
	checksum_ok (unsigned char *),
	hatoi2 (char *),
	parse_fix_age (int),
	parse_fix_type (int),
	vid_parse (char *, char *);
long
	antol (char *, int);
unsigned int
	checksum (unsigned char *);
void
	disp_al (TAIP_AL *),
	disp_am (TAIP_POS *),
	disp_ap (TAIP_PORT *),
	disp_cp (TAIP_POS *),
	disp_id (TAIP_ID *),
	disp_ip (TAIP_IP *),
	disp_ln (TAIP_POS *),
	disp_pt (TAIP_PORT *),
	disp_pv (TAIP_POS *),
	disp_rm (TAIP_RM *),
	disp_st (TAIP_ST *),
	disp_tm (TAIP_TM *),
	disp_vr (TAIP_VR *),
	disp_x1 (TAIP_X1 *),
	fmt_taip (char *, char *),
	parse_al (TAIP_AL *, char *),
	parse_am (TAIP_POS *, char *),
	parse_ap (TAIP_PORT *, char *),
	parse_cp (TAIP_POS *, char *),
	parse_id (TAIP_ID *, char *),
	parse_ip (TAIP_IP *, char *),
	parse_ln (TAIP_POS *, char *),
	parse_pt (TAIP_PORT *, char *),
	parse_pv (TAIP_POS *, char *),
	parse_rm (TAIP_RM *, char *),
	parse_st (TAIP_ST *, char *),
	parse_tm (TAIP_TM *, char *),
	parse_vr (TAIP_VR *, char *),
	parse_x1 (TAIP_X1 *, char *),
	rad2dms (double, int *, int *, double *),
	ser_send (int, byte *, int),
	str_h2i (char *, int *),
	str_hms (char *, double),
	str_lat (char *, double),
	str_ll (char *, double, char []),
	str_lon (char *, double),
	taip_byte (int),
	taip_parse (char *);

/*****************************************************************************
*	List of supported TAIP messages and their associated
*	parsing and display routines
*****************************************************************************/
MSG
	msgs [] = {
	{"AL", parse_al, disp_al},
	{"AM", parse_am, disp_am},
	{"AP", parse_ap, disp_ap},
	{"CP", parse_cp, disp_cp},
	{"ID", parse_id, disp_id},
	{"IP", parse_ip, disp_ip},
	{"LN", parse_ln, disp_ln},
	{"PT", parse_pt, disp_pt},
	{"PV", parse_pv, disp_pv},
	{"RM", parse_rm, disp_rm},
	{"ST", parse_st, disp_st},
	{"TM", parse_tm, disp_tm},
	{"VR", parse_vr, disp_vr},
	{"X1", parse_x1, disp_x1}
};

/****************************************************************************/
void main ()
{
	char
		taip [80];
	static char
		rbuf [BUFSIZ], tbuf [BUFSIZ];
	int
		done, pid, chr;

	printf ("\n");
	printf ("       Sample TAIP Query/Response Program\n");
	printf ("       Copyright Trimble Navigation 1992\n");
	printf ("       Version %s\n\n", VERSION);

	/*
	*	Configure COM1
	*/
	pid = 0;
	SIO_Open (NULL);
	SIO_IntOpen  (0, 8+4, -1, NULL);
	SIO_PortOpen (pid, 0x3f8, 0, HS_DTR | HS_RTS | HS_CTS, NULL);
	SIO_PortMode (pid, 4800L, 8, NOPARITY, ONEBIT, ONEBIT, NULL);
	SIO_RxOpen   (pid, rbuf, (long)BUFSIZ, HS_NONE, NULL);
	SIO_TxOpen   (pid, tbuf, (long)BUFSIZ, HS_NONE, NULL);

	printf ("       Serial Parameters: COM1, 4800 Baud, 8 data bits, 1 stop bit, no parity\n\n");
	
	printf ("       Press <Enter> to Poll for a PV packet\n");
	printf ("       Press <Escape> to quit\n");
	
	for (done = FALSE; !done; ) {	/* While not done... */
		while (SIO_RxGet (pid, &chr) == 0) { /* While characters coming in */
			taip_byte (chr);	/* send them to the TAIP decoder */
		}
		if (kbhit ()) {		/* if keyboard is hit... */
			switch (getch ()) {		/* get key and switch() */
			case 27:	/* <Escape>, Quit */
				done = TRUE;
				break;
			case '\r':	/* <Enter>, Poll for a PV packet */
				fmt_taip (taip, "QPV");		/* format a TAIP packet */
				ser_send (0, taip, strlen (taip));	/* send it */
				printf ("\nSend: %s\n", taip);		/* print it */
				break;
			}
		}
	}
	SIO_Close (0);	/* Shutdown serial ports */
}

#define BUF_LEN		132
/*
*	taip_byte (int chr)
*
*	All data from the GPS receiver is sent here
*/
static void taip_byte (chr)
	int chr;	/* character from serial port */
{
	static byte
		buf [BUF_LEN];	/* buffer to hold TAIP message being received */
	static int
		buf_len;		/* length of buffer "buf" */

	/*	Buffer overflow protection */
	if (buf_len == BUF_LEN) {
		buf_len = 0;
	}

	/*	Add character to message buffer */
	buf [buf_len++] = chr;

	/*	If the buffer's first character is not a '>', start over */
	if (buf [0] != TAIP_START) {
		buf_len = 0;
	}
	else if (chr == TAIP_END) {	/* If we receive a '<' character */
		buf [buf_len] = 0;	/* mark the end of the buffer with a 0 */
		printf ("Recv: %s\n", buf);	/* print received packet */
		/*
		*	if the checksum passes (or message does not contain one)...
		*/
		if (checksum_ok (buf)) {
			taip_parse (buf);	/* process the TAIP message */
		}
		buf_len = 0;	/* start the incoming message buffer over */
	}
}

/*
*	fmt_taip (char *taip, char *msg)
*
*		Wrap TAIP data into a TAIP packet with a checksum
*
*		>"data";*CS<
*
*	Given
*		msg - TAIP formatted message data area ("data" above)
*	Return
*		taip - packet ready for sending to the GPS reciever, complete with
*			   a checksum.
*/
static void fmt_taip (taip, msg)
	char *taip, *msg;
{
	char
		*ptr;

	ptr = taip;
	ptr += sprintf (ptr, ">%s", msg);
	ptr += sprintf (ptr, ";*");
	ptr += sprintf (ptr, "%02X", checksum (taip));
	sprintf (ptr, "<");
}

/*
*	Send a buffer of length "len" out of serial port "port"
*/
static void ser_send (port, buf, len)
	int port, len;
	byte *buf;
{
	int
		i;

	for (i = 0; i < len; i++) {
		SIO_TxPut (port, buf [i]);
	}
}

/*
*	int checksum_ok (char *text)
*
*	Verify TAIP packet's checksum
*
*	Given
*		text -	a complete TAIP packet
*	Returns (as the value of the function)
*		whether the checksum is correct for the packet (TRUE or FALSE)
*/
static int checksum_ok (text)
	unsigned char *text;	/* TAIP packet */
{
	int
		i,
		passed,	/* did the checksum pass? */
		len;	/* length of TAIP packet */
	unsigned int
		xcs;	/* expected checksum */

	len = strlen (text);	/* length of TAIP packet */
	passed = TRUE;	/* set passed TRUE until found otherwise */

	/*
	*	Search for the checksum identifier ('*') starting at
	*	the end of the packet
	*/
	for (i = len - 1; i > 0; i--) {
		if (text [i] == '*') {	/* Checksum identifier found */
			/* convert checksum characters into an integer */
			str_h2i (&text [i + 1], &xcs);
			/* if calculated checksum matches the expected checksum... */
			if (checksum (text) != xcs) {
				passed = FALSE;	/* checksum not correct */
			}
			break;
		}
	}
	return passed;	/* return whether checksum passed (TRUE or FALSE) */
}

/*
*	taip_parse (char *buf)
*
*	process a TAIP message
*
*/
static void taip_parse (buf)
	char *buf;	/* Pointer to 0 terminated TAIP message */
{
	int
		mid;		/* index into message list of this message */
	TAIP_DATA
		taip_data;	/* parser/displayer data transfer storage space */

	/*	Search message list for 2 character TAIP id */
	for (mid = 0; mid < NMSGS; mid++) {
		if (strnicmp (&buf [2], msgs [mid].id, 2) == 0) {
			break;
		}
	}

	if (mid != NMSGS) {	/*	If message id was found in list... */
		/*	Erase data storage area */
		memset ((char *)&taip_data, 0, sizeof (taip_data));

		/* call the message parser */
		(*msgs [mid].parse_f)(&taip_data, &buf [4]);

		/* call the message displayer with the parsed data */
		(*msgs [mid].disp_f)(&taip_data);
	}
	else {	/* message was not found in list */
		char msg [3];
		strncpy (msg, &buf [2], 2);
		msg [2] = 0;
		printf ("Message type \"%s\" not found in message list", msg);
	}
}

/*
*	unsigned int checksum (char *text)
*
*	Calculate a checksum for a string that ends with a '*'
*
*	Given
*		text -	a TAIP formatted packet ending with a '*'
*				the '*' is the character preceding the checksum in a TAIP
*				packet.
*	Returns (as the value of the function)
*		an integer checksum of "text"
*/
static unsigned int checksum (text)
	unsigned char *text;
{
	int
		i,
		len;	/* length of passed string */
	unsigned int
		cs;		/* checksum */

	len = strlen (text);	/* length of passed string */
	cs = 0;			/* clear checksum */
	/*
	*	Until we pass a '*' or the string ends (reach a 0 character),
	*	calculate the checksum as the exclusive OR'ing of all characters
	*	in the string
	*/
	for (i = 0; i < len && (i == 0 || text [i - 1] != '*'); i++) {
		cs ^= (unsigned int)text [i];
	}
	return cs;	/* return the checksum */
}

/****************************************************************************/

/*
*	Display a PV solution
*/
static void disp_pv (pos)
	TAIP_POS *pos;
{
	char
		str [132];

	str_hms (str, pos->time);
	printf ("PV %s ", str);

	str_lat (str, pos->lat);
	printf ("%s ", str);

	str_lon (str, pos->lon);
	printf ("%s ", str);

	printf ("%.2f\xf8 ", R2D * pos->cog);

	printf ("%.2fmph ", MPS2MPH * pos->sog);

	printf ("%s ", fix_type_str [pos->fix_type]);
	printf ("%s\n", fix_age_str [pos->fix_age]);
}

/*
*	Display routines for all other messages besides PV
*/
static void disp_al (al)
	TAIP_AL *al;
{}
static void disp_am (pos)
	TAIP_POS *pos;
{}
static void disp_ap (port)
	TAIP_PORT *port;
{}
static void disp_cp (pos)
	TAIP_POS *pos;
{}
static void disp_id (id)
	TAIP_ID *id;
{}
static void disp_ip (ip)
	TAIP_IP *ip;
{}
static void disp_ln (pos)
	TAIP_POS *pos;
{}
static void disp_pt (port)
	TAIP_PORT *port;
{}
static void disp_rm (rm)
	TAIP_RM *rm;
{}
static void disp_st (st)
	TAIP_ST *st;
{}
static void disp_tm (tm)
	TAIP_TM *tm;
{}
static void disp_vr (vr)
	TAIP_VR *vr;
{}
static void disp_x1 (x1)
	TAIP_X1 *x1;
{}

/*
*	parse_fix_type (int chr);
*
*	Parse the "fix type" character from a TAIP message.
*
*	Given
*		chr - fix type character from TAIP message
*	Return (as the value of the function)
*		an integer value corresponding to the #define POS_FIX_XXX's above
*/
static int parse_fix_type (chr)
	int chr;	/* fix type character from TAIP message */
{
	int
		fix_type;	/* fix type value */

	fix_type = chr - '0';	/* convert from ASCII to integer */
	if (fix_type < 0 || fix_type > 9) {	/* make sure it is valid */
		fix_type = POS_FIX_UNK;
	}
	return fix_type;	/* return fix type value */
}

/*
*	parse_fix_age (int chr);
*
*	Parse the "fix age" character from a TAIP message.
*
*	Given
*		chr - fix age character from TAIP message
*	Return (as the value of the function)
*		an integer value corresponding to the #define POS_AGE_XXX's above
*/
static int parse_fix_age (chr)
	int chr;
{
	int
		fix_age;	/* fix age value */

	fix_age = chr - '0';	/* convert from ASCII to integer */
	if (fix_age < 0 || fix_age > 9) {	/* make sure it is valid */
		fix_age = POS_AGE_UNK;
	}
	return fix_age;	/* return fix age value */
}

/*
*	parse_al (TAIP_AL *al, char *buf)
*
*	Parse a TAIP "AL" message to a TAIP_AL structure
*
*	Sample AL Message: >RAL68069+00030-00212<
*
*	Given
*		al - a pointer to a TAIP_AL structure to be filled
*		buf - a pointer to an AL message without the leading ">RAL"
*	Return (in al)
*		parsed AL message
*/
static void parse_al (al, buf)
	TAIP_AL *al;	/* pointer to a TAIP_AL structure to be filled */
	char *buf;		/* pointer to an AL message without the leading ">RAL" */
{
	al->time = antof (&buf [0], 5);				/* Time */
	al->alt  = antof (&buf [5], 6);				/* Altitude */
	al->vspd = MPH2MPS * antof (&buf [11], 4);	/* Vertical speed */
	al->fix_type = parse_fix_type (buf [15]);	/* Fix type */
	al->fix_age  = parse_fix_age (buf [16]);	/* Fix age */
}

/*
*	parse_ap (TAIP_PORT *port, char *buf)
*
*	Parse a TAIP "AP" message to a TAIP_PORT structure
*
*	Sample AP Message: >RAP1200,8,1,N,1,0<
*
*	Given
*		port - a pointer to a TAIP_PORT structure to be filled
*		buf - a pointer to an AP message without the leading ">RAP"
*	Return (in port)
*		parsed PORT message
*/
static void parse_ap (port, buf)
	TAIP_PORT *port;	/* pointer to a TAIP_PORT structure to be filled */
	char *buf;		/* pointer to an AP message without the leading ">RAP" */
{
	port->baud      = atoi (&buf [0]);		/* Baud rate */
	port->data_bits = atoi (&buf [5]);		/* Data bits */
	port->stop_bits = atoi (&buf [7]);		/* Stop Bits */
	port->parity = buf [9] == 'E' ? 2 : (buf [9] == 'O' ? 1 : 0); /* Parity */
	port->port   = atoi (&buf [11]);		/* Port */
}

/*
*	parse_cp (TAIP_CP *cp, char *buf)
*
*	Parse a TAIP "CP" message to a TAIP_CP structure
*
*	Sample CP Message: >RCP68069+373943-122038412<
*
*	Given
*		pos - a pointer to a TAIP_POS structure to be filled
*		buf - a pointer to an CP message without the leading ">RCP"
*	Return (in cp)
*		parsed CP message
*/
static void parse_cp (pos, buf)
	TAIP_POS *pos;	/* pointer to a TAIP_POS structure to be filled */
	char *buf;		/* pointer to a CP message without the leading ">RCP" */
{
	/* id of TAIP message providing position */
	strcpy (pos->id, "CP");

	/* Time */
	pos->time = antof (&buf [0], 5);

	/* Latitude converted to radians */
	pos->lat  = D2R * antof (&buf [5], 7) * 1.0e-4;

	/* Longitude converted to radians */
	pos->lon  = D2R * antof (&buf [12], 8) * 1.0e-4;

	/* Fix Type */
	pos->fix_type = parse_fix_type (buf [20]);

	/* Fix Age */
	pos->fix_age = parse_fix_age (buf [21]);
}

/*
*	parse_id (TAIP_ID *id, char *buf)
*
*	Parse a TAIP "ID" message to a TAIP_ID structure
*
*	Sample ID Message: >RID1000<
*
*	Given
*		id - a pointer to a TAIP_ID structure to be filled
*		buf - a pointer to an ID message without the leading ">RID"
*	Return (in id)
*		parsed ID message
*/
static void parse_id (id, buf)
	TAIP_ID *id;	/* pointer to a TAIP_ID structure to be filled */
	char *buf;		/* pointer to an ID message without the leading ">RID" */
{
	strncpy (id->id, buf, 4);	/* copy up to 4 characters of id */
	id->id [4] = 0;				/* make sure it's truncated at 4 characters */
}

/*
*	parse_ip (TAIP_IP *ip, char *buf)
*
*	Parse a TAIP "IP" message to a TAIP_IP structure
*
*	Sample IP Message: >RIP+37-122+0003<
*
*	Given
*		ip - a pointer to a TAIP_IP structure to be filled
*		buf - a pointer to an IP message without the leading ">RIP"
*	Return (in ip)
*		parsed IP message
*/
static void parse_ip (ip, buf)
	TAIP_IP *ip;	/* pointer to a TAIP_IP structure to be filled */
	char *buf;		/* pointer to an IP message without the leading ">RIP" */
{
	ip->lat_deg = antoi (&buf [0], 3);		/* Degrees of latitude */
	ip->lon_deg = antoi (&buf [3], 4);		/* Degrees of longitude */
	ip->alt = antol (&buf [7], 5) * 10;		/* Altitude in meters */
}

/*
*	parse_pt (TAIP_PT *pt, char *buf)
*
*	Parse a TAIP "PT" message to a TAIP_PT structure
*
*	Sample PT Message: >RPT4800,8,1,N<
*
*	Given
*		port - a pointer to a TAIP_PORT structure to be filled
*		buf - a pointer to an PT message without the leading ">RPT"
*	Return (in pt)
*		parsed PT message
*/
static void parse_pt (port, buf)
	TAIP_PORT *port;	/* pointer to a TAIP_PORT structure to be filled */
	char *buf;		/* pointer to a PT message without the leading ">RPT" */
{
	port->baud = atoi (&buf [0]);		/* Baud rate */
	port->data_bits = atoi (&buf [5]);	/* Data bits */
	port->stop_bits = atoi (&buf [7]);	/* Stop bits */
	port->parity = buf [9] == 'E' ? 2 : (buf [9] == 'O' ? 1 : 0); /* Parity */
}

/*
*	parse_rm (TAIP_RM *rm, char *buf)
*
*	Parse a TAIP "RM" message to a TAIP_RM structure
*
*	Sample RM Message: >RRM;ID_FLAG=F;CS_FLAG=F;EC_FLAG=F;FR_FLAG=T<
*
*	Given
*		rm - a pointer to a TAIP_RM structure to be filled
*		buf - a pointer to an RM message without the leading ">RRM"
*	Return (in rm)
*		parsed RM message
*/
static void parse_rm (rm, buf)
	TAIP_RM *rm;	/* pointer to a TAIP_RM structure to be filled */
	char *buf;		/* pointer to a RM message without the leading ">RRM" */
{
	/* Set all flags FALSE */
	rm->id_flag = rm->cs_flag = rm->fr_flag = rm->ec_flag = FALSE;

	/*
	*	Scan through the TAIP message for semicolons,
	*	advancing the "buf" pointer each time.
	*/
	while ((buf = strchr (buf, ';')) != NULL) {

		/*	if scan finds ";ID_FLAG=" ... */
		if (strncmp (buf, ";ID_FLAG=", 9) == 0) {
			rm->id_flag = buf [9] == 'T';	/* set TRUE if ID_FLAG=T */
		}

		/*	if scan finds ";CS_FLAG=" ... */
		else if (strncmp (buf, ";CS_FLAG=", 9) == 0) {
			rm->cs_flag = buf [9] == 'T';	/* set TRUE if CS_FLAG=T */
		}

		/*	if scan finds ";EC_FLAG=" ... */
		else if (strncmp (buf, ";EC_FLAG=", 9) == 0) {
			rm->ec_flag = buf [9] == 'T';	/* set TRUE if EC_FLAG=T */
		}

		/*	if scan finds ";FR_FLAG=" ... */
		else if (strncmp (buf, ";FR_FLAG=", 9) == 0) {
			rm->fr_flag = buf [9] == 'T';	/* set TRUE if FR_FLAG=T */
		}

		/* Advance the buf pointer past the semicolon for the next search */
		++buf;
	}
}

/*
*	parse_st (TAIP_ST *st, char *buf)
*
*	Parse a TAIP "ST" message to a TAIP_ST structure
*
*	Sample ST Message: >RST0000240000<
*
*	Given
*		st - a pointer to a TAIP_ST structure to be filled
*		buf - a pointer to an ST message without the leading ">RST"
*	Return (in st)
*		parsed ST message
*/
static void parse_st (st, buf)
	TAIP_ST *st;	/* pointer to a TAIP_ST structure to be filled */
	char *buf;		/* pointer to a ST message without the leading ">RST" */
{
	int
		i;

	/* Copy the 5 status codes from the TAIP message to the ST structure */
	for (i = 0; i < 5; i++) {
		st->codes [i] = hatoi2 (&buf[i*2]);
	}
}

/*
*	parse_vr (TAIP_VR *vr, char *buf)
*
*	Parse a TAIP "VR" message to a TAIP_VR structure
*
*	Sample VR Message: >RVR PLACER 300D; VERSION 1.94 (08/05/92); COPYRIGHT (C) 1991, 1992 TRIMBLE NAVIGATION<
*
*	Given
*		vr - a pointer to a TAIP_VR structure to be filled
*		buf - a pointer to an VR message without the leading ">RVR"
*	Return (in vr)
*		parsed VR message
*/
static void parse_vr (vr, buf)
	TAIP_VR *vr;	/* pointer to a TAIP_VR structure to be filled */
	char *buf;		/* pointer to a VR message without the leading ">RVR" */
{
	char
		*ptr;

	/*	Fill structure with unknowns in case some info is missing in VR */
	strcpy (vr->name, "????????");
	strcpy (vr->vers, "?.??");
	strcpy (vr->rel_date, "??/??/??");

	/* Copy the product name */
	strncpy (vr->name, buf+1, VR_NAME_LEN);
	vr->name [VR_NAME_LEN] = 0;	/* truncate product name to maximum size */
	/*	if name contains a ';', stop the string there */
	if ((ptr = strchr (vr->name, ';')) != NULL) {
		*ptr = 0;
	}

	/*	Scan for a ';' */
	if ((buf = strchr (buf, ';')) != NULL) {

		/*	if Version follows... */
		if (strncmp (buf, "; VERSION ", 10) == 0) {

			/* copy into structure */
			strncpy (vr->vers, buf + 10, VR_VERS_LEN);
			vr->vers [VR_VERS_LEN] = 0;	/* length limited */
			buf += 15;	/* skip over version info */
			if (*buf == '(') {	/* if date is here */
				strncpy (vr->rel_date, buf + 1, VR_REL_LEN); /* copy date */
				vr->rel_date [VR_REL_LEN] = 0;	/* length limited */
			}
		}
	}
}

/*
*	parse_tm (TAIP_TM *tm, char *buf)
*
*	Parse a TAIP "TM" message to a TAIP_TM structure
*
*	Sample TM Message: >RTM1854223750511199208104100000<
*
*	Given
*		tm - a pointer to a TAIP_TM structure to be filled
*		buf - a pointer to an TM message without the leading ">RTM"
*	Return (in tm)
*		parsed TM message
*/
static void parse_tm (tm, buf)
	TAIP_TM *tm;	/* pointer to a TAIP_TM structure to be filled */
	char *buf;		/* pointer to a TM message without the leading ">RTM" */
{
/*
	0123456789012345678901234567
	hhmmsssssDDMMYYYYoofuuvrrrrr	28 characters long
*/
	tm->hr = antoi (&buf [ 0], 2);	/* hour */
	tm->mn = antoi (&buf [ 2], 2);	/* minute */
	tm->sc = antoi (&buf [ 4], 2);	/* second */
	tm->ms = antoi (&buf [ 6], 3);	/* milliseconds */
	tm->dy = antoi (&buf [ 9], 2);	/* day */
	tm->mo = antoi (&buf [11], 2);	/* month */
	tm->yr = antoi (&buf [13], 4);	/* year */

	tm->gpsutc = antoi (&buf [17], 2);	/* GPS to UTC time offset */
	tm->fix_type = parse_fix_type (buf [19]);	/* Fix Type */
	tm->n_sv = antoi (&buf [20], 2);	/* Quantity of satellites */
	tm->gpsutc_valid = buf[22] == '1';	/* Is GPS to UTC offset valid? */
}

/*
*	parse_pv (TAIP_PV *pv, char *buf)
*
*	Parse a TAIP "PV" message to a TAIP_PV structure
*
*	Sample PV Message: >RPV68069+3739434-1220383600100012<
*
*	Given
*		pos - a pointer to a TAIP_POS structure to be filled
*		buf - a pointer to an PV message without the leading ">RPV"
*	Return (in pv)
*		parsed PV message
*/
static void parse_pv (pos, buf)
	TAIP_POS *pos;	/* pointer to a TAIP_POS structure to be filled */
	char *buf;		/* pointer to a PV message without the leading ">RPV" */
{
/*
	0123456789012345678901234567890123456789
	68069+3739434-1220383600100012<
*/
	/* id of TAIP message providing position */
	strcpy (pos->id, "PV");

	/* Time */
	pos->time = antof (&buf [0], 5);

	/* Latitude converted to radians */
	pos->lat  = D2R * antof (&buf [5], 8) * 1.0e-5;

	/* Longitude converted to radians */
	pos->lon  = D2R * antof (&buf [13], 9) * 1.0e-5;

	/* Speed over ground (SOG) converted to meters per second */
	pos->sog  = MPH2MPS * antof (&buf [22], 3);

	/* Course over ground (COG) converted to radians */
	pos->cog  = D2R * antof (&buf [25], 3);
	if (pos->cog < 0.0) {
		pos->cog += 2.0 * PI;
	}

	/* Fix Type */
	pos->fix_type = parse_fix_type (buf [28]);

	/* Fix Age */
	pos->fix_age = parse_fix_age (buf [29]);
}

/*
*	parse_am (TAIP_AM *am, char *buf)
*
*	Parse a TAIP "AM" message to a TAIP_AM structure
*
*	Sample AM Message: >RAM60662+3739435-12203830000000U1200<
*
*	Given
*		pos - a pointer to a TAIP_POS structure to be filled
*		buf - a pointer to an AM message without the leading ">RAM"
*	Return (in am)
*		parsed AM message
*/
static void parse_am (pos, buf)
	TAIP_POS *pos;	/* pointer to a TAIP_POS structure to be filled */
	char *buf;		/* pointer to a AM message without the leading ">RAM" */
{
/*
	0123456789012345678901234567890123
	60662+3739435-12203830000000U1200<
*/
	int
		msg_len;

	/* id of TAIP message providing position */
	strcpy (pos->id, "AM");

	/* Time */
	pos->time = antof (&buf [0], 5);

	/* Latitude converted to radians */
	pos->lat  = D2R * antof (&buf [5], 8) * 1.0e-5;

	/* Longitude converted to radians */
	pos->lon  = D2R * antof (&buf [13], 9) * 1.0e-5;

	/* Speed over ground (SOG) converted to meters per second */
	pos->sog  = MPH2MPS * antof (&buf [22], 3);

	/* Course over ground (COG) converted to radians */
	pos->cog  = D2R * antof (&buf [25], 3);
	if (pos->cog < 0.0) {
		pos->cog += 2.0 * PI;
	}

	/* Alarm Code */
	pos->alarm_code = buf [28];

	/* Fix Type */
	pos->fix_type = parse_fix_type (buf [29]);

	/* Fix Age */
	pos->fix_age = parse_fix_age (buf [30]);

	/* Text Message */
	msg_len = antoi (&buf [31], 2);
	if (msg_len > POS_MSG_LEN) msg_len = POS_MSG_LEN;
	if (msg_len == 0) {
		strcpy (pos->msg, "(None)");
	}
	else {
		strncpy (pos->msg, &buf [33], msg_len);
		pos->msg [msg_len] = 0;
	}
}

/*
*	parse_ln (TAIP_LN *ln, char *buf)
*
*	Parse a TAIP "LN" message to a TAIP_LN structure
*
*	Sample LN Message: >RLN68069188+373943425-1220383623+000099610011-0023000204289323D2263C0350000370000012<
*
*	Given
*		pos - a pointer to a TAIP_POS structure to be filled
*		buf - a pointer to an LN message without the leading ">RLN"
*	Return (in ln)
*		parsed LN message
*/
static void parse_ln (pos, ptr)
	TAIP_POS *pos;	/* pointer to a TAIP_POS structure to be filled */
	char *ptr;		/* pointer to a LN message without the leading ">RLN" */
{
	int
		nsv;
	/*
	012345678901234567890123456789012345678901234567890123456789012345678901234567890
	71126844+373943576-1220384035+000021440000+000000000403D620A6237526EE000500000012
	*/

	/* id of TAIP message providing position */
	strcpy (pos->id, "LN");

	/* Time */
	pos->time = antof (ptr, 8) * 1.0e-3;
	ptr += 8;

	/* Latitude converted to radians */
	pos->lat  = D2R * antof (ptr, 10) * 1.0e-7;
	ptr += 10;

	/* Longitude converted to radians */
	pos->lon  = D2R * antof (ptr, 11) * 1.0e-7;
	ptr += 11;

	/* Altitude */
	pos->alt  = F2M * antof (ptr, 9) * 1.0e-2;
	ptr += 9;

	/* Speed over ground (SOG) converted to meters per second */
	pos->sog  = MPH2MPS * antof (ptr, 4) * 0.1;
	ptr += 4;

	/* Vertical speed */
	pos->vs = MPH2MPS * antof (ptr, 5) * 0.1;
	ptr += 5;

	/* Course over ground (COG) converted to radians */
	pos->cog  = D2R * antof (ptr, 4) * 0.1;
	if (pos->cog < 0.0) {
		pos->cog += 2.0 * PI;
	}
	ptr += 4;

	/*	Quantity of Satellites */
	pos->nsvs = antoi (ptr, 2);
	ptr += 2;

	/*	List of Satellite and their IODEs */
	for (nsv = 0; nsv < pos->nsvs; nsv++) {
		pos->svs [nsv] = antoi (ptr, 2);
		ptr += 2;
		pos->iodes [nsv] = hatoi2 (ptr);
		ptr += 2;
	}

	/*	Reserved area */
	ptr += 10;

	/* Fix Type */
	pos->fix_type = parse_fix_type (*ptr);
	ptr += 1;

	/* Fix Age */
	pos->fix_age = parse_fix_age (*ptr);
}

/*
*	parse_x1 (TAIP_X1 *x1, char *buf)
*
*	Parse a TAIP "X1" message to a TAIP_X1 structure
*
*	Sample X1 Message: >RX1,1,01,0020042,0a,00.0000,01.0293,01.0276
*
*	Given
*		x1 - a pointer to a TAIP_X1 structure to be filled
*		buf - a pointer to an X1 message without the leading ">RX1"
*	Return (in x1)
*		parsed X1 message
*/
static void parse_x1 (x1, buf)
	TAIP_X1 *x1;	/* pointer to a TAIP_X1 structure to be filled */
	char *buf;		/* pointer to a X1 message without the leading ">RX1" */
{
	/*	Sub-Message ID */
	x1->msg = buf [1] - '0';

	/*	Odometer Status */
	x1->odom_sta = hatoi2 (&buf [3]);

	/*	Odometer Scale Factor */
	x1->odom_sf = antol (&buf [6], 7);

	/*	Gyro Status */
	x1->gyro_sta = hatoi2 (&buf [14]);

	/*	Gyro rate bias */
	x1->gyro_rate_bias = antof (&buf [17], 7);

	/*	Gyro left scale factor */
	x1->gyro_lsf = antof (&buf [25], 7);

	/*	Gyro right scale factor */
	x1->gyro_rsf = antof (&buf [33], 7);
}

static int vid_parse (buf, id)
	char *buf, *id;
{
	char
		*ptr;
	int
		got_id;

	ptr = buf;
	got_id = FALSE;
	while ((ptr = strchr (ptr, ';')) != NULL) {
		if (strncmp (ptr, ";ID=", 4) == 0) {
			strncpy (id, ptr + 4, 4);
			id [4] = 0;
			got_id = TRUE;
			break;
		}
		++ptr;
	}
	return got_id;
}

/*
*	Given a quantity of seconds into the day, format a string of the
*	format  HH:MM:SS.SSS
*/
static void str_hms (str, t)
	char *str;
	double t;
{
	int
		h, m;
	double
		s;

	h = t / 3600.0;
	t -= h * 3600.0;
	m = t / 60.0;
	t -= m * 60.0;
	s = t;

	sprintf (str, "%02d:%02d:%06.3f", h, m, s);
}

/*
*	Given an angle in radians, convert to degrees, arc-minutes,
*	and arc-seconds.
*/
static void rad2dms (rad, d, m, s)
	double rad, *s;
	int *d, *m;
{
	if (rad < 0.0) rad = -rad;
	rad += 1.0e-10;
	rad *= R2D;
	*d = rad;
	rad = (rad - *d) * 60.0;
	*m = rad;
	rad = (rad - *m) * 60.0;
	*s = rad;
}

/*****************************************************************************
*	The following routines are used to create an ASCII string of the form
*		DDD^MM'SS.SSSS"H
*	where DDD     is degrees
*		  ^       is the degrees symbol (superscripted 'o')
*		  MM      is arc-minutes
*		  SS.SSSS is arc-seconds
*	and   H       is the hemisphere (N or S for lat, E or W for lon)
*
*		str_lat () - latitude
*		str_lon () - longitude
*
*****************************************************************************/

static void str_lat (str, lat)
	char *str;
	double lat;
{
	str_ll (str, lat, "NS");
}
static void str_lon (str, lon)
	char *str;
	double lon;
{
	str_ll (str, lon, "EW");
}
static void str_ll (str, ll, h)
	char *str, h[];
	double ll;
{
	int
		d, m;
	double
		s;

	rad2dms (ll, &d, &m, &s);
	sprintf (str, "%3d\xf8%02d'%07.4f\"%c", d, m, s, ll >= 0.0 ? h[0] : h[1]);
}

/*****************************************************************************
*	The following routines are used to convert values contained in ASCII
*	strings to their numerical representations.
*
*		antoi () -	 Convert a specified quantity of characters
*					 from a string to an integer
*
*		antol () -	 Convert a specified quantity of characters
*					 from a string to a long integer
*
*		hatoi2 () -  Convert 2 characters from a hexidecimal string
*					 to an integer
*
*		antof () -	 Convert a specified quantity of characters from a string
*					 to a double precision floating point value (double)
*
*		str_h2i () - Convert a hexidecimal string to an integer
*
*****************************************************************************/

/*
*	antoi (char *ptr, int n);
*
*	Similar to ANSI's atoi() but processes only a fixed quantity of characters
*
*	Given
*		ptr - string pointer
*		n   - quantity of characters to process from ptr
*	Return (as the value of the function)
*		an integer value of the ASCII representation from ptr
*/
static int antoi (ptr, n)
	char *ptr;	/* string pointer */
	int n;	/* quantity of characters to process from ptr */
{
	char
		buf [80];			/* local string storage */

	memcpy (buf, ptr, n);	/* copy string to local temporary storage */
	buf [n] = 0;			/* truncate at n */
	return atoi (buf);		/* parse and return integer */
}

/*
*	antol (char *ptr, int n);
*
*	Similar to ANSI's atol() but processes only a fixed quantity of characters
*
*	Given
*		ptr - string pointer
*		n   - quantity of characters to process from ptr
*	Return (as the value of the function)
*		a long integer value of the ASCII representation from ptr
*/
static long antol (ptr, n)
	char *ptr;	/* string pointer */
	int n;	/* quantity of characters to process from ptr */
{
	char
		buf [80];			/* local string storage */

	memcpy (buf, ptr, n);	/* copy string to local temporary storage */
	buf [n] = 0;			/* truncate at n */
	return atol (buf);		/* parse and return long integer */
}

/*
*	hatoi2 (char *ptr);
*
*	Process 2 characters from string to an integer value.
*	String contains a hexidecimal representation of an integer.
*
*	Given
*		ptr - string pointer
*	Return (as the value of the function)
*		an integer value of the ASCII hexidecimal representation from ptr
*/
static int hatoi2 (ptr)
	char *ptr;	/* string pointer */
{
	char
		chr;
	int
		val, i;

	val = 0;	/* clear value accumulator */

	/* loop through 2 characters or until 0 character is reached */
	for (i = 0; i < 2 && *ptr != 0; ptr++, i++) {

		/* shift accululator up 1 place */
		val *= 16;

		/* promote character to upper case to simplify checking below */
		/*
		*	(this step is unnecessary for TAIP messages since they
		*	are all upper case anyway.)
		*/
		chr = toupper (*ptr);

		/* if character is 1-9, add value to accumulator */
		if (chr >= '0' && chr <= '9') {
			val += (chr - '0');
		}

		/* if character is A-F, add value to accumulator */
		else if (chr >= 'A' && chr <= 'F') {
			val += (chr + 10 - 'A');
		}
	}
	return val;	/* return integer value */
}

/*
*	antof (char *ptr, int n);
*
*	Similar to ANSI's atof() but processes only a fixed quantity of characters
*
*	Given
*		ptr - string pointer
*		n   - quantity of characters to process from ptr
*	Return (as the value of the function)
*		a double precision value of the ASCII representation from ptr
*/
static double antof (ptr, n)
	byte *ptr;
	int n;
{
	char
		buf [80];			/* local string storage */

	memcpy (buf, ptr, n);	/* copy string to local temporary storage */
	buf [n] = 0;			/* truncate at n */
	return atof (buf);		/* parse and return double precision value */
}

/*
*
*	void str_h2i (char *p, int *r) 
*
*	Convert hexadecimal string to integer
*
*	Given
*		char *p;	input hexidecimal string
*	Returns
*		int *r;		output integer
*
*	Performs a scan of the input string to convert a hexadecimal value
*	into an integer.  The scan terminates when a non-hex character is hit.
*	Valid hex characters are 0 to 9, A to F, and a to f.
*
*/
static void str_h2i (p, r)
	char *p;
	int *r;
{
	int
		i, j, c;

	i = j = 0;
	for (c = *p; isxdigit (c); c = p [++j]) {
		i <<= 4;
		if (isdigit (c)) i |= c - '0';
		if (isupper (c)) i |= c - 'A' + 10;
		if (islower (c)) i |= c - 'a' + 10;
	}
	*r = i;
}
