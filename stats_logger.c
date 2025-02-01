/* stats_logger.c - Handles logging and statistics collection */

#include "dispatcher_worker.h"

void log_statistics(struct timeval* start_time) {
    struct timeval end_time;
    gettimeofday(&end_time, NULL);
    long long runtime = (end_time.tv_sec - start_time->tv_sec) * 1000 + (end_time.tv_usec - start_time->tv_usec) / 1000;

    FILE* fp = fopen("stats.log", "w");
    if (!fp) {
        perror("Error opening stats file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "Total runtime: %lld milliseconds\n", runtime);
    fclose(fp);
}

void log_dispatcher_activity(const char* command, struct timeval* start_time) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long long timestamp = (current_time.tv_sec - start_time->tv_sec) * 1000 + (current_time.tv_usec - start_time->tv_usec) / 1000;

    FILE* fp = fopen("dispatcher.log", "a");
    if (!fp) {
        perror("Error opening dispatcher log");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "TIME %lld: %s\n", timestamp, command);
    fclose(fp);
}
