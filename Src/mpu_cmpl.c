#include "mpu_cmpl.h"

/**
 * @brief һ�׻����˲�
 * @param angle ���ٶȵõ��ĽǶ�
 * @param gyro �����ǽ��ٶ�
 * @retval �˲��Ľ��
 */
float ComplementaryFilter(Cpflt_t *self,float angle,float gyro)
{
	(self->flt) = 	(self->k)*angle +\
					(1-(self->k))*((self->flt) +\
					gyro*(self->dt));
	return (self->flt);
}






