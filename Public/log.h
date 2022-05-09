#ifndef __LOG_H
#define __LOG_H

#include "usart.h"
#define PLOG(x) printf("%s:%d return %d\r\n",__FILE__,__LINE__,x) 
//#define PLOG(x) x

#endif /*__LOG_H*/



