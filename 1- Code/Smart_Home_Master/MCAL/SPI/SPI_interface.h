/*****************************************************************/
/***********		Author: Ahmed Mohamed 			**************/
/***********		Layer: MCAL			 			**************/
/***********		Component: SPI			 		**************/
/***********		Version: 1.00		 			**************/
/***********		Date: 17-12-2022	 			**************/
/*****************************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidInitMaster(void);

void SPI_voidInitSlave(void);

void SPI_voidTransferByte(u8 Copy_u8Data);

u8 SPI_u8ReceiveByte(void);


u8 SPI_u8Transceive(u8 Copy_u8Data);

void SPI_voidEnableInterrupt(void);

void SPI_voidDisableInterrupt(void);

void SPI_voidSetCallBack(void (*PtrToSPI_ISR)(void));
#endif
