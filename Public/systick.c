#include "SysTick.h"
#include "core_cm3.h"
#include "misc.h"


/**
 * @brief ϵͳ��ʱ����ʱus
 * @param us ������
 * @retval None
 * @note couter��1��ʱ�� ���� 1/systick_clk
 * 	��counter �� reload ��ֵ��С��0��ʱ��Ϊһ��ѭ��������������ж���ִ���жϷ������
 * 	ͬʱ CTRL �� countflag λ����1
 * 	��һ��ѭ����ʱ��Ϊ reload * (1/systick_clk)
 */
void SysTick_Delay_Us( __IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	
	for(i=0;i<us;i++)
	{
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1	
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر�SysTick��ʱ��
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}


/**
 * @brief ϵͳ��ʱ����ʱms
 * @param ms ��ʱ�ĺ�����
 * @retval None
 */
void SysTick_Delay_Ms( __IO uint32_t ms)
{
	uint32_t i;	
	SysTick_Config(SystemCoreClock/1000);
	
	for(i=0;i<ms;i++)
	{
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1
		// ����1ʱ����ȡ��λ����0
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر�SysTick��ʱ��
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}


