//-----  	��Ŀ���ƣ�̫����·�ƿ�����

//-----  		�汾��

//-----  		����ߣ���ά��
	
//-----  		�汾��V1.0

//-----  		���ڣ�2017-12-11

//-----  		������PIC16F1938



//							if((pv_prev+2)>=pv_voltage_value)  //���� MPPT����
//							{
//								buck_pwm_value=buck_pwm_value+( (float) (400-buck_pwm_value) ) * 0.1;
//								
//									if(buck_pwm_value>=400)
//									{
//										buck_pwm_value=390;
//									}
//							
//								Set_Buck_Pwm_Duty(buck_pwm_value);
//							}
//							
//							else if((pv_voltage_value+2)>pv_prev)  //���� MPPT����
//							{
//								buck_pwm_value=buck_pwm_value-( (float) (400-buck_pwm_value)) * 0.1;
//								
//								if(buck_pwm_value<=50)
//									{
//										buck_pwm_value=50;
//									}
//							
//								Set_Buck_Pwm_Duty(buck_pwm_value);
//							}


if((pv_prev+2)>=pv_voltage_value)  //���� MPPT����
//							{
//								buck_pwm_value=buck_pwm_value-( (float) (400-buck_pwm_value) ) * 0.1;
//								
//								if(buck_pwm_value<=50)
//									{
//										buck_pwm_value=50;
//									}
//							
//								Set_Buck_Pwm_Duty(buck_pwm_value);
//							}
//							
//							else if((pv_voltage_value+2)>pv_prev)  //���� MPPT����
//							{
//								buck_pwm_value=buck_pwm_value+( (float) (400-buck_pwm_value) ) * 0.1;
//								
//								if(buck_pwm_value>=400)
//									{
//										buck_pwm_value=390;
//									}
//							
//								Set_Buck_Pwm_Duty(buck_pwm_value);
//							}



signed int pid_calc( PID *pp, int NowPoint )
{
	signed int PWM_var;
	
	float dError, Error; 
	
	Error = pp->SetPoint - NowPoint;            // �ȼ���ƫ��
	
	pp->SumError += Error;                      // �ڶ�ƫ����л���


     
    if((pp->SumError)>=50)     pp->SumError=  50;
    else if((pp->SumError)<=-50)  pp->SumError= -50;

	dError = pp->LastError - pp->PrevError;     // ��ƫ��΢��
	
	pp->PrevError = pp->LastError;
	
	pp->LastError = Error;
					// -------������-----------------������----------------------------΢����---
	PWM_var=(int)(pp->Proportion * Error  + pp->Integral * pp->SumError  + pp->Derivative * dError  ) ;              



	if(PWM_var>20)PWM_var           =  20 ;
	else  if(PWM_var <= -10)PWM_var = -10; 
    
    return (PWM_var );
}


