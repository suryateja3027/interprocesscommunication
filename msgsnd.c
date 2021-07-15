#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include <unistd.h>

struct msgbuf
{
	long mtype;
	int msgtxt;
};
int main(void)
{	
	int racedist = 100;
	struct msgbuf msg;
	int msgid;
	key_t key;
	if((key=ftok("msgsnd.c",'b'))==-1)
	{
		perror("key");
		exit(1);
	}
	if ((msgid=msgget(key,0644|IPC_CREAT))==-1)
	{
		perror("msgid");
		exit(1);
	}
	printf("\n the msgid is %d",msgid);
	printf("enter the text");
	msg.mtype=1;
	int tpos = 0;
	
	while(tpos <= racedist)
	{
	msg.msgtxt = tpos;
	tpos += 1;
	usleep(100000);
		if(msgsnd(msgid, &msg, sizeof(msg),0)==-1)
		{
			perror("msgsnd");
			exit(1);
		}
	}
	if(msgctl(msgid,IPC_RMID,NULL)==-1)
	{
		perror("msgctl");
		exit(1);
	}
	return 0;
}
