#ifndef __TYPES_H
#define __TYPES_H



#ifndef UINT8
#define UINT8 			unsigned char
#endif /*UINT8*/

#ifndef UINT16
#define UINT16 			unsigned short int
#endif /*UINT16*/

#ifndef UINT32
#define UINT32			unsigned long int
#endif /*UINT32*/

#ifndef UINT64
#define UINT64			unsigned long long
#endif /*UINT64*/

#ifndef INT8
#define INT8			char
#endif /*INT8*/

#ifndef INT16
#define INT16			short int
#endif /*INT16*/

#ifndef INT32
#define INT32			long int
#endif /*INT32*/

#ifndef INT64
#define INT64			long long
#endif /*INT64*/

#ifndef FLOAT32
#define FLOAT32			float
#endif /*FLOAT32*/

#ifndef FLOAT64
#define FLOAT64			double
#endif /*FLOAT64*/
	



#if defined(__cplusplus)
#define	BOOL	bool 
#define TRUE	true 
#define FALSE	false
#define _Bool	bool
#elif  defined(__STDC_VERSION__)&&__STDC_VERSION__== 199901U
#include <stdbool.h>
#define BOOL    bool
#define TRUE    true
#define FALSE   false
#elif defined(__STDC_VERSION__)&&__STDC_VERSION__== 201112U
#include <stdbool.h>
#define BOOL    bool
#define TRUE    true
#define FALSE   false
#else
#define BOOL	unsigned char 
#define FALSE	0U
#define TRUE	1U
#endif /*...*/



#endif /*__TYPES_H*/

