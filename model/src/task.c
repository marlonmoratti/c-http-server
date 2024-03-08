#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/task.h"

struct task {
    int id;
    char *title;
    char *description;
    time_t due_date;
    bool done;
};

Task *create_task(int id, const char *title, const char *description, const char *due_date_str, bool done) {
    Task *task = (Task *) malloc(sizeof(Task));
    if (task == NULL) {
        perror("(task.c) Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    struct tm due_date_tm = { 0 };
    if (strptime(due_date_str, "%Y-%m-%d", &due_date_tm) == NULL) {
        perror("(task.c) Invalid date format\n");
        free(task);
        exit(EXIT_FAILURE);
    }

    task->id = id;
    task->title = strdup(title);
    task->description = strdup(description);
    task->due_date = mktime(&due_date_tm);
    task->done = done;

    return task;
}

int get_task_id(const Task *task) {
    return task->id;
}

const char *get_task_title(const Task *task) {
    return task->title;
}

const char *get_task_description(const Task *task) {
    return task->description;
}

const char *get_task_due_date(const Task *task) {
    static char due_date_str[11];
    struct tm *due_date_tm = localtime(&task->due_date);
    strftime(due_date_str, sizeof(due_date_str), "%Y-%m-%d", due_date_tm);
    return due_date_str;
}

bool get_task_done(const Task *task) {
    return task->done;
}

void set_task_title(Task *task, const char *title) {
    free(task->title);
    task->title = strdup(title);
}

void set_task_description(Task *task, const char *description) {
    free(task->description);
    task->description = strdup(description);
}

void set_task_due_date(Task *task, const char *due_date_str) {
    struct tm due_date_tm = { 0 };
    if (strptime(due_date_str, "%Y-%m-%d", &due_date_tm) == NULL) {
        perror("(task.c) Invalid date format\n");
        exit(EXIT_FAILURE);
    }

    task->due_date = mktime(&due_date_tm);
}

void set_task_done(Task *task, bool done) {
    task->done = done;
}

bool is_task_overdue(const Task *task) {
    time_t current_time = time(NULL);
    return difftime(current_time, task->due_date) > 0;
}

void delete_task(Task *task) {
    free(task->title);
    free(task->description);
    free(task);
}
