
#include <iostream>
#include<unistd.h>//unix stand lib
#include<sys/types.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>//file dir
#include <sys/wait.h>//wait func
#include <stdlib.h>//ststem
#include <signal.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

typedef struct
{
	long mtype;
	char message[50];
}MSG_DATA;


//========================================queue===============
int main(int argc, char *argv[])
{
	int msg_id;
	msg_id = msgget((key_t)13579, IPC_CREAT | 0666);
	if (msg_id == -1)
	{
		perror("msgget error:");
		return -1;
	}
	
	MSG_DATA msginfo;
	bzero(&msginfo,sizeof(msginfo));//清空用于接收
	
	if (msgrcv(msg_id, &msginfo, sizeof(msginfo.message), 5, IPC_NOWAIT) == -1)//msgrcv接收,mtype和发送的mtype不一样也可以收到
	{
		perror("message recv error:");
		return -1;
	}
	
	cout << "message recv " << msginfo.message<< endl;
	return 0;
}
