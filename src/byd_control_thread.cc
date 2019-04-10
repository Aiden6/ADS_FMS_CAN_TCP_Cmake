#include "../include/byd_control_thread.h"

/*****************************************************************************
  函数名称:       void* can_rcvThread( void *data )
  说明:           CAN原始报文接收的线程，并传递给API封装一个接口供ECU获取
  调用:
  被调用:
  输入参数:       *data 			

  输出参数:       
  返回值:         void*
  被访问变量:
  被修改变量:
  其他:           用于查询接收到的CAN报文    
*****************************************************************************/
void* can_rcvThread( void *data )
{
    CAN_DEV_INFO *pCAN_Info = (CAN_DEV_INFO *)data;

    VCI_CAN_OBJ can[RX_BUFF_SIZE]; // buffer
    int cnt;                       // current received

    while (gTestFlag) {
       // msleep(10);
        cnt = VCI_Receive(pCAN_Info->devType, pCAN_Info->devIndex,                         
                          pCAN_Info->channelNum, can, RX_BUFF_SIZE, RX_WAIT_TIME);
        if (!cnt)
            continue;
        // Developer API test
        BydAuto_DeveloperAPI_ReceiveTest(can, cnt);
    }
    printf("can_rcvThread End.\n");
    pthread_exit(0);

    return 0;
}


/*****************************************************************************
  函数名称:       void* can_xmt( void )
  说明:           将要发的报文封装，并通过CAN报文发送的线程
  调用:
  被调用:
  输入参数:       void 			

  输出参数:       
  返回值:         void*
  被访问变量:
  被修改变量:
  其他:           用于定时对外CAN报文    
*****************************************************************************/
void can_xmt(union sigval v)
{
	VCI_CAN_OBJ canObj;
	int loop;
    static uint32_t Count = 0;
   
    // Developer API test
	canObj.DataLen = 0;
    canObj.ExternFlag = 1;
    canObj.RemoteFlag = 0;
    uint32_t MessageId[4] = {
					 //保证10ms：BYD_AUTO_IDRIVING_CMD_0优先发送
                     BYD_AUTO_IDRIVING_CMD_0,   //10ms
					 BYD_AUTO_IDRIVING_CMD_1,   //20ms
					 BYD_AUTO_IDRIVING_CMD_2,   //20ms
					 //BYD_AUTO_IDRIVING_CMD_3,
					 //BYD_AUTO_IDRIVING_CMD_4, 
					 BYD_AUTO_IDRIVING_CMD_5    //100ms
	};

    for (loop = 0; loop < 4; loop++) {
        if (BydAuto_DeveloperAPI_TransmitTest(MessageId[loop],
                                                  Count,
                                                  &canObj)) {
            /* Transmit the can message */
            VCI_Transmit(device.devType, device.devIndex, 
                         device.channelNum, &canObj, 1);
		}
	}
	if (10 == Count) {
		Count = 0;
	}
	Count++;

 //   return 0;
}

/*****************************************************************************
  函数名称:       void* cm_rcvThread( void *data)
  说明:           获取键盘命令输入
  调用:

  被调用:
  输入参数:       void 			

  输出参数:       
  返回值:         void*
  被访问变量:
  被修改变量:
  其他:           根据约定的规则对键盘输入进行判断
*****************************************************************************/
void* cm_rcvThread( void *data)
{
    int8_t tmp_char, char_cnt = 0;
    int8_t *pChar = &gCharInput[1];
	for (;;) {  
        tmp_char = getchar();
        if ('\n' != tmp_char) {

            *pChar++ = tmp_char;
            char_cnt++;

            if (27 == gCharInput[1]) {  // ESC
                sem_post(&sem_event);
                break;          
            }
        }
        else {
            gCharInput[0] = char_cnt;
            char_cnt = 0;
            pChar = &gCharInput[1];
            sem_post(&sem_event);
        }
        
    }
    printf("cm_rcvThread End.\n");
    pthread_exit(0);
	return 0;
}

//自动驾驶操作
/*****************************************************************************
  函数名称:       void* acu_ctrlThread( void *data )
  说明:           ACU控制操作的线程
  调用:

  被调用:
  输入参数:       *data 			

  输出参数:       
  返回值:         void*
  被访问变量:
  被修改变量:
  其他:           通过API对各执行机构进行控制以及获取整车状态值
*****************************************************************************/

void* acu_ctrlThread( void *data )
{
    while (gTestFlag) {
        DeveloperAPI_TestItemDisplay();
        sem_wait(&sem_event);
        // Developer API test
        BydAuto_DeveloperAPI_ControlTest(gCharInput);      
    }
    printf("acu_ctrlThread End.\n");
    pthread_exit(0);
    return 0;
}

