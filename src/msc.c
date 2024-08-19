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

	/*
	 * If you want to execute code past ws_socket(), set
	 * .thread_loop to '1'.
	 */

	return (0);
}