void Mppt_Charge(void) -----//V1
{
	
					if((battery_voltage_value<600)&&(charge_index==0x01))  //MPPT���ٳ��    
					{
						
						if(mppt_status==0x00)
						{
								if (charge_current_value>=I_prev)  
								{
							
										buck_pwm_value=buck_pwm_value+  400 * 0.1;
										
											if(buck_pwm_value>=360)
											{
												buck_pwm_value=360;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
									
								}
								else 
								{						
										mppt_status++;
		
										buck_pwm_value=buck_pwm_value-400 * 0.02;
										
										if(buck_pwm_value<=50)
											{
												buck_pwm_value=50;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
		
								}
						}
						else
						{
								if (charge_current_value>=I_prev)  
								{
							
										buck_pwm_value=buck_pwm_value-400 * 0.02;
										
										if(buck_pwm_value<=50)
											{
												buck_pwm_value=50;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
									
								}
								else 
								{						
										mppt_status--;
		
										buck_pwm_value=buck_pwm_value+  400 * 0.1;
										
											if(buck_pwm_value>=360)
											{
												buck_pwm_value=360;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
		
								}

								mppt_status++;

						}
											
						
					}

}




void Mppt_Charge(void)///---V2
{
	
					if((battery_voltage_value<600)&&(charge_index==0x02))  //MPPT���ٳ��    
					{
						
						if(mppt_status==0x00)
						{
								if (charge_current_value>=I_prev)  
								{
							
										buck_pwm_value=buck_pwm_value +  400 * 0.025;
										
											if(buck_pwm_value>=BUCK_PWM_MAX)
											{
												buck_pwm_value=BUCK_PWM_MAX;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
									
								}
								else 
								{						
										mppt_status=1;
		
										buck_pwm_value=buck_pwm_value - 400 * 0.025;
										
										if(buck_pwm_value<=BUCK_PWM_MIN)
											{
												buck_pwm_value=BUCK_PWM_MIN;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
		
								}
						}
						else
						{
								if (charge_current_value>=I_prev)  
								{
							
										buck_pwm_value=buck_pwm_value-400 * 0.025;
										
										if(buck_pwm_value<=BUCK_PWM_MIN)
											{
												buck_pwm_value=BUCK_PWM_MIN;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
										
										
									
								}
								else 
								{						
										mppt_status=0;
		
										buck_pwm_value=buck_pwm_value+  400 * 0.025;
										
											if(buck_pwm_value>=BUCK_PWM_MAX)
											{
												buck_pwm_value=BUCK_PWM_MAX;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
		
								}

								

						}
											
						
					}
					else if((battery_voltage_value>=605)&&(battery_voltage_value<=615)&&(charge_index==0x02)) //CV��ѹ���
					{
							PWM_I=pid_calc(&PID_CV_charge,battery_voltage_value);
							
				           	PWM	 = PWM+PWM_I;
				           	
				           if( PWM>=BUCK_PWM_MAX)
				           {
				           		PWM=BUCK_PWM_MAX;
				           }			           
				           else if(PWM<=BUCK_PWM_MIN) 
				           {
				           		PWM=BUCK_PWM_MIN;
				           }
				           buck_pwm_value = PWM;
				           
				           Set_Buck_Pwm_Duty(buck_pwm_value);
					}
					else if( (battery_voltage_value>615) && (charge_index==0x02) )
					{
							if(buck_pwm_value>BUCK_PWM_MIN)
							{
								buck_pwm_value =	buck_pwm_value-400 * 0.01;
							}
							Set_Buck_Pwm_Duty(buck_pwm_value);
					}
					else NOP();

}



----------------------------------<̫���ܿ�������ң���� ����ͨ��Э��>------------------------------------------------------

>>>>>>>>>>>>>>>>>>>>>>>>>>1.�������ݲ鿴��<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

1.1)ң����(TX)---->������:

��������֡����ͷ(1BYTE)+���ݶ�(N BYTE)+��β(1BYTE)

���ݶ�=������+CRCУ����(У�鷶Χ��BYTE1)

������:0xA1
-----------------------------------------
| ��ͷ	| ������|	CRCУ����	|  ��β	|
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	|
| 0x55  | 0xA1 	| 0x7E 	| 0xF8 	| 0xAA	|
----------------------------------------


1.2)������(TX)---->ң����:

��������֡����ͷ(1BYTE)+���ݶ�(N BYTE)+��β(1BYTE)

���ݶ�=��Ӧ��+״̬����+CRCУ����(У�鷶Χ��BYTE1---BYTE12)

��Ӧ�룺0xB1

״̬����=�����ѹ(2BYTE)+��ص�ѹ(2BYTE)+�����ѹ(2BYTE)+������(2BYTE)+�������(2BYTE)+����ģʽ(1BYTE)

-----------------------------------------------------------------------------------------------------------------------------------------
| ��ͷ	| ��Ӧ��|	�����ѹ  	|	��ص�ѹ  	|	�����ѹ  	|	������  	|	 �������  	  | ����ģʽ |	  CRCУ����	   | ��β	|  		
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	| BYTE6	| BYTE7	| BYTE8	| BYTE9	| BYTE10 | BYTE11 |  BYTE12  | BYTE13 | BYTE14 | BYTE15	|
| 0x55  | 0xB1 	| 0x0B 	| 0xB8 	| 0x04	| 0xB0	| 0x0B	| 0xB8	| 0x00	| 0x96	| 0x00	 | 0x00	  |  0x01	 | 0x0C	  | 0x62   | 0xAA	| 
-----------------------------------------------------------------------------------------------------------------------------------------

>>>>>>>>>>>>>>>>>>>>>>>>>>2.�����鿴:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

2.1)ң����(TX)---->������:

��������֡����ͷ(1BYTE)+���ݶ�(N BYTE)+��β(1BYTE)

���ݶ�=������+CRCУ����(У�鷶Χ��BYTE1)

������:0xA2
-----------------------------------------
| ��ͷ	| ������|	CRCУ����	|  ��β	|
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	|
| 0x55  | 0xA2 	| 0x3E 	| 0xF9 	| 0xAA	|
----------------------------------------


2.2)������(TX)---->ң����:

��������֡����ͷ(1BYTE)+���ݶ�(N BYTE)+��β(1BYTE)

���ݶ�=��Ӧ��+ϵͳ����+CRCУ����(У�鷶Χ��BYTE1--BYTE6)

��Ӧ�룺0xB2

ϵͳ����=��ص�ѹ(2BYTE)+���ص���(2BYTE)+��������ٷֱ�(1BYTE)

------------------------------------------------------------------------------------
| ��ͷ	| ��Ӧ��|	��ص�ѹ  	|	���ص���  	|������� |	CRCУ����     | ��β   |  		
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	| BYTE6   | BYTE7 | BYTE8 | BYTE9  |
| 0x55  | 0xB2 	| 0x00 	| 0x07 	| 0x00	| 0x21	| 0x00    | 0x02  | 0xED  | 0xAA   | 
------------------------------------------------------------------------------------

>>>>>>>>>>>>>>>>>>>>>>>>>>3.��������:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

3.1)ң����(TX)---->������:

��������֡����ͷ(1BYTE)+���ݶ�(N BYTE)+��β(1BYTE)

���ݶ�=������+ϵͳ����+CRCУ����(У�鷶Χ��BYTE1--BYTE6)

������:0xA3
------------------------------------------------------------------------------------
| ��ͷ	| ������|	��ص�ѹ  	|	���ص���  	|������� |	CRCУ����     | ��β   |  		
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	| BYTE6   | BYTE7 | BYTE8 | BYTE9  |
| 0x55  | 0xA3 	| 0x00 	| 0x07 	| 0x00	| 0x21	| 0x00    | 0x02  | 0xED  | 0xAA   | 
------------------------------------------------------------------------------------


3.2)������(TX)---->ң����:

��������֡����ͷ(1BYTE)+���ݶ�(N BYTE)+��β(1BYTE)

���ݶ�=��Ӧ��+״̬+CRCУ����(У�鷶Χ��BYTE1--BYTE2)

��Ӧ�룺0xB3

״̬��01  �������óɹ�
	  02  ��������ʧ��(�������ò�������ϵͳ����������Χ�������ݴ��䶪ʧ)

-------------------------------------------------
| ��ͷ	| ��Ӧ��| ״̬	|	CRCУ����	|  ��β	|
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	|
| 0x55  | 0xB3 	| 0x01 	| 0xB5 	| 0x40	| 0xAA	|
-------------------------------------------------


>>>>>>>>>>>>>>>>>>>>>>>>>>4.���ݼ��:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

4.1)ң����(TX)---->������:(ͬ��1.�������ݲ鿴)

��������֡����ͷ(1BYTE)+���ݶ�(N BYTE)+��β(1BYTE)

���ݶ�=������+CRCУ����(У�鷶Χ��BYTE1)

������:0xA1
-----------------------------------------
| ��ͷ	| ������|	CRCУ����	|  ��β	|
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	|
| 0x55  | 0xA1 	| 0x7E 	| 0xF8 	| 0xAA	|
----------------------------------------


4.2)������(TX)---->ң����:

