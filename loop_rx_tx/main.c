/**
 * @file
 * @brief   Main for UART example.
 * @details This example loops back the TX to the RX on UART1. For this example
 *          you must connect a jumper across P2.14 to P2.16. UART_BAUD and the BUFF_SIZE
 *          can be changed in this example.
 */

/* *****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 **************************************************************************** */


/* **** Includes **** */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mxc_sys.h"
#include "uart.h"
#include "board.h"

#include "mxc_config.h"
#include "max32520.h"
#include "board.h"
#include "cipher.h"
#include "tpu_regs.h"

/* **** Definitions **** */
#define UART_BAUD           115200
#define BUFF_SIZE           512

/* **** Globals **** */
volatile int read_flag;
volatile int write_flag;
volatile int LEIDO;
volatile int CONTADOR=0;
/***** Globals *****/
char temp[] = {0x00, 0x00, 0x00}; //for ascii_to_byte()
char result[512];

char UART_IN[512];

/***** Functions *****/
//Print human-friendly readable output of array
void print(char *stuff)
{
    int i, j, size = 4;
	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			printf("0x%02x ", stuff[i*size+j]);
		}
		printf("\n");
	}
	return;
}

//Convert ascii to byte
void ascii_to_byte(const char *src, char *dst, int len)
{
	int i;
	for(i=0; i < len; ++i) {
		int val;
		temp[0] = *src; src++;
		temp[1] = *src; src++;
		sscanf(temp, "%x", &val);
		//val = hexconf(temp[0])*16 + hexconf(temp[1]);
		dst[i] = val;
	}
	return;
}


/*CHAR TO HEX */
char UT_CharToHex(char ch)
{
        char returnType;
        switch(ch)
        {
        case '0':
                returnType = 0;
                break;
        case  '1':
                returnType = 1;
                break;
        case  '2':
                returnType = 2;
                break;
        case  '3':
                returnType = 3;
                break;
        case  '4':
                returnType = 4;
                break;
        case  '5':
                returnType = 5;
                break;
        case  '6':
                returnType = 6;
                break;
        case  '7':
                returnType = 7;
                break;
        case  '8':
                returnType = 8;
                break;
        case  '9':
                returnType = 9;
                break;
        case  'A':
                returnType = 10;
                break;
        case  'B':
                returnType = 11;
                break;
        case  'C':
                returnType = 12;
                break;
        case  'D':
                returnType = 13;
                break;
        case  'E':
                returnType = 14;
                break;
        case  'F':
                returnType = 15;
                break;
        case  'a':
                returnType = 10;
                break;
        case  'b':
                returnType = 11;
                break;
        case  'c':
                returnType = 12;
                break;
        case  'd':
                returnType = 13;
                break;
        case  'e':
                returnType = 14;
                break;
        case  'f':
                returnType = 15;
                break;
        default:
                returnType = 0;
                break;
        }
        return returnType;
}



int main(void)
{
	//ENABLE UART 0
	UART_Enable(MXC_UART0);


    printf("\n\n***** UART Example *****\n");
    printf("\nConnect UART1 TX (P2.16) to UART1 RX (P2.14) for this example.\n\n");
    printf(" System freq \t: %d Hz\n", SystemCoreClock);
    printf(" UART freq \t: %d Hz\n", UART_BAUD);
    printf(" Loop back \t: %d bytes\n\n", BUFF_SIZE);
    fflush(stdout);

    while (1) {

    	LEIDO=UART_ReadByte(MXC_UART0);
    	printf("%d",UT_CharToHex(LEIDO));
    	fflush(stdout);

    	//printf(" Loop back \t: %d bytes\n\n", BUFF_SIZE);
    }


}



