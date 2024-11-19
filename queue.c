#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head) {
        free(head);
        return NULL;
    }
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;
    element_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, head, list) {
        list_del(&entry->list);
        q_release_element(entry);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *newNode = malloc(sizeof(element_t));
    if (!newNode)
        return false;

    newNode->value = strdup(s);
    if (!newNode->value) {
        free(newNode);
        return false;
    }
    list_add(&newNode->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *newNode = malloc(sizeof(element_t));
    if (!newNode)
        return false;

    newNode->value = strdup(s);
    if (!newNode->value) {
        free(newNode);
        return false;
    }
    list_add_tail(&newNode->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *target = list_first_entry(head, element_t, list);
    if (sp) {
        sp = strncpy(sp, target->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    list_del_init(head->next);
    return target;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *target = list_last_entry(head, element_t, list);
    if (sp) {
        sp = strncpy(sp, target->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    list_del_init(head->prev);
    return target;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;
    /* back and front method can compare with fast slow method at some moment */
    struct list_head *back = head->prev, *front = head->next;
    while (front != back && front->next != back) {
        front = front->next;
        back = back->prev;
    }
    element_t *target = list_entry(back, element_t, list);
    list_del(&target->list);
    q_release_element(target);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head || list_empty(head))
        return false;
    element_t *curr, *next;
    LIST_HEAD(toDelete);
    struct list_head *cut = head;
    list_for_each_entry_safe (curr, next, head, list) {
        if (&next->list != head && !strcmp(next->value, curr->value))
            continue;
        // handle duplicate
        if (curr->list.prev != cut) {
            // cut the sublist to toDelete list
            LIST_HEAD(tmp);
            list_cut_position(&tmp, cut, &curr->list);
            list_splice(&tmp, &toDelete);
        }
        cut = next->list.prev;
    }
    list_for_each_entry_safe (curr, next, &toDelete, list)
        q_release_element(curr);
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (!head || head->next == head || list_empty(head))
        return;
    struct list_head *node;
    list_for_each (node, head) {
        if (node->next == head)
            break;
        list_move(node, node->next);
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
