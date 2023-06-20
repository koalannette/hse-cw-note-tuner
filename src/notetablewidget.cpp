#include "notetablewidget.h"

#include "notemanager.h"

NoteTableWidget* NoteTableWidget::instance = nullptr;

NoteTableWidget::NoteTableWidget()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < NOTE_COUNT; i++) {
        lines[i] = new QWidget();
        lines[i]->setObjectName("line");
        lines[i]->setFixedWidth(500);
        lines[i]->setFixedHeight(30);
        lines[i]->setStyleSheet("#line { background: #f5f5f5; border-top: 1px solid rgba(0, 0, 0, 0.5); }");
        mainLayout->addWidget(lines[i]);
    }

    this->setFixedHeight(360);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

    connect(&NoteManager::getInstance(), &NoteManager::processingStarted, this, [=]() {
        for (auto* widget : noteWidgets) widget->deleteLater();
        noteWidgets.clear();
    });
    connect(&NoteManager::getInstance(), &NoteManager::processingFinished, this, &NoteTableWidget::loadNotes);
}

void NoteTableWidget::loadNotes(std::vector<NoteModel>& notes)
{
    for (NoteModel& note : notes) {
        float x = note.getStartTime() * 100;
        float w = note.getDuration() * 100;

        int row = note.getNote();

        NoteWidget* noteWidget = new NoteWidget(&note);
        noteWidget->setParent(lines[NOTE_COUNT - row - 1]);
        noteWidget->setFixedWidth(w);
        noteWidget->move(x, 1);
        noteWidget->show();

        noteWidgets.push_back(noteWidget);
    }

    float lineW = 2000;
    if (!notes.empty())
        lineW = std::max<float>((notes.back().getStartTime() + notes.back().getDuration()) * 100, 2000);

    for (auto* line : lines)
        line->setFixedWidth(lineW);
}
