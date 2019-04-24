

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


unsigned char pv_voltage_status=0x00;    		//光伏板电压状态

unsigned char battery_voltage_status=0x00;		//电池电压状态

unsigned char load_voltage_status=0x00;			//负载端状态

unsigned char discharge_index=0x00;  			//放电阶段变量

unsigned char charge_index=0x00;				//充电阶段变量

unsigned char nop_index=0x00;

unsigned int involid_time_count=0x00;

unsigned int cv_level_time_count=0x00;

unsigned int load_short_time_count=0x00;		//输出短路检测变量

unsigned int load_open_time_count=0x00;			//输出开路检测变量

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
*函数名称：handle_ad_loop
*描述：AD轮训采样
*返回类型：void
*输入形参：void
***********************************************************************/
void handle_ad_loop(void)
{
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		if(handle_an0_process_flag==0x01)
		{
			ADCON1bits.ADPREF =0b00;  //VEF---VDD
			
			mcu_value=start_ad_convert(MCU_CHANNEL);  			//采样通道选择  MCU_CHANNEL  现版本该引脚用于短路保护 比较器负端输入 
			
			ADCON1bits.ADPREF =0b11;  //VEF---1,024V  内部参考电压
			
			if(mcu_value<490) //60 温度
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
			else if(mcu_value>510 && mcu_value<530) //80--100 温度 放电--降载50%
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
			else if(mcu_value>530 && mcu_value<550) //100--120 温度  放电--降载20%
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
			else if(mcu_value>=550)  //120--   过温保护
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
		
			temperature_value=start_ad_convert(AN1_CHANNEL);  		//采样通道选择	AN1		环境温度  0℃--90      70℃--950
			
			if((temperature_value>90)&&(temperature_value<950))  	//正常工作温度范围：0℃---70℃
			{
				temper_time_count++;
				
				over_temper_time_count=0x00;
				
				if(temper_time_count>=10)
				{
					temper_time_count=0x00;
					
					sys_temper_flag=0x01; 						//系统工作温度正常
				}	
			}
			else
			{
				over_temper_time_count++;
				
				temper_time_count=0x00;
				
				if(over_temper_time_count>=10)
				{
					over_temper_time_count=0x00;
					
					sys_temper_flag=0x00;						//超出系统正常工作温度范围
				}
			}
			
			handle_an1_process_flag=0x00;
						
		}
		
		
		
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		if(handle_an2_process_flag==0x01)
		{
		
			pv_voltage_value=start_ad_convert(AN2_CHANNEL);  		//采样通道选择	AN2		光伏板电压    分压电阻缩减比例 1:69 
			
			
			#if defined(PRINT_TEST)
			
			sprintf(buf, "PV=%4d.....AN2_CHANNEL!\n", pv_voltage_value);
		
			uart1_send_nbyte(buf, strlen(buf));
			
			#endif
			
			if(pv_index==0x00)
			{
				if(pv_voltage_value<=light_on_pv_level) 		//鉴别白天和黑夜   通过光伏板电压检测   5V---10V
				{																								
					night_time_count++;
					
					day_time_count=0x00;
					
					if(night_time_count>light_time_level)  
					{
						night_time_count=0x00;
						
						pv_voltage_status=0x02;			//进入放电模式
						
					}
						
				}
				else if((pv_voltage_value>(light_off_pv_level))) 
				{
					day_time_count++;
					
					night_time_count=0x00;
					
					if(day_time_count>light_time_level)
					{
						day_time_count=0x00;
						
						pv_voltage_status=0x00;  //空闲状态
												
					}				
				}
				else
				{
					day_time_count=0x00;
					
					night_time_count=0x00;
				}
			}
			
			if((pv_voltage_value>=light_off_pv_level)&&(pv_voltage_value<1000)) 	//10V---69V  光伏板电压范围
			{																			
				pv_time_count++;
												
				if(pv_time_count>light_time_level)
				{
					pv_time_count=0x00;
							
					pv_voltage_status=0x01; 			//进入充电模式
					
					day_time_count=0x00;  
					
					night_time_count=0x00; 
					
					pv_index=0x01;										
							
				}				
							
			}
			else if(pv_voltage_value>=1000)
			{
				pv_time_count=0x00;
				
				pv_voltage_status=0x00; //空闲状态
			}
			else
			{
				pv_time_count=0x00;
						
			}
			
			if(pv_index==0x01)
			{				 
				if(pv_voltage_value<=light_on_pv_level) 									//鉴别白天和黑夜   通过光伏板电压检测   5V---10V
				{																								
					night_time_count++;
										
					if(night_time_count>light_time_level)  
					{
						night_time_count=0x00;
						
						pv_voltage_status=0x02;												//夜晚状态   即将进入放电模式
						
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
		if(handle_an9_process_flag==0x01)  								//电流检测范围：0.15A---5A  采样电阻75毫欧
		{
			charge_current_value=0x00;
			
			if(system_status ==	SYSTEM_CHARGE_STATUS)
			{
				charge_current_value=start_ad_convert(AN9_CHANNEL);  		//采样通道选择	AN9		充电电流
			
				#if defined(PRINT_I	)
				
				sprintf(buf, "I=%4d.....AN9_CHANNEL!\n", charge_current_value);
			
				uart1_send_nbyte(buf, strlen(buf));
				
				#endif
				
				if((charge_current_value>=charge_i_limit)&&(charge_index>=0x03)) 		//充电限流5A
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
		
			battery_voltage_value=start_ad_convert(AN12_CHANNEL);  			//采样通道选择	AN12	电池电压    分压电阻缩减比例 1：34
			
			//-------------------------------------------------------------------
			b_v=(float)(((float)battery_voltage_value)/10)*34;
			
			//-------------------------------------------------------------------
			
			if((battery_voltage_value<(dianchi_guoya_baohu+volt_id*5))&&(charge_index==0x00))					//锂电池电压是否正常？  <12.6V
			{
				bt_time_count++;
				
				if(bt_time_count>=100)
				{
					bt_time_count=0x00;
					
					bt_led_status=0x01;
					
					charge_index=0x01;
				
					BATRGE_LED_ON;  																	//系统检测电池正常。
					
					battery_voltage_status=0x01;														//电池状态正常
				}					
				
			}
			else if((battery_voltage_value>=(dianchi_guoya_baohu+volt_id*5))&&(charge_index<=0x01))
			{		
					bt_led_status=0x00;
					
					bt_time_count=0x00;
												
					battery_voltage_status=0x00;					//电池状态异常
			}
			
				
			if( (battery_voltage_value<dianchi_guoya_huifu) && (charge_index==0x02) )  		//<电池充电恢复电压
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
				
				if((charge_current_value<charge_i_limit)&&(charge_index>=0x03))	    				//充电电流：0---5A	
				{
					mppt_time_count++;
					
					if(mppt_time_count>5)
					{
						mppt_time_count=0x00;
						
						Mppt_Charge();       														//MPPT充电模式
						
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
						
						while(1); //等待系统复位
					}	
				}	
			}
												
							
			 
			P_prev=P_last;
			
			pv_prev=pv_voltage_value;
			
			handle_an3_process_flag=0x00;
						
		}
		
		
		
		
		
		//------------------------------------------------------------------------------------------------------------------------------------------------------		
		if(handle_an4_process_flag==0x01)								//分压电阻缩减比例 1:69
		{
			load_voltage_value=0x00;
			
			if(system_status ==	SYSTEM_DISCHARGE_STATUS)
			{
				load_voltage_value=start_ad_convert(AN4_CHANNEL);  			//采样通道选择	AN4		负载输出端电压
			
				//---------------------------------------------------------------------------------------------------
					if((load_voltage_value<shuchu_shortout_voltage)&&(discharge_index==0x02)&&(PID_CC_discharge.SetPoint>0))     	//输出端  <输出短路电压点   可判定：1.输出端短路  2.LED灯珠选用错误
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
							
							while(1); //等待系统复位
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
							
							while(1); //等待系统复位
						}
						
					}
					else
					{
						load_short_time_count=0x00;
					}
								
				//---------------------------------------------------------------------------------------------------
					if((load_voltage_value>shuchu_open_voltage)&&(discharge_index==0x02)) //输出端电压>60V+放电模式=负载端开路过压
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
							
							while(1); //等待系统复位
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
		if(handle_an10_process_flag==0x01)  								//电流检测范围：0.1A---1.2A  采样电阻75毫欧  4--90  默认350mA输出 采样值<10
		{
			discharge_current_value=0x00;
			
			if(system_status ==	SYSTEM_DISCHARGE_STATUS)									//系统处于放电状态
			{
				discharge_current_value=start_ad_convert(AN10_CHANNEL);  					//采样通道选择	AN10	放电电流
							
				if((discharge_current_value>discharge_i_baohu)&&(discharge_index==0x02))  	//过载保护    >2.4A
				{ 									
					over_load_time_count++;
					
					if(over_load_time_count>100)												//过载延时保护
					{										
						discharge_index=0x03;
										
						bost_pwm_value=2;
						
						Set_Bost_Pwm_Duty(bost_pwm_value);
						
						delay_ms(1);
						
						Disable_Bost_Pwm();
						
						LOAD_OUT_DISABLE;
						
						over_load_time_count=0x00;
						
						discharge_led_status=0x00;
						
						while(1); //等待系统复位
					}
					
				}
				else
				{
						over_load_time_count=0x00;
				}
				
				if((battery_voltage_value>dianchi_qianya_huifu)&&(discharge_index==0x01))   //    电池欠压恢复点
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
				
				
				 if((battery_voltage_value>=dianchi_qianya_baohu)&&(discharge_index==0x02))    		//电池电压>欠压保护点
				 {
					 
				 	if((discharge_current_value<=discharge_i_limit)&&(discharge_index==0x02))  		//PID 恒流输出控制  默认350mA(330mA)   PID 调节   电流限制<2.1A
					{								    

						//----------------------------------------------------------------------------时长节能调节模式
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
						
						//---------------------------------------------------------------------------限定功率输出
						if( ((load_cc_I/100)*75) > (Load_Pmax*75/(load_voltage_value*69/1000)) )	
						{
							PID_CC_discharge.SetPoint=(Load_Pmax*75)/(load_voltage_value*69/1000);
							
							limit_power_pid_flag=0x01;	//------PID限功率调节标记											           
							
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
							//------------------------------------------------------内部过温降载
							if(mcu_temp_index==0x01) //80--100℃  降载50%
							{
								PID_CC_discharge.SetPoint = PID_CC_discharge.SetPoint*0.5;
							}
							else if(mcu_temp_index==0x02) //100--120℃  降载20%
							{
								PID_CC_discharge.SetPoint = PID_CC_discharge.SetPoint*0.2;
							}
							else if(mcu_temp_index==0x03) //120 内部过温保护
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
							
							//------------------------------------------------------内部过温降载
							if(mcu_temp_index==0x01) //80--100℃  降载50%
							{
								PID_CC_discharge.SetPoint = PID_CC_discharge.SetPoint*0.5;
							}
							else if(mcu_temp_index==0x02) //100--120℃  降载20%
							{
								PID_CC_discharge.SetPoint = PID_CC_discharge.SetPoint*0.2;
							}
							else if(mcu_temp_index==0x03) //120 内部过温保护
							{
								PID_CC_discharge.SetPoint  =0;
							}
							
							
						}
			
						//---------------------------------------------------------
							pid_index = 0x01; //恒流放电PID调节标志
							
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
						    
						    limit_power_pid_flag=0x00;		//清限定输出功率标志
							
							
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
				 else if((battery_voltage_value<dianchi_qianya_baohu)&&(discharge_index==0x02)) //   欠压保护 
				 {
				 		
				 		battery_low_time_count++;
						
						if(battery_low_time_count>1000)
						{													
							discharge_index=0x03;
							
							bost_pwm_value=2;
							
							Set_Bost_Pwm_Duty(bost_pwm_value);
							
							battery_low_time_count=0x00;
							
							discharge_led_status=0x00;
							
							while(1); //等待系统复位
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
*函数名称：start_ad_convert
*描述：启动AD采样转换
*返回类型：unsigned int
*输入形参：unsigned char
***********************************************************************/
unsigned int start_ad_convert(unsigned char ch)
{
	
			unsigned char i,j,k;
		
			unsigned int ad_h,ad_l;		
			
		
			unsigned int temp;
			
			unsigned char ad_ch;
			
			ad_ch=0x00;
			
			ad_ch=ch;
	
			ADCON0bits.CHS	  =ch;  			//采样通道选择
	
    		ADCON0bits.ADON   =1;				//使能AD外设
    		
    		if((ad_ch==AN10_CHANNEL)||(ad_ch==AN9_CHANNEL))   //放电电流----充电电流
    		{
    			for(i=0;i<51;i++)
				{
					__delay_us(5);//等待采样时间		
			
					ADCON0bits.GO=1; //启动采样
			
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
				__delay_us(10);//等待采样时间		
		
				ADCON0bits.GO=1; //启动采样
		
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
*函数名称：handle_task_process
*描述：系统任务调度处理
*返回类型：void
*输入形参：void
***********************************************************************/		
void handle_task_process(void)
{
	
	
	if(handle_short_flag==0x01)  //短路保护
	{
		over_load_time_count=0x00;
						
		load_voltage_status=0x01;
		
		handle_short_flag=0x00;
		
		discharge_led_status=0x00;
						
		while(1); //等待系统复位
	}
	
	if(work_mode==0x00)//-----------------正常工作模式（自动模式）
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
	else if(work_mode==0x01)  //---------------手动充电模式
	{
		system_status =	SYSTEM_CHARGE_STATUS;
	}
	else if(work_mode==0x02)  //---------------手动放电模式
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
										
										
										//恒流充电PID调节
										PID_CC_charge.Proportion = 0.001;    	// 比例常数 Proportional Const
										
										PID_CC_charge.Integral   = 0; 	// 积分常数 Integral Const
																												    
										PID_CC_charge.Derivative = 0; 		// 微分常数 Derivative Const
																													    
										PID_CC_charge.SetPoint   = 5.0*30.0;    		// 设定目标 Desired value  1000mA
																				
									    
									    
										//恒压充电PID调节
										PID_CV_charge.Proportion = 0.001;    	// 比例常数 Proportional Const
																				
										PID_CV_charge.Integral   = 0; 	// 积分常数 Integral Const
																			    
										PID_CV_charge.Derivative = 0; 		// 微分常数 Derivative Const
																			    
										PID_CV_charge.SetPoint   = (12.44/34)*1000*volt_id;    		// 设定目标 Desired value 12.45V
									    
									    
									    //放电恒流PID调节
									    PID_CC_discharge.Proportion = 0.001;    // 比例常数 Proportional Const
									    
										PID_CC_discharge.Integral   = 0.; 	// 积分常数 Integral Const
																			    
										PID_CC_discharge.Derivative = 0; 	// 微分常数 Derivative Const
																			    
										PID_CC_discharge.SetPoint   = (load_cc_I/100)*75;    	// 设定目标 Desired value 330mA  
										
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
											
											Set_Buck_Pwm_Duty(buck_pwm_value);		//扰动跟踪 初始占空比
											
											#if defined(TEST_CHARGE)
											
											Enable_Buck_Pwm();
											
											buck_pwm_value=900;
											
											Set_Buck_Pwm_Duty(buck_pwm_value);		
											
											while(1)
											{
												CLRWDT();
											}
											
											#endif
										
											
											pid_init ( &PID_CC_charge);				//恒流PID初始化
											
											pid_init ( &PID_CV_charge);  			//恒压PID参数初始化
											
											
											PID_CC_charge.Proportion = 0.001;    	// 比例常数 Proportional Const
	
											PID_CC_charge.Integral   = 0; 	// 积分常数 Integral Const
																			    
											PID_CC_charge.Derivative = 0; 		// 微分常数 Derivative Const
																				    
											PID_CC_charge.SetPoint   = 5.0*30.0;   		// 设定目标 Desired value  1000mA
											
											
											
											PID_CV_charge.Proportion = 0.001;    	// 比例常数 Proportional Const
											
										    PID_CV_charge.Integral   = 0; 	// 积分常数 Integral Const
										    
										    PID_CV_charge.Derivative = 0; 		// 微分常数 Derivative Const
										    
										    PID_CV_charge.SetPoint   = (12.44/34)*1000*volt_id;    		// 设定目标 Desired value    --恒压设定12.45V
										    
											
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
											
											
											pid_init ( &PID_CC_discharge);			//初始化PID控制参数
											
											
											PID_CC_discharge.Proportion = 0.001;  	// 比例常数 Proportional Const
    
										    PID_CC_discharge.Integral   = 0; 		// 积分常数 Integral Const
										    
										    PID_CC_discharge.Derivative = 0; 		// 微分常数 Derivative Const
										    
										    PID_CC_discharge.SetPoint   = (load_cc_I/100)*75;   	// 设定目标 Desired value 默认330mA  
										    
										    open_discharge_time=0x00;
										    
										    ms_cnt=0x00;						
											se_cnt=0x00;						
											mi_cnt=0x00;						
											ho_cnt=0x00;
										    
											Adjust_Pout_Flag=0x00;
																					
											nop_index=0x00;
											
											discharge_index=0x01;
											
											charge_index=0x00;
											
											//------------------------------------保存今天电池电压记录
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
	
					if((battery_voltage_value<dianchi_guoya_huifu)&&(charge_index==0x03))  //MPPT跟踪充电      -----12.35 进入 MPPT充电  362
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
					else if((battery_voltage_value>=dianchi_cv_level)&&(battery_voltage_value<dianchi_guoya_baohu)&&(charge_index==0x03)) //CV恒压充电  12.4--12.6
					{
							cv_level_time_count++;
							
							if(cv_level_time_count>=100)
							{
								cv_level_time_count=0x00;
								
								charge_index=0x04;
							
								PWM	= buck_pwm_value;//------------caiwk-2018-06-23
							}
					}
					else if( (battery_voltage_value<dianchi_guoya_baohu) && (charge_index==0x04) ) //CV恒压充电  12.4--12.6
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

					if((battery_voltage_value<=dianchi_guoya_huifu)&&(charge_index==0x03))     //CC恒流充电   7.5--12.3  
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
					else if((battery_voltage_value>=dianchi_cv_level)&&(battery_voltage_value<dianchi_guoya_baohu)&&(charge_index==0x03)) //CV恒压充电  12.4--12.6
					{
							charge_index=0x04;
							
							PWM	= buck_pwm_value;//------------caiwk-2018-06-23
					}
					else if((battery_voltage_value>=dianchi_guoya_huifu)&&(battery_voltage_value<dianchi_guoya_baohu)&&(charge_index==0x04)) //CV恒压充电  12.4--12.6
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
