#include "G_compensation.h"

/*
根据T=K*I计算出电机转矩
参数：A：电流 安培
返回值：转矩大小  n/m
*/

float torque_calc (float A )
{
    return torque_constant*A;
}


float joint_torque_need_calc (void)
{

}



float torque_pid_calc (Torque_Pid * pid , float* T_now , float* T_need )
{
    pid->last_error = pid->error;
    pid->error = *T_need - *T_now;

    pid->p_out = pid->kp * pid->error;

    pid->different = pid->error - pid->last_error;

    pid->d_out = pid->kd * pid->different;

    pid->points +=pid->error;

    pid->i_out = pid->ki * pid->points;

    if (pid->i_out > pid->max_iout)
    {
        pid->i_out = pid->max_iout;
        /* code */
    }
    if (pid->i_out < -pid->max_iout)
    {
        pid->i_out = -pid->max_iout;
        /* code */
    }
    
    pid->out = pid->d_out + pid->i_out + pid->p_out;
    if (pid->out > pid->max_out)
    {
        pid->out = pid->max_out;
        /* code */
    }
    if (pid->out < -pid->max_out)
    {
        pid->out = -pid->max_out;
        /* code */
    }
    

}


void joint_torque_calc(Joint_Torque * joint_torque)
{
    joint_torque->torque_now = torque_constant * (*joint_torque->torque_A);

    joint_torque_need_calc();

    joint_torque->torque_A_out = joint_torque->torque_A_out + torque_pid_calc(&joint_torque->torque_pid , &joint_torque->torque_now , &joint_torque->torque_need );


}



