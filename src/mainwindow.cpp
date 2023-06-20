#include "mainwindow.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>

#include "qdebug.h"
#include "notemanager.h"
#include "midiplayer.h"
#include "recordmanager.h"
#include "midiwriter.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    msgBox = new QMessageBox(this);

    mainLayout = new QVBoxLayout(this);
    tabs = new QTabWidget();

    noteTableScroll = new QScrollArea();
    noteTableScroll->setFixedHeight(NoteTableWidget::getInstance()->height() + 20);
    noteTableScroll->setWidget(NoteTableWidget::getInstance());

    playNotesBtn = new QPushButton("Проиграть мелодию");
    outputMidiBtn = new QPushButton("Экспорт в MIDI");
    outputMidiBtn->setDisabled(true);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(playNotesBtn);
    buttonsLayout->addWidget(outputMidiBtn);
    buttonsLayout->addStretch();

    mainLayout->addWidget(tabs);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(noteTableScroll);

    this->initFileWidget();
    this->initMicroWidget();

    connect(playNotesBtn, &QPushButton::pressed, [=]() {
        playNotesBtn->setDisabled(true);
        MidiPlayer::getInstance().playNotesAsync(NoteManager::getInstance().getNotes());
    });
    connect(outputMidiBtn, &QPushButton::pressed, this, &MainWindow::writeFile);

    connect(&MidiPlayer::getInstance(), &MidiPlayer::musicEnded, [=]() {
        playNotesBtn->setDisabled(false);
    });

    connect(&NoteManager::getInstance(), &NoteManager::processingStarted, [=]() {
        msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Обработка");
        msgBox->setText("Пожауйста подождите, идет анализ данных...");
        msgBox->setStandardButtons(QMessageBox::NoButton);
        msgBox->setModal(true);
        msgBox->show();
    });
    connect(&NoteManager::getInstance(), &NoteManager::processingFinished, [=](std::vector<NoteModel>& vec) {
        if (!vec.empty())
            outputMidiBtn->setDisabled(false);

        msgBox->deleteLater();
    });
}

MainWindow::~MainWindow() {
    BASS_Free();
}

void MainWindow::initFileWidget()
{
    fileLoaderWidget = new QWidget();

    QVBoxLayout* layout = new QVBoxLayout(fileLoaderWidget);

    fileLoadBtn = new QPushButton("Выбрать файл");
    layout->addWidget(fileLoadBtn);

    tabs->addTab(fileLoaderWidget, "Из файла");

    connect(fileLoadBtn, &QPushButton::pressed, this, &MainWindow::loadFile);
}

void MainWindow::initMicroWidget()
{
    microWidget = new QWidget();

    QVBoxLayout* layout = new QVBoxLayout(microWidget);
    spectrum = new SpectrumWidget();

    recordBtn = new QPushButton("Начать запись");
    layout->addWidget(recordBtn);
    layout->addWidget(spectrum);

    tabs->addTab(microWidget, "С микрофона");

    connect(recordBtn, &QPushButton::pressed, this, &MainWindow::toggleRecord);
}

void MainWindow::loadFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл"), "", tr("Аудио файлы (*.mp3 *.wav *.ogg)"));

    if (!filePath.isEmpty()) {
        NoteManager::getInstance().processFile(filePath);
    }
}

void MainWindow::toggleRecord()
{
    auto recManager = RecordManager::getInstance();

    if (recManager->isRecording()) {
        recordBtn->setText("Начать запись");
        recManager->stopRecording();
    } else {
        recordBtn->setText("Остановить запись");
        recManager->startRecording();
    }
}

void MainWindow::writeFile()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save MIDI File", QDir::homePath(), "MIDI Files (*.mid)");

    if (filename.isEmpty()) return;

    if (MidiWriter::writeToMidi(filename, NoteManager::getInstance().getNotes()))
    {
        QMessageBox::information(this, "Успех", "MIDI файл сохранен!");
    }
}

