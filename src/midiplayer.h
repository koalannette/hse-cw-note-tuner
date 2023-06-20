#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QObject>

#include <windows.h>
#include "notemodel.h"

class MidiPlayer : public QObject
{
    Q_OBJECT

signals:
    void musicEnded();

public:
    static MidiPlayer& getInstance()
    {
        static MidiPlayer instance;
        return instance;
    }

    void playNote(NoteModel* note);
    void playNotesAsync(std::vector<NoteModel>& notes);
    void stopNotes();

private:
    MidiPlayer();
    ~MidiPlayer();

    bool playing = false;

    MidiPlayer(const MidiPlayer&) = delete;
    MidiPlayer& operator=(const MidiPlayer&) = delete;

    void sendMidiNoteOn(int noteNumber, int velocity);
    void sendMidiNoteOff(int noteNumber);

    HMIDIOUT midiOut;
};

#endif // MIDIPLAYER_H
