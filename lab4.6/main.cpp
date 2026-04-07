#include <QApplication>
#include "TicketWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TicketWindow window;
    window.show();
    return app.exec();
}
