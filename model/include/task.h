#ifndef TASK_H
#define TASK_H

#include <stdbool.h>

typedef struct task Task;

/**
 * @brief Creates a new task.
 * @param id Unique identifier for the task.
 * @param title Title of the task.
 * @param description Description of the task.
 * @param due_date_str Due date of the task in the format "YYYY-MM-DD".
 * @param done Completion status of the task.
 * @return A pointer to the newly created task.
 * @note The caller is responsible for freeing the memory allocated for the task using delete_task().
 */
Task *create_task(int id, const char *title, const char *description, const char *due_date_str, bool done);

/**
 * @brief Gets the ID of a task.
 * @param task Pointer to the task.
 * @return The ID of the task.
 */
int get_task_id(const Task *task);

/**
 * @brief Gets the title of a task.
 * @param task Pointer to the task.
 * @return The title of the task.
 */
const char *get_task_title(const Task *task);

/**
 * @brief Gets the description of a task.
 * @param task Pointer to the task.
 * @return The description of the task.
 */
const char *get_task_description(const Task *task);

/**
 * @brief Gets the due date of a task.
 * @param task Pointer to the task.
 * @return The due date of the task in the format "YYYY-MM-DD".
 * @note The returned string is stored in a static buffer.
 *       Subsequent calls to this function will overwrite the content of the buffer.
 *       To safely use the returned string, consider making a copy of it if its
 *       value needs to be preserved beyond the scope of the calling function.
 */
const char *get_task_due_date(const Task *task);

/**
 * @brief Gets the completion status of a task.
 * @param task Pointer to the task.
 * @return The completion status of the task.
 */
bool get_task_done(const Task *task);

/**
 * @brief Sets the title of a task.
 * @param task Pointer to the task.
 * @param title New title for the task.
 */
void set_task_title(Task *task, const char *title);

/**
 * @brief Sets the description of a task.
 * @param task Pointer to the task.
 * @param description New description for the task.
 */
void set_task_description(Task *task, const char *description);

/**
 * @brief Sets the due date of a task.
 * @param task Pointer to the task.
 * @param due_date_str New due date for the task in the format "YYYY-MM-DD".
 */
void set_task_due_date(Task *task, const char *due_date_str);

/**
 * @brief Sets the completion status of a task.
 * @param task Pointer to the task.
 * @param done New completion status for the task.
 */
void set_task_done(Task *task, bool done);

/**
 * @brief Checks if a task is overdue based on the current date.
 * @param task Pointer to the task.
 * @return true if the task is overdue, false otherwise.
 */
bool is_task_overdue(const Task *task);

/**
 * @brief Deletes a task and frees its allocated memory.
 * @param task Pointer to the task to be deleted.
 */
void delete_task(Task *task);

#endif
