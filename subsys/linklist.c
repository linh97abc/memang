#include <linklist.h>
#include <stddef.h>

void slist_sort_add(struct slist_node **_begin,
                    struct slist_node *_node,
                    int (*_key)(const struct slist_node *),
                    bool _reverse)
{
    struct slist_node src_node = {.next = *_begin};
    struct slist_node *i = &src_node, *i_next;
    int val = _key(_node);

    while (i != NULL)
    {
        int val_next;
        i_next = i->next;

        if (!i_next)
        {
            i->next = _node;
            _node->next = NULL;
            break;
        }

        val_next = _key(i_next);
        if ((!_reverse && (val_next >= val)) || (_reverse && (val_next <= val)))
        {
            _node->next = i_next;
            i->next = _node;
            break;
        }

        i = i_next;
    }

    *_begin = src_node.next;
}

bool slist_sort(struct slist_node **_begin, int (*_key)(const struct slist_node *), bool _is_reverse)
{
    struct slist_node src_node = {.next = *_begin};
    struct slist_node *pdes_node = NULL;
    struct slist_node *i;

    i = src_node.next;

    while (i != NULL)
    {
        slist_fast_remove(&src_node, i);
        slist_sort_add(&pdes_node, i, _key, _is_reverse);
        i = src_node.next;
    }

    *_begin = pdes_node;
}

void slist_foreach(struct slist_node *const *_begin, void (*_func)(const struct slist_node *_node))
{
    const struct slist_node *i = *_begin;

    while (i != NULL)
    {
        _func(i);
        i = (const struct slist_node *)i->next;
    }
}

bool slist_remove(struct slist_node **_begin, struct slist_node *_node)
{
    struct slist_node *i = *_begin;
    struct slist_node tmpList = {i};
    struct slist_node *i_pre = &tmpList;

    while (i != NULL)
    {
        if (i == _node)
        {
            slist_fast_remove(i_pre, i);
            *_begin = tmpList.next;

            return true;
        }

        i_pre = i;
        i = i->next;
    }

    return false;
}
