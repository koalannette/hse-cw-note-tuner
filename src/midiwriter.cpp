#include "midiwriter.h"

MidiWriter::MidiWriter()
{

}

bool MidiWriter::writeToMidi(QString filename, std::vector<NoteModel> &notes)
{
    smf::MidiFile midiFile;
    midiFile.setTicksPerQuarterNote(480);

    for (NoteModel& note : notes) {
        note.writeToMidiFile(&midiFile);
    }

    midiFile.sortTracks();
    midiFile.write(filename.toStdString());

    return true;
}
