/******************************************************************************
**                           志和兴业有限公司
**
**                           
**
**--------------基本文件信息---------------------------------------------------
** 文   件   名	: 
** 当前    版本	: V1.0 
** 描        述 : 
** 编   译   器 : xc8
** 硬        件 : 太阳能路灯控制器
**--------------历史版本信息---------------------------------------------------
** 开始创建日期	: 2017-12-11
** 创   建   人	: 蔡维凯
** 版  	     本 : V1.0
** 描　      述 : 

**-----------------------------------------------------------------------------
*******************************************************************************/

//**--------------头文件-------------------------------------------------------
#include <xc.h>
#include <GenericTypeDefs.h>

#include <stdio.h>
#include <string.h>

#include"userdefine.h"

//**--------------全局变量-----------------------------------------------------


unsigned char uart1_rx_buf[80];

unsigned char uart1_tx_buf[80];





unsigned char uart1_time_count=0x00;

unsigned char uart1_receive_byte_count=0;

BOOL uart1_receive_flag=FALSE;

unsigned char uart1_rx_control_flag=0x00;


unsigned char uart_send_delay_timer=0x00;

unsigned char uart_send_end_flag=0x00;

unsigned char uart_send_byte_count=0x00;

unsigned char*uart_send_point=NULL;


unsigned char rx_frame_kind=0x00;  //接受帧 类别  01--运行数据帧		02--参数数据帧		03--参数保存返回确认帧

unsigned char tx_frame_kind=0x00; //发送帧


//**--------------宏定义-------------------------------------------------------

//**--------------函数申明-----------------------------------------------------

//**--------------函数定义-----------------------------------------------------






/**********************************************************************
*函数名称：init_uart1
*描述：uart1初始化 波特率2400 8 1 N
*返回类型：void
*输入形参：void
***********************************************************************/
void init_uart1(void)
{

	SP1BRGL = BDRT_S_L;
	SP1BRGH = BDRT_S_H;
	BAUDCON = 0x08; 	 // 波特率控制寄存器
	  	                 // bit7 ABDOVF 自动波特率检测溢出位 异步模式:1 = 自动波特率定时器溢出 0 = 自动波特率定时器未溢出 同步模式:无关位 R/W-0 
	  	                 // bit6 RCIDL 接收空闲标志位 异步模式:1 = 接收器空闲 0 = 已检测到启动位且接收器处于活动状态 同步模式:无关位 R-1 
	  	                 // bit5 DTRXP 数据接收极性选择位 异步模式:1 = 接收数据反相(低电平有效) 0 = 接收数据未反相(高电平有效) 同步模式:无关位 R/W-0 
	  	                 // bit4 
	  	                 // bit3 BRG16 16位波特率发生器位 1 = 使用16位波特率发生器(SPBRGHx:SPBRGx) 0 = 使用8位波特率发生器(SPBRGx)
	  	                 // bit2
	  	                 // bit1
	  	                 // bit0
	  					 // 使用16位波特率发生器
  	UART1_TX_TRIS = 0x00;
  	UART1_RX_TRIS = 0x01;
	TXSTA = 0x20;
		  	               // bit7 CSRC:时钟源选择位 异步模式:无关位 同步模式:1 = 主模式(时钟由内部BRG产生) 0 = 从模式(时钟来自外部时钟源) R/W-0
		  	               // bit6 TX9:9位发送使能位 1 = 选择9位发送 0 = 选择8位发送 R/W-0
		  	               // bit5 TXEN:发送使能位 1 = 使能发送 0 = 禁止发送 R/W-0
		  	               // bit4 SYNC:EUSART模式选择位 1 = 同步模式 0 = 异步模式 R/W-0
		  	               // bit3 SENDB:发送间隔字符位 异步模式:1 = 在下一次发送时发送同步间隔字符(完成时由硬件清零) 0 = 同步间隔字符发送完成 同步模式:无关位 R/W-0
		  	               // bit2 BRGH:高波特率选择位 异步模式:1 = 高速 0 = 低速 同步模式:在此模式下未使用 R/W-0
		  	               // bit1 TRMT:发送移位寄存器状态位 1 = TSR空 0 = TSR满 R-1
		  	               // bit0 TX9D:发送数据的第9位 可以是地址/数据位或奇偶校验位
	RCSTA = 0x90;
	RCIE = 0x01; 			// 使能UART1接收中断
}

