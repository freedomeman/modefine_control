#include "arm.h"
#include "communicate.h"



#include "Can_receive.h"



extern Can_receive can_receive;

void arm_cmd(void)
{
    can_cmd_1_3_motor(0,0,0,&can_receive);
}
