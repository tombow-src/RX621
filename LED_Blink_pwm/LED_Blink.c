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

void MTU_initialize(void)
{
    /* MTU1 = PWM Mode 1 */
    MSTP(MTU1) = 0;                 /* Wake up MTU1 */
    MTU1.TCR.BIT.TPSC = 1;       /* タイマプリスケーラ選択ビット                                              */
                                 /*   000:内部クロック：PCLK / 1 でカウント                                   */
                                 /*   001:内部クロック：PCLK / 4 でカウント                                   */
                                 /*   010:内部クロック：PCLK / 16 でカウント                                  */
                                 /*   011:内部クロック：PCLK / 64 でカウント                                  */
                                 /*   100:内部クロック：外部クロック：MTCLKn 端子入力でカウント（n=A,E）      */
                                 /*   101:内部クロック：外部クロック：MTCLKn 端子入力でカウント（n=B,F）      */
                                 /*   110:外部クロック：内部クロック：PCLK ／ 256 でカウント                  */
                                 /*   111:外部クロック：TCNTn のオーバフロー／アンダフローでカウント（n=2,8） */


    MTU1.TCR.BIT.CKEG = 1;       /* クロックエッジ選択ビット        */
                                 /*   00:立ち上がりエッジでカウント */
                                 /*   01:立ち下がりエッジでカウント */
                                 /*   1x:両エッジでカウント         */                               

    MTU1.TCR.BIT.CCLR = 1;       /* カウンタクリア要因選択ビット                                                   */
                                 /*   000:TCNTのクリア禁止                                                         */
                                 /*   001:TGRAのコンペアマッチ/インプットキャプチャでTCNTクリア                    */
                                 /*   010:TGRBのコンペアマッチ/インプットキャプチャでTCNTクリア                    */
                                 /*   011:同期クリア/同期動作をしている他のチャネルのカウンタクリアでTCNTをクリア  */

    /* ---------------------------- */
    /* タイマモードレジスタ（TMDR） */
    /* ---------------------------- */
    MTU1.TMDR.BIT.MD = 2;        /* モード選択ビット                    */
                                 /*   0000:ノーマルモード               */
                                 /*   0001:設定しないでください         */
                                 /*   0010:PWMモード1                   */
                                 /*   0011:PWMモード2                   */
                                 /*   0100:位相計数モード1              */
                                 /*   0101:位相計数モード2              */
                                 /*   0110:位相計数モード3              */
                                 /*   0111:位相計数モード4              */
                                 /*   1000:リセット同期PWMモード        */
                                 /*   1001:設定しないでください         */
                                 /*   101x:設定しないでください         */
                                 /*   1100:設定しないでください         */
                                 /*   1101:相補PWMモード1(山で転送)     */
                                 /*   1110:相補PWMモード2(谷で転送)     */
                                 /*   1111:相補PWMモード3(山・谷で転送) */

    /* --------------------------------------- */
    /* タイマ I/O コントロールレジスタ（TIOR） */
    /* --------------------------------------- */
    MTU1.TIOR.BIT.IOA = 2;      /* I/OコントロールAビット */
                                 /*   0000:出力禁止                                      */
                                 /*   0001:初期出力はLow出力,コンペアマッチでLow出力     */
                                 /*   0010:初期出力はLow出力,コンペアマッチでHigh出力    */
                                 /*   0011:初期出力はLow出力,コンペアマッチでトグル出力  */
                                 /*   0100:出力禁止                                      */
                                 /*   0101:初期出力はHigh出力,コンペアマッチでLow出力    */
                                 /*   0110:初期出力はHigh出力,コンペアマッチでHigh出力   */
                                 /*   0111:初期出力はHigh出力,コンペアマッチでトグル出力 */
                                 /*   1000:立ち上がりエッジでインプットキャプチャ        */
                                 /*   1001:立ち下がりエッジでインプットキャプチャ        */
                                 /*   101x:両エッジでインプットキャプチャ                */

    MTU1.TIOR.BIT.IOB = 1;      /* I/OコントロールBビット */
                                 /*   0000:出力禁止                                      */
                                 /*   0001:初期出力はLow出力,コンペアマッチでLow出力     */
                                 /*   0010:初期出力はLow出力,コンペアマッチでHigh出力    */
                                 /*   0011:初期出力はLow出力,コンペアマッチでトグル出力  */
                                 /*   0100:出力禁止                                      */
                                 /*   0101:初期出力はHigh出力,コンペアマッチでLow出力    */
                                 /*   0110:初期出力はHigh出力,コンペアマッチでHigh出力   */
                                 /*   0111:初期出力はHigh出力,コンペアマッチでトグル出力 */
                                 /*   1000:立ち上がりエッジでインプットキャプチャ        */
                                 /*   1001:立ち下がりエッジでインプットキャプチャ        */
                                 /*   101x:両エッジでインプットキャプチャ                */

    MTU1.TGRA = 30000;          /* タイマジェネラルレジスタA */
                                /* (1 / 48000000) * 4 * 30000 = 2.5 msec */

    MTU1.TGRB = 9000;           /* タイマジェネラルレジスタB */
                                /* (1 / 48000000) * 4 * 9000 = 0.75 msec */

    MTU1.TCNT = 0;              /* タイマカウンタ（TCNT） */



    /* ----------------------------------------------------- */
    /* タイマスタートレジスタ（TSTR）                        */
    /* MTUA.TSTR（MTU0 ～ MTU4）、MTUB.TSTR（MTU6 ～ MTU10） */
    /* ----------------------------------------------------- */
    MTUA.TSTR.BIT.CST1 = 1;      /* カウンタスタート1ビット           */
                                 /*   0:MTU1.TCNTのカウント動作は停止 */
                                 /*   1:MTU1.TCNTはカウント動作       */

}

void main(void)
{
    long int i;

    SYSTEM.SCKCR.BIT.ICK = 0;               /* コアクロック96MHz */
    SYSTEM.SCKCR.BIT.PCK = 1;               /* 周辺機器クロック PCLK=48MHz */

    MTU_initialize();

    PORT2.DR.BIT.B1 = 0;                    /* PORT21 OFF 設定 */
    PORT2.DDR.BIT.B1 = 1;                   /* PORT21を出力に設定 */


    while(1) {
        MTU1.TGRB = 2400;                   /* タイマジェネラルレジスタB */
        PORT2.DR.BIT.B1 = 1;

        for (i = 0 ; i <= 50000000 ; i++);

        MTU1.TGRB = 25000;                   /* タイマジェネラルレジスタB */
        PORT2.DR.BIT.B1 = 0;

        for (i = 0 ; i <= 50000000 ; i++);
    }
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
