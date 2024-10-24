#ifndef ANGLEGET_H
#define ANGLEGET_H

#include "Can_receive.h"
#include "communicate.h"

#define motor_2006_ecd_haif     4096
#define motor_2006_full_count   36
#define motor_2006_ecd_full     8191
#define pi                      180
#define reduction_ratio         36
#define FULL_COUNT              19
#define angle_send_data_length  30
#define ecd_to_angle            0.0012208521548f  //2pi * 1/8192/36

typedef struct 
{
    float angle;
    float speed;

    float motor_angle_init;
    float motor_ecd;
    float last_motor_ecd;

    float ecd_count;

    const motor_message * motor;
    /* data */
}Joint;




typedef struct 
{


    Joint joint[6];

    uint8_t angle_send_data[angle_send_data_length];






}Arm;

extern Arm arm;


#ifdef __cplusplus
extern "C"
{
#endif

extern    void Arm_init(Arm *arm);
extern    void angle_comput(Arm *arm);
extern    void speed_comput(Arm *arm);
extern    void angle_send(Arm *arm);
extern    void joint_init(Arm *arm);
extern    void angle_comput_can(Arm *arm ,uint8_t motor_id);
extern    void Arm_to_mid(Arm *arm );

#ifdef __cplusplus
}
#endif





#endif
