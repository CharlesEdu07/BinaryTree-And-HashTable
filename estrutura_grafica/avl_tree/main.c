#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"

struct tree_node {
    int value;
    struct tree_node* left_child;
    struct tree_node* right_child;
    unsigned int height;
};

int get_height(struct tree_node* node) {
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

int get_difference(struct tree_node* node) {
    if (node == NULL) {
        return 0;
    }

    return get_height(node->left_child) - get_height(node->right_child);
}

void update_height(struct tree_node* node) {
    if (node == NULL) {
        return;
    }

    int left_height = get_height(node->left_child);
    int right_height = get_height(node->right_child);

    node->height = (left_height > right_height ? left_height : right_height) + 1;
}

struct tree_node* rotate_left(struct tree_node* node) {
    struct tree_node* new_root = node->right_child;

    node->right_child = new_root->left_child;

    new_root->left_child = node;

    update_height(node);
    update_height(new_root);

    return new_root;
}

struct tree_node* rotate_right(struct tree_node* node) {
    struct tree_node* new_root = node->left_child;

    node->left_child = new_root->right_child;

    new_root->right_child = node;

    update_height(node);
    update_height(new_root);
    
    return new_root;
}

struct tree_node* insert(struct tree_node* root, int value) {
    if (root == NULL) {
        root = malloc(sizeof(struct tree_node));
        root->value = value;
        root->left_child = NULL;
        root->right_child = NULL;
        root->height = 1;
    } else if (value < root->value) {
        root->left_child = insert(root->left_child, value);
    } else if (value > root->value) {
        root->right_child = insert(root->right_child, value);
    } else {
        return root;
    }

    update_height(root);

    int difference = get_difference(root);

    if (difference > 1 && value < root->left_child->value) {
        return rotate_right(root);
    }
    if (difference < -1 && value > root->right_child->value) {
        return rotate_left(root);
    }
    if (difference > 1 && value > root->left_child->value) {
        root->left_child = rotate_left(root->left_child);
        return rotate_right(root);
    }
    if (difference < -1 && value < root->right_child->value) {
        root->right_child = rotate_right(root->right_child);
        return rotate_left(root);
    }

    return root;
}

void print_tree(struct tree_node* root) {
    if (root != NULL) {
        print_tree(root->left_child);
        printf("%d\n", root->value);
        print_tree(root->right_child);
    }
}

void tree_print_dot_body(struct tree_node *root) {
    if (root != NULL)
    {
        tree_print_dot_body(root->left_child);
        printf("  \"%p\" [label=\"{%p|%d|{%p|%p}}\"];\n",
               (void *) root,
	       root,
	       root->value,
	       root->left_child,
	       root->right_child);
	if (root->left_child)
            printf("  \"%p\" -> \"%p\";\n", root, root->left_child);
	if (root->right_child)
            printf("  \"%p\" -> \"%p\";\n", root, root->right_child);
        tree_print_dot_body(root->right_child);
    }
}

void dotTree(FILE *file, struct tree_node *r) {
    if (r != NULL) {
        dotTree(file, r->left_child);

        fprintf(file, "  \"%p\" [shape=record, label=\"{%p|%d|h=%u|{%p|%p}}\"];\n", (void *)r, (void *)r, r->value, r->height, (void *)r->left_child, (void *)r->right_child);

        if (r->left_child) {
            fprintf(file, "  \"%p\" -> \"%p\";\n", (void *)r, (void *)r->left_child);
        }

        if (r->right_child) {
            fprintf(file, "  \"%p\" -> \"%p\";\n", (void *)r, (void *)r->right_child);
        }

        dotTree(file, r->right_child);
    }
}
 
void tree_print_dot(struct tree_node *root)
{
    printf("%s", DOT_HEADER);
    tree_print_dot_body(root);
    printf("%s", DOT_FOOTER);
}

int main(int argc, char **argv) {
    struct tree_node* root = NULL;

    unsigned int n = atoi(argv[1]);

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        root = insert(root, rand());
    }

    printf("\nImprimindo arvore em ordem:\n\n");
    print_tree(root);
    printf("\n");

    tree_print_dot(root);

    FILE *dot_file = fopen("tree.dot", "w");
    if (dot_file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    fprintf(dot_file, "digraph G {\n no [shape=record, height=0.6, width=1.5];\n edge [arrowhead=vee, arrowsize=0.8];\n");
    dotTree(dot_file, root);
    fprintf(dot_file, "}\n");

    fclose(dot_file);

    return 0;
}