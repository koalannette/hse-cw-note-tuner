#include "notemanager.h"
#include "qdebug.h"

#include <aubio/aubio.h>

NoteManager::NoteManager()
{

}

std::vector<NoteModel> &NoteManager::getNotes()
{
    return notes;
}

void NoteManager::processFile(QString filename)
{
    HSTREAM stream = BASS_StreamCreateFile(false, filename.toStdWString().c_str(), 0, 0, BASS_STREAM_DECODE | BASS_SAMPLE_MONO | BASS_SAMPLE_FLOAT);
    processStream(stream);
    BASS_StreamFree(stream);
}

void NoteManager::processStream(HSTREAM stream)
{
    emit processingStarted();
    notes.clear();

    BASS_CHANNELINFO channelInfo;
    BASS_ChannelGetInfo(stream, &channelInfo);
    int samplerate = channelInfo.freq;

    int win_s = 4096;
    int hop_s = win_s / 2;

    aubio_notes_t* notes_o = new_aubio_notes("default", win_s, hop_s, samplerate);

    float audioBuffer[hop_s];

    int totalFrames = 0;
    int bytesRead = 1;

    while (bytesRead > 0) {
        bytesRead = BASS_ChannelGetData(stream, audioBuffer, hop_s * sizeof(float) | BASS_DATA_FLOAT);
        qDebug() << "Bytes read:" << bytesRead;

        fvec_t* samples = new_fvec(hop_s);
        for (int i = 0; i < hop_s; ++i) {
            samples->data[i] = audioBuffer[i];
        }
        fvec_t* new_note = new_fvec(3);
        aubio_notes_do(notes_o, samples, new_note);

        if (new_note->data[0] != 0) {
            NoteModel noteModel;
            noteModel.setMidiNote(new_note->data[0]);
            noteModel.setStartTime( totalFrames / static_cast<float>(samplerate) );
            noteModel.setVelocity(new_note->data[1]);

            if (!notes.empty()) {
                notes.back().setDuration(noteModel.getStartTime() - notes.back().getStartTime());
            }

            notes.push_back(noteModel);
            qDebug() << "Note finded!";
        }

        totalFrames += (bytesRead / 4);
    }

    emit processingFinished(notes);
}

