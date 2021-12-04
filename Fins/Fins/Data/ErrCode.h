#pragma once


#define FINS_CODE			1800

#define FINS_SOCKET_CONNECT_FAIL				1  + FINS_CODE	/* FINS TCP����ʧ�� */	
#define FINS_SOCKET_CREATE_FAIL					2  + FINS_CODE	/* FINS SOCKET����ʧ�� */
#define FINS_SOCKET_CONNECT_ERR					3  + FINS_CODE	/* FINS TCP/IPͨѶ������������Ƿ�Ͽ������ȶ� */
#define FINS_MALLOC_FAIL						3  + FINS_CODE	/* FINS �����ڴ�ʧ�ܣ�ϵͳ�ڴ治�� */
#define FINS_PARAM_POINT_ENTPY					4  + FINS_CODE	/* FINS ����ָ��Ϊ�� */
#define FINS_SEND_TIMEOUT						10 + FINS_CODE	/* FINS ���ͳ�ʱ */
#define FINS_SEND_FAIL							11 + FINS_CODE	/* FINS ����ʧ�� */
#define FINS_RECV_WAIT_TIMEOUT					12 + FINS_CODE	/* FINS �ȴ����ճ�ʱ */	
#define FINS_REPLY_DATA_TOO_SHORT				20 + FINS_CODE	/* FINS �𸴵�����̫�̣������PLC�Ƿ����� */	
#define FINS_REQUST_CONNECT_FAIL				21 + FINS_CODE	/* FINS ������ͨѶʧ�ܣ�������PLC���߲���PLCͨѶ */			
#define FINS_NOT_DATA_AREA						22 + FINS_CODE	/* FINS û�ж�Ӧ�������� */	
#define FINS_REPLY_ERROR_BY_MESSAGE				25 + FINS_CODE	/* FINS ������Ϣ��PLC����Ϣ������� */	
#define FINS_REPLY_READ_DATA_TOO_SHORT			26 + FINS_CODE	/* FINS �𸴵Ķ�ȡ����̫�̣�������Э�� */	
#define FINS_REPLY_WRITE_DATA_TOO_SHORT			27 + FINS_CODE	/* FINS �𸴵�д������̫�̣�������Э�� */
#define FINS_REPLY_READ_DATA_FAIL				28 + FINS_CODE	/* FINS �𸴶�ȡ����ʧ�� */	
#define FINS_REPLY_WRITE_DATA_FAIL				29 + FINS_CODE	/* FINS ��д������ʧ�� */
#define FINS_REPLY_CMD_NO_IS_REQUST_CMD			30 + FINS_CODE	/* FINS �𸴵�command�ͷ��͵�command��һ�� */












