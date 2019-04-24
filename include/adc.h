 
#ifndef _ZH_ADC_H
#define _ZH_ADC_H






#define       N          11

#define    AN0_TRIS      TRISAbits.TRISA0

#define    AN1_TRIS      TRISAbits.TRISA1

#define    AN2_TRIS      TRISAbits.TRISA2

#define    AN3_TRIS      TRISAbits.TRISA3

#define    AN4_TRIS      TRISAbits.TRISA5

#define    AN9_TRIS      TRISBbits.TRISB3

#define    AN10_TRIS     TRISBbits.TRISB1

#define    AN12_TRIS     TRISBbits.TRISB0



#define    AN0_CHANNEL  0b00000

#define    AN1_CHANNEL  0b00001

#define    AN2_CHANNEL  0b00010

#define    AN3_CHANNEL  0b00011

#define    AN4_CHANNEL  0b00100

#define    AN5_CHANNEL  0b00101

#define    AN6_CHANNEL  0b00110

#define    AN7_CHANNEL  0b00111

#define    AN8_CHANNEL  0b01000

#define    AN9_CHANNEL  0b01001

#define    AN10_CHANNEL  0b01010

#define    AN12_CHANNEL  0b01100

#define    MCU_CHANNEL  0b11101


extern unsigned int mcu_value;      		//光照度

extern unsigned int temperature_value;   		//环境温度

extern unsigned int pv_voltage_value;			//光伏板电压

extern unsigned int battery_voltage_value;		//电池电压

extern unsigned int load_voltage_value;			//输出电压

extern unsigned int charge_current_value;		//充电电流

extern unsigned int discharge_current_value;	//放电电流


extern unsigned int adc_buffer[64];






extern void init_adc(void);




#endif