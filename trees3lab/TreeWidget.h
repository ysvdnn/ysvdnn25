#pragma once

#include "BinaryTree.h"

#include <QPainter>
#include <QWidget>

#include <algorithm>
#include <unordered_map>
#include <vector>

class TreeWidget : public QWidget {
public:
    explicit TreeWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumSize(480, 320);
    }

    void setTree(const BinaryTree* tree) {
        tree_ = tree;
        visit_.clear();
        update();
    }
    void setVisitOrder(const std::vector<const Node*>& order) {
        visit_.clear();
        for (size_t i = 0; i < order.size(); ++i) visit_[order[i]] = static_cast<int>(i) + 1;
        update();
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.fillRect(rect(), Qt::white);

        if (!tree_ || tree_->empty()) {
            p.setPen(Qt::gray);
            p.drawText(rect(), Qt::AlignCenter, "Дерево не загружено");
            return;
        }

        Pos pos;
        int cols = 0;
        layout(tree_->root(), 0, cols, pos);
        const int levels = tree_->height();

        const double margin = 40.0;
        const double stepX = cols > 1 ? (width() - 2 * margin) / (cols - 1) : 0.0;
        const double stepY = levels > 1 ? (height() - 2 * margin) / (levels - 1) : 0.0;

        auto point = [&](const Node* n) {
            const auto [c, d] = pos.at(n);
            const double x = cols > 1 ? margin + c * stepX : width() / 2.0;
            const double y = levels > 1 ? margin + d * stepY : height() / 2.0;
            return QPointF(x, y);
        };

        double r = 22.0;
        if (cols > 1) r = std::min(r, stepX * 0.45);
        if (levels > 1) r = std::min(r, stepY * 0.45);
        r = std::max(r, 6.0);

        // рёбра
        p.setPen(QPen(Qt::darkGray, 2));
        for (const auto& kv : pos) {
            const Node* n = kv.first;
            if (n->left) p.drawLine(point(n), point(n->left.get()));
            if (n->right) p.drawLine(point(n), point(n->right.get()));
        }

        // узлы
        QFont font = p.font();
        font.setPixelSize(std::max(8, static_cast<int>(r * 0.9)));
        QFont small = font;
        small.setPixelSize(std::max(7, static_cast<int>(r * 0.6)));

        for (const auto& kv : pos) {
            const Node* n = kv.first;
            const QPointF c = point(n);
            const auto it = visit_.find(n);

            p.setPen(QPen(Qt::black, 2));
            p.setBrush(it != visit_.end() ? QColor(190, 220, 255) : QColor(Qt::white));
            p.drawEllipse(c, r, r);

            p.setFont(font);
            p.drawText(QRectF(c.x() - r, c.y() - r, 2 * r, 2 * r), Qt::AlignCenter,
                       QString::number(n->value));

            if (it != visit_.end()) {
                p.setFont(small);
                p.setPen(QColor(200, 0, 0));
                p.drawText(QPointF(c.x() + r * 0.75, c.y() - r * 0.85), QString::number(it->second));
            }
        }
    }

private:
    using Pos = std::unordered_map<const Node*, std::pair<int, int>>;

    static void layout(const Node* n, int depth, int& col, Pos& pos) {
        if (!n) return;
        layout(n->left.get(), depth + 1, col, pos);
        pos[n] = {col++, depth};
        layout(n->right.get(), depth + 1, col, pos);
    }

    const BinaryTree* tree_ = nullptr;
    std::unordered_map<const Node*, int> visit_;
};
