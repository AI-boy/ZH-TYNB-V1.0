

#include <xc.h>
#include <GenericTypeDefs.h>

#include	<stdio.h>
#include	<stdarg.h>
#include	<string.h>

#include "userdefine.h"


unsigned char buf[50];

unsigned char system_status=0x00;

unsigned char system_check_time=0x00;

unsigned int system_time_count=0x00;

unsigned char work_mode=0x00;


unsigned char pv_voltage_status=0x00;    		//������ѹ״̬

unsigned char battery_voltage_status=0x00;		//��ص�ѹ״̬

unsigned char load_voltage_status=0x00;			//���ض�״̬

unsigned char discharge_index=0x00;  			//�ŵ�׶α���

unsigned char charge_index=0x00;				//���׶α���

unsigned char nop_index=0x00;

unsigned int involid_time_count=0x00;

unsigned int cv_level_time_count=0x00;

unsigned int load_short_time_count=0x00;		//�����·������

unsigned int load_open_time_count=0x00;			//�����·������

unsigned int over_load_time_count=0x00;

unsigned int battery_low_time_count=0x00;


unsigned long int night_time_count=0x00;
					
unsigned long int  day_time_count=0x00;

unsigned long int pv_time_count=0x00;

unsigned long int light_time_level=0x00;

unsigned int pv_prev=0x00;

unsigned int I_prev=0x00;


float PWM	=	0;

float PWM_I=	0;

unsigned char mppt_status=0x00;

unsigned int mppt_time_count=0x00;

unsigned char temper_time_count=0x00;

unsigned char over_temper_time_count=0x00;
					
unsigned char sys_temper_flag=0x01;

unsigned char charge_led_status=0x00;

unsigned char bt_led_status=0x00;

unsigned char discharge_led_status=0x00;

unsigned char bt_time_count=0x00;

unsigned char pv_index=0x00;

unsigned char Adjust_Pout_Flag=0x00;

unsigned char limit_power_pid_flag=0x00;

unsigned char t1=0x00;
unsigned char t2=0x00;
unsigned char t3=0x00;
unsigned char t4=0x00;
unsigned char t5=0x00;

float bt_prev=0.0;

unsigned char mcu_t00_time_count=0x00;
unsigned char mcu_t01_time_count=0x00;
unsigned char mcu_t02_time_count=0x00;
unsigned char mcu_t03_time_count=0x00;
unsigned char mcu_temp_index=0x00;

unsigned char pid_index=0x00;


