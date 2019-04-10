
#ifndef _TCP_CALLBAKCk_H_
#define _TCP_CALLBAKCk_H_

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

#include "./message_encrypt.h"
#include "./ads_message.h"
#include "./async_client.h"

using namespace std;

// tcp session object
extern Async_Client *client;

// login result
char sessionKey[17] = "";
char sessionIv[17] = "";

extern bool isRoutingRecv;

extern sem_t sem_event_SetAcceleratedVelocity;
extern sem_t sem_event_SetAngular;
extern sem_t sem_event_SetCarGear;
extern sem_t sem_event_SetEpbState;
extern sem_t sem_event_SetDrivingMode;


//extern Global variable
extern double nAngular;
extern double AccVal;
extern uint8_t CarGear_val;
extern uint8_t CarEpb_val;
extern uint8_t DrivingMode_val;

string 		ipcID("10000000000000001");     // IPCID
uint8_t 	securityType 		    = 1; 		// AES     //0:no encrypt;1:AES


//0x0101
//IPC login to FMS Server parameters
uint16_t 	applicationID_0x0101        = 0x0101; 	// login   //IPC log in Application
//Dispatcher
uint16_t	messageID_0x0101	        = 1;
//Application Data
string		messageData_0x0101("123456789");

uint16_t	messageDataLength_0x0101   	= 9;
bool		isLogin_0x0101  	        = true;


//0x0108
uint16_t 	applicationID_0x0102 		= 0x0102; 	
//Dispatcher
uint16_t	messageID_0x0102			= 2;
//Application Data
string		messageData_0x0102("00");

uint16_t	messageDataLength_0x0102 	= 2;
bool		isLogin_0x0102  	        = false;


//0x0108
uint16_t 	applicationID_0x0108 		= 0x0108; 	
//Dispatcher
uint16_t	messageID_0x0108			= 2;
//Application Data
string		messageData_0x0108("00");

uint16_t	messageDataLength_0x0108 	= 2;
bool		isLogin_0x0108  	        = false;


//0x0109
uint16_t 	applicationID_0x0109 		= 0x0109; 	
//Dispatcher
uint16_t	messageID_0x0109			= 2;
//Application Data
string		messageData_0x0109("00");

uint16_t	messageDataLength_0x0109 	= 2;
bool		isLogin_0x0109  	        = false;


//0x010A
uint16_t 	applicationID_0x010A 		= 0x010A; 	
//Dispatcher
uint16_t	messageID_0x010A			= 2;
//Application Data
string		messageData_0x010A("00");

uint16_t	messageDataLength_0x010A 	= 2;
bool		isLogin_0x010A  	        = false;

//0x010B
uint16_t 	applicationID_0x010B 		= 0x010B; 	
//Dispatcher
uint16_t	messageID_0x010B			= 2;
//Application Data
string		messageData_0x010B("0000");

uint16_t	messageDataLength_0x010B 	= 4;
bool		isLogin_0x010B  	        = false;

void CallBackRead(const char* addr, int port, const char* data, const int len);

#endif