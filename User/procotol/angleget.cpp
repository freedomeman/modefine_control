#include "angledget.h"


Arm arm;
extern Can_receive can_receive;

void Arm_init( Arm *arm)
{
    Communicate_init();
    int i;
    for ( i = 0; i < 3; i++)
    {
        arm->joint[i].motor = get_1_3_motor_measure_point(i , &can_receive);
        //arm->joint[i].motor_angle_init = arm->joint[i].motor->ecd;
        /* code */
    }
    for ( i = 3; i < 6; i++)
    {
        arm->joint[i].motor = get_4_6_motor_measure_point(i ,&can_receive);
        //arm->joint[i].motor_angle_init = arm->joint[i].motor->ecd;
        /* code */
    }


}

void Arm_to_mid(Arm *arm )
{
    uint8_t  i;
    for ( i = 0; i < 6; i++)
    {
        arm->joint[i].angle=0;
        arm->joint[i].ecd_count = 0;
        arm->joint[i].last_motor_ecd = 0;
        arm->joint[i].motor_ecd = 0;
        arm->joint[i].speed = 0;
        arm->joint[i].motor_angle_init = arm->joint[i].motor->ecd;
        /* code */
    }
    
}


void angle_comput_can(Arm *arm ,uint8_t motor_id)
{
    uint8_t i;
    i = motor_id;
    arm->joint[i].motor_ecd = arm->joint[i].motor->ecd  - arm->joint[i].motor_angle_init;
        if (arm->joint[i].motor_ecd < 0)
        {
            arm->joint[i].motor_ecd +=motor_2006_ecd_full;
          
        }

     
        
    if(arm->joint[i].motor_ecd - arm->joint[i].last_motor_ecd  <= -5000 && arm->joint[i].motor->speed_rpm >=0) // 正转越过0
    {
        arm->joint[i].ecd_count ++ ; //正转一圈
    }

    else if(arm->joint[i].motor_ecd - arm->joint[i].last_motor_ecd  >= 5000 && arm->joint[i].motor->speed_rpm <=0) // 反转越过0
    {
        arm->joint[i].ecd_count -- ; //反转一圈
    }
        arm->joint[i].last_motor_ecd = arm->joint[i].motor_ecd;
    
    if (arm->joint[i].ecd_count == 36 || arm->joint[i].ecd_count == -36) //电机正传或反转一圈
    {
        arm->joint[i].ecd_count = 0;
        /* code */
    }
    


    arm->joint[i].angle = (arm->joint[i].motor_ecd + arm->joint[i].ecd_count *motor_2006_ecd_full) * 2*pi/motor_2006_ecd_full/36 ;    
}