/**********************************************************************
*函数名称：uart1_send_byte
*描述：
*返回类型：void
*输入形参：BYTE  data
***********************************************************************/
void uart1_send_byte(BYTE data)
{  
	while (!TXSTAbits.TRMT); // 等待发送移位寄存器空
	
	#if defined(IRD_BY_UART)	
		CCPR5L=(unsigned char)(0x114>>2);				
		CCP5CONbits.DC5B=(unsigned char)(0x114&0b11);
		TMR2ON=1;
		PWM_IRD_TRIS=0;		
	#endif
	
	TXREG = data;
	
	while (!TXSTAbits.TRMT); // 等待发送移位寄存器空
	
	#if defined(IRD_BY_UART)
		CCPR5L=(unsigned char)(0x00>>2);				
		CCP5CONbits.DC5B=(unsigned char)(0x00&0b11);	
		TMR2ON=0;
		PWM_IRD_TRIS=1;
	#endif
}


/**********************************************************************
*函数名称：uart1_send_nbyte
*描述：
*返回类型：void
*输入形参：BYTE *data,DWORD size
***********************************************************************/
void uart1_send_nbyte(BYTE *data,DWORD size)
{
	while (size)
    {
    	uart1_send_byte(*data);
    	data++;
    	size--;
    }
}

/**********************************************************************
*函数名称：uart1_read_byte
*描述：
*返回类型：BYTE 
*输入形参：void
***********************************************************************/
BYTE uart1_read_byte(void)
{
	BYTE data;

	while (!PIR1bits.RCIF); // 等待接收缓冲区满
	data = RCREG;

  	return data;
}

/**********************************************************************
*函数名称：uart1_read_nbyte
*描述：
*返回类型：void 
*输入形参：BYTE *buffer,BYTE length
***********************************************************************/
void uart1_read_nbyte(BYTE *buffer,BYTE length)
{
  	BYTE i;
  	BYTE data;

  	for (i = 0; i < length; i++)
  	{
    	data = uart1_read_byte(); // Get a character from the USART and save in the string
    	*buffer = data;
    	buffer++; // Increment the string pointer
  	}
}


/**********************************************************************
*函数名称：uart1_read_nbyte
*描述：
*返回类型：void 
*输入形参：BYTE *buffer,BYTE length
*----奇偶校验--------
*----偶校验(%2)--
*----奇校验(/2)-----
***********************************************************************/

bit handle_even_check(unsigned char databyte)
{
	unsigned char i=0;
	
	unsigned char num=0;
	
	num=0x00;//----!!!!!!!!!!!!!!局部变量必须清零
	
	for(i=0;i<8;i++)
	{
		if(databyte&(1<<i))
		{
			num++;
		}
	}
	
	return ((bit)(num%2));


}


/**********************************************************************
*函数名称：handle_uart_rx_buf
*描述：
*返回类型：void 
*输入形参：void
***********************************************************************/

