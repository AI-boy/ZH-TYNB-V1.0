#include <xc.h>
#include <GenericTypeDefs.h>

#include "userdefine.h"



//**--------------全局变量-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------

//**--------------函数定义-----------------------------------------------------

//系统运行状态数据及设置参数
//------------------------------------------------------------------------------//
		__EEPROM_DATA(0x02, 0x58, 0x00, 0x21, 0x64, 0x64, 0x64, 0x64);
		
		__EEPROM_DATA(0x64, 0x01, 0x01, 0x01, 0x01, 0x03, 0x04, 0x03);
		
		__EEPROM_DATA(0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		
		__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		
		__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		
		__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		
		__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
//------------------------------------------------------------------------------//

float p_v=0;    	//当前光伏电压

float b_v=0;		//当前电池电压

float load_v=0;		//当前负载电压

float charge_I =0; 	//当前充电电流

float load_I =0;    //当前负载电流

unsigned char  sys_mode=0;  //当前系统工作模式

unsigned char  today_index=0; //EEPROM 中今天电池电压记录保存索引位置

float bt_00_hv=0;		//0天前电池电压最高值 (即今天)
float bt_00_lv=0;		//0天前电池电压最低值 (即今天)

float bt_01_hv=0;		//1天前电池电压最高值
float bt_01_lv=0;		//1天前电池电压最低值

float bt_02_hv=0;		//2天前电池电压最高值
float bt_02_lv=0;		//2天前电池电压最低值

float bt_03_hv=0;		//3天前电池电压最高值
float bt_03_lv=0;		//3天前电池电压最低值

float bt_04_hv=0;		//4天前电池电压最高值
float bt_04_lv=0;		//4天前电池电压最低值

float bt_05_hv=0;		//5天前电池电压最高值
float bt_05_lv=0;		//5天前电池电压最低值

float bt_06_hv=0;		//6天前电池电压最高值
float bt_06_lv=0;		//6天前电池电压最低值

float bt_07_hv=0;		//7天前电池电压最高值
float bt_07_lv=0;		//7天前电池电压最低值

//参数设置

float light_pv=600;						//光控电压   设定范围:5--10V(500--1000)

float load_cc_I=33;						//LED灯工作电流  负载设定值:0.02--1.2A(2--120)

float load_percent=50;  				//节能输出百分比 50%

float step_01_load_percent=100;  		//节能输出百分比 20%

float step_02_load_percent=100;  		//节能输出百分比 60%

float step_03_load_percent=100;  		//节能输出百分比 80%

float step_04_load_percent=100;  		//节能输出百分比 60%

float step_05_load_percent=100;  		//节能输出百分比 20%

unsigned int  step_01_time_limit=1;		//输出时长 1 h

unsigned int  step_02_time_limit=3;		//输出时长 3 h

unsigned int  step_03_time_limit=4;		//输出时长 4 h

unsigned int  step_04_time_limit=3;		//输出时长 3 h

unsigned int  step_05_time_limit=1;		//输出时长 1 h

unsigned char volt_id	= 0x01; 		//电池电压类型

unsigned char bt_id		= 0x01; 		//电池类型 默认锂电池

unsigned int light_time= 0x00;			//光控时间 (单位：min)
//---------------------volt_id:
//01：12V锂电池系统    默认值
//02：24V锂电池系统  
//03：12V铅酸电池系统   
//04：24V铅酸电池系统
//---------------------bt_id
//01:锂电池 (默认)
//02:铅酸电池
//-----------------------------------节能输出调节(共计五个阶段：第一阶段：100%--80%   第二阶段：80%--60%   第三阶段：60%--40%  第四阶段：40%--20%  第五阶段：20%--0%)
float bt_volt_100 = 12.60; 			//100%电量时

float bt_volt_80  = 11.58; 			//80%电量

float bt_volt_60  = 10.56; 			//60%电量

float bt_volt_40  = 9.54; 			//40%电量

float bt_volt_20  = 8.52; 			//20%电量

float bt_volt_00  = 7.5; 			//0%电量



float dianchi_guoya_baohu=12.60;   	//100%  电池过压保护点

float dianchi_guoya_huifu=12.35;	//95%   电池过压恢复点

float dianchi_qianya_baohu=7.50;	//0%	电池欠压保护点

float dianchi_qianya_huifu=8.52;	//20%	电池欠压恢复点

float dianchi_diya_level=10.56;		//60%	电池低压节能调节点   当电池电压低于60%时进入节能输出以延长照明时间

float dianchi_cv_level=12.40;		//>12.40时 进入恒压充电方式

float charge_i_limit=5.00;			//充电电流限定值

float shuchu_shortout_voltage=7.50; //输出短路电压

float shuchu_open_voltage=63.00;	//输出开路电压

float discharge_i_baohu=2.40;		//放电电流保护点  过流保护  2.4A

float discharge_i_limit=2.00;		//放电电流限定值 2.0A

float light_on_pv_level=6.00;		//亮灯光伏电压门限值 默认6V

float light_off_pv_level=8.00;		//关灯光伏电压门限值 默认8V


float charge_r_value=0.03;	   		//充电电流采样电阻

float discharge_r_value=0.075;		//放电电流采样电阻

float Load_Pmax=41.00;				//输出最大功率



/**********************************************************************
*函数名称：read_param_eeprom
*描述：获取系统参数
*返回类型：void
*输入形参：void
***********************************************************************/
void read_param_eeprom(void)
{
	unsigned char byte_h,byte_l;
	
	//------------------------------------
	byte_h=eeprom_read(0x00);
	
	byte_l=eeprom_read(0x01);
		
	light_pv=(byte_h<<8)|byte_l;   //光控电压
	
	
	//------------------------------------
	byte_h=eeprom_read(0x02);
	
	byte_l=eeprom_read(0x03);
		
	load_cc_I=(byte_h<<8)|byte_l; //负载工作电流
	
	
	//------------------------------------
	byte_l=eeprom_read(0x04);
								
	step_01_load_percent=byte_l;		 //第一阶段降载输出百分比
	
	//------------------------------------
	byte_l=eeprom_read(0x05);
								
	step_02_load_percent=byte_l;		 //第二阶段降载输出百分比
	
	//------------------------------------
	byte_l=eeprom_read(0x06);
								
	step_03_load_percent=byte_l;		 //第三阶段降载输出百分比
	
	//------------------------------------
	byte_l=eeprom_read(0x07);
								
	step_04_load_percent=byte_l;		 //第四阶段降载输出百分比
	
	//------------------------------------
	byte_l=eeprom_read(0x08);
								
	step_05_load_percent=byte_l;		 //第五阶段降载输出百分比
	
	//------------------------------------
	byte_l=eeprom_read(0x09);
								
	volt_id=byte_l;						//系统电池电压类型!!!!
	
	//------------------------------------
	byte_l=eeprom_read(0x0a);
								
	bt_id=byte_l;						//系统电池类型!!!!!!
	//------------------------------------
	byte_l=eeprom_read(0x0b);
								
	light_time=byte_l;					//光控时间
	//------------------------------------
	byte_l=eeprom_read(0x0c);
								
	step_01_time_limit=byte_l;			//第一阶段时长
	//------------------------------------
	byte_l=eeprom_read(0x0d);
								
	step_02_time_limit=byte_l;			//第二阶段时长
	//------------------------------------
	byte_l=eeprom_read(0x0e);
								
	step_03_time_limit=byte_l;			//第三阶段时长
	//------------------------------------
	byte_l=eeprom_read(0x0f);
								
	step_04_time_limit=byte_l;			//第四阶段时长
	//------------------------------------
	byte_l=eeprom_read(0x10);
								
	step_05_time_limit=byte_l;			//第五阶段时长
	//------------------------------------今天电池电压EEPROM存储位置索引
	byte_l=eeprom_read(0x11);
								
	today_index=byte_l;					
	//------------------------------------今天电池电压记录
	byte_h=eeprom_read(0x12+4*( (today_index+8-0)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-0)%8 )+1 );
	
	bt_00_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-0)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-0)%8 )+3 );
	
	bt_00_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------1天前电池电压记录
	byte_h=eeprom_read(0x12+4*( (today_index+8-1)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-1)%8 )+1 );
	
	bt_01_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-1)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-1)%8 )+3 );
	
	bt_01_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------2天前电池电压记录
	byte_h=eeprom_read(0x12+4*( (today_index+8-2)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-2)%8 )+1 );
	
	bt_02_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-2)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-2)%8 )+3 );
	
	bt_02_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------3天前电池电压记录
	byte_h=eeprom_read(0x12+4*( (today_index+8-3)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-3)%8 )+1 );
	
	bt_03_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-3)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-3)%8 )+3 );
	
	bt_03_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------4天前电池电压记录
	byte_h=eeprom_read(0x12+4*( (today_index+8-4)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-4)%8 )+1 );
	
	bt_04_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-4)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-4)%8 )+3 );
	
	bt_04_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------5天前电池电压记录
	byte_h=eeprom_read(0x12+4*( (today_index+8-5)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-5)%8 )+1 );
	
	bt_05_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-5)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-5)%8 )+3 );
	
	bt_05_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------6天前电池电压记录
	byte_h=eeprom_read(0x12+4*( (today_index+8-6)%8 )+0 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-6)%8 )+1 );
	
	bt_06_hv=(byte_h<<8)|byte_l;
	
	byte_h=eeprom_read(0x12+4*( (today_index+8-6)%8 )+2 );
								
	byte_l=eeprom_read(0x12+4*( (today_index+8-6)%8 )+3 );
	
	bt_06_lv=(byte_h<<8)|byte_l;
	
	//------------------------------------7天前电池电压记录
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
	
	
	
	if(volt_id==0x01)			//12V锂电池系统    默认值
	{
		bt_volt_100 = (12.60/34)*1000; 			//100%电量时

		bt_volt_80  = (11.58/34)*1000; 			//80%电量
		
		bt_volt_60  = (10.56/34)*1000; 			//60%电量
		
		bt_volt_40  = (9.54/34)*1000; 			//40%电量
		
		bt_volt_20  = (8.52/34)*1000; 			//20%电量
		
		bt_volt_00  = (7.5/34)*1000; 			//0%电量
		
		
		dianchi_guoya_baohu = (12.60/34)*1000;   	//100%  电池过压保护点
	
		dianchi_guoya_huifu = (12.35/34)*1000;		//95%   电池过压恢复点
		
		dianchi_qianya_baohu = (7.50/34)*1000;		//0%	电池欠压保护点
		
		dianchi_qianya_huifu = (8.52/34)*1000;		//20%	电池欠压恢复点
		
		dianchi_diya_level = (10.56/34)*1000;		//60%	电池低压节能调节点   当电池电压低于60%时进入节能输出以延长照明时间
		
		dianchi_cv_level = (12.40/34)*1000;			//>12.40时 进入恒压充电方式
		
		charge_i_limit = 5.00*30.0;					//充电电流限定值
		
		shuchu_shortout_voltage = (7.50/69)*1000; 	//输出短路电压
		
		shuchu_open_voltage = (63.00/69)*1000;		//输出开路电压
		
		discharge_i_baohu = 2.40*75;				//放电电流保护点  过流保护  2.4A
		
		discharge_i_limit = 2.10*75;				//放电电流限定值 2.1A
		
		light_on_pv_level = (light_pv*10)/69;		//亮灯光伏电压门限值
		
		light_off_pv_level = ((light_pv*10)/69)+30;		//关灯光伏电压门限值
		
		Load_Pmax=41.00;
	}
	else if(volt_id==0x02)
	{
		bt_volt_100 = 2*(12.60/34)*1000; 			//100%电量时

		bt_volt_80  = 2*(11.58/34)*1000; 			//80%电量
		
		bt_volt_60  = 2*(10.56/34)*1000; 			//60%电量
		
		bt_volt_40  = 2*(9.54/34)*1000; 			//40%电量
		
		bt_volt_20  = 2*(8.52/34)*1000; 			//20%电量
		
		bt_volt_00  = 2*(7.5/34)*1000; 			    //0%电量
		
		dianchi_guoya_baohu=2*(12.60/34)*1000;   	//100%  电池过压保护点
	
		dianchi_guoya_huifu=2*(12.35/34)*1000;		//95%   电池过压恢复点
		
		dianchi_qianya_baohu=2*(7.50/34)*1000;		//0%	电池欠压保护点
		
		dianchi_qianya_huifu=2*(8.52/34)*1000;		//20%	电池欠压恢复点
		
		dianchi_diya_level=2*(10.56/34)*1000;		//60%	电池低压节能调节点   当电池电压低于60%时进入节能输出以延长照明时间
		
		dianchi_cv_level=2*(12.40/34)*1000;			//>12.40时 进入恒压充电方式
		
		charge_i_limit=5.00*30.0;					//充电电流限定值
		
		shuchu_shortout_voltage=2*(7.50/69)*1000; 	//输出短路电压
		
		shuchu_open_voltage=(63.00/69)*1000;		//输出开路电压
		
		discharge_i_baohu=2.40*75;					//放电电流保护点  过流保护  2.4A
		
		discharge_i_limit=2.10*75;					//放电电流限定值 2.1A
		
		light_on_pv_level=(light_pv*10)/69;			//亮灯光伏电压门限值
		
		light_off_pv_level=(15.00/69)*1000;			//关灯光伏电压门限值
		
		Load_Pmax=61.50;
	}
	else
	{
		NOP();
	}

}


