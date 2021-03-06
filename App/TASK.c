/**
  ******************************************************************************
  * @文件	TASK.c
  * @日期	2015-2-15
  * @说明	系统任务
  ******************************************************************************
  * 北京交通大学-通信1208-赵小铭
  *
  * 说明:	IAR版本:7.20.2.7314
  *      	库文件版本:标准库 V1.3.0
  *         UCOS版本:3.04.04(已自行修改添加FPU的支持)
  * 文件缩进:	Tab Size:4
  * 自动缩进:	Body:4
  * 详细说明见Documents中Readme.txt
  ******************************************************************************
  */

#include "includes.h"

/* 以下为各个任务的堆栈空间 */
// 启动任务(启动任务在main.c中调用了)
OS_TCB TASK_START_TCB;							// 任务TCB控制块
CPU_STK TASK_START_STK[STARTUP_TASK_STK_SIZE];	// 任务堆栈空间
// LED任务
OS_TCB TASK_LED_BEEP_TCB;							// 任务TCB控制块
CPU_STK TASK_LED_BEEP_STK[TASK_LED_BEEP_STK_SIZE];		// 任务堆栈空间
// CAN发送任务
OS_TCB TASK_CAN_TCB;							// 任务TCB控制块
CPU_STK TASK_CAN_STK[TASK_CAN_STK_SIZE];		// 任务堆栈空间
// 计时任务
OS_TCB TASK_TIME_TCB;							// 任务TCB控制块
CPU_STK TASK_TIME_STK[TASK_TIME_STK_SIZE];		// 任务堆栈空间
// 显示任务
OS_TCB TASK_SHOW_TCB;							// 任务TCB控制块
CPU_STK TASK_SHOW_STK[TASK_SHOW_STK_SIZE];		// 任务堆栈空间
// 按键拨码读取任务
OS_TCB TASK_KEY_TCB;							// 任务TCB控制块
CPU_STK TASK_KEY_STK[TASK_KEY_STK_SIZE];		// 任务堆栈空间
// 手柄读取任务
OS_TCB TASK_PS_TCB;							// 任务TCB控制块
CPU_STK TASK_PS_STK[TASK_KEY_STK_SIZE];		// 任务堆栈空间
// 红外读取任务
OS_TCB TASK_ADC_TCB;							// 任务TCB控制块
CPU_STK TASK_ADC_STK[TASK_KEY_STK_SIZE];		// 任务堆栈空间



