#include <QApplication>
#include "qwindow.h"
#include "qscreen.h"
#include "qwidget.h"
#include "touchscreen.h"
#include "ledscreen.h"
#include "qdebug.h"
#include "QPushButton"
#include "qmessagebox.h"
#include "udpserver.h"

#define PATH_DEFAULT (QString)"/home/fred/Dropbox/Taf/PTL/ImmersiveRoom/kiosk0/files/"










int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QString PATH;
    QStringList params = a.arguments();
    if(params.size()>1)
        PATH = params[1];
    else
        PATH=PATH_DEFAULT;

    bool HIDE_CURSOR=false;
    bool DEBUG=false;

    QFile file(PATH+"config.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"no config file";

    }
    else
    {

        QTextStream in(&file);

        QString  line;
        QString paramName,paramValue;
        QStringList params;


        while(!in.atEnd()) {
            line = in.readLine();
            line = (line.split("#"))[0];
            params = line.split("=");
            if(params.size()>=2)
            {
                paramName = params[0];
                paramValue = params[1];

                if (paramName.mid(0,6)=="CURSOR")
                    HIDE_CURSOR = (paramValue=="NO");
                else if (paramName.mid(0,5)=="DEBUG")
                    DEBUG = (paramValue=="YES");
                else
                    qDebug()<<paramName<<" - "<<paramValue;
            }
        }
        file.close();

    }




    if (HIDE_CURSOR)
    {
        QCursor cursor(Qt::BlankCursor);
        a.setOverrideCursor(cursor);
        a.changeOverrideCursor(cursor);
    }


    UDPServer *server = new UDPServer(NULL);



    touchScreen *ts = new touchScreen(NULL,PATH);
    ts->setGeometry(a.screens()[1]->geometry().x(),a.screens()[1]->geometry().y(),1920,1080);
    ts->showFullScreen();


    ledScreen * ls = new ledScreen(NULL,PATH);
    ls->setGeometry(a.screens()[0]->geometry().x(),a.screens()[0]->geometry().y(),1920,1152);
    ls->showFullScreen();

    a.connect(ls,SIGNAL(bgRestart()),ts,SIGNAL(bgShouldRestart()));

    a.connect(ls,SIGNAL(sendMsg(QByteArray)),server,SLOT(sendData(QByteArray)));
    a.connect(ts,SIGNAL(introVideoStarted()),ls,SLOT(startIntroVideo()));
    a.connect(ts,SIGNAL(introVideoStopped()),ls,SLOT(stopIntroVideo()));

    a.connect(ts,SIGNAL(introVideoStarted()),server,SLOT(startIntro()));
    a.connect(ts,SIGNAL(introVideoStopped()),server,SLOT(stopIntro()));


    a.connect(ts,SIGNAL(startContent(int)),ls,SLOT(playContent(int)));
    a.connect(ts,SIGNAL(stopContent()),ls,SLOT(stopContent()));
    a.connect(ls,SIGNAL(videoOver()),ts,SLOT(goBack()));

    return a.exec();

}
