/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: HAL			 			***********************/
/********************			Component: Servo Motor 		    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 16-12-2022	 			***********************/
/**************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "MAP_interface.h"

#include "SvM_interface.h"
#include "SvM_private.h"
#include "SvM_config.h"
void SERVO_voidTimer1InitOCR1AB(void)
{
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN5,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_OUTPUT);
	TIMER_voidTimer1Enable(TIMER1_MODE_FAST_PWM_ICR1,TIMER1_MODE_CHANNEL_A_CLEAR_OC1A,TIMER1_MODE_CHANNEL_B_CLEAR_OC1B);
	TIMER_voidTimer1SetICR1 (20000);
}
void SERVO_voidTimer1InitOCR1B(void)
{
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_OUTPUT);
	TIMER_voidTimer1Enable(TIMER1_MODE_FAST_PWM_ICR1,TIMER1_MODE_CHANNEL_A_CLEAR_OC1A,TIMER1_MODE_CHANNEL_B_CLEAR_OC1B);
	TIMER_voidTimer1SetICR1 (19999);
}
void SERVO_voidTimer1ServoSetAngleOCR1A(u32 Copy_u32Angle)
{
	//TIMER_voidTimer1SetICR1 (19999);
	u16 Local_u32AnglePulse = Map(0,180,750,2500,Copy_u32Angle);

	TIMER_voidTimer1SetOCR1A(Local_u32AnglePulse);
}
void SERVO_voidTimer1ServoSetAngleOCR1B(u32 Copy_u32Angle)
{
	//TIMER_voidTimer1SetOCR1A (19999);
	u16 Local_u32AnglePulse = Map(0,180,750,2500,Copy_u32Angle);
	TIMER_voidTimer1SetOCR1B(Local_u32AnglePulse);
}
