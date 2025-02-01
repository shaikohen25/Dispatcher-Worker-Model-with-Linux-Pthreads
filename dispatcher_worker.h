/* dispatcher_worker.h - Header file for the dispatcher-worker system */
#ifndef DISPATCHER_WORKER_H
#define DISPATCHER_WORKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

#define MAX_THREADS 4096
#define MAX_COUNTERS 100
#define MAX_CMD_LINE 1024
#define MAX_FILENAME 50
#define MAX_BASIC_CMD 256

/* Enum to track counter operations */
typedef enum { INCREMENT, DECREMENT } CounterAction;

/* Structure to represent a command */
typedef struct BasicCommand {
    char command[MAX_BASIC_CMD];
    int value;
    struct BasicCommand* next;
} BasicCommand;

/* Structure to represent a worker job */
typedef struct Worker {
    BasicCommand* commands;
    int terminate;
    struct timeval start_time;
    struct timeval end_time;
    struct Worker* next;
} Worker;

/* Function Prototypes */
void init_counter_files(int num_counters);
void update_counter(int counter_id, CounterAction action);
void* worker_routine(void* arg);
void dispatcher(const char* filename, int log_enabled, struct timeval* start_time);
Worker* create_worker(BasicCommand* commands, int terminate);
void append_worker_to_queue(Worker* worker);
void log_statistics(struct timeval* start_time);
void wait_for_pending_workers();
void cleanup_resources();

#endif // DISPATCHER_WORKER_H
