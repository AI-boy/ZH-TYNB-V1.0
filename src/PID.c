
#include <xc.h>
#include <GenericTypeDefs.h>

#include "userdefine.h"


#include <string.h>
#include <stdio.h>




 PID PID_CC_charge;       //���Ƶ��ں������

 PID PID_CV_charge;     //���Ƶ��ں�ѹ���
 
 PID PID_CC_discharge;  //���Ƶ��ں������

//---------------------------------------------
//
//
//   
//PID�ṹ����㲿��
//
//
//----------------------------------------------

float pid_calc( PID *pp, int NowPoint )
{
	float PWM_var;
	
	float dError, Error; 
	
	float dk;
	
	dk=1.0; //---caiwk-2018-5-17---!!!
	
	Error = pp->SetPoint - NowPoint;            // �ȼ���ƫ��
	
	if(limit_power_pid_flag==0x01)
	{
		if((Error<=2)&&(Error>=-2))		
			{
				Error=0;
			}
			else if(Error>=8)
			{
				dk=100.0; 
			}
			else if(Error<=-8)
			{
				dk=100.0;
			}
	}
	else
	{
		if(pid_index==0x01)
		{
			if((Error<=2)&&(Error>=-2))		
			{
				Error=0;
			}
			else if(Error>=5)
			{
				dk=100.0; 
			}
			else if(Error<=-5)
			{
				dk=100.0;
			}
		}
		else if(pid_index==0x02)
		{
			if((Error<=1)&&(Error>=-1))		
			{
				Error=0;
			}
			else if((Error>=2)||(Error<=-2))
			{
				dk=100.0; 
			}
		}
			
	}
		
	
	pp->SumError += Error;                      // �ڶ�ƫ����л���


     
    if((pp->SumError)>=2)     pp->SumError=  2;
    else if((pp->SumError)<=-2)  pp->SumError= -2;

	dError = pp->LastError - pp->PrevError;     // ��ƫ��΢��
	
	pp->PrevError = pp->LastError;
	
	pp->LastError = Error;
					// -------������-----------------������----------------------------΢����---
	PWM_var=(pp->Proportion * Error*dk  + pp->Integral * pp->SumError  + pp->Derivative * dError  ) ;              

	
		if((Error>=3 && Error<=5)||(Error<=-3 && Error>=-5))
		{
			if(PWM_var>=2)PWM_var           =  2;
			else  if(PWM_var <= -2)PWM_var  = -2; 
		}
		else if((Error>5)||(Error<-5))
		{
			if(PWM_var>=5)PWM_var           =  5;
			else  if(PWM_var <= -5)PWM_var  = -5; 
		}
		else
		{
			if(PWM_var>=0.5)PWM_var           =  0.5;
			else  if(PWM_var <= -0.5)PWM_var  = -0.5; 
		}		


    
    return (PWM_var );
}


/*====================================================================================================
�������� Initialize PID Structure
=====================================================================================================*/
void pid_init ( PID *pp)
{
	memset (pp,0,sizeof(PID));
}