/*******************************************************************************
函 数 名：TASK_START(void)
描    述：启动任务
*******************************************************************************/
void TASK_START(void)
{
    OS_ERR err;
    
	// 初始化CPU时间戳、中断和CPU name
    CPU_Init();
	// SysTick初始化
    SysTickInit();
	
	////////Todo:外设初始化、系统变量初始化
    // 各个外设的初始化
	Peripheral_Init();
	// 系统变量初始化
	App_Init();
	
	
    
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running */
#endif
    
    OSTaskCreate((OS_TCB     *)&TASK_LED_BEEP_TCB,
                 (CPU_CHAR   *)"TASK_LED_BEEP",
                 (OS_TASK_PTR)TASK_LED_BEEP,
                 (void       *)0,
                 (OS_PRIO    )TASK_LED_BEEP_PRIO,
                 (CPU_STK    *)&TASK_LED_BEEP_STK[0],
                 (CPU_STK_SIZE)TASK_LED_BEEP_STK_SIZE / 10,
                 (CPU_STK_SIZE)TASK_LED_BEEP_STK_SIZE,
                 (OS_MSG_QTY )0,
                 (OS_TICK    )0,
                 (void       *)0,
                 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP), 
                 (OS_ERR     *)&err);	
	OSTaskCreate((OS_TCB     *)&TASK_CAN_TCB,
			 	 (CPU_CHAR   *)"TASK_CAN",
			 	 (OS_TASK_PTR)TASK_CAN,
			 	 (void       *)0,
			 	 (OS_PRIO    )TASK_CAN_PRIO,
			 	 (CPU_STK    *)&TASK_CAN_STK[0],
			 	 (CPU_STK_SIZE)TASK_CAN_STK_SIZE / 10,
			 	 (CPU_STK_SIZE)TASK_CAN_STK_SIZE,
			 	 (OS_MSG_QTY )0,
			 	 (OS_TICK    )0,
			 	 (void       *)0,
			 	 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR /*| OS_OPT_TASK_SAVE_FP*/), 
			 	 (OS_ERR     *)&err);
	OSTaskCreate((OS_TCB     *)&TASK_TIME_TCB,
				 (CPU_CHAR   *)"TASK_TIME",
				 (OS_TASK_PTR)TASK_TIME,
				 (void       *)0,
				 (OS_PRIO    )TASK_TIME_PRIO,
				 (CPU_STK    *)&TASK_TIME_STK[0],
				 (CPU_STK_SIZE)TASK_TIME_STK_SIZE / 10,
				 (CPU_STK_SIZE)TASK_TIME_STK_SIZE,
				 (OS_MSG_QTY )0,
				 (OS_TICK    )0,
				 (void       *)0,
				 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
				 (OS_ERR     *)&err);
	OSTaskCreate((OS_TCB     *)&TASK_SHOW_TCB,
				 (CPU_CHAR   *)"TASK_SHOW",
				 (OS_TASK_PTR)TASK_SHOW,
				 (void       *)0,
				 (OS_PRIO    )TASK_SHOW_PRIO,
				 (CPU_STK    *)&TASK_SHOW_STK[0],
				 (CPU_STK_SIZE)TASK_SHOW_STK_SIZE / 10,
				 (CPU_STK_SIZE)TASK_SHOW_STK_SIZE,
				 (OS_MSG_QTY )0,
				 (OS_TICK    )0,
				 (void       *)0,
				 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
				 (OS_ERR     *)&err);
	OSTaskCreate((OS_TCB     *)&TASK_KEY_TCB,
				 (CPU_CHAR   *)"TASK_KEY",
				 (OS_TASK_PTR)TASK_KEY,
				 (void       *)0,
				 (OS_PRIO    )TASK_KEY_PRIO,
				 (CPU_STK    *)&TASK_KEY_STK[0],
				 (CPU_STK_SIZE)TASK_KEY_STK_SIZE / 10,
				 (CPU_STK_SIZE)TASK_KEY_STK_SIZE,
				 (OS_MSG_QTY )0,
				 (OS_TICK    )0,
				 (void       *)0,
				 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
				 (OS_ERR     *)&err);
    OSTaskCreate((OS_TCB     *)&TASK_PS_TCB,
				 (CPU_CHAR   *)"TASK_PS",
				 (OS_TASK_PTR)TASK_PS,
				 (void       *)0,
				 (OS_PRIO    )TASK_PS_PRIO,
				 (CPU_STK    *)&TASK_PS_STK[0],
				 (CPU_STK_SIZE)TASK_PS_STK_SIZE / 10,
				 (CPU_STK_SIZE)TASK_PS_STK_SIZE,
				 (OS_MSG_QTY )0,
				 (OS_TICK    )0,
				 (void       *)0,
				 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
				 (OS_ERR     *)&err);
	OSTaskCreate((OS_TCB     *)&TASK_ADC_TCB,
			 	 (CPU_CHAR   *)"TASK_ADC",
				 (OS_TASK_PTR)TASK_ADC,
				 (void       *)0,
				 (OS_PRIO    )TASK_ADC_PRIO,
				 (CPU_STK    *)&TASK_ADC_STK[0],
				 (CPU_STK_SIZE)TASK_ADC_STK_SIZE / 10,
				 (CPU_STK_SIZE)TASK_ADC_STK_SIZE,
				 (OS_MSG_QTY )0,
				 (OS_TICK    )0,
				 (void       *)0,
				 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR ),
				 (OS_ERR     *)&err);
	////////Todo:系统任务添加
	// 删除启动任务
    OSTaskDel((OS_TCB*)&TASK_START_TCB,(OS_ERR*)&err);
}

/*******************************************************************************
函 数 名：TASK_LED_BEEP(void *p_arg)
描    述：LED测试任务
*******************************************************************************/
void TASK_LED_BEEP(void *p_arg)
{
    OS_ERR err;
		
	////OS正常初始化哔哔哔哔
	Sys_Start();
    
	//OS正常运行闪烁灯
    while (1)
    {
		CORE_Toggle();
		
		OSTimeDlyHMSM(0, 0, 0, 400,
                      OS_OPT_TIME_HMSM_NON_STRICT,
                      &err);
		
		CORE_Toggle();
		
		OSTimeDlyHMSM(0, 0, 1, 500,
                      OS_OPT_TIME_HMSM_NON_STRICT,
                      &err);
	}
}

