#ifndef LEDSCREEN_H
#define LEDSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "alphaVideoPlayer.h"
#include "qtimer.h"
#include "msgdef.h"
#include "QPropertyAnimation"


class ledScreen : public QLabel
{
    Q_OBJECT
public:
    explicit ledScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp,*introVp;
    std::vector<mpvWidget*> demoVps;
    bool stopped;
    alphaVideo * alphaPlayer;

private slots:
    void startVideo(void);
    void loadPlayer(void);
    void stopVideo(void);
    void startIntroVideo(void);
    void stopIntroVideo(void);
    void playContent(int id);
    void stopContent(void);
signals:
    void sendMsg(QByteArray msg);
    void bgRestart(void);
    void videoOver(void);


protected:
     void keyPressEvent(QKeyEvent *ev);
};

#endif // LEDSCREEN_H
