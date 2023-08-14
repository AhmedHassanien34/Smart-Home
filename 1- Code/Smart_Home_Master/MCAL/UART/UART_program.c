/*****************************************************************/
/***********		Author: Ahmed Mohamed 			**************/
/***********		Layer: MCAL			 			**************/
/***********		Component: UART			 		**************/
/***********		Version: 2.00		 			**************/
/***********		Date: 29-1-2023		 			**************/
/*****************************************************************/
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_register.h"
#include "UART_config.h"

static void (*UART_RX_Fptr) (void) = NULL;
static void (*UART_TX_Fptr) (void) = NULL;

void UART_voidInit(void)
{	

/********************************************************** UBRR ***************************************/
	u16 Local_u16UBRRValue ;
	Local_u16UBRRValue = UART_BAUD_RATE_UBRR;
	UBRRL=(u8)Local_u16UBRRValue;
	UBRRH=(u8)(Local_u16UBRRValue>>8);
/************************************* UCSRA *******************************************************/
    #if     UART_SPEED == UART_NORMAL_SPEED
	        CLR_BIT(UCSRA,UCSRA_U2X);
    #elif   UART_SPEED == UART_DOUBLE_SPEED
	        SET_BIT(UCSRA,UCSRA_U2X);
    #endif

    #if     UART_PROCESSOR_COMMUNICATION == UART_SINGLE_CYCLE_PRICESSOR
            CLR_BIT(UCSRA,UCSRA_MPCM);
    #elif   UART_PROCESSOR_COMMUNICATION == UART_MULTI_PRICESSOR
            SET_BIT(UCSRA,UCSRA_MPCM);
    #endif
/**************************************** UCSRB ****************************************************/
    #if     UART_RX_INTERRUPR == UART_RX_DISABLE_INTERRUPR
            CLR_BIT(UCSRB,UCSRB_RXCIE);
    #elif   UART_RX_INTERRUPR == UART_RX_ENABLE_INTERRUPR
            SET_BIT(UCSRB,UCSRB_RXCIEREG);
    #endif

    #if     UART_RX_INTERRUPR == UART_RX_DISABLE_INTERRUPR
            CLR_BIT(UCSRB,UCSRB_RXCIE);
    #elif   UART_RX_INTERRUPR == UART_RX_ENABLE_INTERRUPR
            SET_BIT(UCSRB,UCSRB_RXCIE);
    #endif


    #if     UART_TX_INTERRUPR == UART_TX_DISABLE_INTERRUPR
            CLR_BIT(UCSRB,UCSRB_TXCIE);
    #elif   UART_TX_INTERRUPR == UART_TX_ENABLE_INTERRUPR
            SET_BIT(UCSRB,UCSRB_TXCIE);
    #endif

    #if     UART_UDRE_EMPTY_INTEREGRRUPR == UART_UDRE_EMPTY_DISABLE_INTERRUPR
            CLR_BIT(UCSRB,UCSRB_UDRIE);
    #elif   UART_UDRE_EMPTY_INTERRUPR == UART_UDRE_EMPTY_ENABLE_INTERRUPR
            SET_BIT(UCSRB,UCSRB_UDRIEREG);
    #endif

     //enable UART  transmitter
    SET_BIT(UCSRB,UCSRB_TXEN);

    //enable UART  receiver
    SET_BIT(UCSRB,UCSRB_RXEN);

 /********************************************** UCSRC **********************************************/
    u8 Local_u8UCSRCValue= 0b10000000;
    #if     UART_MODE_SELECT == UART_ASYNCHRONOUS_OPERATION
            CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);
    #elif   UART_MODE_SELECT == UART_SYNCHRONOUS_OPERATION
            SET_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);
    #endif

    #if     UART_PARITY_MODE == UART_DISABLE_PARITY
            CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
            CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
    #elif   UART_PARITY_MODE == UART_ENABLE_EVEN_PARITY
            SET_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
            CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
    #elif   UART_PARITY_MODE == UART_ENABLE_ODD_PARITY
            SET_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
            SET_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
    #endif


    #if     UART_STOPREG_SELECT == UART_1REG_STOP_SELECT
            CLR_BIT(Local_u8UCSRCValue,UCSRC_USBS);
    #elif   UART_STOPREG_SELECT == UART_2REG_STOP_SELECT
            SET_BIT(Local_u8UCSRCValue,UCSRC_USBS);
    #endif


    #if     UART_CHARACTER_SIZE == UART_5_CHARACTER_SIZE
            CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
            CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
            CLR_BIT(UCSRB,UCSRB_UCSZ2);
    #elif   UART_CHARACTER_SIZE == UART_6_CHARACTER_SIZE
            SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
            CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
            CLR_BIT(UCSRB,UCSRB_UCSZ2);
    #elif   UART_CHARACTER_SIZE == UART_7_CHARACTER_SIZE
            CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
            SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
            CLR_BIT(UCSRB,UCSRB_UCSZ2);
    #elif   UART_CHARACTER_SIZE == UART_8_CHARACTER_SIZE
            SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
            SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
            CLR_BIT(UCSRB,UCSRB_UCSZ2);
    #elif   UART_CHARACTER_SIZE == UART_9_CHARACTER_SIZE
            SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
            SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
            SET_BIT(UCSRB,UCSRB_UCSZ2);
    #endif
    UCSRC=Local_u8UCSRCValue;
}
void UART_voidSendChar(u8 Copy_u8Char)
{
	/*UDRE flag is set when the buffer is empty and ready
	for transmitting a new byte so wait until this flag is set to one
	and it will cleared by hardware when u write  new data to puffer.*/

    while((0==GET_BIT(UCSRA,UCSRA_UDRE)));
    UDR = Copy_u8Char;
}
void UART_voidSendString(u8  *Copy_pu8String)
{
	for(u8 Local_u8Counter=0; Copy_pu8String[Local_u8Counter] != '\0' ; Local_u8Counter++)
	{
		  UART_voidSendChar(Copy_pu8String[Local_u8Counter]);
		  _delay_ms(1);
	}

}

