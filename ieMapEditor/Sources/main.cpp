#include "ieMapEditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    ieMapEditor window;
    window.show();
    window.execute();
    return application.exec();
}
