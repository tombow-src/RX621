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

void timer_1ms(void)
{
    static    unsigned short u2_counter;
    
    if (u2_counter < 1000) {
        u2_counter ++;
    }
    else {
        if (PORT2.DR.BIT.B1 == 1) {
            PORT2.DR.BIT.B1 = 0;
        }
        else {
            PORT2.DR.BIT.B1 = 1;
        }
        u2_counter = 0;
    }
}

void CMT0_initialize(void)
{
    // CMT0 1ms
    MSTP(CMT0) = 0;                 /* Wake up CMT0 */
    CMT0.CMCR.BIT.CMIE = 1;         /* Enable interrupt */
    CMT0.CMCR.BIT.CKS = 0;          /* PCLK/8 */
    CMT0.CMCOR = 6000;              /* Time interval 1ms */
    IPR(CMT0, CMI0) = 3;            /* Interrupt level 3 */
    IEN(CMT0, CMI0) = 1;            /* Enable CMT0 interrup */
    CMT.CMSTR0.BIT.STR0 = 1;        /* CMT0 counter start */
}

void main(void)
{
    SYSTEM.SCKCR.BIT.ICK = 0;               /* コアクロック96MHz */
    SYSTEM.SCKCR.BIT.PCK = 1;               /* 周辺機器クロック PCLK=48MHz */

    PORT2.DR.BIT.B1 = 0;                    /* PORT21 OFF 設定 */
    PORT2.DDR.BIT.B1 = 1;                   /* PORT21を出力に設定 */

    CMT0_initialize();
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
