 
 
 
#include <xc.h>
#include <GenericTypeDefs.h>

#include "userdefine.h"



unsigned int pwm_duty_value=0x0000;

unsigned int bost_pwm_value=0x00;

unsigned int buck_pwm_value=0x00;


long int P_prev=0;  //ǰһ�ι���
long int P_last=0;  //��һ�ι���




/**********************************************************************
*�������ƣ�init_pwm
*������CPP1 CCP2 CCP3 CCP4 CCP5   Time2/Time4/Time6/    BUCK�������ѡ��Time6  BOST���PWMѡ��Time4
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void init_pwm(void)
{

	BUCK_PWM_H_TRIS=1;  //PWM��������˿ڳ�ʼ�׶�Ϊ����  ����ֹPWM�˿�
	
	BUCK_PWM_L_TRIS=1;	//PWM��������˿ڳ�ʼ�׶�Ϊ����  ����ֹPWM�˿�
	
	BOST_PWM_TRIS =1;	//PWM��������˿ڳ�ʼ�׶�Ϊ����  ����ֹPWM�˿�
	
	APFCONbits.CCP3SEL=1;  //CCP3/P3A����λ��RB5/AN13/CPS5/CCP3/P3A/T1G/COM1 ������
	
	
	
	//----------------------------BUCK��ѹPWM�����������  CCP1  TIME6
	
	PR6=0xFF;//0x63;  		   				//PWM��������	Fosc=32MHz  PWM���Ƶ��=31.4Khz  �ֱ���10λ
	
	CCP1CONbits.CCP1M=0b1100;
	
	CCP1CONbits.P1M=0b10;			//����PWM���ģʽ
	
	CCPTMRS0bits.C1TSEL=0b10;      	//CCP1 ѡ��TIME6 
														
	CCPR1L=0x00;					//ռ�ձ�����  ������
	
	CCP1CONbits.DC1B=0b00;
	
	TMR6IF=0;
	
	T6CONbits.T6OUTPS=0b0000;
	
	TMR6ON=0;
	
	T6CONbits.T6CKPS=0b00;    	  //Ԥ��ƵֵΪ1
	

	
	//----------------------------BOST��ѹPWM���   CCP3  TIME4
	
	PR4=0x9F;  		   				//PWM��������	Fosc=32MHz  PWM���Ƶ��=50Khz  �ֱ���9λ
	
	CCP3CONbits.CCP3M=0b1100;
	
	CCP3CONbits.P3M=0b00;
	
	CCPTMRS0bits.C3TSEL=0b01;      	//CCP3 ѡ��TIME4 
														
	CCPR3L=0x00;					//ռ�ձ�����  ������
	
	CCP3CONbits.DC3B=0b00;
	
	TMR4IF=0;
	
	T4CONbits.T4OUTPS=0b0000;
	
	TMR4ON=0;
	
	T4CONbits.T4CKPS=0b00;    	  //Ԥ��ƵֵΪ1
	
	//----------------------------�����ز�Ƶ��38kHz   CCP5  TIME2
	
	PWM_IRD_TRIS=0;					//�����ز�Ƶ��38kHz �˿�����Ϊ���ģʽ
	
	PR2=0xCE;  		   				//PWM��������	Fosc=32MHz  PWM���Ƶ��fp=38Khz  �ֱ���10λ    PR2= Fosc/4/fp - 1
	
	CCP5CONbits.CCP5M=0b1100;
	
	CCP5CONbits.P5M=0b00;
	
	CCPTMRS1bits.C5TSEL=0b00;      					//CCP5 ѡ��TIME2 
														
	CCPR5L=(unsigned char)(0x114>>2);				//ռ�ձ�����  ������  1/3
	
	CCP5CONbits.DC5B=(unsigned char)(0x114&0b11);	
	
	TMR2IF=0;
	
	T2CONbits.T2OUTPS=0b0000;
	
	TMR2ON=0;
	
	T2CONbits.T2CKPS=0b00;    	  //Ԥ��ƵֵΪ1
	
}



/**********************************************************************
*�������ƣ�enable_buck_pwm
*������ʹ��BUCK PWM
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void Enable_Buck_Pwm(void)
{
	BUCK_PWM_H_TRIS=0;  //ʹ��PWM�˿����
	
	//BUCK_PWM_L_TRIS=0;	//ʹ��PWM�˿����
	
	TMR6ON=1;			//����CCP1 PWM  Time6��ʱ��

}



/**********************************************************************
*�������ƣ�disable_buck_pwm
*�������ر�BUCK PWM
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void Disable_Buck_Pwm(void)
{
	BUCK_PWM_H_TRIS=1;  //����PWM�˿����  P1A
	
	BUCK_PWM_L_TRIS=1;	//����PWM�˿����  P1B
	
	TMR6ON=0;			//�ر�CCP1 PWM  Time6��ʱ��

}



/**********************************************************************
*�������ƣ�set_buck_pwm_duty
*����������BUCK PWMռ�ձ�
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void Set_Buck_Pwm_Duty(unsigned int duty)     //D=duty/(4*(PR6+1))
{
	buck_pwm_value=duty;
	
	if(duty<=BUCK_PWM_MAX)
	{
		CCPR1L=(unsigned char)(duty>>2);					//ռ�ձ�����  ������
	
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
*�������ƣ�enable_bost_pwm
*����������BOST PWM
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void Enable_Bost_Pwm(void)
{
	BOST_PWM_TRIS =0;	//ʹ��PWM�˿����  CCP3   RB5
		
	
	TMR4ON=1;
}



/**********************************************************************
*�������ƣ�disable_bost_pwm
*����:�ر�BOST PWM
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void Disable_Bost_Pwm(void)
{
	BOST_PWM_TRIS =1;	//����PWM�˿����  CCP3   RB5
	
//	BOST_PWM_TRIS =0;	//ʹ��PWM�˿����  CCP3   RB5
//	
//	LATBbits.LATB5 = 0x00;
	
	TMR4ON=0;			//�رն�ʱ��4
	
}


/**********************************************************************
*�������ƣ�set_bost_pwm_duty
*����������BOST PWMռ�ձ�
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void Set_Bost_Pwm_Duty(unsigned int dduty)     //D=duty/(4*(PR4+1))
{
	
	bost_pwm_value=dduty;
	
	if(dduty<=BOST_PWM_MAX)  
	{
		CCPR3L=(unsigned char)(dduty>>2);					//ռ�ձ�����  ������
	
		CCP3CONbits.DC3B=(unsigned char)(dduty&0b11);
	}
	else
	{
		dduty=BOST_PWM_MAX;
		
		CCPR3L=(unsigned char)(dduty>>2);					//ռ�ձ�����  ������
	
		CCP3CONbits.DC3B=(unsigned char)(dduty&0b11);
	}

}





