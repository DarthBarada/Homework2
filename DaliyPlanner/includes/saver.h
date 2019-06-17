#ifndef SAVER_H
#define SAVER_H

#pragma once
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTextCodec>
#include <iostream>
#include <QDir>
#include <QDate>
#include <QTime>

class saver:public QDir
{
QString FILE_NAME;
public:
    saver();
    QString& get_FILE_NAME();
    // Функция добавляет в конец фала запись
    void keeper(QString);
    // Функция презаписывает / создаёт файл
    void save(QString);
};

#endif // SAVER_H
