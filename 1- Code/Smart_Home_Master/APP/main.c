#include <util/delay.h>

/********************************************************************************************/
/* Include libraries                                                                        */
/********************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/********************************************************************************************/
/* Include Interface Files in MCAL                                                          */
/********************************************************************************************/
#include "ADC_interface.h"
#include "DIO_interface.h"

/********************************************************************************************/
/* Include Interface Files in HAL                                                           */
/********************************************************************************************/
#include "SvM_interface.h"
#include "CLCD_interface.h"

/* Global Variable */
u8 Global_u8UartRxValue;
u16 Local_u16AnalogRainValue;

/* Function Prototype */
void WIFI_voidReceiveMessage(void);

/**************************************** Entry point *******************************************/
void main (void)
{
	/* Local Variable */
	u8 Local_u8DigitalFireValue,Local_u8DigitalGasValue,Local_u8DigitalPIRValue;
	u8 Soil_Moisture,Soil_Moisture_Value;
	u16 Local_u16AnalogLDRValue,Local_u16AnalogTempValue,Local_u16AnalogSoilValue;
	u16 Temperature;

	/* Initialize DIO */
	DIO_voidInit();

	/* Initialize ADC */
	ADC_voidInit();

	/* Initialize SPI to be master MCU */
	SPI_voidInitMaster();

	/* Initialize UART */
	UART_voidInit();

	/* Enable UART receiver interrupt */
	UART_voidRX_InterruptEnable();

	/* Uart set call back function to interrupt */
	UART_voidRX_SetCallBack(WIFI_voidReceiveMessage);

	/* Initialize LCD */
	CLCD_voidInit();

	/* Enable global interrupt */
	GIE_voidEnable();

	/* Initialize Servo Motors */
	SERVO_voidTimer1InitOCR1AB();

	/* Initialize angle to be 90 */
	SERVO_voidTimer1ServoSetAngleOCR1A(90);
	SERVO_voidTimer1ServoSetAngleOCR1B(90);

	while(1)
	{


		//********************************Flame_Sensor*********************************//

		DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN0,&Local_u8DigitalFireValue);

		if (Local_u8DigitalFireValue == 1)
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_HIGH);
			SPI_voidTransferByte('Z');
			_delay_ms(150);
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
			SPI_voidTransferByte('z');
			_delay_ms(150);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
		}

		//********************************GAS_Sensor*********************************//

		DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN1,&Local_u8DigitalGasValue);

		if (Local_u8DigitalGasValue == 0)
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_HIGH);
			SPI_voidTransferByte('Z');
			_delay_ms(250);
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
			SPI_voidTransferByte('z');
			_delay_ms(250);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
		}



		//********************************Rain_Sensor*********************************//

		Local_u16AnalogRainValue = ADC_u8GetChannelReading(2);
		Local_u16AnalogRainValue = Local_u16AnalogRainValue * 5;

		if ( Local_u16AnalogRainValue >= 350)
		{
			SERVO_voidTimer1ServoSetAngleOCR1B(180);
		}


		//********************************PIR_Sensor*********************************//

		DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN3,&Local_u8DigitalPIRValue);

		if (Local_u8DigitalPIRValue == 1 )
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
		}

		//********************************LDR_Sensor*********************************//

		Local_u16AnalogLDRValue = ADC_u8GetChannelReading(4);

		if ( Local_u16AnalogLDRValue <= 500)
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_LOW);
		}

		//********************************Temperature_Sensor*********************************//

		Local_u16AnalogTempValue = ADC_u8GetChannelReading(5);

		// Calculate the temperature from the ADC value
		Temperature = ( Local_u16AnalogTempValue * 4.88 ) / ( 10 );

		if ( Temperature >= 35)
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
			CLCD_voidGoToXY(0,13);
			CLCD_voidSendString("ON ");
		}
		else if ( Temperature >= 50)
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW);
			CLCD_voidGoToXY(0,13);
			CLCD_voidSendString("OFF");
		}

		//********************************SoilMoisture_Sensor*********************************//

		Local_u16AnalogSoilValue = ADC_u8GetChannelReading(6);

		Soil_Moisture =( Local_u16AnalogSoilValue / 10.24 ) ;

		Soil_Moisture_Value = (100 - Soil_Moisture) ;


		if ( Soil_Moisture_Value <= 10)
		{
			CLCD_voidGoToXY(1,14);
			CLCD_voidSendNumber(Soil_Moisture_Value);
			CLCD_voidGoToXY(1,15);
			CLCD_voidSendString(" ");

			SPI_voidTransferByte('y');
		} else if ( Soil_Moisture_Value == 100)
		{
			CLCD_voidGoToXY(1,14);
			CLCD_voidSendNumber(99);

		}
		else
		{
			CLCD_voidGoToXY(1,14);
			CLCD_voidSendNumber(Soil_Moisture_Value);

			SPI_voidTransferByte('Y');
		}

		//*************************************** LCD *****************************************//

		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Temp:");

		CLCD_voidGoToXY(0,5);
		CLCD_voidSendNumber(Temperature);

		CLCD_voidGoToXY(0,7);
		CLCD_voidSendString(" ");


		CLCD_voidGoToXY(0,9);
		CLCD_voidSendString("Fan:");

		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("Soil Moisture:");

	}
}

void WIFI_voidReceiveMessage(void)
{
	Global_u8UartRxValue = UART_voidReceiveChar();

	switch (Global_u8UartRxValue)
	{
	case 'A': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); break;

	case 'a': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);  break;

	case 'B': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH); break;

	case 'b': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);  break;

	case 'C': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH); break;

	case 'c': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);  break;

	case 'D': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH); break;

	case 'd': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);  break;

	case 'E': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH); break;

	case 'e': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);  break;

	case 'F': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH); break;

	case 'f': DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);  break;

	case 'H': SPI_voidTransferByte('H');		    				    break;

	case 'h': SPI_voidTransferByte('h'); 			  			        break;

	case 'I': SERVO_voidTimer1ServoSetAngleOCR1A(0);  				    break;

	case 'i': SERVO_voidTimer1ServoSetAngleOCR1A(90); 				    break;

	case 'J':
		if ( Local_u16AnalogRainValue <= 100)
		{
			SERVO_voidTimer1ServoSetAngleOCR1B(0);
		}
		break;

	case 'j': SERVO_voidTimer1ServoSetAngleOCR1B(90); 				    break;

	default: break;
	}
}

