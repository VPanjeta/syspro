#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 128

typedef struct msgbuf
{
	long mtype; //message type
	char mtext[SIZE]; //message
}msgbuf;

int main(int argc,char* argv[])
{
	int msgid ; 
	key_t key;
	int n , fd;
	msgbuf buffer;
	char text[SIZE];

	key = 1234;

	msgid = msgget(key,IPC_CREAT|0777);

	buffer.mtype = 1;

	msgrcv(msgid,&buffer,SIZE,1,0);

	fd = open(buffer.mtext,O_RDWR,0777);
	
	n = read(fd,text,SIZE);
	write(STDOUT_FILENO,text,n);
}
