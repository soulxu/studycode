typedef struct TreeNode {
    int val_;
    int height_;
    struct TreeNode* left_;
    struct TreeNode* right_;
} TreeNode;

TreeNode* newTreeNode(int val) {
    TreeNode* new_node = NULL;
    new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->val = val;
    new_node->height_ = 0;
    new_node->left_ = NULL;
    new_node->right_ = NULL;
    return new_node;
}

int main(int, char**) {
    
    return 0;
}