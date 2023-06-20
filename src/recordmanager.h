#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <bass.h>
#include <QObject>

class RecordManager : public QObject
{
    Q_OBJECT

signals:
    void recordingStarted();
    void recordingEnded();
    void fftProcessed(float *data);

public:
    static RecordManager* getInstance()
    {
        static RecordManager instance;
        return &instance;
    }

    bool isRecording() { return recording; }

    void startRecording();
    void stopRecording();

    HRECORD getRec() const;

private:
    HSTREAM outStream;
    HRECORD rec;
    bool recording = false;

    RecordManager();

    friend BOOL CALLBACK recordingCallback(HRECORD handle, const void* buffer, DWORD length, void* user);
    void putData(HRECORD handle, const void* buffer, DWORD length);

};

#endif // RECORDMANAGER_H
