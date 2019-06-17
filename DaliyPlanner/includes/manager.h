#ifndef MANAGER_H
#define MANAGER_H

#pragma once

#include "plan.h"
#include "remind.h"
#include "meetings.h"
#include "shopping_list.h"
#include "todo_list.h"
#include "saver.h"


#include <QMultiMap>
#include <QList>
#include <QString>
#include <QQueue>
#include <QDateTime>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <algorithm>

class manager:public QDir
{
    saver a;
    QString dir="Data";
    plan temp_plan;
    remind temp_remind;
    meeting temp_meeting;
protected:

    QMultiMap <QDateTime,plan> plans;
    QMultiMap <QDateTime,remind> reminds;
    QMultiMap <QDateTime,meeting> meetings;
    QMap <QString,business> todo_list;
    QQueue <std::pair <QString,QString>> delelted;

public:
    virtual ~manager()
        {
            plans.~QMultiMap();
            reminds.~QMultiMap();
            meetings.~QMultiMap();
            /*shopping_lists.~QList();
            todo_lists.~QList();*/
        }

    void get_plans( QString file="plans.txt")
        {
            QFile in(dir+"/"+file);

            if ((in.exists())&&(in.open(QIODevice::ReadOnly)))
            {
                QString buffer="";
                QString str="";

                QDateTime new_time;
                QDate date;
                QTime time;
                int pos=0;

                    while(!in.atEnd())
                        {
                            str=in.readLine();
                            if (str=="\n" || str.isEmpty())
                                {
                                    continue;
                                }
                            for(int i=0;i<int(str.size())-1;i++)
                                {
                                    if((str[i]!='|')&& (str[i]!='\n'))
                                        {
                                          buffer+=str[i];
                                        }
                                    else
                                        {
                                            switch(pos)
                                            {
                                                case (0):
                                                    {
                                                            date=QDate::fromString(buffer,"dd.M.yyyy");buffer.clear();pos++;break;
                                                    }
                                                case (1):
                                                    {
                                                            time=QTime::fromString(buffer,"hh:mm:ss");buffer.clear();pos++;break;
                                                    }
                                                case (2):
                                                    {
                                                            temp_plan.get_prior()=buffer.toInt();buffer.clear();pos++;break;
                                                    }
                                                default:
                                                    {
                                                            temp_plan.get_description()=buffer.toUtf8();pos++;buffer.clear();
                                                    }
                                            }
                                        }
                                }
                            if (!buffer.isEmpty())
                                {
                                    temp_plan.get_description()=buffer.toUtf8();
                                }
                            new_time.setDate(date);
                            new_time.setTime(time);
                            temp_plan.get_time()=new_time;
                            plans.insert(new_time,temp_plan);
                            pos=0;
                            buffer.clear();
                        }
            }
            in.close();
        }

    void get_reminds(QString file="reminds.txt")
        {
            QFile in(dir+"/"+file);
            if ((in.exists())&&(in.open(QIODevice::ReadOnly)))
            {
                QString buffer="";
                QString str="";

                QDateTime new_time;
                QDate date;
                QTime time;
                int pos=0;

                    while(!in.atEnd())
                        {
                            str=in.readLine();
                            if (str=="\n" || str.isEmpty())
                                {
                                    continue;
                                }
                            for(int i=0;i<int(str.size());i++)
                                {
                                    if((str[i]!='|')&&(str[i]!='\n'))
                                        {
                                          buffer+=str[i];
                                        }
                                    else
                                        {
                                            switch(pos)
                                            {
                                                case (0):
                                                    {
                                                            date =QDate::fromString(buffer,"dd.M.yyyy");buffer.clear();pos++;break;
                                                    }
                                                case (1):
                                                    {
                                                            time=QTime::fromString(buffer,"hh:mm:ss");buffer.clear();pos++;break;
                                                    }
                                                default:
                                                    {
                                                            temp_remind.get_description()=buffer;buffer.clear();
                                                    }
                                            }
                                        }
                                }
                            if (!buffer.isEmpty())
                                {
                                    temp_remind.get_description()=buffer.toUtf8();
                                }
                            new_time.setDate(date);
                            new_time.setTime(time);
                            temp_remind.get_time()=new_time;
                            reminds.insert(new_time,temp_remind);
                            pos=0;
                            buffer.clear();
                        }
            }
            in.close();
        }

