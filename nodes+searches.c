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

    // key_find is the matching element
    int i = 0;
    if (curr_leaf_node->key_count < MAX_KEY)
    { // if key count isnt full there is space

        insert_into_leaf(curr_leaf_node, key, datapointer);
    }
    else
    { // key count is full, now split

        printf("CURRENT LEAF NODE WAS FULL...splitting  ");
        split(curr_leaf_node, key, datapointer);
    }
}

void insert_into_leaf(Node *curr_leaf_node, int key, void *datapointer)
{
    int i = 0;
    while (i < curr_leaf_node->key_count && curr_leaf_node->key[i] < key)
    {
        i++;
    }

    int count = curr_leaf_node->key_count;

    for (int j = count; j > i; j--)
    {
        curr_leaf_node->key[j] = curr_leaf_node->key[j - 1];

        curr_leaf_node->leaf.data_pointers[j] = curr_leaf_node->leaf.data_pointers[j - 1];
    }

    curr_leaf_node->key[i] = key;

    curr_leaf_node->leaf.data_pointers[i] = datapointer;

    curr_leaf_node->key_count++;
}

void split_and_insert(Node *curr_leaf_node, int key, void *datapointer)
{

    int j = 0;
    int i = 0;

    int temp_keys[MAX_KEY + 1]; // one more to hold the extra new key

    void *temp_pointers[MAX_KEY + 1]; // one more to hold the extra new pointer

    Node *new_leaf = (Node *)malloc(sizeof(Node));

    // binary search to find the middle key??
    // need to pull the middle key into the parent node

    while (curr_leaf_node->key[i] != NULL)
    {
        i++;
    }

    if (curr_leaf_node->key[i + 1] >= temp_keys)
    {
        // means the array is full
        // call split parent array or do it in this function
    }

    // if its not full, insert the NEW key
    else
    {
        // double for loop or bianry search whichever is easier
    }
}
