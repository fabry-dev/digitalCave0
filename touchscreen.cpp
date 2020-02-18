#include "touchscreen.h"
#include "math.h"
#include "qdebug.h"



touchScreen::touchScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    resize(1080,1920);
    setStyleSheet("QLabel { background-color : white; }");

    QLabel *bg = new QLabel(this);
    bg->resize(this->size());
    bg->show();
    bg->raise();

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(false);
    bgVp->show();

    connect(this,SIGNAL(bgShouldRestart()),bgVp,SLOT(rewind()));

    QTimer::singleShot(10,this,SLOT(loadPlayer()));


}

void touchScreen::loadPlayer()
{
    bgVp->lower();
    bgVp->loadFilePaused(PATH+"touchBg.mp4");
    bgVp->play();
}


