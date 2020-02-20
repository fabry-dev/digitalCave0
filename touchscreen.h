#ifndef MAINSCREEN_H
#define MAINSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "qtimer.h"
#include "powerLabel.h"

class touchScreen : public QLabel
{
    Q_OBJECT
public:
    explicit touchScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp;
    mpvWidget *introVp;
    int cornerCount;
    std::vector<powerLabel *>buttons;
    std::vector<powerLabel *>labels;
    powerLabel *backLbl;

private slots:
    void loadPlayer(void);
    void startIntroVideo(void);
    void stopIntroVideo(void);
    void buttonClick(void);
    void showSummary(void);
    void goBack(void);
    void showContent(int id);

signals:
    void bgShouldRestart(void);
    void introVideoStarted(void);
    void introVideoStopped(void);
    void startContent(int id);
    void stopContent();

protected:
    void mousePressEvent(QMouseEvent *event);

};

#endif // MAINSCREEN_H
