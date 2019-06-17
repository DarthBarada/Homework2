#include "saver.h"

saver::saver()
{

}

QString& saver::get_FILE_NAME()
    {
        return  FILE_NAME;
    }

void saver::keeper(QString temp)
    {
        QString dir="Data";
        if (!QDir::exists(dir))
            {
                QDir::mkdir(dir);
            }
        QTextCodec::setCodecForLocale( QTextCodec::codecForName( "UTF-8" ) );
        QFile out(dir+"/"+FILE_NAME);
        if( out.open( QIODevice::Append) )
            {
                QTextStream stream( &out );
                stream << temp.toUtf8();
                stream<<endl;
                out.close();
            }
    }

void saver::save(QString temp)
    {
        QString dir="Data";
        if (!QDir::exists(dir))
            {
                QDir::mkdir(dir);
            }
        QTextCodec::setCodecForLocale( QTextCodec::codecForName( "UTF-8" ) );
        QFile out(dir+"/"+FILE_NAME);
        if( out.open( QIODevice::WriteOnly) )
            {
                QTextStream stream( &out );
                stream.setCodec( "UTF-8 ");
                stream << temp.toUtf8();
                 stream<<endl;
                out.close();
            }
    }
