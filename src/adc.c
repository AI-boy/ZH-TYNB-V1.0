 
 
#include <xc.h>
#include <GenericTypeDefs.h>

#include "userdefine.h"



unsigned int mcu_value=0x00;      			//内部温度 芯片硅片温度

unsigned int temperature_value=0x00;   		//环境温度

unsigned int pv_voltage_value=0x00;			//光伏板电压

unsigned int battery_voltage_value=0x00;	//电池电压

unsigned int load_voltage_value=0x00;		//输出电压

unsigned int charge_current_value=0x00;		//充电电流

unsigned int discharge_current_value=0x00;	//放电电流


unsigned int adc_buffer[64];




/**********************************************************************
*函数名称：init_adc
*描述：初始化AD采样端口
*返回类型：void
*输入形参：void
***********************************************************************/

void init_adc(void)
{

	AN0_TRIS = 1;
	
	AN1_TRIS = 1;
	
	AN2_TRIS = 1;
	
	AN3_TRIS = 1;
	
	AN4_TRIS = 1;
	
	AN9_TRIS = 1;
	
	AN10_TRIS = 1;
	
	AN12_TRIS = 1;
	
	
	
	ADCON1bits.ADFM   =0b1;   			//右对其
	
	ADCON1bits.ADCS   =0b110; 			//采样转换时钟Fosc/64
	
	ADCON1bits.ADNREF =0b0;   			//vref- 连接Vss
	
	ADCON1bits.ADPREF =0b11;  			//vref+ 内部基准电压1.024V
	
	FVRCONbits.ADFVR =0b01;				//1.024V
	
	FVRCONbits.FVREN =0b1;				//使能固定参考电压
	
	FVRCONbits.TSEN =0b1;				//使能温度指示器
	
	FVRCONbits.TSRNG=0b1;				//VOUT = VDD - 4VT （高电压范围）  Vt = 0.659-(T+40)*(0.00132)  60℃--592   80℃--615  100℃--635  120℃--658
	
	ADCON0bits.CHS	  =MCU_CHANNEL;  	//采样通道选择 初始化时选择 内部温度指示器
	
    ADCON0bits.ADON   =0b0;				//禁止AD外设
    
	PIE1bits.ADIE=0;   					//禁止AD采样中断
	
	PIR1bits.ADIF=0;					//清中断标志



}












































