#ifndef HTTP4_H
#define HTTP4_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QtXml>
#include <QSslSocket>
#include <QDomDocument>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    void doDownload();
    QFile *file;
signals:
public slots:
    void replyFinished (QNetworkReply *reply);
private:
    QNetworkAccessManager *manager;
  void  traverseNode(const QDomNode& );
};


#endif // HTTP4_H
