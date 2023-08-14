/*****************************************************************/
/***********		Author: Ahmed Mohamed 			**************/
/***********		Layer: MCAL			 			**************/
/***********		Component: TIMER		 		**************/
/***********		Version: 2.00		 			**************/
/***********		Date: 29-1-2023		 			**************/
/*****************************************************************/


#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR0					*((volatile u8*)0x53)		//Timer0 control register
#define TCCR0_FOC0              7
#define TCCR0_WGM00				6				    		//Wavefoem generation Mode bit0
#define TCCR0_COM01	            5
#define TCCR0_COM00    	        4
#define TCCR0_WGM01				3							//Wavefoem generation Mode bit1
#define TCCR0_CS02				2 							//Prescaler bit2
#define TCCR0_CS01				1							//Prescaler bit1
#define TCCR0_CS00				0							//Prescaler bit0

#define TCNT0					*((volatile u8*)0x52)		//Timer/Counter Register

#define OCR0 					*((volatile u8*)0x5C)		//Output compare register 0

#define TIMSK					*((volatile u8*)0x59)		//TIMER MASK
#define TIMSK_TOIE0				0							//Timer/Counter0 Overflow Interrupt Enable
#define TIMSK_OCIE0				1							//Output compare 0 interrupt enable
#define TIMSK_TOIE1				2
#define TIMSK_OCIE1B			3
#define TIMSK_OCIE1A			4
#define TIMSK_TICIE1			5							//Timer1 input capture interrupt enable
#define TIMSK_TOIE2				6
#define TIMSK_OCIE2				7



#define TIFR	                *((volatile u8*)0x58)
#define TIFR_TOV0_BIT           0
#define TIFR_OCF0_BIT           1
#define TIFR_TOV2	            6
#define TIFR_OCF2  	            7

#define TIMER_u16_TCNT1               *((volatile u16*)0x4C)

#define TIMER_u16_OCR1A              *((volatile u16*)0x4A)

#define OCR1AH              *((volatile u8*)0x4B)
#define OCR1AL               *((volatile u8*)0x4A)

#define OCR1BH              *((volatile u8*)0x49)
#define OCR1BL               *((volatile u8*)0x48)
#define OCR1B 				 *((volatile u8*)0x48)

#define ICR1H                *((volatile u8*)0x47)
#define ICR1L                *((volatile u8*)0x46)

#define TIMER_u16_OCR1B               *((volatile u16*)0x48)

#define TIMER_u8_ICR1H                *((volatile u8*)0x47)
#define TIMER_u8_ICR1L               *((volatile u8*)0x46)
#define TIMER_u16_ICR1                *((volatile u16*)0x46)
//TIMER2
#define TCCR2	                *((volatile u8*)0x45)
#define TCCR2_FOC2       	    7
#define TCCR2_WGM20      	    6
#define TCCR2_WGM21      	    3
#define TCCR2_COM20      	    4
#define TCCR2_COM21     	    5
#define TCCR2_CS20      	    0
#define TCCR2_CS21       	    1
#define TCCR2_CS22       	    2

#define TCNT2 					*((volatile u8*)0x44)

#define OCR2				    *((volatile u8*)0x43)


/**********************************************************************************/
//TIMER1
#define TCCR1A					*((volatile u8*)0x4F)		//Timer1 control registerA
#define TCCR1A_WGM10			0
#define TCCR1A_WGM11			1
#define TCCR1A_FOC1B         	2
#define TCCR1A_FOC1A         	3
#define TCCR1A_COM1B0      		4
#define TCCR1A_COM1B1       	5
#define TCCR1A_COM1A0			6
#define TCCR1A_COM1A1			7

#define	TCCR1B					*((volatile u8*)0x4E)		//Timer1 control registerB
#define	TCCR1B_CS10				0
#define	TCCR1B_CS11				1
#define	TCCR1B_CS12				2
#define	TCCR1B_WGM12			3
#define	TCCR1B_WGM13			4
#define TCCR1B_ICES1			6 							//Input capture edge select
#define TCCR1B_ICNC1     	    7

#define TCNT1H         	        *((volatile u8*)0x4D)
#define TCNT1L	                *((volatile u8*)0x4C)
#define TCNT1					*((volatile u16*)0x4C)		//Timer1 control register

#define ICR1					*((volatile u16*)0x46)		//Input Capture Register1
#define OCR1A 					*((volatile u16*)0x4A)		//Output compare registerA

#endif
