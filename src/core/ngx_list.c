
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>


 /*
 * pool 内存池对象
 * n 每个链表数组的大小
 * size 每个元素的大小
 */

 /*
 * ngx_list_t testlist = ngx_list_create(r->pool, 4, sizeof(ngx_str_t));
 * if(testlist == NULL) return NGX_ERROR;
 *
 */
ngx_list_t *
ngx_list_create(ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    ngx_list_t  *list;

    list = ngx_palloc(pool, sizeof(ngx_list_t));
    if (list == NULL) {
        return NULL;
    }

    if (ngx_list_init(list, pool, n, size) != NGX_OK) {
        return NULL;
    }

    return list;
}

/*
* ngx_str_t* str = ngx_list_push(testlist);
* if(str == NULL) return NGX_ERROR;
* str->len = sizeof("hello world");
* str->value = "Hello world";
*/
void *
ngx_list_push(ngx_list_t *l)
{
    void             *elt;
    ngx_list_part_t  *last;

    last = l->last;

    if (last->nelts == l->nalloc) {

        /* the last part is full, allocate a new list part */

        last = ngx_palloc(l->pool, sizeof(ngx_list_part_t));
        if (last == NULL) {
            return NULL;
        }

        last->elts = ngx_palloc(l->pool, l->nalloc * l->size);
        if (last->elts == NULL) {
            return NULL;
        }

        last->nelts = 0;
        last->next = NULL;

        l->last->next = last;
        l->last = last;
    }

    elt = (char *) last->elts + l->size * last->nelts;
    last->nelts++;

    return elt;
}

/* 遍历一个ngx_array_t
*/

ngx_list_part_t* part = &testlist.part;
// 指向数组的起始位置
ngx_str_t* str = part->elts;
for(i = 0; ; i++) {
    // 该链表的元素已经访问完，接着访问下一个链表节点的数组
    if(i >= part->nelts) {
        // 没有后续节点
        if(part->next == NULL) {
            break;
        }
        part = part->next;
        header = part->elts;
        i = 0;
    }
    printf("list element: %*s \n", part->elts[i].len, part->elts[i].data);
}

