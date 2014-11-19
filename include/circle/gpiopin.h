//
// gpiopin.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014  R. Stange <rsta2@o2online.de>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _gpiopin_h
#define _gpiopin_h

#define GPIO_PINS	54

enum TGPIOMode
{
	GPIOModeInput,
	GPIOModeOutput,
	GPIOModeInputPullUp,
	GPIOModeInputPullDown,
	GPIOModeAlternateFunction0,
	GPIOModeAlternateFunction1,
	GPIOModeAlternateFunction2,
	GPIOModeAlternateFunction3,
	GPIOModeAlternateFunction4,
	GPIOModeAlternateFunction5,
	GPIOModeUnknown
};

enum TGPIOInterrupt
{
	GPIOInterruptOnRisingEdge,
	GPIOInterruptOnFallingEdge,
	GPIOInterruptOnHighLevel,
	GPIOInterruptOnLowLevel,
	GPIOInterruptOnAsyncRisingEdge,
	GPIOInterruptOnAsyncFallingEdge,
	GPIOInterruptUnknown
};

typedef void TGPIOInterruptHandler (void *pParam);

class CGPIOManager;

class CGPIOPin
{
public:
	// pManager is only required for using interrupts
	CGPIOPin (unsigned nPin, TGPIOMode Mode, CGPIOManager *pManager = 0);
	virtual ~CGPIOPin (void);

	void SetMode (TGPIOMode Mode);
	
	void Write (unsigned nValue);
	unsigned Read (void) const;
#define LOW		0
#define HIGH		1

	void Invert (void);

	void ConnectInterrupt (TGPIOInterruptHandler *pHandler, void *pParam);
	void DisconnectInterrupt (void);

	void EnableInterrupt (TGPIOInterrupt Interrupt);
	void DisableInterrupt (void);

private:
	void SetPullUpMode (unsigned nMode);

	void SetAlternateFunction (unsigned nFunction);

	void InterruptHandler (void);
	friend class CGPIOManager;

private:
	unsigned  m_nPin;
	TGPIOMode m_Mode;
	unsigned  m_nValue;

	CGPIOManager		*m_pManager;
	TGPIOInterruptHandler	*m_pHandler;
	void			*m_pParam;
	TGPIOInterrupt		 m_Interrupt;
};

#endif