#include "http4.h"

Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
    file = new QFile("C:/Qt/Dummy/downloaded.txt");
}

void Downloader::doDownload()
{
    qDebug() << "doDownload\n" ;                            //
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
   // QNetworkRequest request(QUrl("https://www.google.com/search?q=%D1%82%D0%BE%D0%BF+%D0%B6%D0%B6&ie=utf-8&oe=utf-8"));  // топ жж  (кракозябры)
   // QNetworkRequest request(QUrl("https://www.google.com/search?q=github&ie=utf-8&oe=utf-8"));                            // git hub
    QNetworkRequest request(QUrl("https://www.google.com/search?q=doc.qt.io%2F&ie=utf-8&oe=utf-8"));                       // doc.qt.io (фигня)
    QSslConfiguration config(QSslConfiguration::defaultConfiguration());
    config.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(config);
    manager->get(request);
    qDebug() << "out of doDownload\n" ;                            //
}

    /*
void Downloader::doDownload()
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),  this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://google.com")));
}
*/

void Downloader::replyFinished (QNetworkReply *reply)
{
    qDebug() << "replyFinished\n" ;                            //
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

    //    QFile *file = new QFile("C:/Qt/Dummy/downloaded.txt");
        if(file->open(QFile::Append))
        {
            qDebug() << "if(file->open(QFile::Append))\n";                //
            file->write(reply->readAll());
            file->close();
      /**/  QDomDocument doc("title");
            QDomElement  domElement = doc.createElement("title");
            doc.appendChild(domElement);
            if(file->open(QIODevice::WriteOnly))
            {
                qDebug() << "3 if\n" ;                            //
                QTextStream(file) << doc.toString();
                file->close();
                if(file->open(QIODevice::ReadOnly))
                {
                    qDebug() << "1 if\n" ;                            //
                    if(doc.setContent(file))
                    {
                        qDebug() << "2 if\n" ;                            //
                        domElement= doc.documentElement();
                        traverseNode(domElement);
                    }
                    file->close();
                }
       /**/ }

            file->flush();
            file->close();
        }
        delete file;
    }
    reply->deleteLater();
    qDebug() << "out of replyFinished\n" ;                            //
}

void Downloader::traverseNode(const QDomNode& node)
{
   qDebug()<<"traverseNode\n";                         //
   QDomNode domNode = node.firstChild();
   while (!domNode.isNull()) {
       qDebug()<<"!domNode.isNull())\n";                         //
       if (domNode.isElement()) {
          qDebug()<<" if (domNode.isElement())\n";                         //
          QDomElement domElement = domNode.toElement();
          if (!domElement.isNull()) {
              qDebug()<<" !domElement.isNull()\n";                         //
               if (domNode.isElement()) {
                 qDebug()<<" domNode.isElement\n";                         //
                 if (domElement.tagName() == "h3") {                              // поиск по тэгу h3
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
       qDebug()<<"traverseNode(domNode)\n";                         //
       domNode = domNode.nextSibling();
       qDebug()<<"domNode = domNode.nextSibling()\n";                         //
    }
}
