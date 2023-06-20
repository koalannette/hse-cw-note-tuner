#include "notewidget.h"

NoteWidget::NoteWidget(NoteModel* noteModel)
{
    model = noteModel;

    mainLayout = new QVBoxLayout(this);

    noteLabel = new QLabel(noteModel->toStringLetter());

    this->setFixedHeight(28);

    QColor color( ((noteModel->getNote() + 1) / 12.0) * 255,
                  60,
                  255 - ((noteModel->getNote() + 1) / 12.0) * 255);

    setStyleSheet(QString("background-color: %1; border: 0px solid black; color: white; border-radius: 10;").arg(color.name()));

    mainLayout->addStretch();
    mainLayout->addWidget(noteLabel);
    mainLayout->addStretch();
}

void NoteWidget::mousePressEvent(QMouseEvent *event)
{
    model->playMidi();
}
