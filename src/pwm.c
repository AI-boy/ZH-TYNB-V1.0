 
 
 
#include <xc.h>
#include <GenericTypeDefs.h>

#include "userdefine.h"



unsigned int pwm_duty_value=0x0000;

unsigned int bost_pwm_value=0x00;

unsigned int buck_pwm_value=0x00;


long int P_prev=0;  //前一次功率
long int P_last=0;  //后一次功率




/**********************************************************************
*函数名称：init_pwm
*描述：CPP1 CCP2 CCP3 CCP4 CCP5   Time2/Time4/Time6/    BUCK推挽输出选择Time6  BOST输出PWM选择Time4
*返回类型：void
*输入形参：void
***********************************************************************/
void init_pwm(void)
{

	BUCK_PWM_H_TRIS=1;  //PWM推挽输出端口初始阶段为输入  即禁止PWM端口
	
	BUCK_PWM_L_TRIS=1;	//PWM推挽输出端口初始阶段为输入  即禁止PWM端口
	
	BOST_PWM_TRIS =1;	//PWM推挽输出端口初始阶段为输入  即禁止PWM端口
	
	APFCONbits.CCP3SEL=1;  //CCP3/P3A功能位于RB5/AN13/CPS5/CCP3/P3A/T1G/COM1 引脚上
	
	
	
	//----------------------------BUCK降压PWM半桥推挽输出  CCP1  TIME6
	
	PR6=0xFF;//0x63;  		   				//PWM周期设置	Fosc=32MHz  PWM输出频率=31.4Khz  分辨率10位
	
	CCP1CONbits.CCP1M=0b1100;
	
	CCP1CONbits.P1M=0b10;			//半桥PWM输出模式
	
	CCPTMRS0bits.C1TSEL=0b10;      	//CCP1 选择TIME6 
														
	CCPR1L=0x00;					//占空比设置  脉冲宽度
	
	CCP1CONbits.DC1B=0b00;
	
	TMR6IF=0;
	
	T6CONbits.T6OUTPS=0b0000;
	
	TMR6ON=0;
	
	T6CONbits.T6CKPS=0b00;    	  //预分频值为1
	

	
	//----------------------------BOST升压PWM输出   CCP3  TIME4
	
	PR4=0x9F;  		   				//PWM周期设置	Fosc=32MHz  PWM输出频率=50Khz  分辨率9位
	
	CCP3CONbits.CCP3M=0b1100;
	
	CCP3CONbits.P3M=0b00;
	
	CCPTMRS0bits.C3TSEL=0b01;      	//CCP3 选择TIME4 
														
	CCPR3L=0x00;					//占空比设置  脉冲宽度
	
	CCP3CONbits.DC3B=0b00;
	
	TMR4IF=0;
	
	T4CONbits.T4OUTPS=0b0000;
	
	TMR4ON=0;
	
	T4CONbits.T4CKPS=0b00;    	  //预分频值为1
	
	//----------------------------红外载波频率38kHz   CCP5  TIME2
	
	PWM_IRD_TRIS=0;					//红外载波频率38kHz 端口设置为输出模式
	
	PR2=0xCE;  		   				//PWM周期设置	Fosc=32MHz  PWM输出频率fp=38Khz  分辨率10位    PR2= Fosc/4/fp - 1
	
	CCP5CONbits.CCP5M=0b1100;
	
	CCP5CONbits.P5M=0b00;
	
	CCPTMRS1bits.C5TSEL=0b00;      					//CCP5 选择TIME2 
														
	CCPR5L=(unsigned char)(0x114>>2);				//占空比设置  脉冲宽度  1/3
	
	CCP5CONbits.DC5B=(unsigned char)(0x114&0b11);	
	
	TMR2IF=0;
	
	T2CONbits.T2OUTPS=0b0000;
	
	TMR2ON=0;
	
	T2CONbits.T2CKPS=0b00;    	  //预分频值为1
	
}



/**********************************************************************
*函数名称：enable_buck_pwm
*描述：使能BUCK PWM
*返回类型：void
*输入形参：void
***********************************************************************/
void Enable_Buck_Pwm(void)
{
	BUCK_PWM_H_TRIS=0;  //使能PWM端口输出
	
	//BUCK_PWM_L_TRIS=0;	//使能PWM端口输出
	
	TMR6ON=1;			//开启CCP1 PWM  Time6定时器

}



/**********************************************************************
*函数名称：disable_buck_pwm
*描述：关闭BUCK PWM
*返回类型：void
*输入形参：void
***********************************************************************/
void Disable_Buck_Pwm(void)
{
	BUCK_PWM_H_TRIS=1;  //禁能PWM端口输出  P1A
	
	BUCK_PWM_L_TRIS=1;	//禁能PWM端口输出  P1B
	
	TMR6ON=0;			//关闭CCP1 PWM  Time6定时器

}



/**********************************************************************
*函数名称：set_buck_pwm_duty
*描述：设置BUCK PWM占空比
*返回类型：void
*输入形参：void
***********************************************************************/
void Set_Buck_Pwm_Duty(unsigned int duty)     //D=duty/(4*(PR6+1))
{
	buck_pwm_value=duty;
	
	if(duty<=BUCK_PWM_MAX)
	{
		CCPR1L=(unsigned char)(duty>>2);					//占空比设置  脉冲宽度
	
		CCP1CONbits.DC1B=(unsigned char)(duty&0b11);
	}
	else
	{
		duty=BUCK_PWM_MAX;
		
		CCPR1L=(unsigned char)(duty>>2);					
	
		CCP1CONbits.DC1B=(unsigned char)(duty&0b11);
	}

}



/**********************************************************************
*函数名称：enable_bost_pwm
*描述：开启BOST PWM
*返回类型：void
*输入形参：void
***********************************************************************/
void Enable_Bost_Pwm(void)
{
	BOST_PWM_TRIS =0;	//使能PWM端口输出  CCP3   RB5
		
	
	TMR4ON=1;
}



/**********************************************************************
*函数名称：disable_bost_pwm
*描述:关闭BOST PWM
*返回类型：void
*输入形参：void
***********************************************************************/
void Disable_Bost_Pwm(void)
{
	BOST_PWM_TRIS =1;	//禁能PWM端口输出  CCP3   RB5
	
//	BOST_PWM_TRIS =0;	//使能PWM端口输出  CCP3   RB5
//	
//	LATBbits.LATB5 = 0x00;
	
	TMR4ON=0;			//关闭定时器4
	
}


/**********************************************************************
*函数名称：set_bost_pwm_duty
*描述：设置BOST PWM占空比
*返回类型：void
*输入形参：void
***********************************************************************/
void Set_Bost_Pwm_Duty(unsigned int dduty)     //D=duty/(4*(PR4+1))
{
	
	bost_pwm_value=dduty;
	
	if(dduty<=BOST_PWM_MAX)  
	{
		CCPR3L=(unsigned char)(dduty>>2);					//占空比设置  脉冲宽度
	
		CCP3CONbits.DC3B=(unsigned char)(dduty&0b11);
	}
	else
	{
		dduty=BOST_PWM_MAX;
		
		CCPR3L=(unsigned char)(dduty>>2);					//占空比设置  脉冲宽度
	
		CCP3CONbits.DC3B=(unsigned char)(dduty&0b11);
	}

}





