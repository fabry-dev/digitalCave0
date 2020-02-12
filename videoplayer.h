#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include "qmediaplayer.h"
#include "QVideoWidget"
#include <QResizeEvent>
#include <QMediaPlaylist>
#include "QMediaPlayerControl"
#include "QTimer"
class videoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit videoPlayer(QWidget *parent = nullptr);
    void setPauseOnLastFrame(bool pause);
private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QMediaPlaylist *playlist;
    bool shouldPauseOnLastFrame;

private slots:
    void onVideoPositionChanged(qint64 position);

public slots:
    void loadVideo(QString file);
    void play(void);
    void pause(void);
    void stopAndHide(void);
    void setLoop(bool loop);


protected:
    void resizeEvent(QResizeEvent *event);

};

#endif // VIDEOPLAYER_H
