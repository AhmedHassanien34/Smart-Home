/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: LIB			 			***********************/
/********************			Component: STD_TYPES.h			***********************/
/********************			Version: 2.00		 			***********************/
/********************			Date: 29-1-2023 				***********************/
/**************************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char		 u8;
typedef signed char			 s8;

typedef unsigned short		 u16;
typedef signed short		 s16;

typedef unsigned long		 u32;
typedef signed long			 s32;

typedef unsigned long long   u64;
typedef signed long long     s64;

typedef float				 f32;
typedef double				 f64;
typedef long double          f128;

#define TRUE 	 	 (u8)0x01
#define FALSE	 	 (u8)0x00
#define NULL  		 ((void*)0)

#define OK				0
#define NOK				1
#define NULL_POINTER	2

#endif /* STD_TYPES_H_ */
