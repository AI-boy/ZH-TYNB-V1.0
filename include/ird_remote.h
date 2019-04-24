 #ifndef _IRD_REMOTE_H
 #define _IRD_REMOTE_H


//��������
extern float charge_r_value;	   //������������������ֵ **��ŷķ

extern float discharge_r_value;		//�ŵ������������

//��������
extern float p_v;    //��ǰ�����ѹ

extern float b_v;	//��ǰ��ص�ѹ

extern float load_v;	//��ǰ���ص�ѹ

extern float charge_I ; //��ǰ������

extern float load_I ;    //��ǰ���ص���

extern unsigned char  sys_mode;     //��ǰ�豸����ģʽ

extern unsigned char  today_index; //EEPROM�� �����ص�ѹ��¼��������λ��

extern float bt_00_hv;		//0��ǰ��ص�ѹ���ֵ (������)
extern float bt_00_lv;		//0��ǰ��ص�ѹ���ֵ (������)

extern float bt_01_hv;		//1��ǰ��ص�ѹ���ֵ
extern float bt_01_lv;		//1��ǰ��ص�ѹ���ֵ

extern float bt_02_hv;		//2��ǰ��ص�ѹ���ֵ
extern float bt_02_lv;		//2��ǰ��ص�ѹ���ֵ

extern float bt_03_hv;		//3��ǰ��ص�ѹ���ֵ
extern float bt_03_lv;		//3��ǰ��ص�ѹ���ֵ

extern float bt_04_hv;		//4��ǰ��ص�ѹ���ֵ
extern float bt_04_lv;		//4��ǰ��ص�ѹ���ֵ

extern float bt_05_hv;		//5��ǰ��ص�ѹ���ֵ
extern float bt_05_lv;		//5��ǰ��ص�ѹ���ֵ

extern float bt_06_hv;		//6��ǰ��ص�ѹ���ֵ
extern float bt_06_lv;		//6��ǰ��ص�ѹ���ֵ

extern float bt_07_hv;		//7��ǰ��ص�ѹ���ֵ
extern float bt_07_lv;		//7��ǰ��ص�ѹ���ֵ

//��������

extern float light_pv;			//��ص�ѹ   �趨��Χ:5--10V(500--1000)

extern float load_cc_I;			//LED�ƹ�������  �����趨ֵ:0.33--1.2A(33--1200)

extern float load_percent;  	//��������ٷֱ� 50%

extern float step_01_load_percent;  		//��������ٷֱ� 100%

extern float step_02_load_percent;  		//��������ٷֱ� 80%

extern float step_03_load_percent;  		//��������ٷֱ� 60%

extern float step_04_load_percent;  		//��������ٷֱ� 40%

extern float step_05_load_percent;  		//��������ٷֱ� 20%

extern unsigned int  step_01_time_limit;		//���ʱ�� 1 h

extern unsigned int  step_02_time_limit;		//���ʱ�� 3 h

extern unsigned int  step_03_time_limit;		//���ʱ�� 4 h

extern unsigned int  step_04_time_limit;		//���ʱ�� 3 h

extern unsigned int  step_05_time_limit;		//���ʱ�� 1 h

extern unsigned char volt_id;				//��ص�ѹ����

extern unsigned char bt_id; 				//�������

extern unsigned int light_time;			//���ʱ�� (��λ��min)

extern float bt_volt_100 ; 			//100%����ʱ

extern float bt_volt_80  ; 			//80%����

extern float bt_volt_60  ; 			//60%����

extern float bt_volt_40  ; 			//40%����

extern float bt_volt_20  ; 			//20%����

extern float bt_volt_00  ; 			//0%����


extern float dianchi_guoya_baohu;   	//100%  ��ع�ѹ������

extern float dianchi_guoya_huifu;		//95%   ��ع�ѹ�ָ���

extern float dianchi_qianya_baohu;		//0%	���Ƿѹ������

extern float dianchi_qianya_huifu;		//20%	���Ƿѹ�ָ���

extern float dianchi_diya_level;		//60%	��ص�ѹ���ܵ��ڵ�   ����ص�ѹ����60%ʱ�������������ӳ�����ʱ��

extern float dianchi_cv_level;			//>12.40ʱ �����ѹ��緽ʽ

extern float charge_i_limit;			//�������޶�ֵ

extern float shuchu_shortout_voltage; 	//�����·��ѹ

extern float shuchu_open_voltage;		//�����·��ѹ

extern float discharge_i_baohu;		//�ŵ����������  ��������  2.4A

extern float discharge_i_limit;		//�ŵ�����޶�ֵ 2.0A

extern float light_on_pv_level;		//���ƹ����ѹ����ֵ Ĭ��6V

extern float light_off_pv_level;		//�صƹ����ѹ����ֵ Ĭ��12V


float Load_Pmax;	








extern void auto_system(void);

extern void read_param_eeprom(void);





#endif
