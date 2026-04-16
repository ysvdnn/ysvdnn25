#ifndef NPCFORM_H
#define NPCFORM_H

#include <QDialog>
#include "npc.h"

class NpcForm : public QDialog {
    Q_OBJECT

public:
    bool printed;
    explicit NpcForm(NPC* npc, QWidget* parent = nullptr);

private slots:
    void onPrintClicked();
    void onCancelClicked();
};

#endif
