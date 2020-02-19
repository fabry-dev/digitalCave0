#ifndef MAINSCREEN_H
#define MAINSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "qtimer.h"


class touchScreen : public QLabel
{
    Q_OBJECT
public:
    explicit touchScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp;
    mpvWidget *introVp;


private slots:
    void loadPlayer(void);
    void startIntroVideo(void);
    void stopIntroVideo(void);

signals:
    void bgShouldRestart(void);
    void introVideoStarted(void);
    void introVideoStopped(void);

};

#endif // MAINSCREEN_H
