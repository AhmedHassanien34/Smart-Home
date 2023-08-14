/*****************************************************************/
/***********		Author: Ahmed Mohamed 			**************/
/***********		Layer: MCAL			 			**************/
/***********		Component: SPI			 		**************/
/***********		Version: 1.00		 			**************/
/***********		Date: 17-12-2022	 			**************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"
#include "SPI_register.h"

static void (*SPI_ISR) (void)= NULL;

void SPI_voidInitMaster(void)
{
	DIO_u8SetPinDirection(DIO_u8PORTB , DIO_u8PIN5 ,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTB , DIO_u8PIN6 ,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(DIO_u8PORTB , DIO_u8PIN7 ,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTB , DIO_u8PIN4 ,DIO_u8PIN_OUTPUT);
	/*Data Order By Default*/

	/*Master Initialization*/
	SET_BIT(SPCR,SPCR_MASTR);

	/*Clock Polarity By Default*/

	/*Clock Phase By Default*/

	/*Clock Prescaler: Divide by 16 */
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

void SPI_voidInitSlave(void)
{
	DIO_u8SetPinDirection(DIO_u8PORTB , DIO_u8PIN4 ,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(DIO_u8PORTB , DIO_u8PIN5 ,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(DIO_u8PORTB , DIO_u8PIN6 ,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTB , DIO_u8PIN7 ,DIO_u8PIN_INPUT);
	/*Data Order By Default*/

	/*Slave Initialization*/
	CLR_BIT(SPCR,SPCR_MASTR);

	/*Clock Polarity By Default*/

	/*Clock Phase By Default*/

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

void SPI_voidTransferByte(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
	while(GET_BIT(SPSR,SPSR_SPIF) == 0);		/* wait here while SPIF flag set */
}


u8 SPI_u8ReceiveByte(void) {
	while(GET_BIT(SPSR,SPSR_SPIF) == 0);
	return SPDR;
}

u8 SPI_u8Transceive(u8 Copy_u8Data)
{
	/*Send the data*/
	SPDR = Copy_u8Data;

	/*Wait (busy waiting) until transfer complete*/
	while(GET_BIT(SPSR,SPSR_SPIF) == 0); /*Time Out*/ /*1*/

	/*Get the exchanged data*/
	return SPDR; /*2*/
	/*1 , 2 Clear Flag*/

}

void SPI_voidEnableInterrupt(void)
{
	SET_BIT(SPCR ,SPCR_SPIE);
}
void SPI_voidDisableInterrupt(void)
{
	CLR_BIT(SPCR , SPCR_SPIE);
}
void SPI_voidSetCallBack(void (*PtrToSPI_ISR)(void))
{
	SPI_ISR = PtrToSPI_ISR;
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	SPI_ISR();
}