/**********************************************************************
*�������ƣ�handle_ad_loop
*������AD��ѵ����
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void handle_ad_loop(void)
{
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		if(handle_an0_process_flag==0x01)
		{
			ADCON1bits.ADPREF =0b00;  //VEF---VDD
			
			mcu_value=start_ad_convert(MCU_CHANNEL);  			//����ͨ��ѡ��  MCU_CHANNEL  �ְ汾���������ڶ�·���� �Ƚ����������� 
			
			ADCON1bits.ADPREF =0b11;  //VEF---1,024V  �ڲ��ο���ѹ
			
			if(mcu_value<490) //60 �¶�
			{
				mcu_t00_time_count++;
				mcu_t01_time_count=0x00;
				mcu_t02_time_count=0x00;
				mcu_t03_time_count=0x00;
				
				if(mcu_t00_time_count>=120)
				{
					mcu_t00_time_count=0x00;
					
					mcu_temp_index=0x00;
				}
			}				
			else if(mcu_value>510 && mcu_value<530) //80--100 �¶� �ŵ�--����50%
			{
				mcu_t01_time_count++;
				mcu_t00_time_count=0x00;
				mcu_t02_time_count=0x00;
				mcu_t03_time_count=0x00;
				
				if(mcu_t01_time_count>=60)
				{
					mcu_t01_time_count=0x00;
					
					mcu_temp_index=0x01;
				}
			}
			else if(mcu_value>530 && mcu_value<550) //100--120 �¶�  �ŵ�--����20%
			{
					mcu_t02_time_count++;
					mcu_t00_time_count=0x00;
					mcu_t01_time_count=0x00;
					mcu_t03_time_count=0x00;
				
				if(mcu_t02_time_count>=30)
				{
					mcu_t02_time_count=0x00;
					
					mcu_temp_index=0x02;
				}
			}
			else if(mcu_value>=550)  //120--   ���±���
			{
					mcu_t03_time_count++;
					mcu_t00_time_count=0x00;
					mcu_t01_time_count=0x00;
					mcu_t02_time_count=0x00;
				
				if(mcu_t03_time_count>=10)
				{
					mcu_t03_time_count=0x00;
					
					mcu_temp_index=0x03;
				}
			}
			else
			{
				mcu_t00_time_count=0x00;
				mcu_t01_time_count=0x00;
				mcu_t02_time_count=0x00;
				mcu_t03_time_count=0x00;
			}
					
			
			handle_an0_process_flag=0x00;
						
		}
		
		
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		if(handle_an1_process_flag==0x01)
		{
		
			temperature_value=start_ad_convert(AN1_CHANNEL);  		//����ͨ��ѡ��	AN1		�����¶�  0��--90      70��--950
			
			if((temperature_value>90)&&(temperature_value<950))  	//���������¶ȷ�Χ��0��---70��
			{
				temper_time_count++;
				
				over_temper_time_count=0x00;
				
				if(temper_time_count>=10)
				{
					temper_time_count=0x00;
					
					sys_temper_flag=0x01; 						//ϵͳ�����¶�����
				}	
			}
			else
			{
				over_temper_time_count++;
				
				temper_time_count=0x00;
				
				if(over_temper_time_count>=10)
				{
					over_temper_time_count=0x00;
					
					sys_temper_flag=0x00;						//����ϵͳ���������¶ȷ�Χ
				}
			}
			
			handle_an1_process_flag=0x00;
						
		}
		
		
		
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		if(handle_an2_process_flag==0x01)
		{
		
			pv_voltage_value=start_ad_convert(AN2_CHANNEL);  		//����ͨ��ѡ��	AN2		������ѹ    ��ѹ������������ 1:69 
			
			
			#if defined(PRINT_TEST)
			
			sprintf(buf, "PV=%4d.....AN2_CHANNEL!\n", pv_voltage_value);
		
			uart1_send_nbyte(buf, strlen(buf));
			
			#endif
			
			if(pv_index==0x00)
			{
				if(pv_voltage_value<=light_on_pv_level) 		//�������ͺ�ҹ   ͨ��������ѹ���   5V---10V
				{																								
					night_time_count++;
					
					day_time_count=0x00;
					
					if(night_time_count>light_time_level)  
					{
						night_time_count=0x00;
						
						pv_voltage_status=0x02;			//����ŵ�ģʽ
						
					}
						
				}
				else if((pv_voltage_value>(light_off_pv_level))) 
				{
					day_time_count++;
					
					night_time_count=0x00;
					
					if(day_time_count>light_time_level)
					{
						day_time_count=0x00;
						
						pv_voltage_status=0x00;  //����״̬
												
					}				
				}
				else
				{
					day_time_count=0x00;
					
					night_time_count=0x00;
				}
			}
			
			if((pv_voltage_value>=light_off_pv_level)&&(pv_voltage_value<1000)) 	//10V---69V  ������ѹ��Χ
			{																			
				pv_time_count++;
												
				if(pv_time_count>light_time_level)
				{
					pv_time_count=0x00;
							
					pv_voltage_status=0x01; 			//������ģʽ
					
					day_time_count=0x00;  
					
					night_time_count=0x00; 
					
					pv_index=0x01;										
							
				}				
							
			}
			else if(pv_voltage_value>=1000)
			{
				pv_time_count=0x00;
				
				pv_voltage_status=0x00; //����״̬
			}
			else
			{
				pv_time_count=0x00;
						
			}
			
			if(pv_index==0x01)
			{				 
				if(pv_voltage_value<=light_on_pv_level) 									//�������ͺ�ҹ   ͨ��������ѹ���   5V---10V
				{																								
					night_time_count++;
										
					if(night_time_count>light_time_level)  
					{
						night_time_count=0x00;
						
						pv_voltage_status=0x02;												//ҹ��״̬   ��������ŵ�ģʽ
						
						pv_index=0x00;
					}
						
				}
				else
				{					
					night_time_count=0x00;
				} 
			
			}
			
		
			
			handle_an2_process_flag=0x00;
						
		}
		
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		if(handle_an9_process_flag==0x01)  								//������ⷶΧ��0.15A---5A  ��������75��ŷ
		{
			charge_current_value=0x00;
			
			if(system_status ==	SYSTEM_CHARGE_STATUS)
			{
				charge_current_value=start_ad_convert(AN9_CHANNEL);  		//����ͨ��ѡ��	AN9		������
			
				#if defined(PRINT_I	)
				
				sprintf(buf, "I=%4d.....AN9_CHANNEL!\n", charge_current_value);
			
				uart1_send_nbyte(buf, strlen(buf));
				
				#endif
				
				if((charge_current_value>=charge_i_limit)&&(charge_index>=0x03)) 		//�������5A
				{
				
					if(buck_pwm_value>BUCK_PWM_MIN)
					{
						buck_pwm_value =	buck_pwm_value - 1;
					}
					Set_Buck_Pwm_Duty(buck_pwm_value);

				}
			
			}			
			
			handle_an9_process_flag=0x00;
						
		}
		
		
		//------------------------------------------------------------------------------------------------------------------------------------------------------
	
		if(handle_an3_process_flag==0x01)
		{
		
			battery_voltage_value=start_ad_convert(AN12_CHANNEL);  			//����ͨ��ѡ��	AN12	��ص�ѹ    ��ѹ������������ 1��34
			
			//-------------------------------------------------------------------
			b_v=(float)(((float)battery_voltage_value)/10)*34;
			
			//-------------------------------------------------------------------
			
			if((battery_voltage_value<(dianchi_guoya_baohu+volt_id*5))&&(charge_index==0x00))					//﮵�ص�ѹ�Ƿ�������  <12.6V
			{
				bt_time_count++;
				
				if(bt_time_count>=100)
				{
					bt_time_count=0x00;
					
					bt_led_status=0x01;
					
					charge_index=0x01;
				
					BATRGE_LED_ON;  																	//ϵͳ�����������
					
					battery_voltage_status=0x01;														//���״̬����
				}					
				
			}
			else if((battery_voltage_value>=(dianchi_guoya_baohu+volt_id*5))&&(charge_index<=0x01))
			{		
					bt_led_status=0x00;
					
					bt_time_count=0x00;
												
					battery_voltage_status=0x00;					//���״̬�쳣
			}
			
				
			if( (battery_voltage_value<dianchi_guoya_huifu) && (charge_index==0x02) )  		//<��س��ָ���ѹ
			{								
				charge_index=0x03;
				
				charge_led_status=0x01;
				
				CHARGE_LED_ON;
				
				Enable_Buck_Pwm();
			
			}
			else if( (battery_voltage_value>=dianchi_guoya_huifu) && (charge_index==0x02) )
			{
				bt_00_lv = b_v;
				
				charge_led_status=0x00;
				
			}
			else if( (battery_voltage_value<dianchi_guoya_baohu) && (charge_index>=0x03) )
			{
				
				if((charge_current_value<charge_i_limit)&&(charge_index>=0x03))	    				//��������0---5A	
				{
					mppt_time_count++;
					
					if(mppt_time_count>5)
					{
						mppt_time_count=0x00;
						
						Mppt_Charge();       														//MPPT���ģʽ
						
						I_prev=charge_current_value;
					}					 												
							
				}
				
				involid_time_count=0x00;
				
			}
			else if( (battery_voltage_value>=dianchi_guoya_baohu) && (charge_index>=0x03) )  
			{		
				involid_time_count++;
				
				if(involid_time_count>200)
				{
					involid_time_count=0x00;
					
					if(charge_index>=0x03)	
					{
						charge_index=0x05;
						
						Disable_Buck_Pwm();
									
						Set_Buck_Pwm_Duty(0);
						
						charge_led_status=0x00;
						
						while(1); //�ȴ�ϵͳ��λ
					}	
				}	
			}
												
							
			 
			P_prev=P_last;
			
			pv_prev=pv_voltage_value;
			
			handle_an3_process_flag=0x00;
						
		}
		
		
		
		
		
		//------------------------------------------------------------------------------------------------------------------------------------------------------		
		if(handle_an4_process_flag==0x01)								//��ѹ������������ 1:69
		{
			load_voltage_value=0x00;
			
			if(system_status ==	SYSTEM_DISCHARGE_STATUS)
			{
				load_voltage_value=start_ad_convert(AN4_CHANNEL);  			//����ͨ��ѡ��	AN4		��������˵�ѹ
			
				//---------------------------------------------------------------------------------------------------
					if((load_voltage_value<shuchu_shortout_voltage)&&(discharge_index==0x02)&&(PID_CC_discharge.SetPoint>0))     	//�����  <�����·��ѹ��   ���ж���1.����˶�·  2.LED����ѡ�ô���
					{
						load_short_time_count++;
						
						if(load_short_time_count>100)
						{
							load_short_time_count=0x00;				
							
							bost_pwm_value=2;
							
							Set_Bost_Pwm_Duty(bost_pwm_value);
							
							discharge_led_status=0x00;
							
							delay_ms(1);			//2018-03-22
							
							Disable_Bost_Pwm();		//2018-03-22
							
							LOAD_OUT_DISABLE;		//2018-03-22
							
							while(1); //�ȴ�ϵͳ��λ
						}
						
					}
					else if((load_voltage_value>=shuchu_shortout_voltage)&&(load_voltage_value<(shuchu_shortout_voltage*2))&&(discharge_index==0x02)&&(PID_CC_discharge.SetPoint>0))     	//
					{
						load_short_time_count++;
						
						if(load_short_time_count>100)
						{
							load_short_time_count=0x00;	
							
							discharge_index=0x03;			
							
							bost_pwm_value=2;
							
							Set_Bost_Pwm_Duty(bost_pwm_value);
							
							discharge_led_status=0x00;
							
							delay_ms(1);			//2018-03-22
							
							Disable_Bost_Pwm();		//2018-03-22
							
							LOAD_OUT_DISABLE;		//2018-03-22
							
							while(1); //�ȴ�ϵͳ��λ
						}
						
					}
					else
					{
						load_short_time_count=0x00;
					}
								
				//---------------------------------------------------------------------------------------------------
					if((load_voltage_value>shuchu_open_voltage)&&(discharge_index==0x02)) //����˵�ѹ>60V+�ŵ�ģʽ=���ض˿�·��ѹ
					{
						load_open_time_count++;
						
						if(load_open_time_count>100)
						{								
							discharge_index=0x03;
							
							load_open_time_count=0x00;			
												
							bost_pwm_value=5;
								
							Set_Bost_Pwm_Duty(bost_pwm_value);
								
							discharge_led_status=0x00;
							
							delay_ms(1);			//2018-03-22
								
							Disable_Bost_Pwm();		//2018-03-22
								
							LOAD_OUT_DISABLE;		//2018-03-22
							
							while(1); //�ȴ�ϵͳ��λ
						}
					
					}
					else
					{
						load_open_time_count=0x00;
					}	
				//---------------------------------------------------------------------------------------------------
				
			}		
					  			
			handle_an4_process_flag=0x00;
						
		}
		
	
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		if(handle_an10_process_flag==0x01)  								//������ⷶΧ��0.1A---1.2A  ��������75��ŷ  4--90  Ĭ��350mA��� ����ֵ<10
		{
			discharge_current_value=0x00;
			
			if(system_status ==	SYSTEM_DISCHARGE_STATUS)									//ϵͳ���ڷŵ�״̬
			{
				discharge_current_value=start_ad_convert(AN10_CHANNEL);  					//����ͨ��ѡ��	AN10	�ŵ����
							
				if((discharge_current_value>discharge_i_baohu)&&(discharge_index==0x02))  	//���ر���    >2.4A
				{ 									
					over_load_time_count++;
					
					if(over_load_time_count>100)												//������ʱ����
					{										
						discharge_index=0x03;
										
						bost_pwm_value=2;
						
						Set_Bost_Pwm_Duty(bost_pwm_value);
						
						delay_ms(1);
						
						Disable_Bost_Pwm();
						
						LOAD_OUT_DISABLE;
						
						over_load_time_count=0x00;
						
						discharge_led_status=0x00;
						
						while(1); //�ȴ�ϵͳ��λ
					}
					
				}
				else
				{
						over_load_time_count=0x00;
				}
				
				if((battery_voltage_value>dianchi_qianya_huifu)&&(discharge_index==0x01))   //    ���Ƿѹ�ָ���
				{
					discharge_index=0x02;
					
					discharge_led_status=0x01;
					
					open_discharge_time=0x01;
					
					DISCHARGE_LED_ON;					
					
					LOAD_OUT_ENABLE;
																																	
					Enable_Bost_Pwm();					
					
				}
				else if((battery_voltage_value<=dianchi_qianya_huifu)&&(discharge_index==0x01))
				{
					discharge_led_status=0x00;
					
					open_discharge_time=0x00;
				}
				
				
				 if((battery_voltage_value>=dianchi_qianya_baohu)&&(discharge_index==0x02))    		//��ص�ѹ>Ƿѹ������
				 {
					 
				 	if((discharge_current_value<=discharge_i_limit)&&(discharge_index==0x02))  		//PID �����������  Ĭ��350mA(330mA)   PID ����   ��������<2.1A
					{								    

						//----------------------------------------------------------------------------ʱ�����ܵ���ģʽ
						t1=step_01_time_limit;
						t2=step_01_time_limit+step_02_time_limit;
						t3=step_01_time_limit+step_02_time_limit+step_03_time_limit;
						t4=step_01_time_limit+step_02_time_limit+step_03_time_limit+step_04_time_limit;
						t5=step_01_time_limit+step_02_time_limit+step_03_time_limit+step_04_time_limit+step_05_time_limit;
						
						if((ho_cnt<t1) && (Adjust_Pout_Flag<=0x01))	
						{
							Adjust_Pout_Flag=0x01;	
						}
						else if((ho_cnt>=t1) && (ho_cnt<t2) && (Adjust_Pout_Flag<=0x02))
						{
							Adjust_Pout_Flag=0x02;	
						}
						else if((ho_cnt>=t2) && (ho_cnt<t3) && (Adjust_Pout_Flag<=0x03))
						{
							Adjust_Pout_Flag=0x03;	
						}
						else if((ho_cnt>=t3) && (ho_cnt<t4) && (Adjust_Pout_Flag<=0x04))
						{
							Adjust_Pout_Flag=0x04;	
						}
						else if((ho_cnt>=t4) && (ho_cnt<t5) && (Adjust_Pout_Flag<=0x05))
						{
							Adjust_Pout_Flag=0x05;	
						}
						else
						{
							Adjust_Pout_Flag=0x00;
						}
						
						//---------------------------------------------------------------------------�޶��������
						if( ((load_cc_I/100)*75) > (Load_Pmax*75/(load_voltage_value*69/1000)) )	
						{
							PID_CC_discharge.SetPoint=(Load_Pmax*75)/(load_voltage_value*69/1000);
							
							limit_power_pid_flag=0x01;	//------PID�޹��ʵ��ڱ��											           
							
							if(Adjust_Pout_Flag==0x01)
							{
								PID_CC_discharge.SetPoint   = ((Load_Pmax*75)/(load_voltage_value*69/1000))*step_01_load_percent/100;	//2018-03-22
							}
							else if(Adjust_Pout_Flag==0x02)
							{
								PID_CC_discharge.SetPoint   = ((Load_Pmax*75)/(load_voltage_value*69/1000))*step_02_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x03)
							{
								PID_CC_discharge.SetPoint   = ((Load_Pmax*75)/(load_voltage_value*69/1000))*step_03_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x04)
							{
								PID_CC_discharge.SetPoint   = ((Load_Pmax*75)/(load_voltage_value*69/1000))*step_04_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x05)
							{
								PID_CC_discharge.SetPoint   = ((Load_Pmax*75)/(load_voltage_value*69/1000))*step_05_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x00)
							{
								PID_CC_discharge.SetPoint  =0;
							}
							//------------------------------------------------------�ڲ����½���
							if(mcu_temp_index==0x01) //80--100��  ����50%
							{
								PID_CC_discharge.SetPoint = PID_CC_discharge.SetPoint*0.5;
							}
							else if(mcu_temp_index==0x02) //100--120��  ����20%
							{
								PID_CC_discharge.SetPoint = PID_CC_discharge.SetPoint*0.2;
							}
							else if(mcu_temp_index==0x03) //120 �ڲ����±���
							{
								PID_CC_discharge.SetPoint  =0;
							}
															
						}
						else
						{
							PID_CC_discharge.SetPoint=(load_cc_I/100)*75;
							
							
							if(Adjust_Pout_Flag==0x01)
							{
								PID_CC_discharge.SetPoint   = ((load_cc_I/100)*75)*step_01_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x02)
							{
								PID_CC_discharge.SetPoint   = ((load_cc_I/100)*75)*step_02_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x03)
							{
								PID_CC_discharge.SetPoint   = ((load_cc_I/100)*75)*step_03_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x04)
							{
								PID_CC_discharge.SetPoint   = ((load_cc_I/100)*75)*step_04_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x05)
							{
								PID_CC_discharge.SetPoint   = ((load_cc_I/100)*75)*step_05_load_percent/100;
							}
							else if(Adjust_Pout_Flag==0x00)
							{
								PID_CC_discharge.SetPoint  =0;
							}
							
							//------------------------------------------------------�ڲ����½���
							if(mcu_temp_index==0x01) //80--100��  ����50%
							{
								PID_CC_discharge.SetPoint = PID_CC_discharge.SetPoint*0.5;
							}
							else if(mcu_temp_index==0x02) //100--120��  ����20%
							{
								PID_CC_discharge.SetPoint = PID_CC_discharge.SetPoint*0.2;
							}
							else if(mcu_temp_index==0x03) //120 �ڲ����±���
							{
								PID_CC_discharge.SetPoint  =0;
							}
							
							
						}
			
						//---------------------------------------------------------
							pid_index = 0x01; //�����ŵ�PID���ڱ�־
							
							PWM_I=pid_calc(&PID_CC_discharge,discharge_current_value);
									
						    PWM	 = PWM+PWM_I;
						           	
						    if( PWM>=BOST_PWM_MAX)
						      {
						           PWM=BOST_PWM_MAX;
						      }			           
						    else if(PWM<=BOST_PWM_MIN) 
						      {
						           PWM=BOST_PWM_MIN;
						       }
						    
						    bost_pwm_value = (unsigned int)PWM;
						    
						     if(PID_CC_discharge.SetPoint==0)
						    {
						    	bost_pwm_value = 0;
						    }
						           
						    Set_Bost_Pwm_Duty(bost_pwm_value);
						    
						    limit_power_pid_flag=0x00;		//���޶�������ʱ�־
							
							
					}
					else if((discharge_current_value>discharge_i_limit)&&(discharge_index==0x02))
					{
						if(bost_pwm_value>10)
						{
							bost_pwm_value =	bost_pwm_value-1;												
						}
						
						Set_Bost_Pwm_Duty(bost_pwm_value);
					}
					
					battery_low_time_count=0;
					
				 }
				 else if((battery_voltage_value<dianchi_qianya_baohu)&&(discharge_index==0x02)) //   Ƿѹ���� 
				 {
				 		
				 		battery_low_time_count++;
						
						if(battery_low_time_count>1000)
						{													
							discharge_index=0x03;
							
							bost_pwm_value=2;
							
							Set_Bost_Pwm_Duty(bost_pwm_value);
							
							battery_low_time_count=0x00;
							
							discharge_led_status=0x00;
							
							while(1); //�ȴ�ϵͳ��λ
						}
				 
				 }
				 else
				 {
				 		battery_low_time_count=0;
				 }
			
			}
						
			handle_an10_process_flag=0x00;
						
		}


}



/**********************************************************************
*�������ƣ�start_ad_convert
*����������AD����ת��
*�������ͣ�unsigned int
*�����βΣ�unsigned char
***********************************************************************/
unsigned int start_ad_convert(unsigned char ch)
{
	
			unsigned char i,j,k;
		
			unsigned int ad_h,ad_l;		
			
		
			unsigned int temp;
			
			unsigned char ad_ch;
			
			ad_ch=0x00;
			
			ad_ch=ch;
	
			ADCON0bits.CHS	  =ch;  			//����ͨ��ѡ��
	
    		ADCON0bits.ADON   =1;				//ʹ��AD����
    		
    		if((ad_ch==AN10_CHANNEL)||(ad_ch==AN9_CHANNEL))   //�ŵ����----������
    		{
    			for(i=0;i<51;i++)
				{
					__delay_us(5);//�ȴ�����ʱ��		
			
					ADCON0bits.GO=1; //��������
			
					while(ADCON0bits.nDONE);
			
					ad_h=0b00000011&ADRESH;
			
					ad_l=ADRESL;
			
					adc_buffer[i]=(ad_h<<8)|ad_l;
				}
    			for(j=0;j<50;j++)
				{
					for(i=0;i<50-j;i++)
					{
						if(adc_buffer[i]>adc_buffer[i+1])
						{
							temp=adc_buffer[i];
							
							adc_buffer[i]=adc_buffer[i+1];
			
							adc_buffer[i+1]=temp;
						}			
			
					}
				}
			
				ADCON0bits.ADON   =0;
				
				return((adc_buffer[24]+adc_buffer[26]+
						adc_buffer[22]+adc_buffer[28]+
						adc_buffer[20]+adc_buffer[30]+
						adc_buffer[18]+adc_buffer[32]+
						adc_buffer[16]+adc_buffer[34]+
						adc_buffer[14]+adc_buffer[36]+
						adc_buffer[12]+adc_buffer[38]+
						adc_buffer[10]+adc_buffer[40]+
						adc_buffer[8]+adc_buffer[42]+
						adc_buffer[6]+adc_buffer[44]+
						adc_buffer[4]+adc_buffer[46]+
						adc_buffer[2]+adc_buffer[48]+
						adc_buffer[0]+adc_buffer[50])/26);
    		}
    		
    		
    		
    		for(i=0;i<N;i++)
			{
				__delay_us(10);//�ȴ�����ʱ��		
		
				ADCON0bits.GO=1; //��������
		
				while(ADCON0bits.nDONE);
		
				ad_h=0b00000011&ADRESH;
		
				ad_l=ADRESL;
		
				adc_buffer[i]=(ad_h<<8)|ad_l;
			}
			
			for(j=0;j<N-1;j++)
			{
				for(i=0;i<N-j;i++)
				{
					if(adc_buffer[i]>adc_buffer[i+1])
					{
						temp=adc_buffer[i];
						
						adc_buffer[i]=adc_buffer[i+1];
		
						adc_buffer[i+1]=temp;
					}			
		
				}
			}
			
			ADCON0bits.ADON   =0;
			
			return((adc_buffer[((N-1)/2)-1]+adc_buffer[((N-1)/2)+1])/2);
			
					
}
		



