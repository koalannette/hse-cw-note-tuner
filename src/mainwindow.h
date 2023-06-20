#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QMessageBox>

#include "notetablewidget.h"
#include "spectrumwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QMessageBox* msgBox = nullptr;

    QVBoxLayout* mainLayout;
    QTabWidget* tabs;
    QScrollArea* noteTableScroll;

    QWidget* fileLoaderWidget;
    QWidget* microWidget;

    QPushButton* fileLoadBtn;
    QPushButton* recordBtn;

    QPushButton* playNotesBtn;
    QPushButton* outputMidiBtn;

    SpectrumWidget* spectrum;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initFileWidget();
    void initMicroWidget();

    void loadFile();
    void toggleRecord();
    void writeFile();
};
#endif // MAINWINDOW_H
