//-----  	项目名称：太阳能路灯控制器

//-----  		版本：

//-----  		设计者：蔡维凯
	
//-----  		版本：V1.0

//-----  		日期：2017-12-11

//-----  		描述：PIC16F1938



//							if((pv_prev+2)>=pv_voltage_value)  //上坡 MPPT跟踪
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
//							else if((pv_voltage_value+2)>pv_prev)  //上坡 MPPT跟踪
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


if((pv_prev+2)>=pv_voltage_value)  //下坡 MPPT跟踪
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
//							else if((pv_voltage_value+2)>pv_prev)  //下坡 MPPT跟踪
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
	
	Error = pp->SetPoint - NowPoint;            // 先计算偏差
	
	pp->SumError += Error;                      // 在对偏差进行积分


     
    if((pp->SumError)>=50)     pp->SumError=  50;
    else if((pp->SumError)<=-50)  pp->SumError= -50;

	dError = pp->LastError - pp->PrevError;     // 对偏差微分
	
	pp->PrevError = pp->LastError;
	
	pp->LastError = Error;
					// -------比例项-----------------积分项----------------------------微分项---
	PWM_var=(int)(pp->Proportion * Error  + pp->Integral * pp->SumError  + pp->Derivative * dError  ) ;              



	if(PWM_var>20)PWM_var           =  20 ;
	else  if(PWM_var <= -10)PWM_var = -10; 
    
    return (PWM_var );
}


void Mppt_Charge(void) -----//V1
{
	
					if((battery_voltage_value<600)&&(charge_index==0x01))  //MPPT跟踪充电    
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
	
					if((battery_voltage_value<600)&&(charge_index==0x02))  //MPPT跟踪充电    
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
					else if((battery_voltage_value>=605)&&(battery_voltage_value<=615)&&(charge_index==0x02)) //CV恒压充电
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



----------------------------------<太阳能控制器与遥控器 红外通信协议>------------------------------------------------------

>>>>>>>>>>>>>>>>>>>>>>>>>>1.运行数据查看：<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

1.1)遥控器(TX)---->控制器:

完整数据帧：包头(1BYTE)+数据段(N BYTE)+包尾(1BYTE)

数据段=请求码+CRC校验码(校验范围：BYTE1)

请求码:0xA1
-----------------------------------------
| 包头	| 请求码|	CRC校验码	|  包尾	|
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	|
| 0x55  | 0xA1 	| 0x7E 	| 0xF8 	| 0xAA	|
----------------------------------------


1.2)控制器(TX)---->遥控器:

完整数据帧：包头(1BYTE)+数据段(N BYTE)+包尾(1BYTE)

数据段=响应码+状态数据+CRC校验码(校验范围：BYTE1---BYTE12)

响应码：0xB1

状态数据=光伏电压(2BYTE)+电池电压(2BYTE)+输出电压(2BYTE)+充电电流(2BYTE)+输出电流(2BYTE)+工作模式(1BYTE)

-----------------------------------------------------------------------------------------------------------------------------------------
| 包头	| 响应码|	光伏电压  	|	电池电压  	|	输出电压  	|	充电电流  	|	 输出电流  	  | 工作模式 |	  CRC校验码	   | 包尾	|  		
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	| BYTE6	| BYTE7	| BYTE8	| BYTE9	| BYTE10 | BYTE11 |  BYTE12  | BYTE13 | BYTE14 | BYTE15	|
| 0x55  | 0xB1 	| 0x0B 	| 0xB8 	| 0x04	| 0xB0	| 0x0B	| 0xB8	| 0x00	| 0x96	| 0x00	 | 0x00	  |  0x01	 | 0x0C	  | 0x62   | 0xAA	| 
-----------------------------------------------------------------------------------------------------------------------------------------

>>>>>>>>>>>>>>>>>>>>>>>>>>2.参数查看:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

2.1)遥控器(TX)---->控制器:

完整数据帧：包头(1BYTE)+数据段(N BYTE)+包尾(1BYTE)

数据段=请求码+CRC校验码(校验范围：BYTE1)

请求码:0xA2
-----------------------------------------
| 包头	| 请求码|	CRC校验码	|  包尾	|
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	|
| 0x55  | 0xA2 	| 0x3E 	| 0xF9 	| 0xAA	|
----------------------------------------


