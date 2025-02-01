/* worker_threads.c - Handles worker thread execution */

#include "dispatcher_worker.h"

void* worker_routine(void* arg) {
    Worker* my_work = NULL;
    int thread_id = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&queue_mutex);
        while ((my_work = find_available_job()) == NULL) {
            pthread_cond_wait(&queue_condition, &queue_mutex);
        }
        pthread_mutex_unlock(&queue_mutex);

        if (my_work->terminate) {
            free(my_work);
            break;
        }

        execute_worker_job(my_work, thread_id);
    }
    return NULL;
}

void execute_worker_job(Worker* work, int thread_id) {
    BasicCommand* command = work->commands;
    while (command) {
        if (strcmp(command->command, "msleep") == 0) {
            usleep(command->value * 1000);
        } else if (strcmp(command->command, "increment") == 0) {
            update_counter(command->value, INCREMENT);
        } else if (strcmp(command->command, "decrement") == 0) {
            update_counter(command->value, DECREMENT);
        }
        command = command->next;
    }
}
