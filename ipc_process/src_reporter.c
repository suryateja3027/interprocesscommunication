#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>

struct msgbuf
{
	long mtype;
	int msgtxt;
};
int main(void)
{
	struct msgbuf msg1;
	struct msgbuf msg2;

	int msgid1;
	int msgid2;

	key_t key1;
	key_t key2;
	
	int racedist = 100;
	if((key1=ftok("src_turtle.c",'b'))==-1)
	{
		perror("key1");
		exit(1);
	}
	if((key2=ftok("src_hare.c",'b'))==-1)
	{
		perror("key2");
		exit(1);
	}

	if ((msgid1=msgget(key1,0644|IPC_CREAT))==-1)
	{
		perror("msgid1");
		exit(1);
	}
	if ((msgid2=msgget(key2,0644|IPC_CREAT))==-1)
	{
		perror("msgid2");
		exit(1);
	}

	for(;;)
	{
	if(msgrcv(msgid1, &msg1,sizeof(msg1),1,0)==-1)
	{
	perror("msgrcv");
	exit(1);
	}
	if(msgrcv(msgid2, &msg2,sizeof(msg2),2,0)==-1)
	{
	perror("msgrcv");
	exit(1);
	}

	if(msg1.msgtxt < 100+1 && msg2.msgtxt< 100+5 ){
	printf("turtle distance is %d\n",msg1.msgtxt);
	printf("hare distance is %d\n",msg2.msgtxt);
	}
	else
	{
	if(msg1.msgtxt > msg2.msgtxt){
	printf("Turtle won the race");
	exit(0);
	}
	else{
	printf("Hare won the race");
	exit(0);
	}

	}
	}
	system("ipcrm -q msgid1");
	system("ipcrm -q msgid2");
	return 0;
}
