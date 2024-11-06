#ifndef __G_COMPENSATION
#define __G_COMPENSATION

#include "struct_typedef.h"
//T=K*I  

#define torque_constant     0.18f       //0.18n/m

typedef struct Torque_Pid
{
    float kp,ki,kd;

    float p_out,i_out,d_out,out;

    float error,last_error,points,different;

    float max_iout,max_out;


    /* data */
}Torque_Pid;


typedef struct Joint_Torque
{
    int16_t *torque_A;

    float torque_now,torque_need;



    float joint_angle;

    Torque_Pid torque_pid;

    int16_t torque_A_out;


    /* data */
}Joint_Torque;




#endif