void handle_uart_rx_buf(void)
{
	unsigned char i=0;
	
	unsigned int crc_in;
	
	unsigned char byte_h,byte_l;

		switch(rx_frame_kind)
		{
			case 0x01:  //运行数据
					if(uart1_rx_buf[1]==0xA1)
					{
						crc_in=crc16(&uart1_rx_buf[1],1);
						
						if(crc_in==( (uart1_rx_buf[2]<<8) | uart1_rx_buf[3]) )
						{
							
							p_v=(float)(((float)pv_voltage_value)/10)*69;
							
							b_v=(float)(((float)battery_voltage_value)/10)*34;
							
							load_v=(float)(((float)load_voltage_value)/10)*69;
							
							charge_I=((float)charge_current_value)/0.30;
							
							load_I=((float)discharge_current_value)/0.75;
							
							sys_mode=(volt_id<<4)|system_status;																	
							
							//----------------------------------------
							
							uart1_tx_buf[0]=0x55;
						         
							uart1_tx_buf[1]=0xB1;
							
							uart1_tx_buf[2]=(unsigned char )(p_v/256);
							uart1_tx_buf[3]=(unsigned char )p_v;
							
							uart1_tx_buf[4]=(unsigned char )(b_v/256);
							uart1_tx_buf[5]=(unsigned char )b_v;
							
							uart1_tx_buf[6]=(unsigned char )(load_v/256);
							uart1_tx_buf[7]=(unsigned char )load_v;
							
							uart1_tx_buf[8]=(unsigned char )(charge_I/256);
							uart1_tx_buf[9]=(unsigned char )charge_I;
							
							uart1_tx_buf[10]=(unsigned char )(load_I/256);
							uart1_tx_buf[11]=(unsigned char )load_I;
							
							uart1_tx_buf[12]=(unsigned char )sys_mode;
							
							uart1_tx_buf[13]=(unsigned char )(mcu_value/256);
							
							uart1_tx_buf[14]=(unsigned char )(mcu_value);
							
							uart1_tx_buf[15]=(unsigned char )(discharge_current_value/256);
							
							uart1_tx_buf[16]=(unsigned char )(discharge_current_value);
							
							uart1_tx_buf[17]=(unsigned char )(temperature_value/256);
							
							uart1_tx_buf[18]=(unsigned char )(temperature_value);
							
							//-------------------------------------------------------------今天
							uart1_tx_buf[19]=eeprom_read(0x12+4*( (today_index+8-0)%8 )+0 );
							
							uart1_tx_buf[20]=eeprom_read(0x12+4*( (today_index+8-0)%8 )+1 );
							
							uart1_tx_buf[21]=eeprom_read(0x12+4*( (today_index+8-0)%8 )+2 );
							
							uart1_tx_buf[22]=eeprom_read(0x12+4*( (today_index+8-0)%8 )+3 );
							
							//------------------------------------------------------------1天前
							uart1_tx_buf[23]=eeprom_read(0x12+4*( (today_index+8-1)%8 )+0 );
							
							uart1_tx_buf[24]=eeprom_read(0x12+4*( (today_index+8-1)%8 )+1 );
							
							uart1_tx_buf[25]=eeprom_read(0x12+4*( (today_index+8-1)%8 )+2 );
							
							uart1_tx_buf[26]=eeprom_read(0x12+4*( (today_index+8-1)%8 )+3 );
							
							//------------------------------------------------------------2天前
							uart1_tx_buf[27]=eeprom_read(0x12+4*( (today_index+8-2)%8 )+0 );
							
							uart1_tx_buf[28]=eeprom_read(0x12+4*( (today_index+8-2)%8 )+1 );
							
							uart1_tx_buf[29]=eeprom_read(0x12+4*( (today_index+8-2)%8 )+2 );
							
							uart1_tx_buf[30]=eeprom_read(0x12+4*( (today_index+8-2)%8 )+3 );
							
							//------------------------------------------------------------3天前
							uart1_tx_buf[31]=eeprom_read(0x12+4*( (today_index+8-3)%8 )+0 );
							
							uart1_tx_buf[32]=eeprom_read(0x12+4*( (today_index+8-3)%8 )+1 );
							
							uart1_tx_buf[33]=eeprom_read(0x12+4*( (today_index+8-3)%8 )+2 );
							
							uart1_tx_buf[34]=eeprom_read(0x12+4*( (today_index+8-3)%8 )+3 );
							
							//------------------------------------------------------------4天前
							uart1_tx_buf[35]=eeprom_read(0x12+4*( (today_index+8-4)%8 )+0 );
							
							uart1_tx_buf[36]=eeprom_read(0x12+4*( (today_index+8-4)%8 )+1 );
							
							uart1_tx_buf[37]=eeprom_read(0x12+4*( (today_index+8-4)%8 )+2 );
							
							uart1_tx_buf[38]=eeprom_read(0x12+4*( (today_index+8-4)%8 )+3 );
							
							//------------------------------------------------------------5天前
							uart1_tx_buf[39]=eeprom_read(0x12+4*( (today_index+8-5)%8 )+0 );
							
							uart1_tx_buf[40]=eeprom_read(0x12+4*( (today_index+8-5)%8 )+1 );
							
							uart1_tx_buf[41]=eeprom_read(0x12+4*( (today_index+8-5)%8 )+2 );
							
							uart1_tx_buf[42]=eeprom_read(0x12+4*( (today_index+8-5)%8 )+3 );
							
							//------------------------------------------------------------6天前
							uart1_tx_buf[43]=eeprom_read(0x12+4*( (today_index+8-6)%8 )+0 );
							
							uart1_tx_buf[44]=eeprom_read(0x12+4*( (today_index+8-6)%8 )+1 );
							
							uart1_tx_buf[45]=eeprom_read(0x12+4*( (today_index+8-6)%8 )+2 );
							
							uart1_tx_buf[46]=eeprom_read(0x12+4*( (today_index+8-6)%8 )+3 );
							
							//------------------------------------------------------------7天前
							uart1_tx_buf[47]=eeprom_read(0x12+4*( (today_index+8-7)%8 )+0 );
							
							uart1_tx_buf[48]=eeprom_read(0x12+4*( (today_index+8-7)%8 )+1 );
							
							uart1_tx_buf[49]=eeprom_read(0x12+4*( (today_index+8-7)%8 )+2 );
							
							uart1_tx_buf[50]=eeprom_read(0x12+4*( (today_index+8-7)%8 )+3 );
							
							
							crc_data=crc16(&uart1_tx_buf[1],50);
							
							uart1_tx_buf[51]=crc_data/256;							
							uart1_tx_buf[52]=crc_data%256;
							
							uart1_tx_buf[53]=0xAA;
							
							uart1_send_nbyte(uart1_tx_buf,54);		         
																	         						
						}
					}
					break;
			
			case 0x02:				//参数查看
					if(uart1_rx_buf[1]==0xA2)
					{
						crc_in=crc16(&uart1_rx_buf[1],1);
						
						if(crc_in==( (uart1_rx_buf[2]<<8) | uart1_rx_buf[3]) )
						{
							//DISCHARGE_LED_TOG;
							
							uart1_tx_buf[0]=0x55;
						         
							uart1_tx_buf[1]=0xB2;
							
							uart1_tx_buf[2] =(unsigned char )(light_pv/256);
							
							uart1_tx_buf[3] =(unsigned char )light_pv;
							
							uart1_tx_buf[4] =(unsigned char )(load_cc_I/256);
							
							uart1_tx_buf[5] =(unsigned char )load_cc_I;
							
							uart1_tx_buf[6] =(unsigned char )(step_01_load_percent);
							
							uart1_tx_buf[7] =(unsigned char )(step_02_load_percent);
							
							uart1_tx_buf[8] =(unsigned char )(step_03_load_percent);
							
							uart1_tx_buf[9] =(unsigned char )(step_04_load_percent);
							
							uart1_tx_buf[10]=(unsigned char )(step_05_load_percent);
							
							uart1_tx_buf[11]=(unsigned char )(bt_id);
							
							uart1_tx_buf[12]=(unsigned char )(light_time);
							
							uart1_tx_buf[13] =(unsigned char )(step_01_time_limit);
							
							uart1_tx_buf[14] =(unsigned char )(step_02_time_limit);
							
							uart1_tx_buf[15] =(unsigned char )(step_03_time_limit);
							
							uart1_tx_buf[16] =(unsigned char )(step_04_time_limit);
							
							uart1_tx_buf[17] =(unsigned char )(step_05_time_limit);
							
							
							crc_data=crc16(&uart1_tx_buf[1],17);
							
							uart1_tx_buf[18]=crc_data/256;
														
							uart1_tx_buf[19]=crc_data%256;
							
							uart1_tx_buf[20]=0xAA;
							
							uart1_send_nbyte(uart1_tx_buf,21);		  
						}
					}
					break;
			
			case 0x03:
					if(uart1_rx_buf[1]==0xA3)
					{
						crc_in=crc16(&uart1_rx_buf[1],17);
						
						if(crc_in==( (uart1_rx_buf[18]<<8) | uart1_rx_buf[19]) )
						{
							
							light_pv 		= (uart1_rx_buf[2]<<8) | uart1_rx_buf[3];
							
							load_cc_I		= (uart1_rx_buf[4]<<8) | uart1_rx_buf[5];
							
							step_01_load_percent 	= uart1_rx_buf[6];
							
							step_02_load_percent 	= uart1_rx_buf[7];
							
							step_03_load_percent 	= uart1_rx_buf[8];
							
							step_04_load_percent 	= uart1_rx_buf[9];
							
							step_05_load_percent 	= uart1_rx_buf[10];
							
							Adjust_Pout_Flag=0x00;//----!!!!!
							
							bt_id 	= uart1_rx_buf[11];
							
							light_time 	= uart1_rx_buf[12];
							
							step_01_time_limit 	= uart1_rx_buf[13];
							
							step_02_time_limit 	= uart1_rx_buf[14];
							
							step_03_time_limit 	= uart1_rx_buf[15];
							
							step_04_time_limit 	= uart1_rx_buf[16];
							
							step_05_time_limit 	= uart1_rx_buf[17];
							
							if((light_pv>=100)&&(light_pv<=1200)&&(load_cc_I<=300)&&(step_01_load_percent<=100)&&(step_02_load_percent<=100) \
								&&(step_03_load_percent<=100)&&(step_04_load_percent<=100)&&(step_05_load_percent<=100)&&(bt_id>=1)&&(bt_id<=2)\
								&&(light_time<=60)&&(step_01_time_limit<=24)&&(step_02_time_limit<=24)&&(step_03_time_limit<=24)&&(step_04_time_limit<=24)&&(step_05_time_limit<=24))
							{
								//-----------------------------------------------------------保存光控电压参数
								eeprom_write(0x00,(unsigned char)(light_pv/256));
			
								eeprom_write(0x01,(unsigned char)light_pv);
								
								//-----------------------------------------------------------保存负载工作电流参数
								eeprom_write(0x02,(unsigned char)(load_cc_I/256));
			
								eeprom_write(0x03,(unsigned char)load_cc_I);
								
								//-----------------------------------------------------------保存节能输出百分比参数
								eeprom_write(0x04,(unsigned char)(step_01_load_percent));
								
								eeprom_write(0x05,(unsigned char)(step_02_load_percent));
								
								eeprom_write(0x06,(unsigned char)(step_03_load_percent));
								
								eeprom_write(0x07,(unsigned char)(step_04_load_percent));
								
								eeprom_write(0x08,(unsigned char)(step_05_load_percent));
								
								eeprom_write(0x0a,(unsigned char)(bt_id));
								
								eeprom_write(0x0b,(unsigned char)(light_time));
								
								eeprom_write(0x0c,(unsigned char)(step_01_time_limit));
								
								eeprom_write(0x0d,(unsigned char)(step_02_time_limit));
								
								eeprom_write(0x0e,(unsigned char)(step_03_time_limit));
								
								eeprom_write(0x0f,(unsigned char)(step_04_time_limit));
								
								eeprom_write(0x10,(unsigned char)(step_05_time_limit));
								
								//参数更新到系统变量
								light_on_pv_level	=	(light_pv*10)/69;						//亮灯光伏电压门限值
								
								light_off_pv_level 	= 	((light_pv*10)/69)+30;				//关灯光伏电压门限值
								
								PID_CC_discharge.SetPoint   = (load_cc_I/100)*75;    	// 设定目标 Desired value 330mA 
								
								if(light_time==0x00)
								{
									light_time_level = 1000;
								}
								else
								{
									light_time_level = (unsigned long int)(light_time*60*180);
								}
								
								//回复响应帧 
								
								uart1_tx_buf[0]=0x55;
						         
								uart1_tx_buf[1]=0xB3;
								
								uart1_tx_buf[2]=0x01;    //参数设置成功
											         
								crc_data=crc16(&uart1_tx_buf[1],2);
											         
								uart1_tx_buf[3]=crc_data/256;
											         
								uart1_tx_buf[4]=crc_data%256;
											         
								uart1_tx_buf[5]=0xAA;
											         
								uart1_send_nbyte(uart1_tx_buf,6);
							}
							else
							{
								uart1_tx_buf[0]=0x55;
						         
								uart1_tx_buf[1]=0xB3;
								
								uart1_tx_buf[2]=0x02;    //参数设置错误
											         
								crc_data=crc16(&uart1_tx_buf[1],2);
											         
								uart1_tx_buf[3]=crc_data/256;
											         
								uart1_tx_buf[4]=crc_data%256;
											         
								uart1_tx_buf[5]=0xAA;
											         
								uart1_send_nbyte(uart1_tx_buf,6);
								
								RESET();
							}
							
							
																										
						}
					}
					break;
			case 0x04://------------------手动充电模式
								work_mode=0x01;
														
								uart1_tx_buf[0]=0x55;
						         
								uart1_tx_buf[1]=0xB4;
								
								uart1_tx_buf[2]=0x01;    
											         
								crc_data=crc16(&uart1_tx_buf[1],2);
											         
								uart1_tx_buf[3]=crc_data/256;
											         
								uart1_tx_buf[4]=crc_data%256;
											         
								uart1_tx_buf[5]=0xAA;
											         
								uart1_send_nbyte(uart1_tx_buf,6);
					break;
			
			case 0x05://------------------手动放电模式
								work_mode=0x02;
								
								uart1_tx_buf[0]=0x55;
						         
								uart1_tx_buf[1]=0xB5;
								
								uart1_tx_buf[2]=0x01;    
											         
								crc_data=crc16(&uart1_tx_buf[1],2);
											         
								uart1_tx_buf[3]=crc_data/256;
											         
								uart1_tx_buf[4]=crc_data%256;
											         
								uart1_tx_buf[5]=0xAA;
											         
								uart1_send_nbyte(uart1_tx_buf,6);
					break;
			case 0x06://-------------------自动模式
								work_mode=0x00;
								
								uart1_tx_buf[0]=0x55;
						         
								uart1_tx_buf[1]=0xB6;
								
								uart1_tx_buf[2]=0x01;    
											         
								crc_data=crc16(&uart1_tx_buf[1],2);
											         
								uart1_tx_buf[3]=crc_data/256;
											         
								uart1_tx_buf[4]=crc_data%256;
											         
								uart1_tx_buf[5]=0xAA;
											         
								uart1_send_nbyte(uart1_tx_buf,6);
					break;
			default:break;
		}
		
	rx_frame_kind=0x00;//--	
	
	memset (uart1_rx_buf,0,sizeof(uart1_rx_buf));
}
