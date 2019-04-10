#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>
#include <iostream>
#include <boost/asio.hpp>
#include <math.h>
//#include <curses.h>
//#include <ros/ros.h>
//#include <std_msgs/String.h>

////////////////////////////////for BYD/////////////////////////////
#include "./include/byd/api_test.h"
#include "./include/byd/controlcan.h"
#include "./include/byd/idriving_api.h"
#include "./include/byd/std_types.h"
#include "./include/control.h"
#include "./include/byd_control_thread.h"
//////////////////////////////for FMS//////////////////////////////
#include "./include/async_client.h"
#include "./include/boost_tcp_client.h"
#include "./include/message_define.h"
#include "./include/message_encrypt.h"
#include "./include/ads_message.h"
#include "./include/TCP_callback.h"
///////////////////////////////////////////////////////////////////
using namespace	std;
using namespace boost::asio;
//////////////////////////////Apollo//////////////////////////////

bool isRoutingRecv = false;
bool isAutoDrivingStarted = false;

bool isArrval = false;
uint32_t iCounts = 0;
uint32_t iStandCounts = 0;

// rolling counts
uint32_t iRollingCounts = 0;

////////////////////////////for BYD QinPro////////////////////////////
/** Macros **/
#define RX_WAIT_TIME    100
#define RX_BUFF_SIZE    1000
#define TIME_PERIOD     10*1000*1000

/** Global variables **/  
int32_t  gTestFlag = 0;
uint8_t  driving_mode = NORMAL_MODE;
int8_t   gCharInput[STRING_LEN];
sem_t    sem_event;
sem_t    sem_event_SetAcceleratedVelocity;
sem_t    sem_event_SetAngular;
sem_t    sem_event_SetCarGear;
sem_t    sem_event_SetEpbState;
sem_t    sem_event_SetDrivingMode;

CAN_DEV_INFO device;
////////////////////////////for VCM////////////////////////////////////
// tcp session object
Async_Client *client = NULL; 

/////////////////////////Global variable//////////////////////////////
double nAngular = 0;
double AccVal = 0;
uint8_t CarGear_val = 0;
uint8_t CarEpb_val = 0;
uint8_t DrivingMode_val = 0;


