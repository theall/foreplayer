#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include "playercontroller.h"
#include "playlistcontroller.h"

class TThread : public QThread
{
    Q_OBJECT

public:
    explicit TThread(TGuiManager* window=0);
    ~TThread(){ }

    // QThread interface
protected:
    void run() Q_DECL_OVERRIDE;

private slots:
    void playClicked()
    {
        mPlaying = true;
    }
    void pauseClicked()
    {
        mPlaying = false;
    }
private:
    TGuiManager* mManager;
    bool mPlaying;
};

class TMainController : public TAbstractController
{
    Q_OBJECT
public:
    explicit TMainController(QObject *parent = 0);
    ~TMainController();

    void joint(TGuiManager *manager, TCore *core);

signals:

private slots:
    void slotQuitApp();

private:
    TThread *mThread;

    TMainWindow *mMainWindow;
    TPlayerCore *mPlayerCore;

    TPlayerController *mPlayerController;
    TPlaylistController *mPlaylistController;

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // TCONTROLLER_H