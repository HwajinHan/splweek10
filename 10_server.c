#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define MAXLINE 50
#define MAX 200000

int main (int argc, char *argv[]) {
	int n, listenfd, connfd, caddrlen;
	struct hostent *h;
	struct sockaddr_in saddr, caddr;
	char buf[MAXLINE];
	char text[MAX];
	
	char newfilename[MAXLINE+5];
	int port = atoi(argv[1]);

	if ( (listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		printf("socket() failed.\n");
		exit(1);
	}
	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);   
	if ( bind(listenfd,(struct sockaddr*)&saddr,sizeof(saddr)) < 0) {
		printf("bind() failed.\n");
		exit(2);
	}
	if ( listen(listenfd,5) < 0) {
		printf("listen() failed.\n");
		exit(3);
	}

	caddrlen = sizeof(caddr);
	if ((connfd =accept(listenfd,(struct sockaddr*)&caddr,(socklen_t*)&caddrlen)) < 0) {
		printf ("accept() failed.\n");
		exit(4);
	}
	int filesize;
	int fd;
	while (1) {
		char copy[6]="_copy";
		char fname[20]="FILE NAME: ";
		int total = 0;
		memset(buf,0,MAXLINE);
		memset(text,0,MAX); //test.txt
		memset(newfilename,0,MAXLINE+5);
		n = read(connfd, buf, MAXLINE);
		// Receive name of file
		int filename;
	
		if(!strcmp(buf,"quit")){
		    exit(0);
		    break;
		}else{
		strcat(newfilename,buf);
		strcat(newfilename,"_copy");
		memset(copy,0,20);
		write(1,fname,20);
		write(1,newfilename,MAXLINE+5);
		fd=open(newfilename,O_CREAT|O_WRONLY,0644);
		memset(buf,0,MAXLINE);
		n=read(connfd,buf,MAXLINE);
		filesize=atoi(buf);
		n=read(connfd,text,MAX);	
		write(fd,text,n);
		sleep(1);
		close(fd);
		/*** Insert your code ***/
		}
	
	}
	close(connfd);

	return 0;
}
