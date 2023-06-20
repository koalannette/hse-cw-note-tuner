#ifndef MIDIWRITER_H
#define MIDIWRITER_H

#include "notemodel.h"

#include <MidiFile.h>
#include <QString>

class MidiWriter
{
    MidiWriter();
public:
    static bool writeToMidi(QString filename, std::vector<NoteModel>& notes);
};

#endif // MIDIWRITER_H
