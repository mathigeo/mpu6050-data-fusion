#include "system.h"  
#include "systick.h"
#include "mpu6050.h"
#include "mpuExti.h"
#include "usart.h"
#include "math.h"
#include "inv_mpu.h"



/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART_Config(115200);
	
	MPU6050_Init();
	mpu_dmp_init();
	MPU6050_EXTI_Init();
	while(1)
	{		
		printf("%f,%f,%f,%f\n",mpu1.pitch,mpu2.Pitch,mpu1.roll,mpu2.Roll);
	} 
}

