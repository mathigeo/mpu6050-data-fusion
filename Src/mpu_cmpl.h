#ifndef __MPU_CMPL_H
#define __MPU_CMPL_H

#include <math.h>

/**
 * @brief 一阶互补滤波数据结构体
 */
typedef struct 
{
	float pitch;
	float roll;
	float yaw;
	float accx;
	float accy;
	float accz;
	float gyrox;
	float gyroy;
	float gyroz;
}MpuDat_t;




/**
 * @brief 一阶互补滤波参数结构体
 */
typedef struct 
{
	float k;
	float dt;
	float flt;
}Cpflt_t;



float ComplementaryFilter(Cpflt_t *self,float angle,float gyro);


#endif /*__MPU_CMPL_H*/




