/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: MCAL			 			***********************/
/********************			Component: ADC				    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 16-12-2022	 			***********************/
/**************************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


typedef struct
{
	u8 * Channel;
	u8 * Result;
	u8 Size;
	void (*NotificationFunc)(void);

}Chain_t;

void ADC_voidInit(void);

u16 ADC_u8GetChannelReading(u8 Copy_u8Channel);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u8* Copy_pu8Reading);

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u8* Copy_pu8Reading, void(*Copy_pvNotificationFunc)(void));

u8 ADC_u8StartChainAsynch(Chain_t * Copy_Chain);

#endif