u8 UART_voidReceiveChar(void)
{
	/*RXC flag is set when the UART receive data so  wait until this flag is set to one
	and it will cleared by hardware when u read the data*/

	while((0==GET_BIT(UCSRA,UCSRA_RXC)));
	return UDR;
}

void UART_voidRX_InterruptEnable(void)
{
	SET_BIT(UCSRB,UCSRB_RXCIE);
}

void UART_voidRX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,UCSRB_RXCIE);
}

void UART_voidTX_InterruptEnable(void)
{
	SET_BIT(UCSRB,UCSRB_TXCIE);
}

void UART_voidTX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,UCSRB_TXCIE);
}

void UART_voidRX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void __vector_11(void) __attribute__((signal , used));
void __vector_11(void)
{
	UART_RX_Fptr();
}

void UART_voidTX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}

void UART_voidWriteDecimalNumber(u16 Copy_u32Number)
{

	u16 Local_u8Reversed = 1;

	if(0 == Copy_u32Number)
	{
		UART_voidSendChar('0');
	}
	while(0 != Copy_u32Number)
	{
		Local_u8Reversed = ((Local_u8Reversed * 10) + (Copy_u32Number % 10));
		Copy_u32Number /= 10;
	}
	while(1 != Local_u8Reversed)
	{
		UART_voidSendChar((Local_u8Reversed % 10 ) + 48);
		Local_u8Reversed /= 10;
	}



}

u8 UART_u8GetCharBlocking(void)
{
	 u8 Local_u8Char;
	 u16 Counter;
	 while((0==GET_BIT(UCSRA,UCSRA_RXC)));
	 Local_u8Char=UDR;
     return Local_u8Char;
}
u8 UART_u8GetCharNonBlocking(void)
{
	 u8 Local_u8Char;
	 u16 Local_u16Counter;
	 while((Local_u16Counter<2000)&&(0==GET_BIT(UCSRA,UCSRA_RXC)))
	 {
		 Local_u16Counter++;
	 }
	 Local_u8Char=UDR;
     return Local_u8Char;
}
