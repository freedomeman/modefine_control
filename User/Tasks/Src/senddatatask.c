#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "CRC8_CRC16.h"
#include "senddatatask.h"
#include "string.h"
#include "angledget.h"
//#include <stdio.h>



/***********函数定义区******************/

static void Data_Concatenation(uint8_t *data, uint16_t data_lenth);

void vofa_send(float * data);

/*************全局变量区*****************/

Controller_t tx_data; // 自定义控制器发送的数据

void StartSendDataTask(void const *argument)
{
    // uint8_t index = 0;
    uint8_t ch = '\n';
    uint32_t wait_time = xTaskGetTickCount();
    for (;;)
    {
//		wait_time = xTaskGetTickCount();
        
//        uint8_t data[DATA_LENGTH] = {0x40, 0x50, 0x60, 0x70};
         Data_Concatenation(arm.angle_send_data, DATA_LENGTH);
         HAL_UART_Transmit(&huart1, (uint8_t *)(&tx_data), sizeof(tx_data), 50);
         //HAL_UART_Transmit(&huart1, (uint8_t *)(&ch) , 1 , 50);
        //vofa_send(&arm.joint[0].angle);
        // printf(" hello stm32\n");
        // arm.joint[0].angle;
        //printf("%d\n",(int)arm.joint[0].angle );

        //osDelayUntil(&wait_time, 200);
    }
}

/**
 * @brief 数据拼接函数，将帧头、命令码、数据段、帧尾头拼接成一个数组
 * @param data 数据段的数组指针
 * @param data_lenth 数据段长度
 */
static void Data_Concatenation(uint8_t *data, uint16_t data_lenth)
{
    static uint8_t seq = 0;
    /// 帧头数据
    tx_data.frame_header.sof = 0xA5;                              // 数据帧起始字节，固定值为 0xA5
    tx_data.frame_header.data_length = data_lenth;                // 数据帧中数据段的长度
    tx_data.frame_header.seq = seq++;                             // 包序号
    append_CRC8_check_sum((uint8_t *)(&tx_data.frame_header), 5); // 添加帧头 CRC8 校验位
    /// 命令码ID
    tx_data.cmd_id = CONTROLLER_CMD_ID;
    /// 数据段
    memcpy(tx_data.data, data, data_lenth);
    /// 帧尾CRC16，整包校验
    append_CRC16_check_sum((uint8_t *)(&tx_data), DATA_FRAME_LENGTH);
}


void vofa_send(float * data)
{
    uint8_t ArrayByte[8] = {0,0,0,0,0x00, 0x00, 0x80, 0x7f};
    uint8_t i;
    // ArrayByte[0] =  (uint32_t) data ; //arm.angle_send_data[0] ;   //0-7位移到数组元素0
    // ArrayByte[1] =  (uint32_t) data >> 8 ; //arm.angle_send_data[1];   //8-15位移动到数组元素1
    // ArrayByte[2] =  (uint32_t) data >> 16; // arm.angle_send_data[0];  //16-23位移动到数组元素2
    // ArrayByte[3] =  (uint32_t) data >> 24; //arm.angle_send_data[1];  //24-31位移动到数组元素3 

    memcpy(ArrayByte ,data , 4);


    //uint8_t Tail[4] = {0x00, 0x00, 0x80, 0x7f}; //帧尾

    HAL_UART_Transmit(&huart1, (uint8_t *)(&ArrayByte), sizeof(ArrayByte), 50);
    //HAL_UART_Transmit(&huart1, (uint8_t *)(&Tail), sizeof(Tail), 50);


}


//int fputc(int ch, FILE *stream) {
//    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 50);
//    return ch;
//}

