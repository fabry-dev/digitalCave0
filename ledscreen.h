#ifndef LEDSCREEN_H
#define LEDSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "alphaVideoPlayer.h"
#include "qtimer.h"
#include "msgdef.h"

class ledScreen : public QLabel
{
    Q_OBJECT
public:
    explicit ledScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *vp;
    bool stopped;
private slots:
    void startVideo(void);
    void loadPlayer(void);
    void stopVideo(void);
signals:
    void sendMsg(QByteArray msg);


protected:
     void keyPressEvent(QKeyEvent *ev);
};

#endif // LEDSCREEN_H
