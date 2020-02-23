#include "ledscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qthread.h"
#include "qlayout.h"

#include "qmediaplayer.h"


ledScreen::ledScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{

    resize(1920,1152);


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


    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->show();
    introVp->setMute(true);


    for(int i = 0;i<4;i++)
    {
        mpvWidget *demoVp = new mpvWidget(this);
        demoVp->resize(size());
        demoVp->setProperty("keep-open","yes");
        demoVp->setLoop(false);
        demoVp->lower();
        demoVp->show();
        demoVp->setMute(true);
        connect(demoVp,SIGNAL(videoPaused()),this,SIGNAL(videoOver()));
        demoVps.push_back(demoVp);
    }

    /*  alphaPlayer = new alphaVideo(this);
    alphaPlayer->resize(860,800);
    alphaPlayer->move((width()-alphaPlayer->width())/2,(height()-alphaPlayer->height())/2);
*/



connect(this,SIGNAL(videoOver()),this,SLOT(stopContent()));
    //   connect(alphaPlayer,SIGNAL(stoppedPlaying()),this,SIGNAL(videoOver()));



    QTimer::singleShot(10,this,SLOT(loadPlayer()));


}





void ledScreen::loadPlayer()
{
    bgVp->lower();
    bgVp->loadFilePaused(PATH+"ledBg0.mp4");
    bgVp->play();

    introVp->lower();
    introVp->loadFilePaused(PATH+"ledIntro0.mp4");

    for(int i = 0;i<4;i++)
    {
        demoVps[i]->lower();
        demoVps[i]->loadFilePaused(PATH+"kiosk"+QString::number(i+1)+".mp4");
    }
}


void ledScreen::startIntroVideo(void)
{

    introVp->playAndRaise();
    introVp->raise();
    introVp->show();


    qDebug()<<introVp->getProperty("width")<<introVp->getProperty("height")<<introVp->width()<<introVp->height()<<width()<<height();

}


void ledScreen::stopIntroVideo(void)
{

    introVp->lower();
    introVp->pause();
    introVp->rewind();


}



void ledScreen::playContent(int id)
{

    demoVps[id]->playAndRaise();
    demoVps[id]->raise();
    demoVps[id]->show();

    /*  alphaPlayer->addMedia(PATH+"kiosk"+QString::number(id+1)+".mp4");
    alphaPlayer->play();
    alphaPlayer->show();*/

}

void ledScreen::stopContent()
{
    //alphaPlayer->hide();
    for(auto demoVp:demoVps)
        if(demoVp->isVisible())
        {
            demoVp->lower();
            demoVp->pause();
            demoVp->rewind();
            demoVp->hide();

        }

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


