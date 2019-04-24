

#include <xc.h>
#include <GenericTypeDefs.h>
#include"userdefine.h"



unsigned char   open_discharge_time=0x00;			//�ŵ�ʱ����ʱ��
unsigned int    ms_cnt=0x00;						//����
unsigned int	se_cnt=0x00;						//��
unsigned int	mi_cnt=0x00;						//��
unsigned int	ho_cnt=0x00;						//ʱ

unsigned char 	open_an0_time=0x00;  				//AN0 ͨ���������ڶ�ʱ��
unsigned int   	an0_time_count=0x00;				
unsigned char  	handle_an0_process_flag=0x00;


unsigned char 	open_an1_time=0x00; 				//AN1 ͨ���������ڶ�ʱ��
unsigned int   	an1_time_count=0x00;				
unsigned char  	handle_an1_process_flag=0x00;


unsigned char 	open_an2_time=0x00; 				//AN2 ͨ���������ڶ�ʱ��
unsigned int   	an2_time_count=0x00;				
unsigned char  	handle_an2_process_flag=0x00;


unsigned char 	open_an3_time=0x00; 				//AN3 ͨ���������ڶ�ʱ��
unsigned int   	an3_time_count=0x00;				
unsigned char  	handle_an3_process_flag=0x00;


unsigned char 	open_an4_time=0x00; 				//AN4 ͨ���������ڶ�ʱ��
unsigned int   	an4_time_count=0x00;				
unsigned char  	handle_an4_process_flag=0x00;


unsigned char 	open_an9_time=0x00; 				//AN9 ͨ���������ڶ�ʱ��
unsigned int   	an9_time_count=0x00;				
unsigned char  	handle_an9_process_flag=0x00;


unsigned char 	open_an10_time=0x00; 				//AN10 ͨ���������ڶ�ʱ��
unsigned int   	an10_time_count=0x00;				
unsigned char  	handle_an10_process_flag=0x00;

unsigned char handle_short_flag=0x00;



