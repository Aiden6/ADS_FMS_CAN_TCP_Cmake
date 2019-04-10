#ifndef _BYD_CONTROL_THREAD_H_
#define _BYD_CONTROL_THREAD_H_
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

#include "./byd/api_test.h"
#include "./byd/controlcan.h"
#include "./byd/idriving_api.h"
#include "./byd/std_types.h"
#include "./control.h"

/** Global variables **/  
extern int32_t  gTestFlag;
extern uint8_t  driving_mode;
extern int8_t   gCharInput[STRING_LEN];
extern sem_t    sem_event;
extern sem_t    sem_event_SetAcceleratedVelocity;
extern sem_t    sem_event_SetAngular;
extern sem_t    sem_event_SetCarGear;
extern sem_t    sem_event_SetEpbState;
extern sem_t    sem_event_SetDrivingMode;


#define RX_WAIT_TIME    100
#define RX_BUFF_SIZE    1000
#define TIME_PERIOD     10*1000*1000

extern CAN_DEV_INFO device;

extern double nAngular;
extern double AccVal;
extern uint8_t CarGear_val;
extern uint8_t CarEpb_val;
extern uint8_t DrivingMode_val;


void* can_rcvThread( void *data );
void  can_xmt(union sigval v);
void* cm_rcvThread( void *data);
void* acu_ctrlThread( void *data );
void* acu_SetAcceleratedVelocity_Thread( void *data );
void* acu_SetAngular_Thread( void *data );
void* acu_CarGear_Thread( void *data );
void* acu_SetEpbState_Thread( void *data );
void* acu_SetDrivingMode_Thread( void *data );
void Timer10ms( timer_t *timer );
int32_t BydAuto_Can_Connect( void );

#endif