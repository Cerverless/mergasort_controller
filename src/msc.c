#include "msc.h"

/**
 * @brief Called when a client connects to the server.
 *
 * @param client Client connection. The @p client parameter is used
 * in order to send messages and retrieve informations about the
 * client.
 */
void onopen(ws_cli_conn_t *client)
{
	char *cli, *port;
	cli  = ws_getaddress(client);
	port = ws_getport(client);
#ifdef DEBUG
	printf("Connection opened, addr: %s, port: %s\n", cli, port);
#endif
}

/**
 * @brief Called when a client disconnects to the server.
 *
 * @param client Client connection. The @p client parameter is used
 * in order to send messages and retrieve informations about the
 * client.
 */
void onclose(ws_cli_conn_t *client)
{
	char *cli;
	cli = ws_getaddress(client);
#ifdef DEBUG
	printf("Connection closed, addr: %s\n", cli);
#endif
}

void write_to_file (const char* path, const char* word)
{
	FILE *fptr;

	fptr = fopen(path, "w");

	fprintf(fptr, word);
	fprintf(fptr, "\n");

	fclose(fptr); 
	return ;
}		

/**
 * @brief Called when a client connects to the server.
 *
 * @param client Client connection. The @p client parameter is used
 * in order to send messages and retrieve informations about the
 * client.
 *
 * @param msg Received message, this message can be a text
 * or binary message.
 *
 * @param size Message size (in bytes).
 *
 * @param type Message type.
 */
void onmessage(ws_cli_conn_t *client,
		const unsigned char *msg, uint64_t size, int type)
{
	char *cli;
	cli = ws_getaddress(client);
	char result[MAX_RESULT_MSG];

	int message_nr = atoi(strtok(msg, DATA_DELIMITER));
	char* job_nr = strtok(NULL, DATA_DELIMITER);
	char* word_nr = strtok(NULL, DATA_DELIMITER);
	char* word = strtok(NULL, DATA_DELIMITER);

#ifdef DEBUG
	printf("I received the following: message: %d, job_nr: %s, word_nr: %s, word: %s\n",
			message_nr, job_nr, word_nr, word);
#endif
	if (message_nr == MSG_ADD_WORD) { 
		char file_path[20];  // TODO calculate length of file_path based on max amounts of elements that can be sorted
		sprintf(file_path, "%s%s_1_%s", PATH_PREFIX, job_nr, word_nr);
		write_to_file(file_path, word);
		sprintf(result, "%d", RESULT_OK); 
	} else if (message_nr == MSG_GET_STATUS) {
		sprintf(result, "%d", JOB_DONE); 
	} else {
		sprintf(result, "%d", RESULT_UNKOWN_MESSAGE); 
	}


	/**
	 * Mimicks the same frame type received and re-send it again
	 *
	 * Please note that we could just use a ws_sendframe_txt()
	 * or ws_sendframe_bin() here, but we're just being safe
	 * and re-sending the very same frame type and content
	 * again.
	 *
	 * Alternative functions:
	 *   ws_sendframe()
	 *   ws_sendframe_txt()
	 *   ws_sendframe_txt_bcast()
	 *   ws_sendframe_bin()
	 *   ws_sendframe_bin_bcast()
	 */
	ws_sendframe_bcast(8080, result, strlen(result), type);
}

/**
 * @brief Main routine.
 *
 * @note After invoking @ref ws_socket, this routine never returns,
 * unless if invoked from a different thread.
 */
int main(void)
{
	ws_socket(&(struct ws_server){
			/*
			 * Bind host:
			 * localhost -> localhost/127.0.0.1
			 * 0.0.0.0   -> global IPv4
			 * ::        -> global IPv4+IPv6 (DualStack)
			 */
			.host = "0.0.0.0",
			.port = 8080,
			.thread_loop   = 0,
			.timeout_ms    = 1000,
			.evs.onopen    = &onopen,
			.evs.onclose   = &onclose,
			.evs.onmessage = &onmessage
			});

	/*
	 * If you want to execute code past ws_socket(), set
	 * .thread_loop to '1'.
	 */

	return (0);
}
