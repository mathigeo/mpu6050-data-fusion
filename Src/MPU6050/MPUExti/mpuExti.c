#include "mpuExti.h"
#include "mpu6050.h"
#include "inv_mpu.h"


/*互补滤波数据数据*/
MpuDat_t mpu1={0};

/*dmp数据*/
DmpDat_t mpu2={0};

/**
 * @brief 外部中断配置
 * @param None
 * @retval None
 */
void MPU6050_EXTI_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//开启时钟
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;   
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);	
	
	
	/*外部中断*/
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);
	EXTI_InitStruct.EXTI_Line=EXTI_Line10;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
}




/**
 * @brief MPU6050外部中断服务函数
 * @param None
 * @retval None
 */
void EXTI15_10_IRQHandler(void)
{
	//原始数据
	short rGyrox=0,rGyroy=0,rGyroz=0;
	short rAccx=0,rAccy=0,rAccz=0;
	
	//滤波参数
	static Cpflt_t pit = {0.015,0.01,0};
	static Cpflt_t rol = {0.015,0.01,0};
	
	/*一级判定*/
	if(EXTI_GetITStatus(EXTI_Line10)!=0)
	{
		/*二级判定*/
		if(PBin(10)==0)
		{
			//获取原始数据
			MPU6050_Get_Gyroscope(&rGyrox,&rGyroy,&rGyroz);
			MPU6050_Get_Accelerometer(&rAccx,&rAccy,&rAccz);
			
			/*获取DMP数据*/
			mpu_dmp_get_data(&mpu2.Pitch,&mpu2.Roll,&mpu2.Yaw);
			
			//角速度换单位->(度每秒)
			mpu1.gyrox = (float)rGyrox/(float)65536*(float)4000;
			mpu1.gyroy = (float)rGyroy/(float)65536*(float)4000;
			mpu1.gyroz = (float)rGyroz/(float)65536*(float)4000;
			
			//加速度换单位->(米每秒的平方)
			mpu1.accx = (float)rAccx/(float)65536*(float)4*9.8;
			mpu1.accy = (float)rAccy/(float)65536*(float)4*9.8;
			mpu1.accz = (float)rAccz/(float)65536*(float)4*9.8;	
			
			//滤波
			mpu1.pitch = ComplementaryFilter(&pit,-atan2(rAccx,sqrt(rAccz*rAccz+rAccy*rAccy))*180.0f/3.1415926f,mpu1.gyroy);
			//mpu1.pitch = ComplementaryFilter(&pit,-atan2(rAccx,rAccz)*180.0f/3.1415926f,mpu1.gyroy);
			
			//滤波
			mpu1.roll = ComplementaryFilter(&rol,atan2(rAccy,rAccz)*180.0f/3.1415926f,mpu1.gyrox);
			
			/*清除中断标志位*/
			EXTI_ClearITPendingBit(EXTI_Line10);
		}
	}
}





