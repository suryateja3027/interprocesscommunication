#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include <unistd.h>
#include <time.h>

struct msgbuf
{
	long mtype;
	int msgtxt;
};
int main(void)
{	

	struct msgbuf msg1;
	int msgid1;
	key_t key1;
	int racedist = 100;
	int offset = racedist*10;
	racedist += offset;	
	srand(time(0));
	if((key1=ftok("src_turtle.c",'b'))==-1)
	{
		perror("key1");
		exit(1);
	}
	if ((msgid1=msgget(key1,0644|IPC_CREAT))==-1)
	{
		perror("msgid1");
		exit(1);
	}

	msg1.mtype=1;
	int tpos = 0;
	while(tpos <= racedist)
	{
	msg1.msgtxt = tpos;

	usleep(100000);
		if(msgsnd(msgid1, &msg1, sizeof(msg1),0)==-1)
		{
			perror("msgsnd");
			exit(1);
		}
	tpos += 1;
	tpos = tpos + (int) (rand()%10);		
	}
	if(msgctl(msgid1,IPC_RMID,NULL)==-1)
	{
		perror("msgctl");
		exit(1);
	}
	return 0;
	system("ipcrm -q msgid1");
}
