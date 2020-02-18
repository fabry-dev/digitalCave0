#include "ledscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qthread.h"
#include "qlayout.h"

#include "qmediaplayer.h"


ledScreen::ledScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    setStyleSheet("QLabel { background-color : red; }");
    resize(1920,1080);


    QLabel *bg = new QLabel(this);
    bg->resize(this->size());
    bg->show();
    bg->raise();

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(true);
    bgVp->show();

    connect(bgVp,SIGNAL(videoRestart()),this,SIGNAL(bgRestart()));

    QTimer::singleShot(10,this,SLOT(loadPlayer()));


}

void ledScreen::loadPlayer()
{
    bgVp->lower();
    bgVp->loadFilePaused(PATH+"ledBg.mp4");
    bgVp->play();
}




void ledScreen::startVideo(void)
{
    if(stopped)
    {
        stopped = false;
        QTimer::singleShot(0,bgVp,SLOT(play()));
        emit sendMsg(msgStartVideo);
    }
    else
    {
        stopped = true;
        QTimer::singleShot(0,bgVp,SLOT(stopAndHide()));
        emit sendMsg(msgStopVideo);
    }



}


void ledScreen::stopVideo(void)
{

    bgVp->pause();
}

void ledScreen::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==16777220)//enter
    {
        startVideo();

    }
   else if(ev->key() == 16777216)
   {
        emit sendMsg(msgQuit);
        exit(0);
   }

}


