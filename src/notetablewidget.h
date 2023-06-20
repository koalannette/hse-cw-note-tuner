#ifndef NOTETABLEWIDGET_H
#define NOTETABLEWIDGET_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "constants.h"
#include "notewidget.h"

class NoteTableWidget : public QWidget
{
    Q_OBJECT

public:
    static NoteTableWidget* getInstance()
    {
        if (instance == nullptr)
            instance = new NoteTableWidget();

        return instance;
    }

private:
    static NoteTableWidget* instance;

    void setParent(QWidget* obj) {
        QWidget::setParent(obj);
    }

    QVBoxLayout* mainLayout;
    QWidget* lines[NOTE_COUNT];
    QVector<NoteWidget*> noteWidgets;

    NoteTableWidget();

    NoteTableWidget(const NoteTableWidget&) = delete;
    NoteTableWidget& operator=(const NoteTableWidget&) = delete;

    void loadNotes(std::vector<NoteModel>& notes);
};

#endif // NOTETABLEWIDGET_H
