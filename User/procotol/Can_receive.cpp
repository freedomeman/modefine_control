#include "Can_receive.h"
#include "angledget.h"


extern Can_receive can_receive;
extern Arm arm;



void Can_receive_init(void)
{
    can_filter_init();

}

void get_motor1_3_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive)
{
    can_receive->motor1_3_message_2006[num].last_ecd = can_receive->motor1_3_message_2006[num].ecd;
    can_receive->motor1_3_message_2006[num].ecd = (uint16_t)(data[0] << 8 | data[1]);
    can_receive->motor1_3_message_2006[num].speed_rpm = (uint16_t)(data[2] << 8 | data[3]);
    can_receive->motor1_3_message_2006[num].given_current = (uint16_t)(data[4] << 8 | data[5]);
    can_receive->motor1_3_message_2006[num].temperate = data[6];
}

void get_motor4_6_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive)
{
    can_receive->motor4_6_message_2006[num].last_ecd = can_receive->motor1_3_message_2006[num].ecd;
    can_receive->motor4_6_message_2006[num].ecd = (uint16_t)(data[0] << 8 | data[1]);
    can_receive->motor4_6_message_2006[num].speed_rpm = (uint16_t)(data[2] << 8 | data[3]);
    can_receive->motor4_6_message_2006[num].given_current = (uint16_t)(data[4] << 8 | data[5]);
    can_receive->motor4_6_message_2006[num].temperate = data[6];
}

void can_cmd_1_3_motor(int16_t motor1, int16_t motor2, int16_t motor3 , Can_receive * can_receive)
{
    uint32_t send_mail_box;
    can_receive->can_tx_message.StdId = motor_ctrl_all;
    can_receive->can_tx_message.IDE = CAN_ID_STD;
    can_receive->can_tx_message.RTR = CAN_RTR_DATA;
    can_receive->can_tx_message.DLC = 0x08;
    can_receive->can_send_data[0] = motor1 >>8;
    can_receive->can_send_data[1] = motor1;
    can_receive->can_send_data[2] = motor2 >> 8;
    can_receive->can_send_data[3] = motor2;
    can_receive->can_send_data[4] = motor3 >> 8;
    can_receive->can_send_data[5] = motor3;
    can_receive->can_send_data[6] = 0;
    can_receive->can_send_data[7] = 0;

    HAL_CAN_AddTxMessage(&motor1_3, &can_receive->can_tx_message, can_receive->can_send_data, &send_mail_box);
}

void can_cmd_4_6_motor(int16_t motor4, int16_t motor5, int16_t motor6 , Can_receive * can_receive)
{
    uint32_t send_mail_box;
    can_receive->can_tx_message.StdId = motor_ctrl_all;
    can_receive->can_tx_message.IDE = CAN_ID_STD;
    can_receive->can_tx_message.RTR = CAN_RTR_DATA;
    can_receive->can_tx_message.DLC = 0x08;
    can_receive->can_send_data[0] = motor4 >>8;
    can_receive->can_send_data[1] = motor4;
    can_receive->can_send_data[2] = motor5 >> 8;
    can_receive->can_send_data[3] = motor5;
    can_receive->can_send_data[4] = motor6 >> 8;
    can_receive->can_send_data[5] = motor6;
    can_receive->can_send_data[6] = 0;
    can_receive->can_send_data[7] = 0;

    HAL_CAN_AddTxMessage(&motor4_6, &can_receive->can_tx_message, can_receive->can_send_data, &send_mail_box);
}

const motor_message * get_1_3_motor_measure_point(uint8_t num , Can_receive *  can_receive)
{
    return &  can_receive ->motor1_3_message_2006[num];
}

const motor_message *get_4_6_motor_measure_point(uint8_t num , Can_receive * can_receive)
{
    return & can_receive ->motor4_6_message_2006[num];
}

CAN_RxHeaderTypeDef rx_header;
uint8_t rx_data[8];
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
     
    if (hcan == &motor1_3) //接1_3号电机的信息
    {
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
        switch (rx_header.StdId)
        {
        case motor1_2006:
        
            get_motor1_3_measure(0, rx_data , &can_receive);
            //angle_comput_can(&arm ,0);
            //detect_hook(motor1_2006);
            break;
        case motor2_2006:
   
            get_motor1_3_measure(1, rx_data , &can_receive);
            //detect_hook(motor1_2006);
            break;
        case motor3_2006:
            get_motor1_3_measure(2, rx_data , &can_receive);
            //detect_hook(motor3_2006);
            break;
        default:
            break;
        }
    }
    if (hcan == &motor4_6) //接4_6号电机的信息
    {
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
        switch (rx_header.StdId)
        {
        case motor4_2006:
            get_motor4_6_measure(0, rx_data ,&can_receive);
            //detect_hook(motor4_2006);
            break;
        case motor2_2006:
            get_motor4_6_measure(1, rx_data ,&can_receive);
            //detect_hook(motor1_2006);
            break;
        case motor3_2006:
            get_motor4_6_measure(2, rx_data ,&can_receive);
            //detect_hook(motor3_2006);
            break;
        default:
            break;
        }
    }
}




