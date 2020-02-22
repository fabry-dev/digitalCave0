#include "touchscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qpushbutton.h"


touchScreen::touchScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    resize(1920,1080);

    QLabel *bg = new QLabel(this);
    bg->resize(this->size());
    bg->show();
    bg->raise();

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(false);
    bgVp->show();
    bgVp->setAttribute(Qt::WA_TransparentForMouseEvents);
    connect(this,SIGNAL(bgShouldRestart()),bgVp,SLOT(rewindAndPlay()));

    isPlayingIntro = false;
    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->show();
    introVp->setMute(true);
    introVp->setAttribute(Qt::WA_TransparentForMouseEvents);
    connect(introVp,SIGNAL(videoPaused()),this,SLOT(stopIntroVideo()));


    connect(this,SIGNAL(bgShouldRestart()),bgVp,SLOT(rewind()));
    QTimer::singleShot(10,this,SLOT(loadPlayer()));


    int ySpacing = 100;
    int xSpacing = 100;

    for(int i = 0;i<4;i++)
    {
        QPixmap pix(PATH+"kiosk"+QString::number(i+1)+".png");
        int xOffset = (width()-2*pix.width()-xSpacing)/2;
        int yOffset = (height()-2*pix.height()-ySpacing)/2;
        QRect showGeo = QRect(xOffset+(i%2)*(pix.width()+xSpacing),yOffset+(i/2)*(pix.height()+ySpacing),pix.width(),pix.height());
        QRect hideGeo = QRect(width()/2,height(),0,0);
        powerLabel *b = new powerLabel(this,i,hideGeo,showGeo,true,false);
        b->setPixmap(pix);
        b->setScaledContents(true);
        connect(b,SIGNAL(clicked()),this,SLOT(buttonClick()));
        b->animateShow();
        buttons.push_back(b);
    }


    for(int i = 0;i<4;i++)
    {
        QPixmap pix(PATH+"kiosk"+QString::number(i+1)+".png");
        pix = pix.scaled(pix.width()*1,pix.height());

        QRect showGeo = QRect((width()-pix.width())/2,(height()-pix.height())/2,pix.width(),pix.height());
        QRect hideGeo = QRect(width()/2,0,0,0);
        powerLabel *b = new powerLabel(this,i,hideGeo,showGeo,false,false);
        b->setPixmap(pix);
        b->setScaledContents(true);
        labels.push_back(b);
    }

    int backY = 850;
    QPixmap pix(PATH+"back.png");
    backLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect((width()-pix.width())/2,backY,pix.width(),pix.height()),true);
    backLbl->hide();
    backLbl->setPixmap(pix);
    backLbl->setScaledContents(true);
    connect(backLbl,SIGNAL(clicked()),this,SLOT(goBack()));
    connect(backLbl,SIGNAL(clicked()),this,SIGNAL(stopContent()));
    connect(backLbl,SIGNAL(hideAnimationOver()),this,SLOT(showSummary()));


    cornerCount = 0;

    showSummary();

}



void touchScreen::buttonClick(void)
{

    int id = ((powerLabel*)QObject::sender())->getId();
    for(auto b:buttons)
        b->animateHide();

    showContent(id);
}



void touchScreen::showContent(int id)
{
    labels.at(id)->animateShow();
    backLbl->animateShow();
    emit startContent(id);

}




void touchScreen::goBack()
{
    backLbl->animateHide();

    for(auto l:labels)
    {
        if(l->isVisible())
            l->animateHide();
    }


}

void touchScreen::showSummary()
{
    for(auto b:buttons)
        b->animateShow();




}




void touchScreen::startIntroVideo()
{
    emit introVideoStarted();
    introVp->playAndRaise();
    introVp->raise();
    isPlayingIntro = true;

}

void touchScreen::stopIntroVideo()
{
    introVp->lower();
    emit introVideoStopped();
    introVp->pause();
    introVp->rewind();
    isPlayingIntro = false;
}


void touchScreen::mousePressEvent(QMouseEvent *event)
{
    int x0 = event->pos().x();
    int y0 = event->pos().y();
    int delta = 150;

    if((abs(x0)<delta)&&((abs(y0)<delta)))
        cornerCount = 1;
    else if((abs(width()-x0)<delta)&&((abs(y0)<delta))&&(cornerCount = 1))
    {
        cornerCount = 0;
        if(!isPlayingIntro)
            startIntroVideo();
        else
            stopIntroVideo();

    }
    else cornerCount = 0;




}


void touchScreen::loadPlayer()
{

    bgVp->loadFilePaused(PATH+"touchBg0.mp4");
    bgVp->play();

    introVp->loadFilePaused(PATH+"touchIntro0.mp4");

}


