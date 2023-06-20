#include "notemodel.h"

#include "midiplayer.h"

NoteModel::NoteModel() {}

int NoteModel::getNote() const
{
    return note;
}

void NoteModel::setNote(int newNote)
{
    note = newNote;
}

int NoteModel::getOctave() const
{
    return octave;
}

void NoteModel::setOctave(int newOctave)
{
    octave = newOctave;
}

int NoteModel::getMidiNote() const
{
    return midiNote;
}

void NoteModel::setMidiNote(int newMidiNote)
{
    midiNote = newMidiNote;

    octave = (static_cast<int>(midiNote) / 12) - 1;
    note = static_cast<int>(midiNote) % 12;
}

float NoteModel::getStartTime() const
{
    return startTime;
}

void NoteModel::setStartTime(float newStartTime)
{
    startTime = newStartTime;
}

float NoteModel::getDuration() const
{
    return duration;
}

void NoteModel::setDuration(float newDuration)
{
    duration = newDuration;
}

int NoteModel::getVelocity() const
{
    return velocity;
}

void NoteModel::setVelocity(int newVelocity)
{
    velocity = newVelocity;
}

QString NoteModel::toStringLetter() const {
    QString note_names[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

    return note_names[note] + QString::number(octave);
}

QString NoteModel::toStringRu() const {
    QString note_names[] = { "До", "До#", "Ре", "Ре#", "Ми", "Фа", "Фа#", "Соль", "Соль#", "Ля", "Ля#", "Си" };

    return note_names[note] + QString::number(octave);
}

QString NoteModel::toStringEn() const {
    QString note_names[] = { "Do", "Do#", "Re", "Re#", "Mi", "Fa", "Fa#", "So", "So#", "Lja", "Lja#", "Si" };

    return note_names[note] + QString::number(octave);
}

void NoteModel::writeToMidiFile(smf::MidiFile *midiFile) {
    double ticksPerSecond = 1000.0 / (60000.0 / (midiFile->getTicksPerQuarterNote() * 120));
    int timestampInTicks = static_cast<int>(startTime * ticksPerSecond);

    smf::MidiEvent noteOnEvent;
    noteOnEvent.tick = timestampInTicks;
    noteOnEvent.track = 0;
    noteOnEvent.setSize(3);
    noteOnEvent[0] = 0x90 | 0;
    noteOnEvent[1] = midiNote;
    noteOnEvent[2] = velocity;

    midiFile->addEvent(noteOnEvent);

    smf::MidiEvent noteOffEvent;
    noteOffEvent.tick = timestampInTicks + (duration * ticksPerSecond);
    noteOffEvent.track = 0;
    noteOffEvent.setSize(3);
    noteOffEvent[0] = 0x80 | 0;
    noteOffEvent[1] = midiNote;
    noteOffEvent[2] = 0;

    midiFile->addEvent(noteOffEvent);
}

void NoteModel::playMidi()
{
    MidiPlayer::getInstance().playNote(this);
}
