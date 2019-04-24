
#ifndef _ZH_INTERRUPT_H
#define _ZH_INTERRUPT_H

//**--------------�����ļ�-----------------------------------------------------

//**--------------�궨��-------------------------------------------------------

//**--------------���ݽṹ-----------------------------------------------------

//**--------------��������-----------------------------------------------------
extern void init_interrupt(void);
	
//**--------------ȫ�ֱ���-----------------------------------------------------

extern unsigned char   open_discharge_time;			//�ŵ�ʱ����ʱ��
extern unsigned int    ms_cnt;						//����
extern unsigned int		se_cnt;						//��
extern unsigned int		mi_cnt;						//��
extern unsigned int		ho_cnt;						//ʱ

extern unsigned char 	open_an0_time;  			//AN0 ͨ���������ڶ�ʱ��
extern unsigned int   	an0_time_count;				
extern unsigned char  	handle_an0_process_flag;


extern unsigned char 	open_an1_time; 				//AN1 ͨ���������ڶ�ʱ��
extern unsigned int   	an1_time_count;				
extern unsigned char  	handle_an1_process_flag;


extern unsigned char 	open_an2_time; 				//AN2 ͨ���������ڶ�ʱ��
extern unsigned int   	an2_time_count;				
extern unsigned char  	handle_an2_process_flag;


extern unsigned char 	open_an3_time; 				//AN3 ͨ���������ڶ�ʱ��
extern unsigned int   	an3_time_count;				
extern unsigned char  	handle_an3_process_flag;


extern unsigned char 	open_an4_time; 				//AN4 ͨ���������ڶ�ʱ��
extern unsigned int   	an4_time_count;				
extern unsigned char  	handle_an4_process_flag;


extern unsigned char 	open_an9_time; 				//AN9 ͨ���������ڶ�ʱ��
extern unsigned int   	an9_time_count;				
extern unsigned char  	handle_an9_process_flag;


extern unsigned char 	open_an10_time; 				//AN10 ͨ���������ڶ�ʱ��
extern unsigned int   	an10_time_count;				
extern unsigned char  	handle_an10_process_flag;


extern unsigned char handle_short_flag;

#endif 
