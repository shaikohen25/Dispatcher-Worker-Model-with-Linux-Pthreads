/* command_parser.c - Parses dispatcher and worker commands */

#include "dispatcher_worker.h"

void parse_command(char* line, char* args[]) {
    char* token = strtok(line, " ;\t\n\r");
    int arg_count = 0;

    while (token != NULL) {
        args[arg_count++] = token;
        token = strtok(NULL, " ;\t\n\r");
    }
    args[arg_count] = NULL;
}

Worker* create_worker(char* args[]) {
    Worker* new_worker = (Worker*)malloc(sizeof(Worker));
    if (!new_worker) {
        perror("Error allocating memory for worker");
        exit(EXIT_FAILURE);
    }
    new_worker->commands = parse_worker_commands(args);
    new_worker->terminate = 0;
    return new_worker;
}

BasicCommand* parse_worker_commands(char* args[]) {
    BasicCommand* head = NULL;
    BasicCommand* tail = NULL;

    for (int i = 1; args[i] != NULL; i += 2) {
        BasicCommand* cmd = (BasicCommand*)malloc(sizeof(BasicCommand));
        if (!cmd) {
            perror("Error allocating memory for command");
            exit(EXIT_FAILURE);
        }
        strcpy(cmd->command, args[i]);
        cmd->value = atoi(args[i + 1]);
        cmd->next = NULL;

        if (!head) {
            head = cmd;
        } else {
            tail->next = cmd;
        }
        tail = cmd;
    }
    return head;
}
