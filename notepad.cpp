//
// Created by kabir on 06/02/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_notepad.h" resolved
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB
#include <QFont>
#include <QFontDialog>
#include <QAction>

#include "notepad.h"
#include "ui_notepad.h"

notepad::notepad(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::notepad)
        {
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
//functions defined
    connect(ui->actionNew, &QAction::triggered, this, &notepad::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &notepad::open);
    connect(ui->actionSave, &QAction::triggered, this ,&notepad::save);
    connect(ui->actionSaveAs, &QAction::triggered, this, &notepad::saveAs);
    connect(ui->actionPrint, &QAction::triggered, this ,&notepad::print);
    connect(ui->actionCut, &QAction::triggered, this ,&notepad::cut);
    connect(ui->actionPaste, &QAction::triggered, this, &notepad::paste);
    connect(ui->actionCopy, &QAction::triggered, this ,&notepad::copy);
    connect(ui->actionUndo, &QAction::triggered, this ,&notepad::undo);
    connect(ui->actionRedo, &QAction::triggered, this ,&notepad::redo);
    connect(ui->actionExit, &QAction::triggered, this ,&notepad::exit);
    connect(ui->actionAbout, &QAction::triggered, this ,&notepad::about);
    connect(ui->actionFont, &QAction::triggered, this ,&notepad::selectFont);
    connect(ui->actionBold, &QAction::triggered, this ,&notepad::selectBold);
    connect(ui->actionItalic, &QAction::triggered, this ,&notepad::selectItalic);
    connect(ui->actionUnderline, &QAction::triggered, this ,&notepad::selectUnderline);

#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
    ui->actionPrint->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false)
    ui->actionCopy->setEnabled(false)
    ui->actionPaste->setEnabled(false)
#endif
}

notepad::~notepad() {
    delete ui;
}

void notepad::newDocument() {
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void notepad::save() {
    QString filename;
    //dont have a filename get it
    if(currentFile.isEmpty()) {
        filename = QFileDialog::getSaveFileName(this, "Save");
        currentFile = filename;
    }
    else
    {
        filename=currentFile;
    }
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"WARNING","Cannot save file"+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void notepad::saveAs()  {
    QString filename= QFileDialog::getSaveFileName(this, "Save As");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"WARNING","Cannot save file"+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void notepad::print() {
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrinterDialog dialog(&printDev, this);
    if(dialog.exec() == QDialog::Rejected)
        return;
#endif
    ui->textEdit->print(&printDev);
#endif
}

void notepad::exit() {
    QCoreApplication::quit();
}

void notepad::copy() {
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}
void notepad::cut() {
#if QT_CONFIG(clipboard)
    ui->textEdit->cut();
#endif
}

void notepad::paste() {
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}

void notepad::undo() {
    ui->textEdit->undo();
}

void notepad::redo() {
    ui->textEdit->redo();
}

void notepad::selectFont() {
    bool fontSelected;
    QFont font = QFontDialog::getFont(reinterpret_cast<bool *>(fontSelected), this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void notepad::selectUnderline(bool underline) {
    ui->textEdit->setFontUnderline(underline);
}

void notepad::selectItalic(bool italic) {
    ui->textEdit->setFontItalic(italic);
}

void notepad::selectBold(bool bold) {
    if (bold) {
        ui->textEdit->setFontWeight(QFont::Bold);
    } else {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
}
void notepad::about() {
    QMessageBox::about(this,tr("About MDI"),
                       tr("This <b>NOTEPAD</b> examples demonstrate how to code a basic text Editor using QWidgets"));
}

