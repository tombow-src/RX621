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

void MTU2_initialize(void)
{
    /* MTU9 = PWM Mode 1 */
    MSTP(MTU9) = 0;              /* Wake up MTU9 */

    /* タイマプリスケーラ選択ビット */
    /* 内部クロック：PCLK / 16 でカウント */
    MTU9.TCR.BIT.TPSC = 2;

    /* クロックエッジ選択ビット */
    /* 立ち下がりエッジでカウント */
    MTU9.TCR.BIT.CKEG = 1;
                             

    /* カウンタクリア要因選択ビット */
    /* TGRAのコンペアマッチ/インプットキャプチャでTCNTクリア */
    MTU9.TCR.BIT.CCLR = 1;

    /* モード選択ビット */
    /* PWMモード1 */
    MTU9.TMDR.BIT.MD = 2;

    /* バッファ動作Aビット */
    /* TGRAとTGRCレジスタは通常動作 */
    MTU9.TMDR.BIT.BFA = 0;

    /* バッファ動作Bビット */
    /* TGRBとTGRDレジスタは通常動作 */
    MTU9.TMDR.BIT.BFB = 0;

    /* I/OコントロールAビット */
    /* 初期出力はLow出力,コンペアマッチでHigh出力 */
    MTU9.TIORH.BIT.IOA = 2;

    /* I/OコントロールBビット */
    /* 初期出力はLow出力,コンペアマッチでLow出力 */
    MTU9.TIORH.BIT.IOB = 1;

    /* タイマジェネラルレジスタA */
    /* (1/48000000)*16*60000=20msec(50Hz) */
    MTU9.TGRA = 60000;

    /* タイマジェネラルレジスタB */
    /* (1/48000000)*16*4500=1.5msec */
    MTU9.TGRB = 4500;            

    /* I/OコントロールCビット */
    /* 初期出力はLow出力,コンペアマッチでHigh出力 */
    MTU9.TIORL.BIT.IOC = 2;

    /* I/OコントロールDビット */
       /*  初期出力はLow出力,コンペアマッチでLow出力 */
    MTU9.TIORL.BIT.IOD = 1;

    /* タイマジェネラルレジスタC */
       /* (1/48000000)*16*60000=20 msec(50Hz) */
    MTU9.TGRC = 60000;

    /* タイマジェネラルレジスタD */
       /* (1/48000000)*16*4500=1.5 msec */
    MTU9.TGRD = 4500;

    /* タイマカウンタ（TCNT） */
    MTU9.TCNT = 0;
    
    /* MTU9.TCNTはカウント動作 */
    MTUB.TSTR.BIT.CST3 = 1;
}

void main(void)
{
    long int i;

    /* コアクロック96MHz */
    SYSTEM.SCKCR.BIT.ICK = 0;

    /* 周辺機器クロック PCLK=48MHz */
    SYSTEM.SCKCR.BIT.PCK = 1;

    MTU2_initialize();

    while(1) {
        /* タイマジェネラルレジスタB    */
        /* (1/48000000)*16*2400=0.8msec */
        MTU9.TGRB = 2400;
        for (i = 0 ; i <= 21000000 ; i++) {
            /* タイマジェネラルレジスタD */
            MTU9.TGRD = 2400 + (i / 5000);
        }

        /* タイマジェネラルレジスタB     */
        /* (1/48000000)*16*6600=2.25msec */
        MTU9.TGRB = 6600;
        for (i = 0 ; i <= 21000000 ; i++) {
            /* タイマジェネラルレジスタD */
            MTU9.TGRD = 6600 - (i / 5000);
        }
    }
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
