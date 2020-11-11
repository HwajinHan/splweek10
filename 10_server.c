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
	char buff[MAXLINE];
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
	int count=0;
	while (1) {
		int total = 0;
		memset(buf,0,MAXLINE); // test.txt
		memset(text,0,MAX); // contents
		memset(newfilename,0,MAXLINE+5); // new filename
		memset(buff,0,MAXLINE); // size of file
		n=read(connfd,buf,MAXLINE);
		 // test.txt
		// Receive name of file
		int filename;	
		printf("title: %s\n", buf);
		if(!strcmp(buf,"quit")){
		    exit(0);
		    break;
		}else{
		strcat(buf,"_copy"); // test.txt_copy
		strcat(newfilename,buf);
		fd=open(newfilename,O_CREAT|O_WRONLY,0644);
		printf("new filename: %s\n",newfilename);
		memset(buf,0,MAXLINE);
		n=read(connfd,buff,MAXLINE);
		printf("filesize: %s\n", buff);
		filesize=atoi(buff);
		printf("Got %d bytes received from client.\n",filesize);
		n=read(connfd,text,MAX);
		printf("contents: %s\n",text);
		write(fd,text,filesize);
		sleep(5);
		count++;
		close(fd);
		/*** Insert your code ***/
		}
	
	}
	close(connfd);

	return 0;
}
