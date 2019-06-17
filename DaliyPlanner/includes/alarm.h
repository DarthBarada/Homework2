#ifndef ALARM_H
#define ALARM_H

#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QDir>
#include <QMessageBox>

class Alarm
{
 QMediaPlayer player;
public:
Alarm()
    {

    }
virtual ~Alarm()
    {
        player.~QMediaPlayer();
    }

void play_alarm()
    {
       player.setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/sound/alarm.mp3"));
       player.setVolume(50);
       player.play();
    }
void play_signal()
    {
         player.setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/sound/cnock.mp3"));
         player.setVolume(50);
         player.play();
    }
void play_error()
    {
         player.setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/sound/error.mp3"));
         player.setVolume(50);
         player.play();
    }
};

#endif // ALARM_H