/**********************************************************************
*�������ƣ�handle_task_process
*������ϵͳ������ȴ���
*�������ͣ�void
*�����βΣ�void
***********************************************************************/		
void handle_task_process(void)
{
	
	
	if(handle_short_flag==0x01)  //��·����
	{
		over_load_time_count=0x00;
						
		load_voltage_status=0x01;
		
		handle_short_flag=0x00;
		
		discharge_led_status=0x00;
						
		while(1); //�ȴ�ϵͳ��λ
	}
	
	if(work_mode==0x00)//-----------------��������ģʽ���Զ�ģʽ��
	{
		if((pv_voltage_status==0x01)&&(battery_voltage_status==0x01)&&(sys_temper_flag==0x01)&&(mcu_temp_index<0x03))
		{
										
			system_status =	SYSTEM_CHARGE_STATUS;		
								
		}
		else if((pv_voltage_status==0x02)&&(battery_voltage_status==0x01)&&(sys_temper_flag==0x01)&&(mcu_temp_index<0x03))
		{
		
			system_status =	SYSTEM_DISCHARGE_STATUS;
			
		}
		else
		{
			system_status = SYSTEM_NOP_STATUS;
		}	
	}
	else if(work_mode==0x01)  //---------------�ֶ����ģʽ
	{
		system_status =	SYSTEM_CHARGE_STATUS;
	}
	else if(work_mode==0x02)  //---------------�ֶ��ŵ�ģʽ
	{
		system_status =	SYSTEM_DISCHARGE_STATUS;
	}
	else
	{
		system_status = SYSTEM_NOP_STATUS;
	}
	
	
	switch(system_status)
	{
		case SYSTEM_NOP_STATUS:      
									if(nop_index==0x00)
									{
										bt_led_status=0x00;
										
										charge_led_status=0x00;
										
										discharge_led_status=0x00;
										
										CHARGE_LED_OFF;
										
										DISCHARGE_LED_OFF;
										
										BATRGE_LED_OFF;
										
										Disable_Buck_Pwm();
								
										Set_Buck_Pwm_Duty(0);	
								
										Disable_Bost_Pwm();
								
										Set_Bost_Pwm_Duty(0);
										
										LOAD_OUT_DISABLE;
										
										P_last=0;
										
										P_prev=0;
										
										pv_prev=0;
										
										buck_pwm_value=0;
										
										bost_pwm_value=0;
										
										PWM	=50;
										
										pid_init ( &PID_CC_charge);
										
										pid_init ( &PID_CV_charge);
	
										pid_init ( &PID_CC_discharge);
										
										
										//�������PID����
										PID_CC_charge.Proportion = 0.001;    	// �������� Proportional Const
										
										PID_CC_charge.Integral   = 0; 	// ���ֳ��� Integral Const
																												    
										PID_CC_charge.Derivative = 0; 		// ΢�ֳ��� Derivative Const
																													    
										PID_CC_charge.SetPoint   = 5.0*30.0;    		// �趨Ŀ�� Desired value  1000mA
																				
									    
									    
										//��ѹ���PID����
										PID_CV_charge.Proportion = 0.001;    	// �������� Proportional Const
																				
										PID_CV_charge.Integral   = 0; 	// ���ֳ��� Integral Const
																			    
										PID_CV_charge.Derivative = 0; 		// ΢�ֳ��� Derivative Const
																			    
										PID_CV_charge.SetPoint   = (12.44/34)*1000*volt_id;    		// �趨Ŀ�� Desired value 12.45V
									    
									    
									    //�ŵ����PID����
									    PID_CC_discharge.Proportion = 0.001;    // �������� Proportional Const
									    
										PID_CC_discharge.Integral   = 0.; 	// ���ֳ��� Integral Const
																			    
										PID_CC_discharge.Derivative = 0; 	// ΢�ֳ��� Derivative Const
																			    
										PID_CC_discharge.SetPoint   = (load_cc_I/100)*75;    	// �趨Ŀ�� Desired value 330mA  
										
										open_discharge_time=0x00;
										
										ms_cnt=0x00;						
										se_cnt=0x00;						
										mi_cnt=0x00;						
										ho_cnt=0x00;
										
										Adjust_Pout_Flag=0x00;
										
										nop_index=0x01;
											
										discharge_index=0x00;
											
										charge_index=0x00;
									}
										
								
										break;
		
		case SYSTEM_CHARGE_STATUS:	
										if(charge_index==0x01)
										{
											
											discharge_led_status=0x01;
											
											DISCHARGE_LED_OFF;	
																						
											Disable_Bost_Pwm();
											
											Set_Bost_Pwm_Duty(0);
											
											LOAD_OUT_DISABLE;											
											
											Disable_Buck_Pwm();
											
											PWM	=BUCK_PWM_MIN;
											
											buck_pwm_value=BUCK_PWM_MIN;
											
											Set_Buck_Pwm_Duty(buck_pwm_value);		//�Ŷ����� ��ʼռ�ձ�
											
											#if defined(TEST_CHARGE)
											
											Enable_Buck_Pwm();
											
											buck_pwm_value=900;
											
											Set_Buck_Pwm_Duty(buck_pwm_value);		
											
											while(1)
											{
												CLRWDT();
											}
											
											#endif
										
											
											pid_init ( &PID_CC_charge);				//����PID��ʼ��
											
											pid_init ( &PID_CV_charge);  			//��ѹPID������ʼ��
											
											
											PID_CC_charge.Proportion = 0.001;    	// �������� Proportional Const
	
											PID_CC_charge.Integral   = 0; 	// ���ֳ��� Integral Const
																			    
											PID_CC_charge.Derivative = 0; 		// ΢�ֳ��� Derivative Const
																				    
											PID_CC_charge.SetPoint   = 5.0*30.0;   		// �趨Ŀ�� Desired value  1000mA
											
											
											
											PID_CV_charge.Proportion = 0.001;    	// �������� Proportional Const
											
										    PID_CV_charge.Integral   = 0; 	// ���ֳ��� Integral Const
										    
										    PID_CV_charge.Derivative = 0; 		// ΢�ֳ��� Derivative Const
										    
										    PID_CV_charge.SetPoint   = (12.44/34)*1000*volt_id;    		// �趨Ŀ�� Desired value    --��ѹ�趨12.45V
										    
											
											P_prev=0;
											
											P_last=0;
											
											open_discharge_time=0x00;
											
											ms_cnt=0x00;						
											se_cnt=0x00;						
											mi_cnt=0x00;						
											ho_cnt=0x00;
											
											Adjust_Pout_Flag=0x00;
											
											nop_index=0x00;
											
											discharge_index=0x00;
											
											charge_index=0x02;
											
											//--------------------------
											today_index = today_index+1;
											 
											today_index = today_index%8;
											
											eeprom_write(0x11,(unsigned char)today_index);
										
											bt_00_lv = b_v;
											//--------------------------
										}
										break;
		
		case SYSTEM_DISCHARGE_STATUS:
																		
										if(discharge_index==0)
										{
											
											charge_led_status=0x01;
											
											CHARGE_LED_OFF;
																														
											Disable_Buck_Pwm();
								
											Set_Buck_Pwm_Duty(0);
											
											LOAD_OUT_DISABLE;
											
											Disable_Bost_Pwm();
											
											PWM	=50;
											
											bost_pwm_value=50;
										
											Set_Bost_Pwm_Duty(bost_pwm_value); 
											
											 		
											
											#if defined(TEST_DISCHARGE)
											
											LOAD_OUT_ENABLE;
											
											Enable_Bost_Pwm();
											
											bost_pwm_value=480;
										
											Set_Bost_Pwm_Duty(bost_pwm_value);  		
											
											while(1)
											{
												CLRWDT();
											}
											
											#endif
											
											
											pid_init ( &PID_CC_discharge);			//��ʼ��PID���Ʋ���
											
											
											PID_CC_discharge.Proportion = 0.001;  	// �������� Proportional Const
    
										    PID_CC_discharge.Integral   = 0; 		// ���ֳ��� Integral Const
										    
										    PID_CC_discharge.Derivative = 0; 		// ΢�ֳ��� Derivative Const
										    
										    PID_CC_discharge.SetPoint   = (load_cc_I/100)*75;   	// �趨Ŀ�� Desired value Ĭ��330mA  
										    
										    open_discharge_time=0x00;
										    
										    ms_cnt=0x00;						
											se_cnt=0x00;						
											mi_cnt=0x00;						
											ho_cnt=0x00;
										    
											Adjust_Pout_Flag=0x00;
																					
											nop_index=0x00;
											
											discharge_index=0x01;
											
											charge_index=0x00;
											
											//------------------------------------��������ص�ѹ��¼
											bt_00_hv = b_v;
											
											eeprom_write((0x12+4*( (today_index+8-0)%8 )+0),(unsigned char)(bt_00_hv/256));
			
											eeprom_write((0x12+4*( (today_index+8-0)%8 )+1),(unsigned char)bt_00_hv);
											
											eeprom_write((0x12+4*( (today_index+8-0)%8 )+2),(unsigned char)(bt_00_lv/256));
			
											eeprom_write((0x12+4*( (today_index+8-0)%8 )+3),(unsigned char)bt_00_lv);
											
											
											//-----------------------------------
										}
		
										break;
		
		default:break;
	
	}
	

}


