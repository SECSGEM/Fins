#pragma once


#define FINS_CODE			1800

#define FINS_SOCKET_CONNECT_FAIL				1  + FINS_CODE	/* FINS TCP连接失败 */	
#define FINS_SOCKET_CREATE_FAIL					2  + FINS_CODE	/* FINS SOCKET创建失败 */
#define FINS_SOCKET_CONNECT_ERR					3  + FINS_CODE	/* FINS TCP/IP通讯出错，检查网线是否断开、不稳定 */
#define FINS_MALLOC_FAIL						3  + FINS_CODE	/* FINS 申请内存失败，系统内存不足 */
#define FINS_PARAM_POINT_ENTPY					4  + FINS_CODE	/* FINS 参数指针为空 */
#define FINS_SEND_TIMEOUT						10 + FINS_CODE	/* FINS 发送超时 */
#define FINS_SEND_FAIL							11 + FINS_CODE	/* FINS 发送失败 */
#define FINS_RECV_WAIT_TIMEOUT					12 + FINS_CODE	/* FINS 等待接收超时 */	
#define FINS_REPLY_DATA_TOO_SHORT				20 + FINS_CODE	/* FINS 答复的数据太短，请测试PLC是否正常 */	
#define FINS_REQUST_CONNECT_FAIL				21 + FINS_CODE	/* FINS 请求建立通讯失败，请重启PLC或者测试PLC通讯 */			
#define FINS_NOT_DATA_AREA						22 + FINS_CODE	/* FINS 没有对应的数据区 */	
#define FINS_REPLY_ERROR_BY_MESSAGE				25 + FINS_CODE	/* FINS 发送消息后，PLC答复消息错误代码 */	
#define FINS_REPLY_READ_DATA_TOO_SHORT			26 + FINS_CODE	/* FINS 答复的读取数据太短，不符合协议 */	
#define FINS_REPLY_WRITE_DATA_TOO_SHORT			27 + FINS_CODE	/* FINS 答复的写入数据太短，不符合协议 */
#define FINS_REPLY_READ_DATA_FAIL				28 + FINS_CODE	/* FINS 答复读取数据失败 */	
#define FINS_REPLY_WRITE_DATA_FAIL				29 + FINS_CODE	/* FINS 答复写入数据失败 */
#define FINS_REPLY_CMD_NO_IS_REQUST_CMD			30 + FINS_CODE	/* FINS 答复的command和发送的command不一致 */












