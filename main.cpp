#include <QApplication>
#include "notepad.h"

int main(int argc, char *argv[]) {
    QApplication EditorApp(argc, argv);
    notepad Editor;
    Editor.show();
    return QApplication::exec();
}