/**********************************************************************
*函数名称：auto_system
*描述：自动识别系统电压 电池类型（锂电池、铅酸蓄电池）
*返回类型：void
*输入形参：void
***********************************************************************/
void auto_system(void)
{
	float sys_bt_voltage;	
	
	delay_ms(100);
	
	//------------------------------------系统电池类型!!!!!!
	bt_id=eeprom_read(0x0a);  
	//------------------------------------							
								
	sys_bt_voltage=0x00;
	
	battery_voltage_value=start_ad_convert(AN12_CHANNEL);
	
	sys_bt_voltage=(((float)battery_voltage_value)/1000)*34;
	
	if(bt_id==0x01)//----------------------锂电池
	{
			if((sys_bt_voltage>=7.5)&&(sys_bt_voltage<=12.6))
			{
				volt_id=0x01;
				
				eeprom_write(0x09,volt_id);				//12V Li电池系统
			}
			else if((sys_bt_voltage>=15.0)&&(sys_bt_voltage<=25.2))
			{
				volt_id=0x02;
				
				eeprom_write(0x09,volt_id);				//24V Li电池系统
			}
			else
			{
				NOP();
			}
	}
	else if(bt_id==0x02)//-------------------铅酸电池
	{
			if((sys_bt_voltage>=7.5)&&(sys_bt_voltage<=12.6))
			{
				volt_id=0x01;
				
				eeprom_write(0x09,volt_id);				//12V Li电池系统
			}
			else if((sys_bt_voltage>=15.0)&&(sys_bt_voltage<=25.2))
			{
				volt_id=0x02;
				
				eeprom_write(0x09,volt_id);				//24V Li电池系统
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
				
				eeprom_write(0x09,volt_id);				//12V Li电池系统
			}
			else if((sys_bt_voltage>=15.0)&&(sys_bt_voltage<=25.2))
			{
				volt_id=0x02;
				
				eeprom_write(0x09,volt_id);				//24V Li电池系统
			}
			else
			{
				NOP();
			}	
	}


	
}