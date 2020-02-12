#include "videoplayer.h"

videoPlayer::videoPlayer(QWidget *parent) : QWidget(parent)
{
    player = new QMediaPlayer(this);

    videoWidget = new QVideoWidget(this);
    videoWidget->resize(size());


    playlist = new QMediaPlaylist();

    player->setPlaylist(playlist);
    player->setVideoOutput(videoWidget);
    player->setNotifyInterval(10);
    shouldPauseOnLastFrame = false;
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(onVideoPositionChanged(qint64)));
    hide();
}



void videoPlayer::resizeEvent(QResizeEvent *event)
{
    videoWidget->resize(event->size());
}

void videoPlayer::loadVideo(QString file)
{

    playlist->clear();
    playlist->addMedia( QUrl::fromLocalFile(file) );

}



void videoPlayer::setLoop(bool loop)
{

    if(loop)
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    else
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

}









void videoPlayer::play(void)
{
    player->play();
    //
    show();

}

void videoPlayer::pause(void)
{
   player->pause();
}


void videoPlayer::stopAndHide(void)
{
    player->stop();
    hide();
}


void videoPlayer::setPauseOnLastFrame(bool pause)
{
    shouldPauseOnLastFrame = pause;
}


void videoPlayer::onVideoPositionChanged(qint64 position)
{   


    if(player->state()!=QMediaPlayer::PlayingState)
        return;


   if(player->duration()<=0)
       return;



    if((shouldPauseOnLastFrame)&&(player->duration()-position <= 50))
    {

        QTimer::singleShot(0,player,SLOT(pause()));
    }
}
