#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include "notemodel.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>

class NoteWidget : public QFrame
{
    QVBoxLayout* mainLayout;
    QLabel* noteLabel;
    NoteModel* model;

public:
    NoteWidget(NoteModel* noteModel);

    void mousePressEvent(QMouseEvent* event) override;
};

#endif // NOTEWIDGET_H