void angle_comput(Arm *arm)
{
    int i=0;
//    int count;
    for(i = 0 ; i < 6 ; i++)
    {
        // if (arm-> joint[i].motor->ecd - arm->joint[i].motor->last_ecd > motor_2006_ecd_haif)
        // {
        //     arm->joint[i].ecd_count --;
        //     /* code */
        // }
        // else if (arm-> joint[i].motor->ecd - arm->joint[i].motor->last_ecd < -motor_2006_ecd_haif)
        // {
        //     arm->joint[i].ecd_count ++;
        //     /* code */
        // }
        // if (arm->joint[i].ecd_count == motor_2006_full_count)
        // {
        //     arm->joint[i].ecd_count =0;
        //     /* code */
        // }
        // arm->joint[i].angle = (arm->joint[i].ecd_count * motor_2006_ecd_full + arm->joint[i].motor->ecd) *ecd_to_angle;
        // if (arm->joint[i].angle < 0)
        // {
        //     arm->joint[i].angle = 2*pi-arm->joint[i].angle;
        //     /* code */
        // }

    // if (arm->joint[i].motor->ecd - arm->joint[i].motor->last_ecd > motor_2006_ecd_haif)
    // {
    //     arm->joint[i].ecd_count--;
    // }
    // else if (arm->joint[i].motor->ecd - arm->joint[i].motor->last_ecd < -motor_2006_ecd_haif)
    // {
    //     arm->joint[i].ecd_count++;
    // }

    // if ( arm->joint[i].ecd_count == FULL_COUNT)
    // {
    //     arm->joint[i].ecd_count = -(FULL_COUNT - 1);
    // }
    // else if (arm->joint[i].ecd_count == -FULL_COUNT)
    // {
    //     arm->joint[i].ecd_count = FULL_COUNT - 1;
    // }

    // //计算输出轴角度
    // arm->joint[i].angle = (arm->joint[i].ecd_count * motor_2006_ecd_full + (arm->joint[i].motor->ecd)) * ecd_to_angle;





			// ////////////////////////////////////////////////////////////////////////////////////////////////////
            // angle_error = arm-> joint[i].motor->ecd - arm->joint[i].motor->last_ecd;     //转子的角度差 = 现在转子角度 - 上一次的转子角度
			// if(arm-> joint[i].motor->speed_rpm > 0)                          //如果转子速度为正
			// {
			// 	if(-18<arm->joint[i].ecd_count&&arm->joint[i].ecd_count < 18)                   //判读输出轴是否转了一圈
			// 	{
			// 		if(angle_error < -1000)                                          //角度为负
			// 		{ 
			// 		  arm->joint[i].ecd_count++;                                            //转子已经转了一圈，cyclinder_number++
			// 		} 
			// 	}
			// 	else
			// 	{
			// 		arm->joint[i].ecd_count = 0;
			// 	}
			// }
			// else if(arm-> joint[i].motor->speed_rpm < 0)
			// {
			// 	if(-18<arm->joint[i].ecd_count&&arm->joint[i].ecd_count < 18)
			// 	{
			// 		if(angle_error > 1000)
			// 		{
			// 		  arm->joint[i].ecd_count--;
			// 		}
			// 	}
			// 	else
			// 	{
			// 		arm->joint[i].ecd_count = 0;
			// 	}				
			// }
		
			// out_angle = arm-> joint[i].motor->ecd + arm->joint[i].ecd_count*8191;     //输出轴的机械刻度
			// if(out_angle >=0)                                                            //如果这个条件使用，在elsed中处理一下控制角度的周期
			// {
			// 	arm->joint[i].angle = out_angle/(8191*18.00f)*360;       //输出轴的机械刻度换算成角度
			// }
			// else
			// {
			// 	arm->joint[i].angle = out_angle/(8191*18.00f)*360;        //输出轴的机械刻度换算成角度
			// }                                                       
		




            //  if (arm-> joint[i].motor->ecd - arm-> joint[i].motor->last_ecd > motor_2006_ecd_haif)
            //  {
            //      arm-> joint[i].ecd_count--;
            //  }
            //  else if (arm-> joint[i].motor->ecd - arm-> joint[i].motor->last_ecd  < -motor_2006_ecd_haif)
            //  {
            //      arm-> joint[i].ecd_count++;
            //  }

            //  if (arm-> joint[i].ecd_count == motor_2006_full_count)
            //  {
            //      arm-> joint[i].ecd_count = -(motor_2006_full_count - 1);
            //  }
            //  else if (arm-> joint[i].ecd_count == -motor_2006_full_count)
            //  {
            //      arm-> joint[i].ecd_count = motor_2006_full_count - 1;
            //  }
            //  //计算拨盘电机输出轴角度
            // arm->joint[i].angle= (arm-> joint[i].motor->ecd  + arm-> joint[i].ecd_count * motor_2006_full_count) * ecd_to_angle;



 arm->joint[i].motor_ecd = arm->joint[i].motor->ecd  - arm->joint[i].motor_angle_init;
        if (arm->joint[i].motor_ecd < 0)
        {
            arm->joint[i].motor_ecd +=motor_2006_ecd_full;
          
        }

     
        
    if(arm->joint[i].motor_ecd - arm->joint[i].last_motor_ecd  <= -5000 && arm->joint[i].motor->speed_rpm >=0) // 正转越过0
    {
        arm->joint[i].ecd_count ++ ; //正转一圈
    }

    else if(arm->joint[i].motor_ecd - arm->joint[i].last_motor_ecd  >= 5000 && arm->joint[i].motor->speed_rpm <=0) // 反转越过0
    {
        arm->joint[i].ecd_count -- ; //反转一圈
    }
        arm->joint[i].last_motor_ecd = arm->joint[i].motor_ecd;
    
    if (arm->joint[i].ecd_count == 36 || arm->joint[i].ecd_count == -36) //电机正传或反转一圈
    {
        arm->joint[i].ecd_count = 0;
        /* code */
    }
    

        
        //arm->joint[i].angle = arm->joint[i].motor_ecd * 2*pi/motor_2006_ecd_full;
    arm->joint[i].angle = (arm->joint[i].motor_ecd + arm->joint[i].ecd_count *motor_2006_ecd_full) * 2*pi/motor_2006_ecd_full/36 ;    
        
       

       
      //  arm->joint[i].motor_angle_last = arm-> joint[i].motor->last_ecd * 2*pi/motor_2006_ecd_full;


        // if ( 0<arm->joint[i].motor_angle < 90 && 270<arm->joint[i].motor_angle_last<360) // 正转
        // {
        //     count = 1;
        //     /* code */
        // }
        // else if ( 0<arm->joint[i].motor_angle_last < 90 && 270<arm->joint[i].motor_angle<360) //反转
        // {
        //     count = -1;
        //     /* code */
        // }
        // if (arm->joint[i].motor_angle < arm->joint[i].motor_angle_last)
        // {
        //     /* code */
        //     arm->joint[i].angle = (count *10 - arm->joint[i].motor_angle/36);
        // }
        // else if(arm->joint[i].motor_angle > arm->joint[i].motor_angle_last)
        // {
        //     arm->joint[i].angle = (count *10 + arm->joint[i].motor_angle/36);
        // }
        
        
        // //arm->joint[i].angle = count *10 + arm->joint[i].motor_angle/36;
        
        // if (arm->joint[i].angle  <= 0)
        // {
        //     arm->joint[i].angle -=2*pi;
        //     /* code */
        // }
        
        







    }
}

void speed_comput(Arm *arm)
{
    int i=0;
    for ( i = 0; i < 6; i++)
    {
        arm->joint[i].speed = arm->joint[i].motor->speed_rpm  / reduction_ratio;
        /* code */
    }
    

}


void angle_send(Arm *arm)
{
    int i=0;
    int j=0;
    for ( i = 0; i < 6; i++)
    {
        j=i*2+1;
        arm->angle_send_data[j-1]=((int16_t) arm->joint[i].angle) >> 8;
        arm->angle_send_data[j]  =((int16_t) arm->joint[i].angle);

        /* code */
    }
    for ( i = 0; i < 6; i++)
    {
        j= (i+6)*2+1;
        arm->angle_send_data[j-1]=((int16_t) arm->joint[i].speed) >> 8;
        arm->angle_send_data[j]  =((int16_t) arm->joint[i].speed);        
        /* code */
    }
    
    

}


void joint_init(Arm *arm)
{
    int i;
    for ( i = 0; i < 6; i++)
    {
        arm->joint[i].motor_angle_init = arm->joint[i].motor->ecd;
        /* code */
    }
    
}



// void arm_cmd(void)
// {
//     can_cmd_1_3_motor(0 , 0 , 0 , &can_receive);
// }




