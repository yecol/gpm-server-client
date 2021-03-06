#include <stdio.h>
#include <stdlib.h>
#include "tcp_server.h"

int main(int argc,char* argv[])
{
	if (argc < 3) {
		printf("argument is not enough!\n");
		printf("argument: 1. port number, eg, 9527\n");
		printf("argument: 2. graph file name\n");
		return -1;
	}
	
	int port = atoi(argv[1]);
        tcp_server ts(port);
	ts.init_graph_index(argv[2]);
        int ret = ts.recv_msg();
	if (ret == 1) ts.clean_up();
        return 0;
}
