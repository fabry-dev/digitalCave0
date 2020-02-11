#include "ledscreen.h".h"
#include "math.h"
#include "qdebug.h"


ledScreen::ledScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    setStyleSheet("QLabel { background-color : green; }");

    vp = new mpvWidget(this);
    vp->resize(this->size());
    vp->show();

}



