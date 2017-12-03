#include <stdio.h>
#include <stdlib.h>

#include "b_tree.h"

#define NODE_DATA_ARRAY_LENGTH 4
#define NODE_CHILDREN_ARRAY_LENGTH 5

/**
 *
 */
BTreeNode create(
    const unsigned short key,
    const int data
)
{
    BTreeNode node;
    node.keys = malloc(sizeof(unsigned short) * NODE_DATA_ARRAY_LENGTH);
    node.datas = malloc(sizeof(int) * NODE_DATA_ARRAY_LENGTH);
    node.children = malloc(sizeof(BTreeNode*) * NODE_CHILDREN_ARRAY_LENGTH);

    for (
        unsigned short i = 0;
        i < NODE_CHILDREN_ARRAY_LENGTH;
        i += 1
    )
    {
        node.children[i] = NULL;
    }

    for (
        unsigned short i = 0;
        i < NODE_DATA_ARRAY_LENGTH;
        i += 1
    )
    {
        node.keys[i] = 0;
        node.datas[i] = 0;
    }

    node.keys[0] = key;
    node.datas[0] = data;

    node.size = 1;

    /* the unique node is a leaf node */
    node.isLeaf = 1;

    return node;
}

/**
 *
 */
const unsigned short search(
    BTreeNode* tree,
    const unsigned short key
)
{
    unsigned short i = 0;

    while (
        i < NODE_DATA_ARRAY_LENGTH &&
        key > tree->keys[i]
    )
    {
        i += 1;
    }

    if (
        i == NODE_DATA_ARRAY_LENGTH - 1 &&
        key > tree->keys[i]
    )
    {
        i += 1;
    }

    if (tree->keys[i] == key)
    {
        return 1;
    }

    if (tree->isLeaf)
    {
        return 0;
    }

    if (tree->children[i] == NULL)
    {
        return 0;
    }

    return search(
        tree->children[i],
        key
    );
}

/**
 *
 */
void insert(
    BTreeNode* tree,
    const unsigned short key,
    const int data
)
{
    printf("%d", key);

    if (tree->size == NODE_DATA_ARRAY_LENGTH)
    {
        unsigned short i = 0;

        while (
            i < NODE_DATA_ARRAY_LENGTH &&
            tree->keys[i] < key
        ) {
            i += 1;
        }

        if (
            i == NODE_DATA_ARRAY_LENGTH - 1 &&
            tree->keys[i] < key
        ) {
            i += 1;
        }

        if (tree->children[i] != NULL)
        {
            /* TODO: #147 order insertion into child node */
            insert(
                tree->children[i],
                key,
                data
            );

            return;
        }

        /* TODO: #148 check how this child node creation can be merged
           with the create() method of the BTreeNode */
        tree->children[i] = malloc(sizeof(BTreeNode));
        tree->children[i]->keys = malloc(sizeof(unsigned short) * NODE_DATA_ARRAY_LENGTH);
        tree->children[i]->datas = malloc(sizeof(int) * NODE_DATA_ARRAY_LENGTH);
        tree->children[i]->children = malloc(sizeof(BTreeNode*) * NODE_CHILDREN_ARRAY_LENGTH);

        for (
            unsigned short j = 0;
            j < NODE_CHILDREN_ARRAY_LENGTH;
            j += 1
        )
        {
            tree->children[i]->children[j] = NULL;
        }

        tree->children[i]->keys[0] = key;
        tree->children[i]->datas[0] = data;
        tree->children[i]->size = 1;
        tree->children[i]->isLeaf = 1;

        tree->isLeaf = 0;

        return;
    }

    tree->keys[tree->size] = key;
    tree->datas[tree->size] = data;
    tree->size += 1;
}
