#pragma once

#include <functional>
#include <list>
#include <cassert>
#include <stdio.h>

namespace Algo {

template<class T>
class Tree {
public:
    
    using DataVisitor = std::function<void(T)>;
    Tree() {}
    Tree(const std::vector<T>& pre_order, const std::vector<T>& in_order) {
        root = buildTree(pre_order, in_order);
    }

    ~Tree() {
        travelLevelImpl(root, [](Tree::TreeNode* node) {
            delete node;
            return true;
        });
        root = nullptr;
    }

    void add(T data) {
        TreeNode** last = travelToLastByLevel(&root);
        newNode(last, data);
    }

    void addBST(T data) {
        TreeNode** node = travelToLastByBST(&root, data);
        if (node == nullptr) {
            return;
        }
        newNode(node, data);
    }

    void removeBST(T data);
    void removeBST2(T data) {
        root = removeBST2Impl(root, data);
    }

    void addBST2(T data);
    void addBST3(T data);

    int height() {
        return height(root);
    }
    bool findBST(T data) {
        return findBSTImpl(root, data);
    }

    bool findBST2(T data);

    void travelLevel(DataVisitor visitor) {
        travelLevelImpl(root, visitor);
    }

    void travelPreOrder(DataVisitor visitor) {
        travelPreOrderImpl(root, visitor);
    }

    void travelInOrder(DataVisitor visitor) {
        travelInOrderImpl(root, visitor);
    }

    void deleteMin() {
        root = deleteMin(root);
    }
private:
    struct TreeNode {
        TreeNode(T d, TreeNode* l, TreeNode* r) : data(d), left(l), right(r) {}
        T data;
        int height{0};
        TreeNode* left;
        TreeNode* right;
    };

    using NodeVisitor = std::function<bool(TreeNode*)>;

    TreeNode* buildTree(const std::vector<T>& pre_order, const std::vector<T>& in_order) {
        std::unordered_map<T, int> in_order_map;
        for (int i = 0; i < in_order.size(); i++) {
            in_order_map.insert(std::make_pair(in_order[i], i));
        }
        return buildTreeImpl(pre_order, in_order_map, 0, 0, in_order.size() - 1);
    }

    TreeNode* buildTreeImpl(const std::vector<T>& pre_order, const std::unordered_map<T, int>& in_order_map, int i, int l, int r) {
        if ((r - l) < 0) {
            return nullptr;
        }
        TreeNode* new_node = new TreeNode(pre_order[i], nullptr, nullptr);
        int m = in_order_map.at(pre_order[i]);
        new_node->left = buildTreeImpl(pre_order, in_order_map, i + 1, l, m - 1);
        new_node->right = buildTreeImpl(pre_order, in_order_map, i + 1 + m - l, m + 1, r);
        new_node->height = 1 + std::max(height(new_node->left), height(new_node->right));
        return new_node;
    }

    void newNode(TreeNode** node, T data) {
        *node = new TreeNode(data, nullptr, nullptr);
    }

    int height(TreeNode* node) {
        if (node == nullptr) {
            return -1;
        }
        return node->height;
    }

    TreeNode* balance(TreeNode *node) {
        // printf("balance\n");
        if (balanceFactor(node) < -1) {
            // printf("left inbalance\n");
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            node = rotateLeft(node);
        } else if (balanceFactor(node) > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            node = rotateRight(node);
        }
        return node;
    }

    int balanceFactor(TreeNode* node) {
        return height(node->left) - height(node->right);
    }

    TreeNode* rotateLeft(TreeNode* node) {
        // printf("rotate left\n");
        TreeNode* m = node->right;
        node->right = m->left;
        m->left = node;
        node->height = 1 + std::max(height(node->left), height(node->right));
        m->height = 1 + std::max(height(m->left), height(m->right));
        return m;
    }

    TreeNode* rotateRight(TreeNode* node) {
        TreeNode* m = node->left;
        node->left = m->right;
        m->right = node;
        node->height = 1 + std::max(height(node->left), height(node->right));
        m->height = 1 + std::max(height(m->left), height(m->right));
        return m;
    }

    TreeNode* addBST3Impl(TreeNode* node, T data);

    TreeNode* min(TreeNode* node) {
        assert(node != nullptr);
        TreeNode* min = node;
        while (min->left != nullptr) {
            min = min->left;
        }
        return min;
    }
    TreeNode* deleteMin(TreeNode* node) {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = deleteMin(node->left);
        node->height = 1 + std::max(height(node->left), height(node->right));
        return balance(node);
    }

    TreeNode* removeBST2Impl(TreeNode* node, T data) {
        if (node == nullptr) {
            return node;
        }
        if (data < node->data) {
            node->left = removeBST2Impl(node->left, data);
        } else if (data > node->data) {
            node->right = removeBST2Impl(node->right, data);
        } else {
            if (node->left == nullptr) {
                TreeNode* tmp = node->right;
                delete node;
                return tmp;
            }
            if (node->right == nullptr) {
                TreeNode* tmp = node->left;
                delete node;
                return tmp;
            }
            TreeNode* m = min(node->right);
            //printf("min = %d\n", m->data);
            m->right = deleteMin(node->right);
            m->left = node->left;
            m->height = 1 + std::max(height(m->left), height(m->right));
            delete node;
            return balance(m);
        }
        node->height = 1 + std::max(height(node->left), height(node->right));
        return balance(node);
    }

    bool findBSTImpl(TreeNode* node, T data) {
        if (node == nullptr) {
            return false;
        }

        if (data < node->data && node->left != nullptr) {
            return findBSTImpl(node->left, data);
        }
        else if (data > node->data  && node->right != nullptr) {
            return findBSTImpl(node->right, data);
        } else if (data == node->data) {
            return true;
        }
        return false;
    }

