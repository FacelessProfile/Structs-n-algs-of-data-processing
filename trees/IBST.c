#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NODE_COUNT 100

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *build_numeric_tree(int index, int max_index) {
    if (index > max_index) return NULL;

    Node *root = create_node(index);
    root->left = build_numeric_tree(2 * index, max_index);
    root->right = build_numeric_tree(2 * index + 1, max_index);
    return root;
}

void inorder_traversal(Node *node) {
    if (node != NULL) {
        inorder_traversal(node->left);
        printf("%d ", node->value);
        inorder_traversal(node->right);
    }
}

int tree_size(Node *node) {
    if (node == NULL) return 0;
    return 1 + tree_size(node->left) + tree_size(node->right);
}

int checksum(Node *node) {
    if (node == NULL) return 0;
    return node->value + checksum(node->left) + checksum(node->right);
}

int tree_height(Node *node) {
    if (node == NULL) return 0;
    int left_height = tree_height(node->left);
    int right_height = tree_height(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int total_path_length(Node *node, int level) {
    if (node == NULL) return 0;
    return level + total_path_length(node->left, level + 1) + total_path_length(node->right, level + 1);
}

float average_depth(Node *root) {
    if (root == NULL) return 0.0f;
    int total = total_path_length(root, 1);
    int size = tree_size(root);
    return (float)total / size;
}

void fill_incremental_array(int n, int array[]) {
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }
}

Node *build_balanced_bst(int left, int right, int array[]) {
    if (left > right) return NULL;
    int mid = (left + right) / 2;

    Node *node = create_node(array[mid]);
    node->left = build_balanced_bst(left, mid - 1, array);
    node->right = build_balanced_bst(mid + 1, right, array);
    return node;
}

// "Graphical" tree representation in terminal
void print_tree(Node *node, int level) {
    if (!node) return;
    print_tree(node->right, level + 1);
    printf("%*s%d\n", level * 4, "", node->value);
    print_tree(node->left, level + 1);
}

void export_dot_recursive(Node *node, FILE *file) {
    if (!node) return;

    if (node->left) {
        fprintf(file, "    %d -> %d;\n", node->value, node->left->value);
        export_dot_recursive(node->left, file);
    }
    if (node->right) {
        fprintf(file, "    %d -> %d;\n", node->value, node->right->value);
        export_dot_recursive(node->right, file);
    }
}

void export_to_dot(Node *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Cannot open file for DOT export");
        return;
    }

    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [shape=circle];\n");

    export_dot_recursive(root, file);

    fprintf(file, "}\n");
    fclose(file);
}


int main() {
    int values[NODE_COUNT];
    fill_incremental_array(NODE_COUNT, values);

    // Balanced BST
    Node *balanced_root = build_balanced_bst(0, NODE_COUNT - 1, values);

    printf("In-order traversal (Balanced BST):\n");
    inorder_traversal(balanced_root);
    printf("\nSize: %d\n", tree_size(balanced_root));
    printf("Checksum: %d\n", checksum(balanced_root));
    printf("Height: %d\n", tree_height(balanced_root));
    printf("Average Depth: %.2f\n", average_depth(balanced_root));
   // printf("\nGraphical display (Balanced BST):\n");
   // print_tree(balanced_root, 0);

    // Numeric Tree
    Node *numeric_root = build_numeric_tree(1, NODE_COUNT);

    printf("\nIn-order traversal (Numeric Tree):\n");
    inorder_traversal(numeric_root);
    printf("\nSize: %d\n", tree_size(numeric_root));
    printf("Checksum: %d\n", checksum(numeric_root));
    printf("Height: %d\n", tree_height(numeric_root));
    printf("Average Depth: %.2f\n", average_depth(numeric_root));
   // printf("\nGraphical display (Numeric Tree):\n");
   // print_tree(numeric_root, 0);


    //-------------------EXPORT TO IMAGE---------------------
    export_to_dot(balanced_root, "balanced_tree.dot");
    system("dot -Tpng balanced_tree.dot -o balanced_tree.png");
    export_to_dot(numeric_root, "numeric_tree.dot");
    system("dot -Tpng numeric_tree.dot -o numeric_tree.png");

    printf("\nGraphical images have been generated:\n");
    printf(" - balanced_tree.png\n");
    printf(" - numeric_tree.png\n");

    system("start balanced_tree.png");
    return 0;
}
