#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QString>

#include <MidiFile.h>

class NoteModel
{

private:
    int note;
    int octave;
    int midiNote;

    float startTime;
    float duration;

    int velocity;

public:
    NoteModel();

    QString toStringLetter() const;
    QString toStringRu() const;
    QString toStringEn() const;

    void writeToMidiFile(smf::MidiFile* midiFile);
    void playMidi();

    int getNote() const;
    void setNote(int newNote);
    int getOctave() const;
    void setOctave(int newOctave);
    int getMidiNote() const;
    void setMidiNote(int newMidiNote);
    float getStartTime() const;
    void setStartTime(float newStartTime);
    float getDuration() const;
    void setDuration(float newDuration);
    int getVelocity() const;
    void setVelocity(int newVelocity);
};

#endif // NOTEMODEL_H
