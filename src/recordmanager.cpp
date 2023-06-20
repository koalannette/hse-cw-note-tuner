#include "recordmanager.h"
#include "constants.h"
#include "notemanager.h"

#include <QDebug>

BOOL CALLBACK recordingCallback(HRECORD handle, const void* buffer, DWORD length, void* user)
{
    qDebug() << "Recording";

    RecordManager::getInstance()->putData(handle, buffer, length);
    return true;
}

RecordManager::RecordManager()
{
    if (!BASS_RecordInit(-1)) {
        return;
    }
}

void RecordManager::putData(HRECORD handle, const void *buffer, DWORD length)
{
    BASS_StreamPutData(outStream, buffer, length);
    qDebug() << "Stream put:" << BASS_ErrorGetCode();
}

void RecordManager::startRecording()
{
    emit recordingStarted();

    recording = true;
    outStream = BASS_StreamCreate(44100, 1, BASS_STREAM_DECODE | BASS_SAMPLE_MONO | BASS_SAMPLE_FLOAT, STREAMPROC_PUSH, 0);
    rec = BASS_RecordStart(44100, 1, BASS_SAMPLE_FLOAT, recordingCallback, nullptr);
}

void RecordManager::stopRecording()
{
    emit recordingEnded();

    BASS_ChannelStop(rec);
    recording = false;
    NoteManager::getInstance().processStream(outStream);

    BASS_StreamFree(outStream);
    BASS_StreamFree(rec);
}

HRECORD RecordManager::getRec() const
{
    return rec;
}
