/*
 * =====================================================================================
 *
 *       Filename:  msc_functions.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/17/2024 06:13:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jan-Rudolph Buhrmann (JRB), 
 *        Company:  S2C Consulting
 *
 * =====================================================================================
 */

#ifndef MSC_FUNCTIONS_H
#define MSC_FUNCTIONS_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/ws.h"
#include "messaging.h"
#include <dirent.h>
#include <sys/stat.h>

#if (defined(_WIN32) || defined(__WIN32__))
#define mkdir(A, B) mkdir(A)
#endif

#define itoa(A, B) sprintf(B, "%d", A)

#define PATH_PREFIX "jobs_busy"
#define DATA_DELIMITER ";"
#define MAX_RESULT_MSG 20

void onopen(ws_cli_conn_t *client);


void onclose(ws_cli_conn_t *client);


void onmessage(ws_cli_conn_t *client,
                const unsigned char *msg, uint64_t size, int type);


#endif /* MSC_FUNCTIONS_H */
