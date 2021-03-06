///******************************************************************************
//*
//* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
//*
//* Permission is hereby granted, free of charge, to any person obtaining a copy
//* of this software and associated documentation files (the "Software"), to deal
//* in the Software without restriction, including without limitation the rights
//* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//* copies of the Software, and to permit persons to whom the Software is
//* furnished to do so, subject to the following conditions:
//*
//* The above copyright notice and this permission notice shall be included in
//* all copies or substantial portions of the Software.
//*
//* Use of the Software is limited solely to applications:
//* (a) running on a Xilinx device, or
//* (b) that interact with a Xilinx device through a bus or interconnect.
//*
//* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
//* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//* SOFTWARE.
//*
//* Except as contained in this notice, the name of the Xilinx shall not be used
//* in advertising or otherwise to promote the sale, use or other dealings in
//* this Software without prior written authorization from Xilinx.
//*
//******************************************************************************/
//
///*
// * helloworld.c: simple test application
// *
// * This application configures UART 16550 to baud rate 9600.
// * PS7 UART (Zynq) is not initialized by this application, since
// * bootrom/bsp configures it to baud rate 115200
// *
// * ------------------------------------------------
// * | UART TYPE   BAUD RATE                        |
// * ------------------------------------------------
// *   uartns550   9600
// *   uartlite    Configurable only in HW design
// *   ps7_uart    115200 (configured by bootrom/bsp)
// */
//
//#include <stdio.h>
//#include "xil_printf.h"
//#include "platform.h"
//#include "xparameters.h"
//#include "xgpio_l.h"
//#include "xtmrctr_l.h"
//#include "xil_io.h"
////#include "xuartlite_l.h"
//
//#include "stdbool.h"
//
///******************************** Data types *********************************/
//
//// State machine data type
//typedef enum {Stopped, Started, SetLSSec, SetMSSec, SetLSMin, SetMSMin} TFSMState;
//
//// Buttons GPIO masks
//#define BUTTON_UP_MASK		0x01
//#define BUTTON_DOWN_MASK	0x04
//#define BUTTON_RIGHT_MASK	0x08
//#define BUTTON_CENTER_MASK	0x10
//
//// Data structure to store buttons status
//typedef struct SButtonStatus
//{
//	bool upPressed;
//	bool downPressed;
//	bool setPressed;
//	bool startPressed;
//
//	bool setPrevious;
//	bool startPrevious;
//} TButtonStatus;
//
//// Data structure to store countdown timer value
//typedef struct STimerValue
//{
//	unsigned int minMSValue;
//	unsigned int minLSValue;
//	unsigned int secMSValue;
//	unsigned int secLSValue;
//} TTimerValue;
//
///***************************** Helper functions ******************************/
//
//// Rising edge detection and clear
//bool DetectAndClearRisingEdge(bool* pOldValue, bool newValue)
//{
//	bool retValue;
//
//	retValue = (!(*pOldValue)) && newValue; //&& - AND l?gico as we work with boolean values
//	*pOldValue = newValue;
//	return retValue;
//}
//
//// Modular increment
//bool ModularInc(unsigned int* pValue, unsigned int modulo)
//{
//	if (*pValue < modulo - 1)
//	{
//		(*pValue)++;
//		return FALSE;
//	}
//	else
//	{
//		*pValue = 0;
//		return TRUE;
//	}
//}
//
//// Modular decrement
//bool ModularDec(unsigned int* pValue, unsigned int modulo)
//{
//	if (*pValue > 0)
//	{
//		(*pValue)--;
//		return FALSE;
//	}
//	else
//	{
//		*pValue = modulo - 1;
//		return TRUE;
//	}
//}
//
//// Tests if all timer digits are zero
//bool IsTimerValueZero(const TTimerValue* pTimerValue)
//{
//	return ((pTimerValue->secLSValue == 0) && (pTimerValue->secMSValue == 0) &&
//			(pTimerValue->minLSValue == 0) && (pTimerValue->minMSValue == 0));
//}
//
//// Conversion of the countdown timer values stored in a structure to an array of digits
//void TimerValue2DigitValues(const TTimerValue* pTimerValue, unsigned int digitValues[8])
//{
//	digitValues[0] = 0;		//d?gito mais ? direita
//	digitValues[1] = 0;
//	digitValues[2] = pTimerValue->secLSValue;
//	digitValues[3] = pTimerValue->secMSValue;
//	digitValues[4] = pTimerValue->minLSValue;
//	digitValues[5] = pTimerValue->minMSValue;
//	digitValues[6] = 0;
//	digitValues[7] = 0;		//d?gito mais ? esquerda
//}
//
///******************* Countdown timer operations functions ********************/
//
//void RefreshDisplayInfo(unsigned char digitEnables, const unsigned int digitValues[8], //all enables come in positive logic
//					 unsigned char decPtEnables, unsigned char refrRate, unsigned char brightness)
//{
//	// Insert your code here...
//    ///*** STEP 1
//    unsigned int newDigitValues = 0;
//
//    for (int i = 0; i < 8; i++) {
//        newDigitValues = newDigitValues << 4 | digitValues[7-i];
//    }
//
//    Xil_Out32(XPAR_CUSTOMDISPLAYS_0_S00_AXI_BASEADDR + 0, ~digitEnables);
//    Xil_Out32(XPAR_CUSTOMDISPLAYS_0_S00_AXI_BASEADDR + 4, ~decPtEnables);
//    Xil_Out32(XPAR_CUSTOMDISPLAYS_0_S00_AXI_BASEADDR + 8, newDigitValues);
//}
//
//void ReadButtons(TButtonStatus* pButtonStatus)
//{
//	unsigned int buttonsPattern;
//
//	//buttonsPattern = // Insert your code here...
//	///*** STEP 2 (DONE)
//
//	buttonsPattern = XGpio_ReadReg(XPAR_AXI_GPIO_BUTTONS_BASEADDR, XGPIO_DATA_OFFSET);
//
//	pButtonStatus->upPressed    = buttonsPattern & BUTTON_UP_MASK;
//	pButtonStatus->downPressed  = buttonsPattern & BUTTON_DOWN_MASK;
//	pButtonStatus->setPressed   = buttonsPattern & BUTTON_RIGHT_MASK;
//	pButtonStatus->startPressed = buttonsPattern & BUTTON_CENTER_MASK;
//}
//
//void UpdateStateMachine(TFSMState* pFSMState, TButtonStatus* pButtonStatus, bool zeroFlag, unsigned char* pSetFlags)
//{
//	// Insert your code here...
//	///*** STEP 4 (DONE)
//
//	switch(*pFSMState)
//	{
//		case Stopped:
//		{
//			*pSetFlags = 0x0;
//			if (DetectAndClearRisingEdge(&pButtonStatus->startPrevious, pButtonStatus->startPressed) && !zeroFlag)
//				*pFSMState = Started;
//			else if (DetectAndClearRisingEdge(&pButtonStatus->setPrevious, pButtonStatus->setPressed)) {
//				*pFSMState = SetMSMin;
//				*pSetFlags = 0x8;
//			}
//			break;
//		}
//
//		case Started:
//		{
//			*pSetFlags = 0x0;
//			if (DetectAndClearRisingEdge(&pButtonStatus->startPrevious, pButtonStatus->startPressed) || zeroFlag)
//				*pFSMState = Stopped;
//			else if (DetectAndClearRisingEdge(&pButtonStatus->setPrevious, pButtonStatus->setPressed)) {
//				*pFSMState = SetMSMin;
//				*pSetFlags = 0x8;
//			}
//			break;
//		}
//
//		case SetMSMin:
//		{
//			if (DetectAndClearRisingEdge(&pButtonStatus->setPrevious, pButtonStatus->setPressed)) {
//				*pFSMState = SetLSMin;
//				*pSetFlags = 0x4;
//			}
//			break;
//		}
//
//		case SetLSMin:
//		{
//			if (DetectAndClearRisingEdge(&pButtonStatus->setPrevious, pButtonStatus->setPressed)) {
//				*pFSMState = SetMSSec;
//				*pSetFlags = 0x2;
//			}
//			break;
//		}
//
//		case SetMSSec:
//		{
//			if (DetectAndClearRisingEdge(&pButtonStatus->setPrevious, pButtonStatus->setPressed)) {
//				*pFSMState = SetLSSec;
//				*pSetFlags = 0x1;
//			}
//			break;
//		}
//
//		case SetLSSec:
//		{
//			if (DetectAndClearRisingEdge(&pButtonStatus->setPrevious, pButtonStatus->setPressed)) {
//				*pFSMState = Stopped;
//				*pSetFlags = 0x0;
//			}
//			break;
//		}
//
//		default:
//		{
//			*pFSMState = Stopped;
//			*pSetFlags = 0x0;
//		}
//	}
//}
//
//void SetCountDownTimer(TFSMState fsmState, const TButtonStatus* pButtonStatus, TTimerValue* pTimerValue)
//{
//	// Insert your code here...
//	///*** STEP 5 (DONE)
//
//	switch(fsmState)
//	{
//		case SetMSMin:
//		{
//			if (pButtonStatus->upPressed)
//				ModularInc(&pTimerValue->minMSValue, 6);
//			else if (pButtonStatus->downPressed)
//				ModularDec(&pTimerValue->minMSValue, 6);
//			break;
//		}
//
//		case SetLSMin:
//		{
//			if (pButtonStatus->upPressed)
//				ModularInc(&pTimerValue->minLSValue, 10);
//			else if (pButtonStatus->downPressed)
//				ModularDec(&pTimerValue->minLSValue, 10);
//			break;
//		}
//
//		case SetMSSec:
//		{
//			if (pButtonStatus->upPressed)
//				ModularInc(&pTimerValue->secMSValue, 6);
//			else if (pButtonStatus->downPressed)
//				ModularDec(&pTimerValue->secMSValue, 6);
//			break;
//		}
//
//		case SetLSSec:
//		{
//			if (pButtonStatus->upPressed)
//				ModularInc(&pTimerValue->secLSValue, 10);
//			else if (pButtonStatus->downPressed)
//				ModularDec(&pTimerValue->secLSValue, 10);
//			break;
//		}
//		default:
//		{
//			fsmState = Stopped;
//		}
//	}
//}
//
//void DecCountDownTimer(TFSMState fsmState, TTimerValue* pTimerValue)
//{
//	// Insert your code here...
//	///*** STEP 3 (DONE)
//
//	if (fsmState==Started)
//	{
//		if (ModularDec(&pTimerValue->secLSValue, 10))
//		{
//			if (ModularDec(&pTimerValue->secMSValue, 6))
//			{
//				if (ModularDec(&pTimerValue->minLSValue, 10))
//				{
//					if (ModularDec(&pTimerValue->minMSValue, 6))
//					{
//						pTimerValue->secLSValue = 0;
//						pTimerValue->secMSValue = 0;
//						pTimerValue->minLSValue = 0;
//						pTimerValue->minMSValue = 0;
//					}
//				}
//			}
//		}
//	}
//}
//
///******************************* Main function *******************************/
//
//int main()
//{
//	init_platform();
//	xil_printf("\n\nCount down timer - polling based version with custom 7-segment display control.\nConfiguring...");
//
//	//	GPIO tri-state configuration
//	//	Inputs
//	XGpio_WriteReg(XPAR_AXI_GPIO_SWITCHES_BASEADDR, XGPIO_TRI_OFFSET,  0xFFFFFFFF);
//	XGpio_WriteReg(XPAR_AXI_GPIO_BUTTONS_BASEADDR,  XGPIO_TRI_OFFSET,  0xFFFFFFFF);
//
//	//	Outputs
//	XGpio_WriteReg(XPAR_AXI_GPIO_LEDS_BASEADDR,     XGPIO_TRI_OFFSET,  0xFFFF0000);
//
//	xil_printf("\nIOs configured.");
//
// 	// Disable hardware timer
// 	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, 0, 0x00000000);
//	// Set hardware timer load value
//	XTmrCtr_SetLoadReg(XPAR_AXI_TIMER_0_BASEADDR, 0, 12500000); // Counter will wrap around every 0.125s
//	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, 0, XTC_CSR_LOAD_MASK);
//	// Enable hardware timer, down counting with auto reload
//	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, 0, XTC_CSR_ENABLE_TMR_MASK  |
//															  XTC_CSR_AUTO_RELOAD_MASK |
//															  XTC_CSR_DOWN_COUNT_MASK);
//
//	xil_printf("\n\rHardware timer configured.");
//
//	xil_printf("\n\rSystem running.\n\r");
//
//	// Timer event software counter
//	unsigned hwTmrEventCount = 0;
//
//	TFSMState     fsmState       = Stopped;
//	unsigned char setFlags       = 0x0;
//	TButtonStatus buttonStatus   = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};
//	TTimerValue   timerValue     = {5, 9, 5, 9};
//	bool          zeroFlag       = FALSE;
//
//	unsigned char digitEnables   = 0x3C;
//	unsigned int  digitValues[8] = {0, 0, 9, 5, 9, 5, 0, 0};
//	unsigned char decPtEnables   = 0x00;
//
//	bool          blink1HzStat   = FALSE;
//	bool          blink2HzStat   = FALSE;
//
//  	while (1)
//  	{
//  		unsigned int tmrCtrlStatReg = XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, 0);
//
//  		if (tmrCtrlStatReg & XTC_CSR_INT_OCCURED_MASK)
//		{
//  			// Clear hardware timer event (interrupt request flag)
//			XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, 0,
//										tmrCtrlStatReg | XTC_CSR_INT_OCCURED_MASK);
//			hwTmrEventCount++;
//
//			// Put here operations that must be performed at 8Hz rate
//			// Read push buttons
//			ReadButtons(&buttonStatus);
//			// Update state machine
//			UpdateStateMachine(&fsmState, &buttonStatus, zeroFlag, &setFlags);
//			if ((setFlags == 0x0) || (blink2HzStat))
//			{
//				digitEnables = 0x3C; // All digits active
//			}
//			else
//			{
//				digitEnables = (~(setFlags << 2)) & 0x3C; // Setting digit inactive
//			}
//
//
//			if (hwTmrEventCount % 2 == 0) // 4Hz
//			{
//				// Put here operations that must be performed at 4Hz rate
//				// Switch digit set 2Hz blink status
//				blink2HzStat = !blink2HzStat;
//
//
//				if (hwTmrEventCount % 4 == 0) // 2Hz
//				{
//					// Put here operations that must be performed at 2Hz rate
//					// Switch point 1Hz blink status
//					blink1HzStat = !blink1HzStat;
//					if (fsmState == Started)
//						decPtEnables = (blink1HzStat ? 0x00 : 0x10);
//
//					// Digit set increment/decrement
//					SetCountDownTimer(fsmState, &buttonStatus, &timerValue);
//
//
//					if (hwTmrEventCount == 8) // 1Hz
//					{
//						xil_printf("\r%d%d:%d%d", timerValue.minMSValue, timerValue.minLSValue, timerValue.secMSValue, timerValue.secLSValue);
//						// Put here operations that must be performed at 1Hz rate
//						// Count down timer normal operation
//						DecCountDownTimer(fsmState, &timerValue);
//
//						// Reset hwTmrEventCount every second
//						hwTmrEventCount = 0;
//					}
//				}
//			}
//			zeroFlag = IsTimerValueZero(&timerValue);
//			TimerValue2DigitValues(&timerValue, digitValues);
//
//			// Refresh displays
//		}
//
//  		// Put here operations that are performed whenever possible
//		///*** STEP 6
//  		XGpio_WriteReg(XPAR_AXI_GPIO_LEDS_BASEADDR, XGPIO_DATA_OFFSET, zeroFlag ? 0x0001 : 0x0000); //switch on the led indicating the end of counting
//		///***
//	}
//
//	cleanup_platform();
//	return 0;
//}
