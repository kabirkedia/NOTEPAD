//
// Created by kabir on 06/02/21.
//

#ifndef NOTEPAD_NOTEPAD_H
#define NOTEPAD_NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class notepad;
}
QT_END_NAMESPACE

class notepad : public QMainWindow {
Q_OBJECT

public:
    explicit notepad(QWidget *parent = nullptr);

    ~notepad() override;

private slots:

    void newDocument();

    void cut();

    void copy();

    void paste();

    void undo();

    void redo();

    void open();

    void save();

    void saveAs();

    void print();

    void selectFont();

    void selectBold(bool bold);

    void selectUnderline(bool underline);

    void selectItalic(bool italic);

    static void exit();

    void about();

private:
    Ui::notepad *ui;
    QString currentFile;
};

#endif //NOTEPAD_NOTEPAD_H
