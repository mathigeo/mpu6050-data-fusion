#include "mpu_cmpl.h"

/**
 * @brief 一阶互补滤波
 * @param angle 加速度得到的角度
 * @param gyro 陀螺仪角速度
 * @retval 滤波的结果
 */
float ComplementaryFilter(Cpflt_t *self,float angle,float gyro)
{
	(self->flt) = 	(self->k)*angle +\
					(1-(self->k))*((self->flt) +\
					gyro*(self->dt));
	return (self->flt);
}






