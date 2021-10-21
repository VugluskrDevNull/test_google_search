#include "http4.h"

int main(int argc, char *argv[])
{
    qDebug()<<QSslSocket::sslLibraryBuildVersionString();
    QCoreApplication a(argc, argv);
    Downloader d;
    d.doDownload();

    return a.exec();
}


