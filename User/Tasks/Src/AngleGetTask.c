
#include "AngleGetTask.h"
//#include "angledget.h"


extern    void Arm_init(Arm *arm);
extern    void angle_comput(Arm *arm);
extern    void speed_comput(Arm *arm);
extern    void angle_send(Arm *arm);
extern    void arm_cmd(void);

void Angle_Get_Task(void const *argument)
{
   Arm_init(&arm);
   vTaskDelay(500);
   //joint_init(&arm);
   Arm_to_mid(&arm);

   while (1)
   {
         angle_comput(&arm);
         speed_comput(&arm);
        angle_send(&arm);
        arm_cmd();
        vTaskDelay(5);

    /* code */
   }
    
}
 