#ifndef __PID_H
#define __PID_H


//-------------------------------------
//
//
//PID�ṹ��
//
//
//
//---------------------------------------

typedef struct PID_VAR{

     float SetPoint;   // �趨Ŀ�� Desired value
     float Proportion; // �������� Proportional Const
     float Integral;   // ���ֳ��� Integral Const
     float Derivative; // ΢�ֳ��� Derivative Const
     float LastError;  // Error[-1]
     float PrevError;  // Error[-2]
     float SumError;   // Sums of Errors
} PID;




extern	PID PID_CC_charge;       //���Ƶ��ں������

extern  PID PID_CV_charge;     //���Ƶ��ں�ѹ���
 
extern  PID PID_CC_discharge;  //���Ƶ��ں������

extern  void pid_init (PID *pp);

extern  float  pid_calc( PID *pp, int NowPoint );

#endif
