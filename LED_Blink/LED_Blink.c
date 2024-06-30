/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#include "iodefine.h"

extern void MTU2_initialize(void);

#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif


void main(void)
{
    long int i;

	SYSTEM.SCKCR.BIT.ICK = 0;				/* コアクロック96MHz */
    SYSTEM.SCKCR.BIT.PCK = 1;				/* 周辺機器クロック PCLK=48MHz */

	PORT2.DR.BIT.B0 = 0;					/* PORT20 OFF 設定 */
	PORT2.DR.BIT.B1 = 0;					/* PORT21 OFF 設定 */
	PORT2.DDR.BIT.B0 = 1;					/* PORT20を出力に設定 */
	PORT2.DDR.BIT.B1 = 1;					/* PORT21を出力に設定 */


    while(1) {
		PORT2.DR.BIT.B0 = 1;
		PORT2.DR.BIT.B1 = 1;

		for (i = 0 ; i <= 50000000 ; i++);

		PORT2.DR.BIT.B0 = 0;
		PORT2.DR.BIT.B1 = 0;

        for (i = 0 ; i <= 50000000 ; i++);
    }
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
