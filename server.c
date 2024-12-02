
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

struct message {
	char source[50];
	char target[50]; 
	char msg[200]; // message body
};

void terminate(int sig) {
	printf("Exiting....\n");
	fflush(stdout);
	exit(0);
}

int main() {
	int server;
	int target;
	int dummyfd;
	struct message req;
	signal(SIGPIPE,SIG_IGN);
	signal(SIGINT,terminate);
	server = open("serverFIFO",O_RDONLY);
	dummyfd = open("serverFIFO",O_WRONLY);

	while (1) {
		target = open(req.target, O_WRONLY);
		// TODO:
		// read requests from serverFIFO
		if (read(server, &req, sizeof(req)) > 0) {
			printf("Received a request from %s to send the message [%s] to %s.\n",
			req.source, req.msg, req.target);
		}
		//save
		target = open(req.target, O_WRONLY);
		// TODO:
		// open target FIFO and write the whole message struct to the target FIFO
		// close target FIFO after writing the message
		if ((!target) == 0) {
			write(target, &req, sizeof(req));
			close(target);
		}
		else {
			printf("Failed to open target FIFO: %s\n", req.target);
		}
	}
	close(server);
	close(dummyfd);
	return 0;
}

