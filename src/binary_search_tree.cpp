#include "project/binary_search_tree.h"

#include <algorithm>
#include <stdexcept>

BinarySearchTree::BinarySearchTree() : root_(nullptr), size_(0) {}

BinarySearchTree::~BinarySearchTree() {
    deleteSubtree(root_);
}

void BinarySearchTree::deleteSubtree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

bool BinarySearchTree::insert(int value) {
    const std::size_t oldSize = size_;
    root_ = insertRecursive(root_, value);
    return size_ > oldSize;
}

bool BinarySearchTree::remove(int value) {
    const std::size_t oldSize = size_;
    root_ = removeRecursive(root_, value);
    return size_ < oldSize;
}

bool BinarySearchTree::search(int value) const {
    return searchRecursive(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    return search(value);
}

bool BinarySearchTree::empty() const noexcept {
    return size_ == 0;
}

std::size_t BinarySearchTree::size() const noexcept {
    return size_;
}

int BinarySearchTree::height() const {
    return heightRecursive(root_);
}

std::vector<int> BinarySearchTree::inorderTraversal() const {
    std::vector<int> result;
    inorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::preorderTraversal() const {
    std::vector<int> result;
    preorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::postorderTraversal() const {
    std::vector<int> result;
    postorderRecursive(root_, result);
    return result;
}

int BinarySearchTree::minimum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return minimumRecursive(root_);
}

int BinarySearchTree::maximum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return maximumRecursive(root_);
}

TreeNode* BinarySearchTree::insertRecursive(TreeNode* node, int value) {
    // Base case: empty spot found, so the new node goes here.
    if (node == nullptr) {
        ++size_;
        return new TreeNode(value);
    }

    // Recursive case: go left for smaller values, right for larger ones.
    // Duplicates are ignored.
    if (value < node->value) {
        node->left = insertRecursive(node->left, value);
    } else if (value > node->value) {
        node->right = insertRecursive(node->right, value);
    }
    return node;
}

TreeNode* BinarySearchTree::removeRecursive(TreeNode* node, int value) {
    // Base case: value is not in the tree.
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->value) {
        node->left = removeRecursive(node->left, value);
        return node;
    }
    if (value > node->value) {
        node->right = removeRecursive(node->right, value);
        return node;
    }

    // Zero or one child: replace the node with its only child (or nullptr).
    if (node->left == nullptr || node->right == nullptr) {
        TreeNode* child = (node->left != nullptr) ? node->left : node->right;
        delete node;
        --size_;
        return child;
    }

    // Two children: copy the in-order successor's value here,
    // then remove the successor from the right subtree.
    const int successor = minimumRecursive(node->right);
    node->value = successor;
    node->right = removeRecursive(node->right, successor);
    return node;
}

bool BinarySearchTree::searchRecursive(const TreeNode* node, int value) const {
    // Base case: reached an empty subtree or found the value.
    if (node == nullptr) {
        return false;
    }
    if (value == node->value) {
        return true;
    }

    // Recursive case: only one side can contain the value.
    if (value < node->value) {
        return searchRecursive(node->left, value);
    }
    return searchRecursive(node->right, value);
}

void BinarySearchTree::inorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (node == nullptr) {
        return;
    }
    inorderRecursive(node->left, result);
    result.push_back(node->value);
    inorderRecursive(node->right, result);
}

void BinarySearchTree::preorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (node == nullptr) {
        return;
    }
    result.push_back(node->value);
    preorderRecursive(node->left, result);
    preorderRecursive(node->right, result);
}

void BinarySearchTree::postorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (node == nullptr) {
        return;
    }
    postorderRecursive(node->left, result);
    postorderRecursive(node->right, result);
    result.push_back(node->value);
}

int BinarySearchTree::heightRecursive(const TreeNode* node) const {
    // Base case: an empty tree has height 0.
    if (node == nullptr) {
        return 0;
    }
    // Recursive case: 1 for this node plus the taller subtree.
    return 1 + std::max(heightRecursive(node->left), heightRecursive(node->right));
}

int BinarySearchTree::minimumRecursive(const TreeNode* node) const {
    // The smallest value is the leftmost node.
    if (node->left == nullptr) {
        return node->value;
    }
    return minimumRecursive(node->left);
}

int BinarySearchTree::maximumRecursive(const TreeNode* node) const {
    // The largest value is the rightmost node.
    if (node->right == nullptr) {
        return node->value;
    }
    return maximumRecursive(node->right);
}
