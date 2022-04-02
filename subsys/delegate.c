#include <linklist.h>
#include <mem_slab.h>
#include <delegate.h>
#include <toolchain.h>

struct delegate_node
{
    struct slist_node __node;
    void (*cb)(void *);
};

static struct mem_slab memDelegate;
static struct delegate_node g_node[CONFIG_MAX_DELEGATE];


static void delegate_module_init(void)
{
    mem_slab_create(&memDelegate, g_node, sizeof(g_node), sizeof(struct delegate_node));
}

SYS_PRE_INIT(delegate_module_init)

void delegate_invoke(const struct delegate *_delegate)
{
    if (_delegate)
    {
        const struct slist_node *i = _delegate->begin;

        while (i)
        {
            struct delegate_node *pDelegate = CONTAINER_OF(i, struct delegate_node, __node);
            void (*cb)(void *) = pDelegate->cb;

            if (cb)
            {
                cb(_delegate->arg);
            }

            i = i->next;
        }
    }
}

bool delegate_add(struct delegate *_delegate, void (*cb)(void *))
{
    if (cb)
    {
        struct delegate_node *node = (struct delegate_node *)mem_slab_alloc(&memDelegate);

        if (!node)
        {
            return false;
        }

        node->__node.next = _delegate->begin;
        node->cb = cb;
        _delegate->begin = &node->__node;

        return true;
    }

    return false;
}

bool delegate_remove(struct delegate *_delegate, void (*cb)(void *))
{
    struct slist_node manager = {_delegate->begin};
    struct slist_node *i = &manager;
    struct delegate_node *pnode = CONTAINER_OF(i->next, struct delegate_node, __node);

    while (i->next)
    {
        if (pnode->cb == cb)
        {
            slist_fast_remove(i, i->next);
            _delegate->begin = manager.next;
            mem_slab_free(&memDelegate, pnode);

            return true;
        }

        i = i->next;
        pnode = CONTAINER_OF(i->next, struct delegate_node, __node);
    }

    return false;
}

bool delegate_delete(struct delegate *_delegate)
{
    struct slist_node *i = _delegate->begin;
    struct delegate_node *pnode;

    while (i)
    {
        pnode = CONTAINER_OF(i, struct delegate_node, __node);
        i = i->next;

        mem_slab_free(&memDelegate, pnode);
    }

    _delegate->begin = NULL;
}