/*******************************************************************************
函 数 名：TASK_CAN(void *p_arg)
描    述：CAN测试任务
*******************************************************************************/
void TASK_CAN(void *p_arg)
{
    OS_ERR err;
	
	//底盘配置为速度控制模式
	Speed_Mode_Init();
    while (1)
    {
		//获取手柄数据
        Get_PS_Data();
		//防止碰撞
		//Avoid_Confict();
        
		
		//设置底盘速度
        Set_Speed();
		//设置风扇机械臂速度和位置
		//Set_Fan(FanCMD.height-(fanheight-15.0)*10.0,FanCMD.FanSpeed,FanCMD.FanDirection);
		Set_Fan(FanCMD.height,FanCMD.FanSpeed,FanCMD.FanDirection);
		
		OSTimeDlyHMSM(0, 0, 0, TASK_CAN_DELAY,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
	}
}

/*******************************************************************************
函 数 名：TASK_TIME(void *p_arg)
描    述：计时任务，优先级12
*******************************************************************************/
void TASK_TIME(void *p_arg)
{
	OS_ERR err;
	CPU_TS OS_ticks;

	while(1)
	{
		// 获取系统Ticks计算系统时间
		OS_ticks = OSTimeGet(&err);
		OS_ticks /= 1000;
		Time.sec = OS_ticks%60;
		Time.min = OS_ticks/60%60;
		Time.hour = OS_ticks/3600%60;			

		OSTimeDlyHMSM(0, 0, 1, 0,
                      OS_OPT_TIME_HMSM_NON_STRICT,
                      &err);
	}
}

/*******************************************************************************
函 数 名：TASK_SHOW(void *p_arg)
描    述：显示任务，优先级13
*******************************************************************************/
void TASK_SHOW(void *p_arg)
{
	OS_ERR err;
	//char time_s[] 		= "  :  :  ";
	//char cpu_usage_s[]	= "00.00%";
	
	
	
	OLED_Init_Show();
	
	while(1)
	{
//		CPU_SR_ALLOC();// 申请cpu_sr
//		
//		sprintf( time_s,"%2d:%2d:%2d",\
//						 Time.hour,Time.min,Time.sec);
//		sprintf( cpu_usage_s,"%2.2f%%",((float)OSStatTaskCPUUsage/100));
//				
//		
//		CPU_CRITICAL_ENTER(); // 关键段，关闭全局中断，视具体情况添加此语句
//		// 时间
//		OLED_P6x8Str(0,2,(u8*)time_s);
//		// CPU使用率
//		OLED_P6x8Str(66,2,"CPU:");
//		OLED_P6x8Str(90,2,(u8*)cpu_usage_s);
//		CPU_CRITICAL_EXIT(); // 退出关键段，开启全局中断，视具体情况添加此语句

		OSTimeDlyHMSM(0, 0, 1, 0,
                      OS_OPT_TIME_HMSM_NON_STRICT,
                      &err);
	}
}

/*******************************************************************************
函 数 名：TASK_KEY(void *p_arg)
描    述：按键拨码读取任务
*******************************************************************************/
void TASK_KEY(void *p_arg)
{
	OS_ERR err;
	
		
	while(1)
	{


		OSTimeDlyHMSM(0, 0, 1, 0,
                      OS_OPT_TIME_HMSM_NON_STRICT,
                      &err);
	}
}
/*******************************************************************************
函 数 名：TASK_PS(void *p_arg)
描    述：手柄读取任务
*******************************************************************************/
void TASK_PS(void *p_arg)
{
	OS_ERR err;
	
	while(1)
	{
      

		OSTimeDlyHMSM(0, 0, 1, 0,
                      OS_OPT_TIME_HMSM_NON_STRICT,
                      &err);
	}
}
/*******************************************************************************
函 数 名：TASK_ADC(void *p_arg)
描    述：红外读取任务
*******************************************************************************/
void TASK_ADC(void *p_arg)
{
	OS_ERR err;
	
	while(1)
	{
      
	  //Set_Speed();
		OSTimeDlyHMSM(0, 0, 0, 20,
                      OS_OPT_TIME_HMSM_NON_STRICT,
                      &err);
        
	}
}