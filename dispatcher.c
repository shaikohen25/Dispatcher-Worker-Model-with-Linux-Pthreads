/* dispatcher.c - Handles job dispatching and counter management */

#include "dispatcher_worker.h"

void dispatcher(const char* filename, int log_enabled, struct timeval* start_time) {
    char line[MAX_CMD_LINE];
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening command file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, MAX_CMD_LINE, file) != NULL) {
        if (log_enabled) {
            log_dispatcher_activity(line, start_time);
        }
        process_command(line);
    }

    fclose(file);
}

void process_command(const char* command) {
    char* args[MAX_BASIC_CMD];
    parse_command(command, args);

    if (strcmp(args[0], "worker") == 0) {
        Worker* new_worker = create_worker(args);
        append_worker_to_queue(new_worker);
        pthread_cond_broadcast(&queue_condition);
    } else if (strcmp(args[0], "dispatcher_msleep") == 0) {
        usleep(atoi(args[1]) * 1000);
    } else if (strcmp(args[0], "dispatcher_wait") == 0) {
        wait_for_pending_workers();
    }
}
