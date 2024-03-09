#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

typedef struct 
{
    long mtype;
    char msg_data[50];
}MSG_DATA;



int main(int argc, char *argv[])
{
    int msg_id;
    msg_id = msgget((key_t)13579, IPC_CREAT | 0666);
    if (msg_id == -1)
    {
        perror("msgget error");
    }

    MSG_DATA msginfo;
    msginfo.mtype = 2;
    msginfo.msg_data[0] = 1;
    msginfo.msg_data[2] = 2;
    msginfo.msg_data[3] = 3;
    msginfo.msg_data[1] = 1;
    //strcpy(msginfo.msg_data, "hello message");

    if (msgsnd(msg_id, &msginfo, sizeof(msginfo.msg_data), 0) == -1)
    {
        perror("message send error:");
    }

    cout << "message send success" << endl;

    return 0;
}
