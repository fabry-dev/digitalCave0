#include "touchscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qpushbutton.h"


touchScreen::touchScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    resize(1080,1920);

    QLabel *bg = new QLabel(this);
    bg->resize(this->size());
    bg->show();
    bg->raise();

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(false);
    bgVp->show();


    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->show();
    introVp->setMute(false);
    connect(introVp,SIGNAL(videoPaused()),this,SLOT(stopIntroVideo()));
    connect(introVp,SIGNAL(clicked(QPoint)),this,SLOT(stopIntroVideo()));

    connect(this,SIGNAL(bgShouldRestart()),bgVp,SLOT(rewind()));
    QTimer::singleShot(10,this,SLOT(loadPlayer()));


    QPushButton *startB = new QPushButton(this);
    startB->setText("Start video");
    startB->resize(400,400);
    startB->move((width()-startB->width())/2,(height()-startB->height())/2);
    startB->show();
    connect(startB,SIGNAL(clicked(bool)),this,SLOT(startIntroVideo()));


}


void touchScreen::startIntroVideo()
{
    emit introVideoStarted();
    introVp->playAndRaise();
    introVp->raise();

}

void touchScreen::stopIntroVideo()
{
    introVp->lower();
    emit introVideoStopped();
    introVp->pause();
    introVp->rewind();
}





void touchScreen::loadPlayer()
{

    bgVp->loadFilePaused(PATH+"touchBg0.mp4");
    bgVp->play();

    introVp->loadFilePaused(PATH+"touchIntro0.mp4");

}


