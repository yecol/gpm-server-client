#include "tcp_client.h"

char *trimwhitespace(char *str) {
	char *end;

	// Trim leading space
	while(isspace(*str)) str++;

	if(*str == 0)  // All spaces?
		return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}


tcp_client::tcp_client(char* server_ip,char* server_port, char*msg1, char*msg2)
{
       if( (socket_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 ) {
                printf("create socket error: %s(errno:%d)\n)",strerror(errno),errno);
                exit(0);
        }

        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(atoi(server_port));

        if( inet_pton(AF_INET,server_ip,&server_addr.sin_addr) <=0 ) {
                printf("inet_pton error for %s\n",server_ip);
                exit(0);
        }

        if( connect(socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0) {
                printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
                exit(0);
        }

        printf("send message to server: \n");
        //fgets(message,4096,stdin);
	sprintf(message, "%s %s\n", msg1, msg2);
        if( send( socket_fd,message,strlen(message),0 ) < 0 ) {
                printf("send message error\n");
                exit(0);
        }
	
	if( read(socket_fd,message,4096) < 0 ) {
                printf("read message error\n");
                exit(0);
        }
	printf("%s\n", message);

        close(socket_fd);
        exit(0);
}

