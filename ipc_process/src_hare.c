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

	time_t t;
	srand((unsigned) time(&t));
	struct msgbuf msg2;
	struct msgbuf msg3;	
	int msgid2;
	int msgid3;	
	key_t key2;
	key_t key3;
	int racedist = 100;	
	int offset = racedist*10;
	racedist += offset;		
	if((key2=ftok("src_hare.c",'b'))==-1)
	{
		perror("key2");
		exit(1);
	}
	if ((msgid2=msgget(key2,0644|IPC_CREAT))==-1)
	{
		perror("msgid2");
		exit(1);
	}	
	if((key3=ftok("src_god.c",'b'))==-1)
	{
		perror("key3");
		exit(1);
	}
	if ((msgid3=msgget(key3,0644|IPC_CREAT))==-1)
	{
		perror("msgid3");
		exit(1);
	
	}
	if(msgrcv(msgid3, &msg3,sizeof(msg3),3,0)==-1)
	{
	perror("msgrcv");
	exit(1);
	}

	int flag = 0;
	msg2.mtype=2;
	int hpos = 0;
	while(hpos <= racedist)
	{
	msg2.msgtxt = hpos;
	hpos += 5;
	if( flag = 0 && msg3.msgtxt <= 10 )
	{
	hpos = racedist/2;
	flag = 1;
	}

		if(msgsnd(msgid2, &msg2, sizeof(msg2),0)==-1)
		{
			perror("msgsnd");
			exit(1);
		}
	if (msg2.msgtxt > (racedist-offset)*9/10)
	usleep(rand()%1000000);
	usleep(100000);		
	}
	if(msgctl(msgid2,IPC_RMID,NULL)==-1)
	{
		perror("msgctl");
		exit(1);
	}
	system("ipcrm -q msgid2");
	return 0;
}	