��������֡����ͷ(1BYTE)+���ݶ�(N BYTE)+��β(1BYTE)

���ݶ�=��Ӧ��+״̬����+CRCУ����(У�鷶Χ��BYTE1---BYTE12)

��Ӧ�룺0xB1

״̬����=�����ѹ(2BYTE)+��ص�ѹ(2BYTE)+�����ѹ(2BYTE)+������(2BYTE)+�������(2BYTE)+����ģʽ(1BYTE)

-----------------------------------------------------------------------------------------------------------------------------------------
| ��ͷ	| ��Ӧ��|	�����ѹ  	|	��ص�ѹ  	|	�����ѹ  	|	������  	|	 �������  	  | ����ģʽ |	  CRCУ����	   | ��β	|  		
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	| BYTE6	| BYTE7	| BYTE8	| BYTE9	| BYTE10 | BYTE11 |  BYTE12  | BYTE13 | BYTE14 | BYTE15	|
| 0x55  | 0xB1 	| 0x0B 	| 0xB8 	| 0x04	| 0xB0	| 0x0B	| 0xB8	| 0x00	| 0x96	| 0x00	 | 0x00	  |  0x01	 | 0x0C	  | 0x62   | 0xAA	| 
-----------------------------------------------------------------------------------------------------------------------------------------


































