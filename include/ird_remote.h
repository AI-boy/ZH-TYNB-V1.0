 #ifndef _IRD_REMOTE_H
 #define _IRD_REMOTE_H


//采样电阻
extern float charge_r_value;	   //充电采样电流采样电阻值 **毫欧姆

extern float discharge_r_value;		//放电电流采样电阻

//运行数据
extern float p_v;    //当前光伏电压

extern float b_v;	//当前电池电压

extern float load_v;	//当前负载电压

extern float charge_I ; //当前充电电流

extern float load_I ;    //当前负载电流

extern unsigned char  sys_mode;     //当前设备工作模式

extern unsigned char  today_index; //EEPROM中 今天电池电压记录保存索引位置

extern float bt_00_hv;		//0天前电池电压最高值 (即今天)
extern float bt_00_lv;		//0天前电池电压最低值 (即今天)

extern float bt_01_hv;		//1天前电池电压最高值
extern float bt_01_lv;		//1天前电池电压最低值

extern float bt_02_hv;		//2天前电池电压最高值
extern float bt_02_lv;		//2天前电池电压最低值

extern float bt_03_hv;		//3天前电池电压最高值
extern float bt_03_lv;		//3天前电池电压最低值

extern float bt_04_hv;		//4天前电池电压最高值
extern float bt_04_lv;		//4天前电池电压最低值

extern float bt_05_hv;		//5天前电池电压最高值
extern float bt_05_lv;		//5天前电池电压最低值

extern float bt_06_hv;		//6天前电池电压最高值
extern float bt_06_lv;		//6天前电池电压最低值

extern float bt_07_hv;		//7天前电池电压最高值
extern float bt_07_lv;		//7天前电池电压最低值

//参数设置

extern float light_pv;			//光控电压   设定范围:5--10V(500--1000)

extern float load_cc_I;			//LED灯工作电流  负载设定值:0.33--1.2A(33--1200)

extern float load_percent;  	//节能输出百分比 50%

extern float step_01_load_percent;  		//节能输出百分比 100%

extern float step_02_load_percent;  		//节能输出百分比 80%

extern float step_03_load_percent;  		//节能输出百分比 60%

extern float step_04_load_percent;  		//节能输出百分比 40%

extern float step_05_load_percent;  		//节能输出百分比 20%

extern unsigned int  step_01_time_limit;		//输出时长 1 h

extern unsigned int  step_02_time_limit;		//输出时长 3 h

extern unsigned int  step_03_time_limit;		//输出时长 4 h

extern unsigned int  step_04_time_limit;		//输出时长 3 h

extern unsigned int  step_05_time_limit;		//输出时长 1 h

extern unsigned char volt_id;				//电池电压类型

extern unsigned char bt_id; 				//电池类型

extern unsigned int light_time;			//光控时间 (单位：min)

extern float bt_volt_100 ; 			//100%电量时

extern float bt_volt_80  ; 			//80%电量

extern float bt_volt_60  ; 			//60%电量

extern float bt_volt_40  ; 			//40%电量

extern float bt_volt_20  ; 			//20%电量

extern float bt_volt_00  ; 			//0%电量


extern float dianchi_guoya_baohu;   	//100%  电池过压保护点

extern float dianchi_guoya_huifu;		//95%   电池过压恢复点

extern float dianchi_qianya_baohu;		//0%	电池欠压保护点

extern float dianchi_qianya_huifu;		//20%	电池欠压恢复点

extern float dianchi_diya_level;		//60%	电池低压节能调节点   当电池电压低于60%时进入节能输出以延长照明时间

extern float dianchi_cv_level;			//>12.40时 进入恒压充电方式

extern float charge_i_limit;			//充电电流限定值

extern float shuchu_shortout_voltage; 	//输出短路电压

extern float shuchu_open_voltage;		//输出开路电压

extern float discharge_i_baohu;		//放电电流保护点  过流保护  2.4A

extern float discharge_i_limit;		//放电电流限定值 2.0A

extern float light_on_pv_level;		//亮灯光伏电压门限值 默认6V

extern float light_off_pv_level;		//关灯光伏电压门限值 默认12V


float Load_Pmax;	








extern void auto_system(void);

extern void read_param_eeprom(void);





#endif
