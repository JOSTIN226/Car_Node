//#include "MPC5604B.h"

#include "includes.h"


void main(void)
{
	//int flag = 1;
	
	init_all_and_POST();
	g_f_enable_speed_control=0;
	g_f_enable_supersonic=0;
	set_speed_pwm(150);
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
			
			fieldover=0;
			AnalysRoad();
			Display_Video();
			if(g_f_stopline)
			{
				if(g_f_red)
				{
					set_speed_target(0);
					EMIOS_0.CH[3].CCR.B.FEN=0;//关场中断
				}
				else 
				{
					SteerControl();
					EMIOS_0.CH[3].CSR.B.FLAG = 1;//清场中断标志位
					EMIOS_0.CH[3].CCR.B.FEN=1;//开场中断
				}
			}
			else
			{
				SteerControl();
				EMIOS_0.CH[3].CSR.B.FLAG = 1;//清场中断标志位
				EMIOS_0.CH[3].CCR.B.FEN=1;//开场中断
			}
			//Send_CCD_Video();
//			EMIOS_0.CH[3].CSR.B.FLAG = 1;
//			EMIOS_0.CH[3].CCR.B.FEN=1;
		}
#endif
		
	}

}


