#include "BinaryTree.h"

#include <algorithm>
#include <queue>
#include <stdexcept>
#include <string>

namespace {

int parseValue(const std::string& tok) {
    try {
        size_t pos = 0;
        int v = std::stoi(tok, &pos);
        if (pos != tok.size()) throw std::invalid_argument("");
        return v;
    } catch (const std::exception&) {
        throw std::runtime_error("Некорректное значение узла: \"" + tok + "\"");
    }
}

void reversePreorderRec(const Node* n, std::vector<const Node*>& out) {
    if (!n) return;
    out.push_back(n);                         // У
    reversePreorderRec(n->right.get(), out);  // П
    reversePreorderRec(n->left.get(), out);   // Л
}

long long leavesSumRec(const Node* n) {
    if (!n) return 0;
    if (!n->left && !n->right) return n->value;
    return leavesSumRec(n->left.get()) + leavesSumRec(n->right.get());
}

int heightRec(const Node* n) {
    if (!n) return 0;
    return 1 + std::max(heightRec(n->left.get()), heightRec(n->right.get()));
}

}  // namespace

BinaryTree BinaryTree::fromStream(std::istream& in) {
    BinaryTree t;

    if (in.peek() == 0xEF) {
        char bom[3];
        in.read(bom, 3);
    }

    std::string tok;
    if (!(in >> tok) || tok == "-") return t;

    t.root_ = std::make_unique<Node>(parseValue(tok));
    std::queue<Node*> q;
    q.push(t.root_.get());

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        for (auto* slot : {&cur->left, &cur->right}) {
            if (!(in >> tok)) return t;
            if (tok == "-") continue;
            *slot = std::make_unique<Node>(parseValue(tok));
            q.push(slot->get());
        }
    }
    return t;
}

std::vector<const Node*> BinaryTree::reversePreorderNodes() const {
    std::vector<const Node*> out;
    reversePreorderRec(root_.get(), out);
    return out;
}

std::vector<int> BinaryTree::reversePreorder() const {
    std::vector<int> out;
    for (const Node* n : reversePreorderNodes()) out.push_back(n->value);
    return out;
}

long long BinaryTree::leavesSum() const { return leavesSumRec(root_.get()); }

int BinaryTree::height() const { return heightRec(root_.get()); }
