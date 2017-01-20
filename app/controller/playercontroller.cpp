#include "playercontroller.h"

TPlayerController::TPlayerController(QObject *parent) :
    TAbstractController(parent)
{

}

void TPlayerController::joint(TGuiManager *gui, TCore *core)
{
    Q_ASSERT(gui);
    Q_ASSERT(core);

    TAbstractController::joint(gui, core);

    mPlayerCore = core->player();
    Q_ASSERT(mPlayerCore);

    mPlaylistCore = core->playlist();
    Q_ASSERT(mPlaylistCore);

    mMainWindow = gui->mainWindow();
    Q_ASSERT(mMainWindow);

    QStringList titles;
    titles.append("13: 岁月无声 beyond IV (from 1983-2003) contributed");
    titles.append("标题: 岁月无声 beyond IV");
    titles.append("艺术家: beyond beyond IV");
    titles.append("专辑: beyond IV (from 1983-2003) contributed to beyond.Spirit of wong.");
    titles.append("格式: MP3 44KHZ 320K");

    mMainWindow->setCaption("fulkfour is coming!");
    mMainWindow->setTitles(titles);
    mMainWindow->setTime(99, 354);
}

void TPlayerController::slotRequestPlay(int pIndex, int mIndex, int tIndex)
{
    if(!mPlaylistCore || !mPlayerCore)
        return;

    TPlaylistItem *playlistItem = mPlaylistCore->playlistItem(pIndex);
    if(playlistItem)
    {
        TMusicItem *musicItem = playlistItem->musicItem(mIndex);
        if(musicItem)
        {
            TTrackItem *trackItem = musicItem->trackItem(tIndex);
            if(trackItem)
            {
                mPlayerCore->setTrack(trackItem);
            }
        }
    }
}

void TPlayerController::slotTimerEvent()
{
}
