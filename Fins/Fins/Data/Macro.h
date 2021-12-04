#pragma once

// TCP命令
#define FINS_TCP_CMD_CONNECT_REQUST			0
#define FINS_TCP_CMD_CONNECT_RESPONSE 		1
#define FINS_TCP_CMD_DATA					2


// 数据长度
#define FINS_TCP_HEAD_SIZE					16					// TCP头长度		
#define FINS_CONTROL_HEAD_SIZE				12					// TCP头长度	

#define FINS_MEMORY_AREA_READ_SIZE			6					// 内存读取区长度	
#define FINS_MEMORY_AREA_READ_FIX_R_SIZE	2					// 内存读取区固定答复长度	

#define FINS_MEMORY_AREA_WRITE_FIX_SIZE		6					// 内存写入区固定长度	
#define FINS_MEMORY_AREA_WRITE_R_SIZE		2					// 内存写入区答复长度

#define FINS_CONNECT_REQUST_SIZE			4					// FINIS 通讯请求长度
#define FINS_CONNECT_RESPONS_SIZE			8					// FINIS 通讯请求答复长度



