void Mppt_Charge(void)
{
	
					if((battery_voltage_value<dianchi_guoya_huifu)&&(charge_index==0x03))  //MPPT���ٳ��      -----12.35 ���� MPPT���  362
					{
						
						if(mppt_status==0x00)
						{
								if (charge_current_value>=I_prev)  
								{
							
										buck_pwm_value=buck_pwm_value +  200 * 0.025;
										
											if(buck_pwm_value>=BUCK_PWM_MAX)
											{
												buck_pwm_value=BUCK_PWM_MAX;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
									
								}
								else 
								{						
										mppt_status=1;
		
										buck_pwm_value=buck_pwm_value - 200 * 0.025;
										
										if(buck_pwm_value<=BUCK_PWM_MIN)
											{
												buck_pwm_value=BUCK_PWM_MIN;
												
												mppt_status=0;//-----2018-1-17
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
		
								}
						}
						else
						{
								if (charge_current_value>=I_prev)  
								{
							
										buck_pwm_value=buck_pwm_value-200 * 0.025;
										
										if(buck_pwm_value<=BUCK_PWM_MIN)
											{
												buck_pwm_value=BUCK_PWM_MIN;
												
												mppt_status=0;//-----2018-1-17
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
										
										
									
								}
								else 
								{						
										mppt_status=0;
		
										buck_pwm_value=buck_pwm_value+  200 * 0.025;
										
											if(buck_pwm_value>=BUCK_PWM_MAX)
											{
												buck_pwm_value=BUCK_PWM_MAX;
											}
									
										Set_Buck_Pwm_Duty(buck_pwm_value);
		
								}

								

						}
					
						PWM	= buck_pwm_value;//------------caiwk-2018-06-23	
					
						cv_level_time_count=0x00;					
						
					}
					else if((battery_voltage_value>=dianchi_cv_level)&&(battery_voltage_value<dianchi_guoya_baohu)&&(charge_index==0x03)) //CV��ѹ���  12.4--12.6
					{
							cv_level_time_count++;
							
							if(cv_level_time_count>=100)
							{
								cv_level_time_count=0x00;
								
								charge_index=0x04;
							
								PWM	= buck_pwm_value;//------------caiwk-2018-06-23
							}
					}
					else if( (battery_voltage_value<dianchi_guoya_baohu) && (charge_index==0x04) ) //CV��ѹ���  12.4--12.6
					{
							pid_index = 0x02;
							
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
				           buck_pwm_value = (unsigned int)PWM;
				           
				           Set_Buck_Pwm_Duty(buck_pwm_value);
					}
					else NOP();

}



void CC_CV_Charge(void)
{

					if((battery_voltage_value<=dianchi_guoya_huifu)&&(charge_index==0x03))     //CC�������   7.5--12.3  
					{
							PWM_I=pid_calc(&PID_CC_charge,charge_current_value);														
							
				           	PWM	 = PWM+PWM_I;
				           	
				           if( PWM>=BUCK_PWM_MAX)
				           {
				           		PWM=BUCK_PWM_MAX;
				           }			           
				           else if(PWM<=BUCK_PWM_MIN) 
				           {
				           		PWM=BUCK_PWM_MIN;
				           }
				           
				           #if defined(PRINT_PWM)
			
							sprintf(buf, "PWM=%3.2f.....AN3_CHANNEL!\n", PWM);
						
							uart1_send_nbyte(buf, strlen(buf));		
							
							#endif
							
				           buck_pwm_value = (unsigned int)PWM;	
				           
				         	           
				           Set_Buck_Pwm_Duty(buck_pwm_value);
				           
				           
					}
					else if((battery_voltage_value>=dianchi_cv_level)&&(battery_voltage_value<dianchi_guoya_baohu)&&(charge_index==0x03)) //CV��ѹ���  12.4--12.6
					{
							charge_index=0x04;
							
							PWM	= buck_pwm_value;//------------caiwk-2018-06-23
					}
					else if((battery_voltage_value>=dianchi_guoya_huifu)&&(battery_voltage_value<dianchi_guoya_baohu)&&(charge_index==0x04)) //CV��ѹ���  12.4--12.6
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
					else NOP();
					
					
					
					
					
					
}
