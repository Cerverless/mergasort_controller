#include "msc.h"

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

	/********* START  Code to test locally */
	// // int message_nr = atoi(strtok(msg, ";"));
	// // char *job_nr = strtok(NULL, DATA_DELIMITER);
	// // char *word_nr = strtok(NULL, DATA_DELIMITER); or file amount wneh starting job (2)
	// // char *word = strtok(NULL, DATA_DELIMITER);
	// // char *lock_size = strtok(NULL, DATA_DELIMITER);
	// char msg[] = "2;7;100;WAT;5"; // first element 2 starts job
	// 	onmessage(NULL, msg, 0, MSG_START_JOB);
	//
	// char msg1[] = "0;7;101;WAT;5"; // first element 0 to add word
	// onmessage(NULL, msg1, 0, MSG_START_JOB);
	/********** END Code to test locally */

	/*
	 * If you want to execute code past ws_socket(), set
	 * .thread_loop to '1'.
	 */
	return (0);
}
