/******************************************************************************
**                           ־����ҵ���޹�˾
**
**                           
**
**--------------�����ļ���Ϣ---------------------------------------------------
** ��   ��   ��	: 
** ��ǰ    �汾	: V1.0 
** ��        �� : 
** ��   ��   �� : xc8
** Ӳ        �� : ̫����·�ƿ�����
**--------------��ʷ�汾��Ϣ---------------------------------------------------
** ��ʼ��������	: 2017-12-11
** ��   ��   ��	: ��ά��
** ��  	     �� : V1.0
** �衡      �� : 

**-----------------------------------------------------------------------------
*******************************************************************************/

//**--------------ͷ�ļ�-------------------------------------------------------
#include <xc.h>
#include <GenericTypeDefs.h>

#include <stdio.h>
#include <string.h>

#include"userdefine.h"

//**--------------ȫ�ֱ���-----------------------------------------------------


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


unsigned char rx_frame_kind=0x00;  //����֡ ���  01--��������֡		02--��������֡		03--�������淵��ȷ��֡

unsigned char tx_frame_kind=0x00; //����֡


//**--------------�궨��-------------------------------------------------------

//**--------------��������-----------------------------------------------------

//**--------------��������-----------------------------------------------------






/**********************************************************************
*�������ƣ�init_uart1
*������uart1��ʼ�� ������2400 8 1 N
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void init_uart1(void)
{

	SP1BRGL = BDRT_S_L;
	SP1BRGH = BDRT_S_H;
	BAUDCON = 0x08; 	 // �����ʿ��ƼĴ���
	  	                 // bit7 ABDOVF �Զ������ʼ�����λ �첽ģʽ:1 = �Զ������ʶ�ʱ����� 0 = �Զ������ʶ�ʱ��δ��� ͬ��ģʽ:�޹�λ R/W-0 
	  	                 // bit6 RCIDL ���տ��б�־λ �첽ģʽ:1 = ���������� 0 = �Ѽ�⵽����λ�ҽ��������ڻ״̬ ͬ��ģʽ:�޹�λ R-1 
	  	                 // bit5 DTRXP ���ݽ��ռ���ѡ��λ �첽ģʽ:1 = �������ݷ���(�͵�ƽ��Ч) 0 = ��������δ����(�ߵ�ƽ��Ч) ͬ��ģʽ:�޹�λ R/W-0 
	  	                 // bit4 
	  	                 // bit3 BRG16 16λ�����ʷ�����λ 1 = ʹ��16λ�����ʷ�����(SPBRGHx:SPBRGx) 0 = ʹ��8λ�����ʷ�����(SPBRGx)
	  	                 // bit2
	  	                 // bit1
	  	                 // bit0
	  					 // ʹ��16λ�����ʷ�����
  	UART1_TX_TRIS = 0x00;
  	UART1_RX_TRIS = 0x01;
	TXSTA = 0x20;
		  	               // bit7 CSRC:ʱ��Դѡ��λ �첽ģʽ:�޹�λ ͬ��ģʽ:1 = ��ģʽ(ʱ�����ڲ�BRG����) 0 = ��ģʽ(ʱ�������ⲿʱ��Դ) R/W-0
		  	               // bit6 TX9:9λ����ʹ��λ 1 = ѡ��9λ���� 0 = ѡ��8λ���� R/W-0
		  	               // bit5 TXEN:����ʹ��λ 1 = ʹ�ܷ��� 0 = ��ֹ���� R/W-0
		  	               // bit4 SYNC:EUSARTģʽѡ��λ 1 = ͬ��ģʽ 0 = �첽ģʽ R/W-0
		  	               // bit3 SENDB:���ͼ���ַ�λ �첽ģʽ:1 = ����һ�η���ʱ����ͬ������ַ�(���ʱ��Ӳ������) 0 = ͬ������ַ�������� ͬ��ģʽ:�޹�λ R/W-0
		  	               // bit2 BRGH:�߲�����ѡ��λ �첽ģʽ:1 = ���� 0 = ���� ͬ��ģʽ:�ڴ�ģʽ��δʹ�� R/W-0
		  	               // bit1 TRMT:������λ�Ĵ���״̬λ 1 = TSR�� 0 = TSR�� R-1
		  	               // bit0 TX9D:�������ݵĵ�9λ �����ǵ�ַ/����λ����żУ��λ
	RCSTA = 0x90;
	RCIE = 0x01; 			// ʹ��UART1�����ж�
}

/**********************************************************************
*�������ƣ�uart1_send_byte
*������
*�������ͣ�void
*�����βΣ�BYTE  data
***********************************************************************/
void uart1_send_byte(BYTE data)
{  
	while (!TXSTAbits.TRMT); // �ȴ�������λ�Ĵ�����
	
	#if defined(IRD_BY_UART)	
		CCPR5L=(unsigned char)(0x114>>2);				
		CCP5CONbits.DC5B=(unsigned char)(0x114&0b11);
		TMR2ON=1;
		PWM_IRD_TRIS=0;		
	#endif
	
	TXREG = data;
	
	while (!TXSTAbits.TRMT); // �ȴ�������λ�Ĵ�����
	
	#if defined(IRD_BY_UART)
		CCPR5L=(unsigned char)(0x00>>2);				
		CCP5CONbits.DC5B=(unsigned char)(0x00&0b11);	
		TMR2ON=0;
		PWM_IRD_TRIS=1;
	#endif
}


