#include "touchscreen.h"
#include "math.h"
#include "qdebug.h"



touchScreen::touchScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    resize(1920,1080);
    setStyleSheet("QLabel { background-color : white; }");
}

