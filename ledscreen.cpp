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

    vp = new mpvWidget(this);
    vp->resize(size());

    vp->setLoop(true);
    vp->show();


    stopped = true;

    QTimer::singleShot(10,this,SLOT(loadPlayer()));

}

void ledScreen::loadPlayer()
{
vp->lower();
vp->loadFilePaused(PATH+"video.mp4");
}



void ledScreen::startVideo(void)
{
    if(stopped)
    {
        stopped = false;
        QTimer::singleShot(25,vp,SLOT(play()));
        emit msgVideoStart();
    }
    else
    {
        stopped = true;
                QTimer::singleShot(25,vp,SLOT(stopAndHide()));
        emit msgVideoStop();
    }



}


void ledScreen::stopVideo(void)
{

    vp->pause();
}

void ledScreen::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==16777220)//enter
    {
        startVideo();

    }
   else if(ev->key() == 16777216)
        exit(0);

}


