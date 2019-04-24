
//**--------------头文件-------------------------------------------------------
#include <xc.h>
#include <GenericTypeDefs.h>

#include "userdefine.h"

//**--------------全局变量-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------

//**--------------函数定义-----------------------------------------------------







/**********************************************************************
*函数名称：init_led
*描述：指示灯初始化
*返回类型：void
*输入形参：void
***********************************************************************/
void init_led(void)
{
	CHARGE_LED_TRIS 	= 	0;  //充电指示灯 端口设置输出模式
	DISCHARGE_LED_TRIS	=	0;	//放电指示灯 端口设置输出模式
	BATRGE_LED_TRIS		=	0;	//电池指示灯 端口设置输出模式
	
	CHARGE_LED_OFF		;   //输出低电平 D9灯灭
	DISCHARGE_LED_OFF	;	//输出低电平 D10灯灭
	BATRGE_LED_OFF		;	//输出低电平 D11灯灭
}
