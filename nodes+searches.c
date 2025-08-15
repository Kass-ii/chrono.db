#include <stdio.h>
#include <stdlib.h>
#define MAX_KEY 100
#define MAX_POINTERS 100
#define MAX_CHILDREN 100

typedef enum
{ // naming - tells if a node is internal or a leaf
    INTERNAL,
    LEAF
} NodeType;

typedef struct Node Node; // declaration

struct Node
{
    NodeType type;    // will pull from enum name and correspond
    int key_count;    // # of keys currently in node
    int key[MAX_KEY]; // array that holds the keys

    union
    {
        struct // ** if this a internal node **
        {
            struct Node *child_pointers[MAX_CHILDREN];
        } internal;

        struct //** if a leaf node **
        {
            void *data_pointers[MAX_KEY];
            struct Node *next;
        } leaf;
    };
};

struct Tree
{

    Node *root;
};
Tree_system;

struct Tree Tree_system; // declaration

int create_tree();

int main(int argc, char argv[])
{
}

int create_tree()
{
    Node *temp_root = (Node *)malloc(sizeof(Node));
    if (temp_root == NULL)
    {
        printf("node did not initialize");
        exit(0);
    }

    temp_root->type = LEAF;
    temp_root->key_count = 0;
    temp_root->leaf.next = NULL;

    Tree_system.root = temp_root;
}

void *sort()
{

    // sort goes
    //  left = small
    //  right == large

    // sorting will go heap sort
}

Node *search(Node *start, int key_find)
{

    Node *Current_node = start;

    while (Current_node->type != LEAF)
    { // checks if node is internal
        int i = 0;
        int count = 0;
        for (i; i < Current_node->key_count /* key count because that specefic key count*/; i++)
        {

            if (key_find < Current_node->key[i])
            { // checks if key of internal node and key key are the same
                // not less than EQUAL becauise should be first key found
                count = 1;
                break;
            }
        }
        if (!count)
        {                                // edge case, might be useless key_find greater than all
            i = Current_node->key_count; // i stays whatever it is, for loop now exits because condition is met to end
        } // outside of foor loop bc as long as the key i bigger it will continue to not set and close out

        Current_node = Current_node->internal.child_pointers[i];
    }

    return Current_node; // you return because the while stastement is over, because this means the current node is a leaf
}

void verify_to_insert(Node *start, int key, void *datapointer)
{

    Node *curr_leaf_node = search(start, key);

    // key_find is the matching elemtn
    int i = 0;
    if (curr_leaf_node->key_count < MAX_KEY)
    { // if key count isnt full there is space

        insert(curr_leaf_node, key, datapointer);
    }
    else
    { // key count is full, now split

        printf("CURRENT LEAF NODE WAS FULL...splitting  ");
        split(curr_leaf_node, key, datapointer);
    }
}

int split(Node *curr_leaf_node, int key, void *datapointer)
{
}
