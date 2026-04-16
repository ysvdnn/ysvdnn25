#include "npc.h"
#include "npcForm.h"

bool MagP::Craft(QWidget* parent) {
    NpcForm form(this, parent);
    form.exec();
    return form.printed;
}

bool VragP::Craft(QWidget* parent) {
    NpcForm form(this, parent);
    form.exec();
    return form.printed;
}