/**********************************************************************
*�������ƣ�interrupt isr
*�������жϷ������
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void interrupt isr(void)
{
	unsigned char r1_data,r2_data;
	
	//---------------------------------------------------------------------------------------------------------------------
	if (TMR1IE && TMR1IF) // ��ʱ��1�ж� 1ms���
	{
					TMR1IF = 0x00;
					TMR1H = 0xE0;
					TMR1L = 0xC0; // ��ʱ1ms   
					
					//------------------------------------------------------------	
					if(system_check_time==0x01)
					{
						system_time_count++;
					
						if(system_time_count>250)
						{
							system_time_count=0x00;
							
							if(!bt_led_status)//��ص�ѹ��ѹ�������ͽ�����������
							{
								BATRGE_LED_TOG;
							}
							
							if(!charge_led_status)   //������ѹ����򳬳���Χ  ��ص�ѹ���ڳ������ֵ
							{
								CHARGE_LED_TOG;
							}
							
							if(!discharge_led_status)	 //	
							{
								DISCHARGE_LED_TOG;
							}												
							
						}
					}
					//------------------------------------------------------------�ŵ�׶�ʱ������
					if(open_discharge_time==0x01)
					{
						if(ms_cnt<1000)
						{
							ms_cnt++;
						}
						else
						{
							ms_cnt=0x00;
							
							if(se_cnt<60)
							{
								se_cnt++;		//----1��
							}
							else
							{
								se_cnt=0x00;
								
								if(mi_cnt<60)
								{
									mi_cnt++;  //-----1����
								}
								else
								{
									mi_cnt=0x00;
									
									if(ho_cnt<24)
									{
										ho_cnt++; //1Сʱ
									}
									else
									{
										ho_cnt=0x00;
									}
								}
							}
						}
					}
					//------------------------------------------------------------
					if(open_an0_time==0x01) //AN0 ͨ���������ڶ�ʱ��  1s  �ڲ��¶ȼ��
					{
						an0_time_count++;
						
						if(an0_time_count>=1000)
						{
							an0_time_count=0x00;
							
							handle_an0_process_flag=0x01;
						}
						
					}
					if(open_an1_time==0x01)	//AN1 ͨ���������ڶ�ʱ��   1s �¶ȼ��
					{
						an1_time_count++;
						
						if(an1_time_count>=1000)
						{
							an1_time_count=0x00;
							
							handle_an1_process_flag=0x01;
						}
						
					}
					if(open_an2_time==0x01) //AN2 ͨ���������ڶ�ʱ��  5ms  �����ѹ
					{
						an2_time_count++;
						
						if(an2_time_count>=5)
						{
							an2_time_count=0x00;
							
							handle_an2_process_flag=0x01;
						}
						
					}
					
					if(open_an3_time==0x01) //AN3 ͨ���������ڶ�ʱ��  5ms  ��ص�ѹ���
					{
						an3_time_count++;
						
						if(an3_time_count>=5)
						{
							an3_time_count=0x00;
							
							handle_an3_process_flag=0x01;
						}
						
					}
									
					
					if(open_an9_time==0x01) //AN9 ͨ���������ڶ�ʱ��   5ms ������  
					{
						an9_time_count++;
						
						if(an9_time_count>=5)
						{
							an9_time_count=0x00;
																			
							handle_an9_process_flag=0x01;
							
						
						}
						
					}
					
					if(open_an4_time==0x01) //AN4 ͨ���������ڶ�ʱ��  5ms ����˵�ѹ 
					{
						an4_time_count++;
						
						if(an4_time_count>=5)
						{
							an4_time_count=0x00;
							
							handle_an4_process_flag=0x01;
						}
						
					}
					
					if(open_an10_time==0x01) //AN10 ͨ���������ڶ�ʱ��  5ms  �ŵ����
					{
						an10_time_count++;
						
						if(an10_time_count>=2)
						{
							an10_time_count=0x00;
							
							handle_an10_process_flag=0x01;
						}
						
					}
					//------------------------------------------------------
		
					if (uart1_time_count > 0x00)   //UART1���ܽ�������
					{
						uart1_time_count--;
						
						if(uart1_time_count==0)
						{
							if((uart1_receive_byte_count==5)&&(uart1_rx_buf[1]==0xA1)&&(uart1_rx_buf[4]==0xAA))
							{
								rx_frame_kind=0x01;				//������������
								
								uart1_receive_flag=TRUE;
							}
							else if((uart1_receive_byte_count==5)&&(uart1_rx_buf[1]==0xA2)&&(uart1_rx_buf[4]==0xAA))
							{
								rx_frame_kind=0x02;				//��������
								
								uart1_receive_flag=TRUE;
							}
							else if((uart1_receive_byte_count==21)&&(uart1_rx_buf[1]==0xA3)&&(uart1_rx_buf[20]==0xAA))
							{
								rx_frame_kind=0x03;				//��������
								
								uart1_receive_flag=TRUE;
							}
							else if((uart1_receive_byte_count==5)&&(uart1_rx_buf[1]==0xA4)&&(uart1_rx_buf[4]==0xAA))
							{
								rx_frame_kind=0x04;				//�ֶ����ģʽ
								
								uart1_receive_flag=TRUE;
							}
							else if((uart1_receive_byte_count==5)&&(uart1_rx_buf[1]==0xA5)&&(uart1_rx_buf[4]==0xAA))
							{
								rx_frame_kind=0x05;				//�ֶ��ŵ�ģʽ
								
								uart1_receive_flag=TRUE;
							}
							else if((uart1_receive_byte_count==5)&&(uart1_rx_buf[1]==0xA6)&&(uart1_rx_buf[4]==0xAA))
							{
								rx_frame_kind=0x06;				//�Զ�ģʽ
								
								uart1_receive_flag=TRUE;
							}
							else
							{
									if (RCSTAbits.FERR || RCSTAbits.OERR)  //uart2 RS485
										{
											RCSTAbits.CREN = 0x00;
											RCSTAbits.SPEN = 0x00;
											NOP();
											NOP();
											NOP();
											RCSTAbits.CREN = 0x01;
											RCSTAbits.SPEN = 0x01;				
										}
			
										uart1_receive_byte_count=0x00;
							}
						}
						
					}				    		
			    		
		
					if (uart_send_delay_timer > 0x00)   //��ʱ����
					{
						uart_send_delay_timer--;
						
						if (uart_send_delay_timer == 0x00)
						{							
							TXIE = 0x01; // ʹ��UART1�����ж�
						}
						
					}
					
					if (uart_send_end_flag == 0x01)    //�������������������
			       	{
				       	if (TXSTAbits.TRMT) 			// ���ע��
			           	{
			            				
							uart_send_end_flag = 0x00;  
							
			          	}
			          	
			      	}
			      	
			      	
			      	
	}


	//---------------------------------------------------------------------------------------------------------------------	
	if (TXIE && TXIF) // �����ж� 
	{
		if (uart_send_byte_count > 0x00)
       	{
          	uart_send_byte_count--;
           	TXREG = *uart_send_point;
           	uart_send_point++;
      	}
       	else if (uart_send_byte_count == 0x00)
      	{
          	uart_send_end_flag = 0x01;
          	TXIE = 0x00;
      	}
		else
		{
			NOP();
		}	
	}
	
	if(RCIF && RCIE)    //uart1 
     {
           
            r1_data=RCREG;
                  
             uart1_time_count=0x0A;//UART1�������� ���5ms����ʾһ֡���ݵĽ���  9600--0x05   2400--0x0A

            if( (uart1_receive_byte_count<21)&&(uart1_receive_flag==FALSE) )
              {
                 uart1_rx_buf[uart1_receive_byte_count]=r1_data;
          
                  if(uart1_rx_buf[0]==MAC_ADDR)
                    {
                       uart1_receive_byte_count++;
                    } 
               }     
          
                                    
                
     }
     
     //---------------------------------------------�Ƚ����ж�
     if(C1IE && C1IF)
     {
     		C1IF=0;
     		     	
     		handle_short_flag=0x01;
     		
     		
     	
     		discharge_index=0x03;
     		
     		LOAD_OUT_DISABLE;
										
			bost_pwm_value=2;
						
			Set_Bost_Pwm_Duty(bost_pwm_value);
						
			Disable_Bost_Pwm();			
						
			
     	
     }
     
     
		
}

/******************************************************************************
** �������� : init_interrupt
** ������� : ��
** ������� : ��
** �������� : ��ʼ���ж�
			  ʹ�������ж�
			  ʹ��ȫ���ж�
** ȫ�ֱ��� : ��
** ��    �� : caiwk
** ��    �� : 2014-10-16
** ��    �� : ��
** ��    �� : V1.0
*******************************************************************************/
void init_interrupt(void)
{
	
	//�Ƚ���ģ������
	
	CM1CON0bits.C1POL=0;
	
	CM1CON0bits.C1OE=0;
	
	CM1CON0bits.C1SP=1;
	
	CM1CON0bits.C1HYS=1;
	
	CM1CON0bits.C1SYNC=0;
	
	CM1CON1bits.C1INTN=1;
	
	CM1CON1bits.C1PCH=0b00;
	
	CM1CON1bits.C1NCH=0b00;
	
	PIE2bits.C1IE=1;
	
	PIR2bits.C1IF=0;
	
	CM1CON0bits.C1ON=1;
	
	PEIE = 0x01; // ʹ�������ж�
	GIE = 0x01; // ʹ��ȫ���ж�	   
}
