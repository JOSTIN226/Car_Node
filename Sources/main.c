//#include "MPC5604B.h"

#include "includes.h"


void main(void)
{
	//int flag = 1;
	
	init_all_and_POST();
	set_speed_target(10);


	/* Loop forever */
		
	for (;;)
	{
		
#if 1
		/* 执行远程命令 */
		if (REMOTE_FRAME_STATE_OK == g_remote_frame_state)
		{
			g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
			
			execute_remote_cmd(remote_frame_data+5);
		}

		/* 整车动作控制 */
		control_car_action();

		/* 报告在线 */
		report_online();
#endif
#if 1
		if(fieldover)
		{
			
			D3=1;//7ms
			fieldover=0;
			AnalysRoad();
			if(g_f_stopline)
			{
				set_speed_target(0);
				g_f_enable_camera_control = 0;
			}
			Display_Video();
			Send_CCD_Video();
			D3=0;
			//write_camera_data_to_TF();
		}
#endif
		
	}

}


