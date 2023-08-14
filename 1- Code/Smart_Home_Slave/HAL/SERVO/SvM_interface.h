/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: HAL			 			***********************/
/********************			Component: Servo Motor 		    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 16-12-2022	 			***********************/
/**************************************************************************************/

#ifndef SvM_INTERFACE_H
#define SvM_INTERFACE_H



void SERVO_voidTimer1InitOCR1AB(void);
void SERVO_voidTimer1InitOCR1B(void);
void SERVO_voidTimer1ServoSetAngleOCR1A(u32 copy_u32Angle);
void SERVO_voidTimer1ServoSetAngleOCR1B(u32 copy_u32Angle);




#endif
