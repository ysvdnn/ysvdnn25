#pragma once

#include <istream>
#include <memory>
#include <vector>

struct Node {
    int value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    explicit Node(int v) : value(v) {}
};

class BinaryTree {
public:
    BinaryTree() = default;

    static BinaryTree fromStream(std::istream& in);

    bool empty() const { return !root_; }
    const Node* root() const { return root_.get(); }

    std::vector<const Node*> reversePreorderNodes() const;
    std::vector<int> reversePreorder() const;

    long long leavesSum() const;

    int height() const;

private:
    std::unique_ptr<Node> root_;
};
