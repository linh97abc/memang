#ifndef __DELEGATE_H__
#define __DELEGATE_H__

#include <stdbool.h>
#define CONFIG_MAX_DELEGATE 128

#ifdef __cplusplus
extern "C" {
#endif

struct delegate
{
    struct slist_node *begin;
    const char *name;
    void *arg;
};

/**
 * @brief Define a delegate object.
 * @param _d    name of delegate
 */
#define DELEGATE_DEFINE(_d) struct delegate _d = {NULL, NULL, NULL}

/**
 * @brief Add a callback function to delegate object.
 * @param _delegate    is a pointer to delegate object
 * @param cb  callback function
 * @retval true  is success
 * @retval false if failed
 */
bool delegate_add(struct delegate *_delegate, void (*cb)(void*));

/**
 * @brief Remove a callback function from delegate object.
 * @param _delegate    is a pointer to delegate object
 * @param cb  callback function
 * @retval true  is success
 * @retval false if failed
 */
bool delegate_remove(struct delegate *_delegate, void (*cb)(void*));

/**
 * @brief Remove all callback function from delegate object.
 * @param _delegate    is a pointer to delegate object
 * @retval true  is success
 * @retval false if failed
 */
bool delegate_delete(struct delegate *_delegate);

/**
 * @brief Invoke all callback in delegate object.
 * @param _delegate    is a pointer to delegate object
 */
void delegate_invoke(const struct delegate *_delegate);


#ifdef __cplusplus
}
#endif
#endif
