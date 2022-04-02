#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdbool.h>
#include <stdint.h>
#include <sys/util.h>

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------*/
struct slist_node
{
    struct slist_node *next;
};

struct dlist_node
{
    struct dlist_node *next;
    struct dlist_node *pre;
};

static inline void slist_add(struct slist_node **_begin, struct slist_node *_node)
{
    _node->next = (*_begin)->next;
    *_begin = _node;
}

static inline void slist_fast_add(struct slist_node *_node_pre, struct slist_node *_node)
{
    _node->next = _node_pre->next;
    _node_pre->next = _node;
}

static inline void slist_fast_remove(struct slist_node *_node_pre, struct slist_node *_node)
{
    _node_pre->next = _node->next;
}

static inline void dlist_add(struct dlist_node **_begin, struct dlist_node *_node)
{
    (*_begin)->pre = _node;
    _node->next = *_begin;
    _node->pre = (*_begin)->pre;
    *_begin = _node;
}

static inline void dlist_append(struct dlist_node **_begin, struct dlist_node *_node)
{
    _node->next = *_begin;
    _node->pre = (*_begin)->pre;
    (*_begin)->pre->next = _node;
    (*_begin)->pre = _node;
}

static inline void dlist_fast_remove(struct dlist_node *_node)
{
    _node->pre->next = _node->next;
    _node->next->pre = _node->pre;
}

static inline void dlist_fast_add_after(struct dlist_node *_node_pre, struct dlist_node *_node)
{
    _node->next = _node_pre->next;
    _node->pre = _node_pre;
    _node_pre->next->pre = _node;
    _node_pre->next = _node;
}

static inline void dlist_fast_add_before(struct dlist_node *_node_next, struct dlist_node *_node)
{
    _node->next = _node_next;
    _node->pre = _node_next->pre;
    _node_next->pre->next = _node;
    _node_next->pre = _node;
}

bool slist_remove(struct slist_node **_begin, struct slist_node *_node);
bool slist_sort(struct slist_node **_begin, int (*_key)(const struct slist_node *), bool _is_reverse);
void slist_foreach(struct slist_node *const *_begin, void (*_func)(const struct slist_node *_node));
void slist_sort_add(struct slist_node **_begin,
                    struct slist_node *_node,
                    int (*_key)(const struct slist_node *),
                    bool _reverse);
#ifdef __cplusplus
}
#endif

#endif