    void get_meetings(QString file="meetings.txt")
        {
            QFile in(dir+"/"+file);
            if ((in.exists())&&(in.open(QIODevice::ReadOnly)))
                {
                    QString buffer="";
                    QString str="";

                    QDateTime new_time;
                    QDate date;
                    QTime time;
                    int pos=0;

                        while(!in.atEnd())
                            {
                                str=in.readLine();
                                if (str=="\n" || str.isEmpty())
                                    {
                                        continue;
                                    }
                                for(int i=0;i<int(str.size());i++)
                                    {
                                        if((str[i]!='|')&& (str[i]!='\n'))
                                            {
                                              buffer+=str[i];
                                            }
                                        else
                                            {
                                                switch(pos)
                                                {
                                                    case (0):
                                                        {
                                                                date=QDate::fromString(buffer,"dd.M.yyyy");buffer.clear();pos++;break;
                                                        }
                                                    case (1):
                                                        {
                                                                time=QTime::fromString(buffer,"hh:mm:ss");buffer.clear();pos++;break;
                                                        }
                                                    default:
                                                        {
                                                                temp_meeting.get_description()=buffer;buffer.clear();
                                                        }
                                                }
                                            }
                                    }
                                if (!buffer.isEmpty())
                                    {
                                        temp_meeting.get_description()=buffer.toUtf8();
                                    }
                                new_time.setDate(date);
                                new_time.setTime(time);
                                temp_meeting.get_time()=new_time;
                                meetings.insert(new_time,temp_meeting);
                                pos=0;
                                buffer.clear();
                            }
                }
            in.close();
        }

    void get_todo(QString file="todo.txt")
        {
            QFile in(dir+"/"+file);
            todo_list.clear();
            if ((in.exists())&&(in.open(QIODevice::ReadOnly)))
                {
                    QString buffer="";
                    QString str="";

                    business temp;
                    int pos=0;

                        while(!in.atEnd())
                            {
                                str=in.readLine();
                                if (str=="\n" || str.isEmpty())
                                    {
                                        continue;
                                    }
                                for(int i=0;i<int(str.size());i++)
                                    {
                                        if((str[i]!='|')&&(str[i]!='\n'))
                                            {
                                              buffer+=str[i];
                                            }
                                        else
                                            {
                                                switch(pos)
                                                {
                                                    case (0):
                                                        {
                                                               temp.get_description()=buffer;pos++;buffer.clear();break;
                                                        }
                                                    default:
                                                        {
                                                               temp.get_status()=buffer.toInt();pos++;buffer.clear();break;
                                                        }
                                                }

                                            }
                                    }
                                if (!buffer.isEmpty())
                                    {
                                        temp.get_status()=buffer.toInt();
                                    }
                                todo_list.insert(temp.get_description(),temp);
                                pos=0;
                                buffer.clear();
                            }
                }
            in.close();
        }

    /*void search_and_clean()
        {      //  Если есть более удоюный способ нахождения меньших дат, то он мне нужен!

        // What is this?
           //- Это функция, которая проходит по всем векторам и удаляет устаревшие
            for(auto i=plans.begin();i!=plans.end();i++)
                {
                    if (i.key()<QDateTime::currentDateTime())
                        {
                            queue.push_back(std::pair<QString,QString>(i->get_time().toString(),i->get_description()));
                            plans.erase(i);
                        }
                }
            for(auto i=reminds.begin();i!=reminds.end();i++)
                {
                    if (i.key()<QDateTime::currentDateTime())
                        {
                            queue.push_back(std::pair<QString,QString>(i->get_time().toString(),i->get_description()));
                            reminds.erase(i);
                        }
                }
            for(auto i=meetings.begin();i!=meetings.end();i++)
                {
                    if (i.key()<QDateTime::currentDateTime())
                        {
                            queue.push_back(std::pair<QString,QString>(i->get_time().toString(),i->get_description()));
                            meetings.erase(i);
                        }
                }
        }*/

    void search_and_clean_in_files(QString filename)
     {
        QFile watch(dir+"/"+filename);
        a.get_FILE_NAME()=filename;
        QString new_file;
        if ((watch.exists())&&(watch.open(QIODevice::ReadOnly)))
            {
                QString buffer="";
                QString str="";
                QDateTime date;
                int pos=0;
                int i=0;

                    while(!watch.atEnd())
                        {
                            str=watch.readLine();
                            if (str=="\n" || str.isEmpty())
                                {
                                    continue;
                                }
                            while (pos!=2)
                                {
                                    if (str[i]!="|"&&str[i]!="\n")
                                        {
                                            buffer+=str[i];
                                        }
                                    else
                                        {
                                            pos++;
                                        }
                                    i++;
                                }
                            if (!buffer.isEmpty())
                                {
                                    date=QDateTime::fromString(buffer,"dd.M.yyyyhh:mm:ss");
                                    if (date >= QDateTime::currentDateTime())
                                        {
                                            new_file.append(str);
                                        }
                                    else
                                        {
                                            delelted.push_back(std::pair<QString,QString>(buffer,str));
                                        }
                                }
                            buffer.clear();
                            pos=0;
                            i=0;
                        }
            }
        watch.close();
        a.save(new_file);
     }

};

#endif // MANAGER_H
