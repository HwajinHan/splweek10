#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAXLINE 50
#define MAX 200000
int main (int argc, char *argv[]) {
	int n, cfd;
	struct hostent *h;
	struct sockaddr_in saddr;
	char buf[MAXLINE];
	char buff[MAXLINE];
	char context[MAXLINE];
	char text[MAX];
	char *host = argv[1]; //localhost
	int port = atoi(argv[2]); // 10002 example

	if ((cfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		printf("socket() failed.\n"); 
		exit(1);
	}
	if ((h = gethostbyname(host)) == NULL) {
		printf("invalid hostname %s\n", host); 
		exit(2);
	}   
	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *)&saddr.sin_addr.s_addr, (char *)h->h_addr, h->h_length);
	saddr.sin_port = htons(port);
	
	if (connect(cfd,(struct sockaddr*)&saddr,sizeof(saddr)) < 0) {
		printf("connect() failed.\n");
		exit(3);
	}
	int fd;
	while (1) {
		int readbuf;
		memset(buf,0,MAXLINE); 
		memset(text,0,MAX);
		memset(buff,0,MAXLINE);
		memset(context,0,MAXLINE);
		int total = 0;
		n = read(0, buf, MAXLINE); //stdin by me (filename).
		buf[n-1] = '\0';
		write(cfd,buf,n);
		printf("title: %s\n",buf);
		if(!strcmp(buf,"quit")){
		    exit(0);
		    break;
		}else{
		fd=open(buf,O_RDONLY); // open by filename.
		
		while((n=read(fd,context,1))>0){ // read the file data
		    strncat(text,context,1);
		     //send the file one by one byte
		    //write(1,buf,n); //print the file contents
		    total++; //total file size
		}
		text[total-1]='\0';
		sprintf(buff,"%d",total);
		printf("file size: %s Byte\n",buff);
		write(cfd,buff,MAXLINE);
		printf("contentx: %s\n",text);
		write(cfd,text,total);
		close(fd);
		printf("Send %d bytes to the server.\n" , total);
		}
		/*** Insert your code ***/
		
	}
	
	close(cfd);

	return 0;
}


