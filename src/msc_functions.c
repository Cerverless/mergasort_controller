/*
 * =====================================================================================
 *
 *       Filename:  msc_functions.c
 *
 *    Description: Functions used by msc application 
 *
 *        Version:  1.0
 *        Created:  08/17/2024 06:05:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jan-Rudolph Buhrmann (JRB), 
 *        Company:  S2C Consulting
 *
 * =====================================================================================
 */

#include "msc_functions.h"

#define DEBUG

/**
 * @brief Called when a client connects to the server.
 *
 * @param client Client connection. The @p client parameter is used
 * in order to send messages and retrieve informations about the
 * client.
 */
void onopen(ws_cli_conn_t *client) {
    char *cli, *port;
    cli = ws_getaddress(client);
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
void onclose(ws_cli_conn_t *client) {
    char *cli;
    cli = ws_getaddress(client);
#ifdef DEBUG
    printf("Connection closed, addr: %s\n", cli);
#endif
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  to_upper
 *  Description:  Turns string into all upper case letters
 * =====================================================================================
 */
void to_upper(char *string) {
    for (int i = 0; ; i++) {
        if (string[i] == '\0')
            return;
        if ((string[i] > 96) && (string[i] < 123)) {
            /*
             * Each lowercase letter is 32 + uppercase equivalent.
             * This means simply flipping the bit at position 5
             * (counting from least significant bit at position 0) inverts the case of a letter.
             */
            string[i] = string[i] ^ 0x20;
        }
    }

    return;
}

/**
 * Returns amount of files under processing for a job
 */
int files_per_job(const char *path, const char *job_id, struct stat *p_stat_buf) {
    const char *file_name;
    int result = 0;
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            file_name = dir->d_name;
            printf("%s\n", file_name);
            if (strcmp(strtok(file_name, "_"), job_id) == 0) {
                result++;
                char path[30];
                sprintf(path, "%s%s", PATH_PREFIX, file_name);

                if (stat(path, p_stat_buf) == -1) {
                    perror("lstat");
                }
            }
        }

        closedir(d);
    }
    return result;
}

/* -----  end of function files_per_job  ----- */

void write_to_file(const char *path, char *word) {
    FILE *fptr;

    fptr = fopen(path, "a");

    to_upper(word);

    fprintf(fptr, word);
    fprintf(fptr, "\n");

    fclose(fptr);
    return;
}

/**
 * @brief Called when a client connects to the server.
 *
 * @param client Client connection. The @p client parameter is used
 * in order to send messages and retrieve informations about the
 * client.
 *
 * @param msg Received message, this message can be a text
 *
 * or binary message.
 *
 * @param size Message size (in bytes).
 *
 * @param type Message type.
 */
void onmessage(ws_cli_conn_t *client,
               const unsigned char *msg, uint64_t size, int type) {
    // char *cli;
    // cli = ws_getaddress(client);
    char result[MAX_RESULT_MSG];

    int message_nr = atoi(strtok(msg, DATA_DELIMITER));
    char *job_nr = strtok(NULL, DATA_DELIMITER);
    char *word_nr = strtok(NULL, DATA_DELIMITER);
    char *word = strtok(NULL, DATA_DELIMITER);
    char *lock_size = strtok(NULL, DATA_DELIMITER);
// #ifdef DEBUG
    printf("The following message was received: %d, job_nr: %s, word_nr: %s, word: %s lock size: %s\n",
           message_nr, job_nr, word_nr, word, lock_size);
// #endif
    if (message_nr == MSG_START_JOB) {
        char spec_path[20]; // TODO calculate length of file_path based on max amounts of elements that can be sorted
        sprintf(spec_path, "%s/%s", PATH_PREFIX, "job_spec");
        write_to_file(spec_path, job_nr);
        write_to_file(spec_path, word_nr);
        write_to_file(spec_path, lock_size);

        char file_path[20]; // TODO calculate length of file_path based on max amounts of elements that can be sorted
        // char* index = strlen(file_path);
        sprintf(file_path, "%s/%s", PATH_PREFIX, job_nr);
        mkdir(file_path, 0700);
        // index += strlen(file_path);
        sprintf(file_path, "%s/%s", file_path, "1"); // round is 1
        mkdir(file_path, 0700);
    } else if (message_nr == MSG_ADD_WORD) {
        char file_path[20]; // TODO calculate length of file_path based on max amounts of elements that can be sorted
        const int base = atoi(word_nr) - (atoi(word_nr) % atoi(lock_size));
        char baseChar[10];
        itoa(base, baseChar);
        sprintf(file_path, "%s/%s/%s/%s", PATH_PREFIX, job_nr, "1", baseChar);
        mkdir(file_path, 0700);
        sprintf(file_path, "%s/%s_1_%s", file_path, job_nr, word_nr);
        write_to_file(file_path, word);
        sprintf(result, "%d", RESULT_OK);
    } else if (message_nr == MSG_GET_STATUS) {
        struct stat sb;
        // TODO more sophistication required between BUSY and ERROR?
        int files_being_processed = files_per_job(PATH_PREFIX, job_nr, &sb);
        if (files_being_processed == 0) {
            sprintf(result, "%d", JOB_ERROR);
        } else if (files_being_processed == 1) {
            sprintf(result, "%d;%ld", JOB_DONE, sb.st_mtime);
        } else {
            sprintf(result, "%d", JOB_BUSY);
        }
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
