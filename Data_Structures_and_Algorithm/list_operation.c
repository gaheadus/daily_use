#include <stdlib.h>
#include <stdio.h>

typedef struct list_node {
    int data;
    struct list_node *next;
} Node;


Node *insert(Node **list, int data){
    Node *list_head = *list;
    Node *pre_node = NULL;
    Node *cur_node = NULL;

    // init list head
    if (list_head == NULL){
        list_head = (Node*)malloc(sizeof(Node));
        memset(list_head,sizeof(Node),0);
        list_head->next = NULL;
        *list = list_head;
        printf("Init list successful.\n");
    }

#if 1
    // insert a node to the list tail
    for( pre_node = list_head,cur_node = list_head->next; cur_node != NULL; pre_node = cur_node,cur_node = cur_node->next);

    cur_node = (Node*)malloc(sizeof(Node));
    memset(cur_node,sizeof(Node),0);
    cur_node->data = data;
    pre_node->next = cur_node;
    cur_node->next = NULL;
#else
    // insert a node after list head
    cur_node = (Node*)malloc(sizeof(Node));
    memset(cur_node,sizeof(Node),0);
    cur_node->data = data;
    cur_node->next = list_head->next;
    list_head->next = cur_node;
#endif

    printf("Insert node %d successful.\n", cur_node->data);

    return *list;
}


void traverse(Node **list){
    Node *list_head = *list;
    Node *cur_node = NULL;

    if (list_head == NULL){
        printf("No Node. Empty list.\n");
        return;
    }

    for(cur_node = list_head->next; cur_node != NULL; cur_node = cur_node->next){
        printf("Node data: %d.\n", cur_node->data);
    }
}


Node *delete(Node **list, int data){
    Node *list_head = *list;
    Node *pre_node = NULL;
    Node *cur_node = NULL;

    if (list_head == NULL){
        printf("Delete error, Empty list.\n");
    }

    for( pre_node = list_head,cur_node = list_head->next; cur_node != NULL; pre_node = cur_node,cur_node = cur_node->next){
        if(cur_node->data == data){
            pre_node->next = cur_node->next;
            free(cur_node);
            cur_node = NULL;
            printf("Delete node %d successful.\n", data);
            break;
        }
    }

    return *list;
}

void destory(Node **list){
    Node *list_head = *list;
    Node *pre_node = NULL;
    Node *cur_node = NULL;
    int data;

    if (list_head == NULL){
        printf("List already empty.\n");
    }

    for( cur_node = list_head->next; cur_node != NULL; cur_node = list_head->next){
        data = cur_node->data;
        list_head->next = cur_node->next;
        free(cur_node);
        cur_node = NULL;
        printf("Destory, delete node %d successful.\n", data);
    }

    free(list_head);
    list_head = NULL;

    *list = NULL;

    printf("Destory list successful.\n");
}



int main(int argc, char * argv[])
{
    Node *list = NULL;
    int a[7] = {3,7,1,9,8,11,17};
    int i;

    for(i=0;i<7;i++){
        insert(&list, a[i]); //注意:实参使用&list才能改变指针变量list
    }

    traverse(&list);

    delete(&list, a[5]);
    traverse(&list);

    delete(&list, a[2]);
    traverse(&list);

    destory(&list);
    traverse(&list);
}