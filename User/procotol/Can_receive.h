#ifndef  CAN_RECEIVE_H
#define  CAN_RECEIVE_H




#include "cmsis_os.h"
#include "can.h"
#include "main.h"



#ifdef __cplusplus
extern "C"
{
#endif
#include "bsp_can.h"
#include "bsp_can.h"
#ifdef __cplusplus
}
#endif



extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;


#define motor4_6 hcan2
#define motor1_3 hcan1

typedef enum
{
  //电机1——3的接收id
  motor1_2006 = 0x201,
  motor2_2006 = 0x202,
  motor3_2006 = 0x203,


  //电机4——6的接收id
  motor4_2006 = 0x201,
  motor5_2006 = 0x202,
  motor6_2006 = 0x203,

  //电机的控制码
  motor_ctrl_all = 0x200,

} can_msg_id_e;

typedef struct 
{
  uint16_t ecd; // 读出的编码器角度
  int16_t speed_rpm; // 读出的当前转速
  int16_t given_current; // 给的电流值
  uint8_t temperate; // 读出的温度
  int16_t last_ecd; // 上一次的编码器值
    /* data */
}motor_message;


typedef struct Can_receive
{


    motor_message motor1_3_message_2006[3];
    motor_message motor4_6_message_2006[3];

    CAN_TxHeaderTypeDef can_tx_message;

    uint8_t can_send_data[8];


}Can_receive;


    void Can_receive_init(void);
    void get_motor1_3_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive);
    void get_motor4_6_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive);
    void can_cmd_1_3_motor(int16_t motor1, int16_t motor2, int16_t motor3 , Can_receive * can_receive);
    void can_cmd_4_6_motor(int16_t motor4, int16_t motor5, int16_t motor6 , Can_receive * can_receive);
    const motor_message *get_1_3_motor_measure_point(uint8_t num , Can_receive * can_receive);
    const motor_message *get_4_6_motor_measure_point(uint8_t num , Can_receive * can_receive);







#endif
