

#ifndef _ZH_PWM_H
#define _ZH_PWM_H 





#define    PWM_IRD_TRIS      	TRISAbits.TRISA4

#define    BUCK_PWM_H_TRIS      TRISCbits.TRISC2

#define    BUCK_PWM_L_TRIS      TRISBbits.TRISB2

#define    BOST_PWM_TRIS      	TRISBbits.TRISB5


#define 	BUCK_PWM_MAX		900  	

#define 	BUCK_PWM_MIN		50	


#define 	BOST_PWM_MAX		488  	

#define 	BOST_PWM_MIN		5	


extern unsigned int pwm_duty_value;

extern unsigned int bost_pwm_value;

extern unsigned int buck_pwm_value;


extern long int P_prev;  //前一次功率

extern long int P_last;  //后一次功率





extern void init_pwm(void);

extern void Enable_Buck_Pwm(void);

extern void Disable_Buck_Pwm(void);

extern void Set_Buck_Pwm_Duty(unsigned int duty);

extern void Enable_Bost_Pwm(void);

extern void Disable_Bost_Pwm(void);

extern void Set_Bost_Pwm_Duty(unsigned int dduty);





#endif