/*****************************************************************************
  函数名称:       int32_t main( void )
  说明:           主函数
  调用:
  被调用:
  输入参数:       void 			
  输出参数:       
  返回值:         状态 
  被访问变量:
  被修改变量:
  其他:          
*****************************************************************************/
int32_t main(int argc, char *argv[])
{
    printf("TCP is connecting..\n\n");
	boost_tcp_init_connection("212.64.55.44", 9001, &client, CallBackRead); 
    
    ads_message adsMsg_0x0101(securityType,applicationID_0x0101,ipcID,messageID_0x0101,messageData_0x0101,messageDataLength_0x0101,
					   isLogin_0x0101);
	boost_tcp_sync_send(client, adsMsg_0x0101.messageComplete_, adsMsg_0x0101.messageLength_); 

	printf("IPC is requesting to login...\n\n");

	usleep(500 * 1000); //wait for read-thread finishing parsing data
	iRollingCounts = 0;
////////////////////////////////////////////BYD//////////////////////////////////////////////

    //for BYD timer
    timer_t timer10ms;
	//for BYD thread
	pthread_t cm_thread;
    pthread_t rx_thread;
	pthread_t ctrl_thread;
    pthread_t SetAcceleratedVelocity_thread;
    pthread_t SetAngular_thread;
    pthread_t SetCarGear_thread;
    pthread_t SetEpbState_thread;
    pthread_t SetDrivingMode_thread;

    /* ==================================== */
    /*            start to test             */
    /* ==================================== */
	BydAuto_Can_Connect();            //周立功CAN卡相关操作
    BydAuto_DeveloperAPI_Start();     //BYD 秦Pro API初始化
    DeveloperAPI_AutoDrive_Init();    //进入智能驾驶的初始信号 目前为正常驾驶模式，关闭横纵向控制，正常模式反馈，加速度 角度为0

    gTestFlag = 1;

    /* create samaphore */
    sem_init(&sem_event, 0, 0);
	sem_init(&sem_event_SetAcceleratedVelocity, 0, 0);
	sem_init(&sem_event_SetAngular, 0, 0);
	sem_init(&sem_event_SetCarGear, 0, 0);
	sem_init(&sem_event_SetEpbState, 0, 0);
	sem_init(&sem_event_SetDrivingMode, 0, 0);

    //获取键盘键值线程
    /* create CM-threads */
    pthread_create(&cm_thread, NULL, &cm_rcvThread, NULL);
    //CAN报文接收线程
	/* create RX-threads  */
    pthread_create(&rx_thread, NULL, &can_rcvThread, &device);
    //CAN报文发送定时器
	/* create Tx-timer  */
	Timer10ms(&timer10ms);
    //控制执行线程
    /* create Control-threads  */
	pthread_create(&ctrl_thread, NULL, &acu_ctrlThread, NULL);
    pthread_create(&SetAcceleratedVelocity_thread, NULL, &acu_SetAcceleratedVelocity_Thread, NULL);
    pthread_create(&SetAngular_thread, NULL, &acu_SetAngular_Thread, NULL);
    pthread_create(&SetCarGear_thread, NULL, &acu_CarGear_Thread, NULL);
    pthread_create(&SetEpbState_thread, NULL, &acu_SetEpbState_Thread, NULL);
    pthread_create(&SetDrivingMode_thread, NULL, &acu_SetDrivingMode_Thread, NULL);


/////////////////////////////////////////////////////////////////////////////////////////////
    /* waiting */
    for(;;)
	{
        iRollingCounts ++ ;

		printf("iRollingCounts: %d... ", iRollingCounts);
		printf("waiting for FMS command... \n");
	
		if (isRoutingRecv) {
			// initialization
			iCounts = 0;
			iStandCounts = 0;
			isArrval = false;

			// routing command received
			printf("received FMS planning command, start autonomous driving... \n");
			
			if(isAutoDrivingStarted) {
				printf("is in autonomous driving, path planning error... \n");
			}
			else {
				printf("starting autonomous driving... \n");

				usleep(10* 1000 * 1000); // waiting 1000ms

	
				isAutoDrivingStarted =  true;
				isRoutingRecv = false; // avoid repeated threads open 

			}
			cout << iRollingCounts;
			isAutoDrivingStarted = false;
		}

		usleep(1000 * 1000); // waiting 1000ms
         if (27 == gCharInput[1]) {  // ESC
            sem_post(&sem_event);
			//sem_post(&sem_event_SetAcceleratedVelocity);
            break; 	
		}
	}

    //BYD test
	/* end to test */
    gTestFlag = 0;
    msleep(200);
    
    /* destroy samaphore */
    sem_destroy(&sem_event);
    sem_destroy(&sem_event_SetAcceleratedVelocity);
    sem_destroy(&sem_event_SetAngular);
    sem_destroy(&sem_event_SetCarGear);
    sem_destroy(&sem_event_SetEpbState);
    sem_destroy(&sem_event_SetDrivingMode);


	/* shut down the threads */
	pthread_cancel(cm_thread);
	pthread_join(cm_thread,NULL);

	pthread_cancel(rx_thread);
	pthread_join(rx_thread,NULL);

	pthread_cancel(ctrl_thread);
	pthread_join(ctrl_thread,NULL);

	pthread_cancel(SetAcceleratedVelocity_thread);
	pthread_join(SetAcceleratedVelocity_thread,NULL);

	pthread_cancel(SetAngular_thread);
	pthread_join(SetAngular_thread,NULL);

	pthread_cancel(SetCarGear_thread);
	pthread_join(SetCarGear_thread,NULL);

	pthread_cancel(SetEpbState_thread);
	pthread_join(SetEpbState_thread,NULL);

	pthread_cancel(SetDrivingMode_thread);
	pthread_join(SetDrivingMode_thread,NULL);

	/* delete the timer */
	timer_delete(timer10ms);
	/* close the can devices*/
    VCI_CloseDevice(device.devType, device.devIndex);
    printf("VCI_CloseDevice\n"); 
	return 0;






}

