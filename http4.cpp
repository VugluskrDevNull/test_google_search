#include "http4.h"

Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
    file = new QFile("C:/Qt/Dummy/downloaded.txt");
}

void Downloader::doDownload()
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    QNetworkRequest request(QUrl("https://www.google.com/search?q=%D1%82%D0%BE%D0%BF+%D0%B6%D0%B6&ie=utf-8&oe=utf-8"));  // топ жж  (кракозябры)
   // QNetworkRequest request(QUrl("https://www.google.com/search?q=github&ie=utf-8&oe=utf-8"));                            // git hub
   // QNetworkRequest request(QUrl("https://www.google.com/search?q=doc.qt.io%2F&ie=utf-8&oe=utf-8"));                       // doc.qt.io (фигня)
    QSslConfiguration config(QSslConfiguration::defaultConfiguration());
    config.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(config);
    manager->get(request);
}


void Downloader::replyFinished (QNetworkReply *reply)
{
    QString str="";
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        if(file->open(QFile::Append))
        {
            file->write(reply->readAll());
            file->close();
        /*    if(file->open(QIODevice::WriteOnly))
            {
                while(!file->atEnd())
                {
                    str=str+file->readLine();
                }
                QDomDocument doc(str);
                QDomElement  domElement = doc.createElement(str);
                doc.appendChild(domElement);
                    QTextStream(file) << doc.toString();
                    file->close();
                    if(file->open(QIODevice::ReadOnly))
                    {

                        if(doc.setContent(file))
                        {
                            domElement= doc.documentElement();
                            traverseNode(domElement);
                        }
                        file->close();
                    }
                }  */

                file->flush();
                file->close();
            }
            delete file;
        }
        reply->deleteLater();
}

void Downloader::traverseNode(const QDomNode& node)
{
   QDomNode domNode = node.firstChild();
   while (!domNode.isNull()) {
       if (domNode.isElement()) {
          QDomElement domElement = domNode.toElement();
          if (!domElement.isNull()) {
               if (domNode.isElement()) {
                   if (domElement.tagName() == "h3")
                   {                              // поиск по тэгу h3
                      qDebug()<<" domElement.tagName()\n";                         //
                      qDebug() << "title: "  << domElement.attribute("h3", "");
                   }
                   else {
                       qDebug() << "title not found\n" ;
                   }
               }
          }
       }
       traverseNode(domNode);
       domNode = domNode.nextSibling();
    }
}