    TreeNode** travelToLastByBST(TreeNode** node, T data) {
        if (*node == nullptr) {
            return node;
        }
        if (data < (*node)->data) {
            if ((*node)->left != nullptr) {
                return travelToLastByBST(&((*node)->left), data);
            }
            return &((*node)->left);
        } else if (data > (*node)->data) {
            if ((*node)->right != nullptr) {
                return travelToLastByBST(&((*node)->right), data);
            }
            return &((*node)->right);
        }
        return nullptr;
    }

    void travelPreOrderImpl(TreeNode* node, DataVisitor visitor) {
        if (node == nullptr) {
            return;
        }
        visitor(node->data);
        travelPreOrderImpl(node->left, visitor);
        travelPreOrderImpl(node->right, visitor);
    }

    void travelInOrderImpl(TreeNode* node, DataVisitor visitor) {
        if (node == nullptr) {
            return;
        }
        
        travelInOrderImpl(node->left, visitor);
        visitor(node->data);
        travelInOrderImpl(node->right, visitor);
    }

    void travelLevelImpl(TreeNode* node, NodeVisitor visitor) {
        std::list<TreeNode*> queue;

        if (node != nullptr) {
            queue.push_back(node);
        }

        while (!queue.empty()) {
            TreeNode* cur = queue.front();
            queue.pop_front();
            if (cur->left != nullptr) {
                queue.push_back(cur->left);
            }
            if (cur->right != nullptr) {
                queue.push_back(cur->right);
            }
            if (!visitor(cur)) {
                break;
            }
        }
    }

    void travelLevelImpl(TreeNode* node, DataVisitor visitor) {
        std::list<TreeNode*> queue;

        if (node != nullptr) {
            queue.push_back(node);
        }

        while (!queue.empty()) {
            TreeNode* cur = queue.front();
            queue.pop_front();
            visitor(cur->data);
            if (cur->left != nullptr) {
                queue.push_back(cur->left);
            }
            if (cur->right != nullptr) {
                queue.push_back(cur->right);
            }
        }
    }

    TreeNode** travelToLastByLevel(TreeNode** node) {
        std::list<TreeNode**> queue;
        queue.push_back(node);
        TreeNode** cur = nullptr;

        while (!queue.empty()) {
            cur = queue.front();
            queue.pop_front();
            if (*cur == nullptr) {
                break;
            }

            queue.push_back(&(*cur)->left);
            queue.push_back(&(*cur)->right);
        }

        return cur;
    }

    
    TreeNode* root;
};

template <class T>
void Tree<T>::addBST2(T data) {
    if (root == nullptr) {
        newNode(&root, data);
        return;
    }

    TreeNode* cur = root;
    TreeNode* prev = nullptr;
    while (cur != nullptr) {
        if (data == cur->data) {
            return;
        }
        prev = cur;
        if (data > cur->data) {
            cur = cur->right;
        } else if (data < cur->data) {
            cur = cur->left;
        }
    }

    if (prev != nullptr) {
        if (data > prev->data) {
            newNode(&(prev->right), data);
        } else if (data < prev->data) {
            newNode(&(prev->left), data);
        }
    }
}

template <class T>
void Tree<T>::addBST3(T data) {
    // 使用递归，每次修改当前节点
    root = addBST3Impl(root, data);
}

template <class T>
typename Tree<T>::TreeNode* Tree<T>::addBST3Impl(typename Tree<T>::TreeNode* node, T data) {
    // printf("addBST3Impl %d\n", data);
    if (node == nullptr) {
        // 当前节点为空，说明已经找到位置了，则创建新节点
        // printf("new node %d\n", data);
        return new typename Tree<T>::TreeNode(data, nullptr, nullptr);
    }

    // 数据大于或者小于当前节点，则继续迭代下去修改相应的左右节点
    if (data < node->data) {
        // printf("small than %d\n", data);
        node->left = addBST3Impl(node->left, data);
    } else if(data > node->data) {
        // printf("larger than %d\n", data);
        node->right = addBST3Impl(node->right, data);
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    // 如果数据已经存在，说明不用修改，直接返回当前节点
    // printf("before balance\n");
    return balance(node);
}

template <class T>
bool Tree<T>::findBST2(T data) {
    TreeNode* cur = root;
    while (cur != nullptr) {
        if (data == cur->data) {
            break;
        }
        if (data > cur->data) {
            cur = cur->right;
        } else if (data < cur->data) {
            cur = cur->left;
        }
    }
    return cur != nullptr;
}

template <class T>
void Tree<T>::removeBST(T data) {
    TreeNode* cur = root;
    TreeNode* prev = nullptr;

    while (cur != nullptr) {
        if (data == cur->data) {
            // printf("#### find data\n");
            break;
        }
        prev = cur;
        if (data > cur->data) {
            cur = cur->right;
        } else if (data < cur->data) {
            cur = cur->left;
        }
    }

    if (cur == nullptr) {
        return;
    }

    if (cur->left == nullptr || cur->right == nullptr) {
        // printf("#### delete data\n");
        TreeNode* child = cur->left != nullptr ? cur->left : cur->right;
        if (prev != nullptr) {
            if (prev->left == cur) {
                prev->left = child;
            } else {
                // printf("#### delete2 data %d, %d, %d\n", child->data, prev->data, cur->data);
                prev->right = child;
            }
            delete cur;
            return;
        } else {
            root = child;
            delete cur;
        }
    }

    TreeNode* tmp = cur->right;
    while (tmp->left != nullptr) {
        tmp = tmp->left;
    }

    T tmp_data = tmp->data;
    removeBST(tmp->data);
    cur->data = tmp_data;
}

}