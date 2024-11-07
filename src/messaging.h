/*
 * =====================================================================================
 *
 *       Filename:  messaging.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2024 08:53:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jan-Rudolph Buhrmann (JRB), 
 *        Company:  S2C Consulting
 *
 * =====================================================================================
 */


#ifndef MESSAGING_H
#define MESSAGING_H

// Messages
#define MSG_ADD_WORD 0
#define MSG_GET_STATUS 1
#define MSG_START_JOB 2

// Result codes
#define RESULT_OK 0
#define RESULT_UNKOWN_MESSAGE 1
#define JOB_BUSY 2
#define JOB_DONE 3
#define JOB_ERROR 4

#endif /* MESSAGING_H */