/**********************************************************************
*�������ƣ�uart1_send_nbyte
*������
*�������ͣ�void
*�����βΣ�BYTE *data,DWORD size
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
*�������ƣ�uart1_read_byte
*������
*�������ͣ�BYTE 
*�����βΣ�void
***********************************************************************/
BYTE uart1_read_byte(void)
{
	BYTE data;

	while (!PIR1bits.RCIF); // �ȴ����ջ�������
	data = RCREG;

  	return data;
}

/**********************************************************************
*�������ƣ�uart1_read_nbyte
*������
*�������ͣ�void 
*�����βΣ�BYTE *buffer,BYTE length
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
*�������ƣ�uart1_read_nbyte
*������
*�������ͣ�void 
*�����βΣ�BYTE *buffer,BYTE length
*----��żУ��--------
*----żУ��(%2)--
*----��У��(/2)-----
***********************************************************************/

bit handle_even_check(unsigned char databyte)
{
	unsigned char i=0;
	
	unsigned char num=0;
	
	num=0x00;//----!!!!!!!!!!!!!!�ֲ�������������
	
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
*�������ƣ�handle_uart_rx_buf
*������
*�������ͣ�void 
*�����βΣ�void
***********************************************************************/

void handle_uart_rx_buf(void)
{
	unsigned char i=0;
	
	unsigned int crc_in;
	
	unsigned char byte_h,byte_l;

		switch(rx_frame_kind)
		{
			case 0x01:  //��������
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
							
							//-------------------------------------------------------------����
							uart1_tx_buf[19]=eeprom_read(0x12+4*( (today_index+8-0)%8 )+0 );
							
							uart1_tx_buf[20]=eeprom_read(0x12+4*( (today_index+8-0)%8 )+1 );
							
							uart1_tx_buf[21]=eeprom_read(0x12+4*( (today_index+8-0)%8 )+2 );
							
							uart1_tx_buf[22]=eeprom_read(0x12+4*( (today_index+8-0)%8 )+3 );
							
							//------------------------------------------------------------1��ǰ
							uart1_tx_buf[23]=eeprom_read(0x12+4*( (today_index+8-1)%8 )+0 );
							
							uart1_tx_buf[24]=eeprom_read(0x12+4*( (today_index+8-1)%8 )+1 );
							
							uart1_tx_buf[25]=eeprom_read(0x12+4*( (today_index+8-1)%8 )+2 );
							
							uart1_tx_buf[26]=eeprom_read(0x12+4*( (today_index+8-1)%8 )+3 );
							
							//------------------------------------------------------------2��ǰ
							uart1_tx_buf[27]=eeprom_read(0x12+4*( (today_index+8-2)%8 )+0 );
							
							uart1_tx_buf[28]=eeprom_read(0x12+4*( (today_index+8-2)%8 )+1 );
							
							uart1_tx_buf[29]=eeprom_read(0x12+4*( (today_index+8-2)%8 )+2 );
							
							uart1_tx_buf[30]=eeprom_read(0x12+4*( (today_index+8-2)%8 )+3 );
							
							//------------------------------------------------------------3��ǰ
							uart1_tx_buf[31]=eeprom_read(0x12+4*( (today_index+8-3)%8 )+0 );
							
							uart1_tx_buf[32]=eeprom_read(0x12+4*( (today_index+8-3)%8 )+1 );
							
							uart1_tx_buf[33]=eeprom_read(0x12+4*( (today_index+8-3)%8 )+2 );
							
							uart1_tx_buf[34]=eeprom_read(0x12+4*( (today_index+8-3)%8 )+3 );
							
							//------------------------------------------------------------4��ǰ
							uart1_tx_buf[35]=eeprom_read(0x12+4*( (today_index+8-4)%8 )+0 );
							
							uart1_tx_buf[36]=eeprom_read(0x12+4*( (today_index+8-4)%8 )+1 );
							
							uart1_tx_buf[37]=eeprom_read(0x12+4*( (today_index+8-4)%8 )+2 );
							
							uart1_tx_buf[38]=eeprom_read(0x12+4*( (today_index+8-4)%8 )+3 );
							
							//------------------------------------------------------------5��ǰ
							uart1_tx_buf[39]=eeprom_read(0x12+4*( (today_index+8-5)%8 )+0 );
							
							uart1_tx_buf[40]=eeprom_read(0x12+4*( (today_index+8-5)%8 )+1 );
							
							uart1_tx_buf[41]=eeprom_read(0x12+4*( (today_index+8-5)%8 )+2 );
							
							uart1_tx_buf[42]=eeprom_read(0x12+4*( (today_index+8-5)%8 )+3 );
							
							//------------------------------------------------------------6��ǰ
							uart1_tx_buf[43]=eeprom_read(0x12+4*( (today_index+8-6)%8 )+0 );
							
							uart1_tx_buf[44]=eeprom_read(0x12+4*( (today_index+8-6)%8 )+1 );
							
							uart1_tx_buf[45]=eeprom_read(0x12+4*( (today_index+8-6)%8 )+2 );
							
							uart1_tx_buf[46]=eeprom_read(0x12+4*( (today_index+8-6)%8 )+3 );
							
							//------------------------------------------------------------7��ǰ
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
			
			case 0x02:				//�����鿴
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
								//-----------------------------------------------------------�����ص�ѹ����
								eeprom_write(0x00,(unsigned char)(light_pv/256));
			
								eeprom_write(0x01,(unsigned char)light_pv);
								
								//-----------------------------------------------------------���渺�ع�����������
								eeprom_write(0x02,(unsigned char)(load_cc_I/256));
			
								eeprom_write(0x03,(unsigned char)load_cc_I);
								
								//-----------------------------------------------------------�����������ٷֱȲ���
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
								
								//�������µ�ϵͳ����
								light_on_pv_level	=	(light_pv*10)/69;						//���ƹ����ѹ����ֵ
								
								light_off_pv_level 	= 	((light_pv*10)/69)+30;				//�صƹ����ѹ����ֵ
								
								PID_CC_discharge.SetPoint   = (load_cc_I/100)*75;    	// �趨Ŀ�� Desired value 330mA 
								
								if(light_time==0x00)
								{
									light_time_level = 1000;
								}
								else
								{
									light_time_level = (unsigned long int)(light_time*60*180);
								}
								
								//�ظ���Ӧ֡ 
								
								uart1_tx_buf[0]=0x55;
						         
								uart1_tx_buf[1]=0xB3;
								
								uart1_tx_buf[2]=0x01;    //�������óɹ�
											         
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
								
								uart1_tx_buf[2]=0x02;    //�������ô���
											         
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
			case 0x04://------------------�ֶ����ģʽ
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
			
			case 0x05://------------------�ֶ��ŵ�ģʽ
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
			case 0x06://-------------------�Զ�ģʽ
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
