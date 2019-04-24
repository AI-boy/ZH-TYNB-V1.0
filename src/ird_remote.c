#include <xc.h>
#include <GenericTypeDefs.h>

#include "userdefine.h"



//**--------------ȫ�ֱ���-----------------------------------------------------

//**--------------��������-----------------------------------------------------

//**--------------��������-----------------------------------------------------

//ϵͳ����״̬���ݼ����ò���
//------------------------------------------------------------------------------//
		__EEPROM_DATA(0x02, 0x58, 0x00, 0x21, 0x64, 0x64, 0x64, 0x64);
		
		__EEPROM_DATA(0x64, 0x01, 0x01, 0x01, 0x01, 0x03, 0x04, 0x03);
		
		__EEPROM_DATA(0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		
		__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		
		__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		
		__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		
		__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
//------------------------------------------------------------------------------//

float p_v=0;    	//��ǰ�����ѹ

float b_v=0;		//��ǰ��ص�ѹ

float load_v=0;		//��ǰ���ص�ѹ

float charge_I =0; 	//��ǰ������

float load_I =0;    //��ǰ���ص���

unsigned char  sys_mode=0;  //��ǰϵͳ����ģʽ

unsigned char  today_index=0; //EEPROM �н����ص�ѹ��¼��������λ��

float bt_00_hv=0;		//0��ǰ��ص�ѹ���ֵ (������)
float bt_00_lv=0;		//0��ǰ��ص�ѹ���ֵ (������)

float bt_01_hv=0;		//1��ǰ��ص�ѹ���ֵ
float bt_01_lv=0;		//1��ǰ��ص�ѹ���ֵ

float bt_02_hv=0;		//2��ǰ��ص�ѹ���ֵ
float bt_02_lv=0;		//2��ǰ��ص�ѹ���ֵ

float bt_03_hv=0;		//3��ǰ��ص�ѹ���ֵ
float bt_03_lv=0;		//3��ǰ��ص�ѹ���ֵ

float bt_04_hv=0;		//4��ǰ��ص�ѹ���ֵ
float bt_04_lv=0;		//4��ǰ��ص�ѹ���ֵ

float bt_05_hv=0;		//5��ǰ��ص�ѹ���ֵ
float bt_05_lv=0;		//5��ǰ��ص�ѹ���ֵ

float bt_06_hv=0;		//6��ǰ��ص�ѹ���ֵ
float bt_06_lv=0;		//6��ǰ��ص�ѹ���ֵ

float bt_07_hv=0;		//7��ǰ��ص�ѹ���ֵ
float bt_07_lv=0;		//7��ǰ��ص�ѹ���ֵ

//��������

float light_pv=600;						//��ص�ѹ   �趨��Χ:5--10V(500--1000)

float load_cc_I=33;						//LED�ƹ�������  �����趨ֵ:0.02--1.2A(2--120)

float load_percent=50;  				//��������ٷֱ� 50%

float step_01_load_percent=100;  		//��������ٷֱ� 20%

float step_02_load_percent=100;  		//��������ٷֱ� 60%

float step_03_load_percent=100;  		//��������ٷֱ� 80%

float step_04_load_percent=100;  		//��������ٷֱ� 60%

float step_05_load_percent=100;  		//��������ٷֱ� 20%

unsigned int  step_01_time_limit=1;		//���ʱ�� 1 h

unsigned int  step_02_time_limit=3;		//���ʱ�� 3 h

unsigned int  step_03_time_limit=4;		//���ʱ�� 4 h

unsigned int  step_04_time_limit=3;		//���ʱ�� 3 h

unsigned int  step_05_time_limit=1;		//���ʱ�� 1 h

unsigned char volt_id	= 0x01; 		//��ص�ѹ����

unsigned char bt_id		= 0x01; 		//������� Ĭ��﮵��

unsigned int light_time= 0x00;			//���ʱ�� (��λ��min)
//---------------------volt_id:
//01��12V﮵��ϵͳ    Ĭ��ֵ
//02��24V﮵��ϵͳ  
//03��12VǦ����ϵͳ   
//04��24VǦ����ϵͳ
//---------------------bt_id
//01:﮵�� (Ĭ��)
//02:Ǧ����
//-----------------------------------�����������(��������׶Σ���һ�׶Σ�100%--80%   �ڶ��׶Σ�80%--60%   �����׶Σ�60%--40%  ���Ľ׶Σ�40%--20%  ����׶Σ�20%--0%)
float bt_volt_100 = 12.60; 			//100%����ʱ

float bt_volt_80  = 11.58; 			//80%����

float bt_volt_60  = 10.56; 			//60%����

float bt_volt_40  = 9.54; 			//40%����

float bt_volt_20  = 8.52; 			//20%����

float bt_volt_00  = 7.5; 			//0%����



float dianchi_guoya_baohu=12.60;   	//100%  ��ع�ѹ������

float dianchi_guoya_huifu=12.35;	//95%   ��ع�ѹ�ָ���

float dianchi_qianya_baohu=7.50;	//0%	���Ƿѹ������

float dianchi_qianya_huifu=8.52;	//20%	���Ƿѹ�ָ���

float dianchi_diya_level=10.56;		//60%	��ص�ѹ���ܵ��ڵ�   ����ص�ѹ����60%ʱ�������������ӳ�����ʱ��

float dianchi_cv_level=12.40;		//>12.40ʱ �����ѹ��緽ʽ

float charge_i_limit=5.00;			//�������޶�ֵ

float shuchu_shortout_voltage=7.50; //�����·��ѹ

float shuchu_open_voltage=63.00;	//�����·��ѹ

float discharge_i_baohu=2.40;		//�ŵ����������  ��������  2.4A

float discharge_i_limit=2.00;		//�ŵ�����޶�ֵ 2.0A

float light_on_pv_level=6.00;		//���ƹ����ѹ����ֵ Ĭ��6V

float light_off_pv_level=8.00;		//�صƹ����ѹ����ֵ Ĭ��8V


float charge_r_value=0.03;	   		//��������������

float discharge_r_value=0.075;		//�ŵ������������

float Load_Pmax=41.00;				//��������



/**********************************************************************
*�������ƣ�read_param_eeprom
*��������ȡϵͳ����
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void read_param_eeprom(void)
{
	unsigned char byte_h,byte_l;
	
	//------------------------------------
	byte_h=eeprom_read(0x00);
	
	byte_l=eeprom_read(0x01);
		
	light_pv=(byte_h<<8)|byte_l;   //��ص�ѹ
	
	
	//------------------------------------
	byte_h=eeprom_read(0x02);
	
	byte_l=eeprom_read(0x03);
		
	load_cc_I=(byte_h<<8)|byte_l; //���ع�������
	
	
	//------------------------------------
	byte_l=eeprom_read(0x04);
								
	step_01_load_percent=byte_l;		 //��һ�׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=eeprom_read(0x05);
								
	step_02_load_percent=byte_l;		 //�ڶ��׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=eeprom_read(0x06);
								
	step_03_load_percent=byte_l;		 //�����׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=eeprom_read(0x07);
								
	step_04_load_percent=byte_l;		 //���Ľ׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=eeprom_read(0x08);
								
	step_05_load_percent=byte_l;		 //����׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=eeprom_read(0x09);
								
	volt_id=byte_l;						//ϵͳ��ص�ѹ����!!!!
	
	//------------------------------------
	byte_l=eeprom_read(0x0a);
								
	bt_id=byte_l;						//ϵͳ�������!!!!!!
	//------------------------------------
	byte_l=eeprom_read(0x0b);
								
	light_time=byte_l;					//���ʱ��
	//------------------------------------
	byte_l=eeprom_read(0x0c);
								
	step_01_time_limit=byte_l;			//��һ�׶�ʱ��
	//------------------------------------
	byte_l=eeprom_read(0x0d);
								
	step_02_time_limit=byte_l;			//�ڶ��׶�ʱ��
	//------------------------------------
	byte_l=eeprom_read(0x0e);
								
	step_03_time_limit=byte_l;			//�����׶�ʱ��
	//------------------------------------
	byte_l=eeprom_read(0x0f);
								
	step_04_time_limit=byte_l;			//���Ľ׶�ʱ��
	//------------------------------------
	byte_l=eeprom_read(0x10);
								
	step_05_time_limit=byte_l;			//����׶�ʱ��
	//------------------------------------�����ص�ѹEEPROM�洢λ������
	byte_l=eeprom_read(0x11);
								
	today_index=byte_l;					
	//------------------------------------�����ص�ѹ��¼
	byte_h=eeprom_read(0x12+4*( (today_index+8-0)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-0)%8 )+1 );
	
	bt_00_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-0)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-0)%8 )+3 );
	
	bt_00_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------1��ǰ��ص�ѹ��¼
	byte_h=eeprom_read(0x12+4*( (today_index+8-1)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-1)%8 )+1 );
	
	bt_01_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-1)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-1)%8 )+3 );
	
	bt_01_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------2��ǰ��ص�ѹ��¼
	byte_h=eeprom_read(0x12+4*( (today_index+8-2)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-2)%8 )+1 );
	
	bt_02_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-2)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-2)%8 )+3 );
	
	bt_02_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------3��ǰ��ص�ѹ��¼
	byte_h=eeprom_read(0x12+4*( (today_index+8-3)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-3)%8 )+1 );
	
	bt_03_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-3)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-3)%8 )+3 );
	
	bt_03_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------4��ǰ��ص�ѹ��¼
	byte_h=eeprom_read(0x12+4*( (today_index+8-4)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-4)%8 )+1 );
	
	bt_04_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-4)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-4)%8 )+3 );
	
	bt_04_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------5��ǰ��ص�ѹ��¼
	byte_h=eeprom_read(0x12+4*( (today_index+8-5)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-5)%8 )+1 );
	
	bt_05_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-5)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-5)%8 )+3 );
	
	bt_05_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------6��ǰ��ص�ѹ��¼
	byte_h=eeprom_read(0x12+4*( (today_index+8-6)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-6)%8 )+1 );
	
	bt_06_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-6)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-6)%8 )+3 );
	
	bt_06_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------7��ǰ��ص�ѹ��¼
	byte_h=eeprom_read(0x12+4*( (today_index+8-7)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-7)%8 )+1 );
	
	bt_07_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-7)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-7)%8 )+3 );
	
	bt_07_lv=(byte_h<<8)|byte_l;
	
	
	
	
	
	
	
	if(light_time==0x00)
	{
		light_time_level = 1000;
	}
	else
	{
		light_time_level = (unsigned long int)((unsigned long int)light_time*60*180);
	}				
	
	
	
	if(volt_id==0x01)			//12V﮵��ϵͳ    Ĭ��ֵ
	{
		bt_volt_100 = (12.60/34)*1000; 			//100%����ʱ

		bt_volt_80  = (11.58/34)*1000; 			//80%����
		
		bt_volt_60  = (10.56/34)*1000; 			//60%����
		
		bt_volt_40  = (9.54/34)*1000; 			//40%����
		
		bt_volt_20  = (8.52/34)*1000; 			//20%����
		
		bt_volt_00  = (7.5/34)*1000; 			//0%����
		
		
		dianchi_guoya_baohu = (12.60/34)*1000;   	//100%  ��ع�ѹ������
	
		dianchi_guoya_huifu = (12.35/34)*1000;		//95%   ��ع�ѹ�ָ���
		
		dianchi_qianya_baohu = (7.50/34)*1000;		//0%	���Ƿѹ������
		
		dianchi_qianya_huifu = (8.52/34)*1000;		//20%	���Ƿѹ�ָ���
		
		dianchi_diya_level = (10.56/34)*1000;		//60%	��ص�ѹ���ܵ��ڵ�   ����ص�ѹ����60%ʱ�������������ӳ�����ʱ��
		
		dianchi_cv_level = (12.40/34)*1000;			//>12.40ʱ �����ѹ��緽ʽ
		
		charge_i_limit = 5.00*30.0;					//�������޶�ֵ
		
		shuchu_shortout_voltage = (7.50/69)*1000; 	//�����·��ѹ
		
		shuchu_open_voltage = (63.00/69)*1000;		//�����·��ѹ
		
		discharge_i_baohu = 2.40*75;				//�ŵ����������  ��������  2.4A
		
		discharge_i_limit = 2.10*75;				//�ŵ�����޶�ֵ 2.1A
		
		light_on_pv_level = (light_pv*10)/69;		//���ƹ����ѹ����ֵ
		
		light_off_pv_level = ((light_pv*10)/69)+30;		//�صƹ����ѹ����ֵ
		
		Load_Pmax=41.00;
	}
	else if(volt_id==0x02)
	{
		bt_volt_100 = 2*(12.60/34)*1000; 			//100%����ʱ

		bt_volt_80  = 2*(11.58/34)*1000; 			//80%����
		
		bt_volt_60  = 2*(10.56/34)*1000; 			//60%����
		
		bt_volt_40  = 2*(9.54/34)*1000; 			//40%����
		
		bt_volt_20  = 2*(8.52/34)*1000; 			//20%����
		
		bt_volt_00  = 2*(7.5/34)*1000; 			    //0%����
		
		dianchi_guoya_baohu=2*(12.60/34)*1000;   	//100%  ��ع�ѹ������
	
		dianchi_guoya_huifu=2*(12.35/34)*1000;		//95%   ��ع�ѹ�ָ���
		
		dianchi_qianya_baohu=2*(7.50/34)*1000;		//0%	���Ƿѹ������
		
		dianchi_qianya_huifu=2*(8.52/34)*1000;		//20%	���Ƿѹ�ָ���
		
		dianchi_diya_level=2*(10.56/34)*1000;		//60%	��ص�ѹ���ܵ��ڵ�   ����ص�ѹ����60%ʱ�������������ӳ�����ʱ��
		
		dianchi_cv_level=2*(12.40/34)*1000;			//>12.40ʱ �����ѹ��緽ʽ
		
		charge_i_limit=5.00*30.0;					//�������޶�ֵ
		
		shuchu_shortout_voltage=2*(7.50/69)*1000; 	//�����·��ѹ
		
		shuchu_open_voltage=(63.00/69)*1000;		//�����·��ѹ
		
		discharge_i_baohu=2.40*75;					//�ŵ����������  ��������  2.4A
		
		discharge_i_limit=2.10*75;					//�ŵ�����޶�ֵ 2.1A
		
		light_on_pv_level=(light_pv*10)/69;			//���ƹ����ѹ����ֵ
		
		light_off_pv_level=(15.00/69)*1000;			//�صƹ����ѹ����ֵ
		
		Load_Pmax=61.50;
	}
	else
	{
		NOP();
	}

}


/**********************************************************************
*�������ƣ�auto_system
*�������Զ�ʶ��ϵͳ��ѹ ������ͣ�﮵�ء�Ǧ�����أ�
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void auto_system(void)
{
	float sys_bt_voltage;	
	
	delay_ms(100);
	
	//------------------------------------ϵͳ�������!!!!!!
	bt_id=eeprom_read(0x0a);  
	//------------------------------------							
								
	sys_bt_voltage=0x00;
	
	battery_voltage_value=start_ad_convert(AN12_CHANNEL);
	
	sys_bt_voltage=(((float)battery_voltage_value)/1000)*34;
	
	if(bt_id==0x01)//----------------------﮵��
	{
			if((sys_bt_voltage>=7.5)&&(sys_bt_voltage<=12.6))
			{
				volt_id=0x01;
				
				eeprom_write(0x09,volt_id);				//12V Li���ϵͳ
			}
			else if((sys_bt_voltage>=15.0)&&(sys_bt_voltage<=25.2))
			{
				volt_id=0x02;
				
				eeprom_write(0x09,volt_id);				//24V Li���ϵͳ
			}
			else
			{
				NOP();
			}
	}
	else if(bt_id==0x02)//-------------------Ǧ����
	{
			if((sys_bt_voltage>=7.5)&&(sys_bt_voltage<=12.6))
			{
				volt_id=0x01;
				
				eeprom_write(0x09,volt_id);				//12V Li���ϵͳ
			}
			else if((sys_bt_voltage>=15.0)&&(sys_bt_voltage<=25.2))
			{
				volt_id=0x02;
				
				eeprom_write(0x09,volt_id);				//24V Li���ϵͳ
			}
			else
			{
				NOP();
			}
	}
	else
	{
			if((sys_bt_voltage>=7.5)&&(sys_bt_voltage<=12.6))
			{
				volt_id=0x01;
				
				eeprom_write(0x09,volt_id);				//12V Li���ϵͳ
			}
			else if((sys_bt_voltage>=15.0)&&(sys_bt_voltage<=25.2))
			{
				volt_id=0x02;
				
				eeprom_write(0x09,volt_id);				//24V Li���ϵͳ
			}
			else
			{
				NOP();
			}	
	}


	
}