#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include "notemodel.h"

#include <QObject>
#include <bass.h>

class NoteManager : public QObject
{

    Q_OBJECT

signals:
    void processingFinished(std::vector<NoteModel>& notes);
    void processingStarted();
    void processProgress(float percent);

public:
    static NoteManager& getInstance() {
        static NoteManager noteManager;
        return noteManager;
    }

    void processFile(QString filename);
    void processStream(HSTREAM stream);

    std::vector<NoteModel> &getNotes();

private:
    NoteManager();

    std::vector<NoteModel> notes;
};

#endif // NOTEMANAGER_H