2.2)控制器(TX)---->遥控器:

完整数据帧：包头(1BYTE)+数据段(N BYTE)+包尾(1BYTE)

数据段=响应码+系统参数+CRC校验码(校验范围：BYTE1--BYTE6)

响应码：0xB2

系统参数=光控电压(2BYTE)+负载电流(2BYTE)+节能输出百分比(1BYTE)

------------------------------------------------------------------------------------
| 包头	| 响应码|	光控电压  	|	负载电流  	|节能输出 |	CRC校验码     | 包尾   |  		
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	| BYTE6   | BYTE7 | BYTE8 | BYTE9  |
| 0x55  | 0xB2 	| 0x00 	| 0x07 	| 0x00	| 0x21	| 0x00    | 0x02  | 0xED  | 0xAA   | 
------------------------------------------------------------------------------------

>>>>>>>>>>>>>>>>>>>>>>>>>>3.参数保存:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

3.1)遥控器(TX)---->控制器:

完整数据帧：包头(1BYTE)+数据段(N BYTE)+包尾(1BYTE)

数据段=命令码+系统参数+CRC校验码(校验范围：BYTE1--BYTE6)

命令码:0xA3
------------------------------------------------------------------------------------
| 包头	| 命令码|	光控电压  	|	负载电流  	|节能输出 |	CRC校验码     | 包尾   |  		
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	| BYTE6   | BYTE7 | BYTE8 | BYTE9  |
| 0x55  | 0xA3 	| 0x00 	| 0x07 	| 0x00	| 0x21	| 0x00    | 0x02  | 0xED  | 0xAA   | 
------------------------------------------------------------------------------------


3.2)控制器(TX)---->遥控器:

完整数据帧：包头(1BYTE)+数据段(N BYTE)+包尾(1BYTE)

数据段=响应码+状态+CRC校验码(校验范围：BYTE1--BYTE2)

响应码：0xB3

状态：01  参数设置成功
	  02  参数设置失败(参数设置不合理超出系统工作参数范围或是数据传输丢失)

-------------------------------------------------
| 包头	| 响应码| 状态	|	CRC校验码	|  包尾	|
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	|
| 0x55  | 0xB3 	| 0x01 	| 0xB5 	| 0x40	| 0xAA	|
-------------------------------------------------


>>>>>>>>>>>>>>>>>>>>>>>>>>4.数据监测:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

4.1)遥控器(TX)---->控制器:(同上1.运行数据查看)

完整数据帧：包头(1BYTE)+数据段(N BYTE)+包尾(1BYTE)

数据段=请求码+CRC校验码(校验范围：BYTE1)

请求码:0xA1
-----------------------------------------
| 包头	| 请求码|	CRC校验码	|  包尾	|
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	|
| 0x55  | 0xA1 	| 0x7E 	| 0xF8 	| 0xAA	|
----------------------------------------


4.2)控制器(TX)---->遥控器:

完整数据帧：包头(1BYTE)+数据段(N BYTE)+包尾(1BYTE)

数据段=响应码+状态数据+CRC校验码(校验范围：BYTE1---BYTE12)

响应码：0xB1

状态数据=光伏电压(2BYTE)+电池电压(2BYTE)+输出电压(2BYTE)+充电电流(2BYTE)+输出电流(2BYTE)+工作模式(1BYTE)

-----------------------------------------------------------------------------------------------------------------------------------------
| 包头	| 响应码|	光伏电压  	|	电池电压  	|	输出电压  	|	充电电流  	|	 输出电流  	  | 工作模式 |	  CRC校验码	   | 包尾	|  		
| BYTE0 | BYTE1	| BYTE2	| BYTE3	| BYTE4	| BYTE5	| BYTE6	| BYTE7	| BYTE8	| BYTE9	| BYTE10 | BYTE11 |  BYTE12  | BYTE13 | BYTE14 | BYTE15	|
| 0x55  | 0xB1 	| 0x0B 	| 0xB8 	| 0x04	| 0xB0	| 0x0B	| 0xB8	| 0x00	| 0x96	| 0x00	 | 0x00	  |  0x01	 | 0x0C	  | 0x62   | 0xAA	| 
-----------------------------------------------------------------------------------------------------------------------------------------


































