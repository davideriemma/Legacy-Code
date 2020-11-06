/*
 * polledIO.c
 *
 * Created: 09/06/2018 23:31:38
 * Author : david
 */ 


#include "pio.h"

unsigned char init_pio(const int (*transmit)(char, FILE *),const int (*receive)(char))
{
	static FILE out = FDEV_SETUP_STREAM(transmit, receive, _FDEV_SETUP_RW);
	
	if (out)
	{
		stdin = &out;
		stdout = &out;
	}
	else
	{
		return -1;
	}
	
	return 0;
}
