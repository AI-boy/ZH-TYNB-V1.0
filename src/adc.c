 
 
#include <xc.h>
#include <GenericTypeDefs.h>

#include "userdefine.h"



unsigned int mcu_value=0x00;      			//�ڲ��¶� оƬ��Ƭ�¶�

unsigned int temperature_value=0x00;   		//�����¶�

unsigned int pv_voltage_value=0x00;			//������ѹ

unsigned int battery_voltage_value=0x00;	//��ص�ѹ

unsigned int load_voltage_value=0x00;		//�����ѹ

unsigned int charge_current_value=0x00;		//������

unsigned int discharge_current_value=0x00;	//�ŵ����


unsigned int adc_buffer[64];




/**********************************************************************
*�������ƣ�init_adc
*��������ʼ��AD�����˿�
*�������ͣ�void
*�����βΣ�void
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
	
	
	
	ADCON1bits.ADFM   =0b1;   			//�Ҷ���
	
	ADCON1bits.ADCS   =0b110; 			//����ת��ʱ��Fosc/64
	
	ADCON1bits.ADNREF =0b0;   			//vref- ����Vss
	
	ADCON1bits.ADPREF =0b11;  			//vref+ �ڲ���׼��ѹ1.024V
	
	FVRCONbits.ADFVR =0b01;				//1.024V
	
	FVRCONbits.FVREN =0b1;				//ʹ�̶ܹ��ο���ѹ
	
	FVRCONbits.TSEN =0b1;				//ʹ���¶�ָʾ��
	
	FVRCONbits.TSRNG=0b1;				//VOUT = VDD - 4VT ���ߵ�ѹ��Χ��  Vt = 0.659-(T+40)*(0.00132)  60��--592   80��--615  100��--635  120��--658
	
	ADCON0bits.CHS	  =MCU_CHANNEL;  	//����ͨ��ѡ�� ��ʼ��ʱѡ�� �ڲ��¶�ָʾ��
	
    ADCON0bits.ADON   =0b0;				//��ֹAD����
    
	PIE1bits.ADIE=0;   					//��ֹAD�����ж�
	
	PIR1bits.ADIF=0;					//���жϱ�־



}












































