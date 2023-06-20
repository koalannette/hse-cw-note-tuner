#include "midiplayer.h"

#include <thread>
#include <chrono>

MidiPlayer::MidiPlayer()
{
    midiOutOpen(&midiOut, 0, 0, 0, CALLBACK_NULL);
}

MidiPlayer::~MidiPlayer()
{
    midiOutClose(midiOut);
}

void MidiPlayer::playNote(NoteModel *note)
{
    sendMidiNoteOn(note->getMidiNote(), note->getVelocity());
}

void MidiPlayer::playNotesAsync(std::vector<NoteModel> &notes)
{
    playing = true;
    std::thread thread([=]() {
        for (const NoteModel& note : notes) {
            if (!playing)
                break;

            sendMidiNoteOn(note.getMidiNote(), note.getVelocity());
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(note.getDuration() * 1000)));
            sendMidiNoteOff(note.getMidiNote());
        }
        emit musicEnded();
    });


    thread.detach();
}

void MidiPlayer::sendMidiNoteOn(int noteNumber, int velocity) {
    DWORD message = 0x90 | (noteNumber << 8) | (velocity << 16);
    midiOutShortMsg(midiOut, message);
}

void MidiPlayer::sendMidiNoteOff(int noteNumber) {
    DWORD message = 0x80 | (noteNumber << 8);
    midiOutShortMsg(midiOut, message);
}


