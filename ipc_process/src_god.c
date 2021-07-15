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
	struct msgbuf msg3;
	int msgid3;
	key_t key3;
	srand(time(0));



int exit_status1 = system("gnome-terminal --window-with-profile=test -- ./o_reporter");
//gnome-terminal --window-with-profile=NAMEOFTHEPROFILE -- command
int exit_status2 = system("gnome-terminal -- ./o_turtle");
int exit_status3 = system("gnome-terminal -- ./o_hare");

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
	msg3.mtype=3;

	msg3.msgtxt = rand();
	
	if(msgsnd(msgid3, &msg3, sizeof(msg3),0)==-1)
		{
			perror("msgsnd");
			exit(1);
		}	
	
	if(msgctl(msgid3,IPC_RMID,NULL)==-1)
	{
		perror("msgctl");
		exit(1);
	}

return 0;
}