void* acu_SetAcceleratedVelocity_Thread( void *data )
{
    while (gTestFlag) {
        //DeveloperAPI_TestItemDisplay();
        sem_wait(&sem_event_SetAcceleratedVelocity);
        SetAcceleratedVelocity_BYD(AccVal); 
    }
    printf("SetAcceleratedVelocity_Thread.\n");
    pthread_exit(0);
    return 0;
}

void* acu_SetAngular_Thread( void *data )
{
    while (gTestFlag) {
        //DeveloperAPI_TestItemDisplay();
        sem_wait(&sem_event_SetAngular);
        SetAngular_BYD(nAngular);
    }
    printf("SetAngular_Thread End.\n");
    pthread_exit(0);

    return 0;
}
void* acu_CarGear_Thread( void *data )
{
    while (gTestFlag) {
        //DeveloperAPI_TestItemDisplay();
        sem_wait(&sem_event_SetCarGear);
        SetCarGear_BYD(CarGear_val);
    }
    printf("CarGear_Thread End.\n");
    pthread_exit(0);

    return 0;
}
void* acu_SetEpbState_Thread( void *data )
{
    while (gTestFlag) {
        //DeveloperAPI_TestItemDisplay();
        sem_wait(&sem_event_SetEpbState);
        SetEpbState_BYD(CarEpb_val );
    }
    printf("SetEpbState_Thread End.\n");
    pthread_exit(0);

    return 0;
}
void* acu_SetDrivingMode_Thread( void *data )
{
    while (gTestFlag) {
        //DeveloperAPI_TestItemDisplay();
        sem_wait(&sem_event_SetDrivingMode);
        SetDrivingMode_BYD(DrivingMode_val);
    }
    printf("SetDrivingMode_Thread End.\n");
    pthread_exit(0);
    return 0;
}

/*****************************************************************************
  函数名称:       void Timer10ms( timer_t *timer )
  说明:           
  调用:

  被调用:
  输入参数:       *timer 			

  输出参数:       
  返回值:         void
  被访问变量:
  被修改变量:
  其他:           
*****************************************************************************/
void Timer10ms( timer_t *timer )
{
	int ret;	
	struct sigevent evp10ms;
	struct itimerspec ts10ms;

	memset(&evp10ms,0,sizeof(evp10ms));
	evp10ms.sigev_value.sival_ptr = timer;
	evp10ms.sigev_notify = SIGEV_THREAD;
	evp10ms.sigev_notify_function = can_xmt;//绑定CAN报文发送

    ret = timer_create(CLOCK_REALTIME,&evp10ms,timer);
	if(ret)
		printf("the timer10ms create error!\n");
	ts10ms.it_interval.tv_sec = 0;
	ts10ms.it_interval.tv_nsec = TIME_PERIOD;
	ts10ms.it_value.tv_sec = 0;
	ts10ms.it_value.tv_nsec = TIME_PERIOD;
	ret = timer_settime(*timer,TIMER_ABSTIME,&ts10ms,NULL);
	if(ret)
		printf("timer10s time_setting error!\n");
	return;
}

/*****************************************************************************
  函数名称:       int32_t BydAuto_Can_Connect( void )
  说明:           CAN卡配置
  调用:

  被调用:
  输入参数:       void 			

  输出参数:       
  返回值:         void
  被访问变量:
  被修改变量:
  其他:           
*****************************************************************************/
int32_t BydAuto_Can_Connect( void )
{
    int32_t  devType = VCI_USBCAN2;        //CAN卡类型
    int32_t  devIndex = 0;
    int32_t  channelNum = 0;               //CAN通道

    device.devType = devType;              //CAN卡配置
    device.devIndex = devIndex;
    device.channelNum = channelNum;

    VCI_INIT_CONFIG config;                //CAN初始化结构体
    config.AccCode = 0;
    config.AccMask = 0xffffffff;
    config.Filter = 1;
    config.Mode = 0;
    config.Timing0 = 0xC0;
    config.Timing1 = 0x3A;  // 500 kbps

    //打开CAN卡
    if (!VCI_OpenDevice(devType, devIndex, 0)) {
        printf("VCI_OpenDevice failed\n");
        return 0;
    }
    printf("VCI_OpenDevice succeeded\n");
    //初始化CAN卡
    if (!VCI_InitCAN(devType, devIndex, channelNum, &config)) {
        printf("VCI_InitCAN failed\n");
        return 0;
    }
    //开始CAN接收
    if (!VCI_StartCAN(devType, devIndex, channelNum)) {
        printf("VCI_InitCAN failed\n");
        return 0;
    }
	return 1;
}
