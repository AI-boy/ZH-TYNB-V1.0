
#ifndef _ZH_LED_H
#define _ZH_LED_H


//**--------------�����ļ�-----------------------------------------------------

//**--------------�궨��-------------------------------------------------------



//���ָʾ��
#define CHARGE_LED_TRIS			(TRISCbits.TRISC4) 				// RC4
#define CHARGE_LED_OFF			(LATCbits.LATC4 = 0x00) 		// ����͵�ƽ
#define CHARGE_LED_ON			(LATCbits.LATC4 = 0x01) 		// ����ߵ�ƽ
#define CHARGE_LED_TOG			(LATCbits.LATC4 ^= 0x01) 		// �������ƽ



//�ŵ�ָʾ��
#define DISCHARGE_LED_TRIS		(TRISCbits.TRISC5) 				// RC5
#define DISCHARGE_LED_OFF		(LATCbits.LATC5 = 0x00) 		// ����͵�ƽ
#define DISCHARGE_LED_ON		(LATCbits.LATC5 = 0x01) 		// ����ߵ�ƽ
#define DISCHARGE_LED_TOG		(LATCbits.LATC5 ^= 0x01) 		// �������ƽ


//���ָʾ��
#define BATRGE_LED_TRIS			(TRISBbits.TRISB4) 				// RB4
#define BATRGE_LED_OFF			(LATBbits.LATB4 = 0x00) 		// ����͵�ƽ
#define BATRGE_LED_ON			(LATBbits.LATB4 = 0x01) 		// ����ߵ�ƽ
#define BATRGE_LED_TOG			(LATBbits.LATB4 ^= 0x01) 		// �������ƽ






//**--------------���ݽṹ-----------------------------------------------------

//**--------------��������-----------------------------------------------------


extern void init_led(void);
	


#endif 
