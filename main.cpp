#include <QCoreApplication>
#include "http4.h"
#include <QtXml>

void traverseNode(const QDomNode& node)
{
   QDomNode domNode = node.firstChild();
   while (!domNode.isNull()) {
       if (domNode.isElement()) {
          QDomElement domElement = domNode.toElement();
          if (!domElement.isNull()) {
              if (domElement.tagName() == "h3") {                              // поиск по тэгу h3
                  qDebug() << "title: "  << domElement.attribute("h3", "");
              }
              else {
                  qDebug() << "title not found\n" ;
             }
          }
       }
       traverseNode(domNode);
       domNode = domNode.nextSibling();
    }
}

int main(int argc, char *argv[])
{
    // QFile file("C:\\Qt\\Dummy\\downloaded.txt");
    qDebug()<<QSslSocket::sslLibraryBuildVersionString();
    QCoreApplication a(argc, argv);

    Downloader d;
    d.doDownload();

    QDomDocument doc("title");
    QDomElement  domElement = doc.createElement("title");
    doc.appendChild(domElement);
    QFile file("C:\\Qt\\Dummy\\downloaded.txt");                               // "...xml"
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << doc.toString();
        file.close();
    }

    if(file.open(QIODevice::ReadOnly)) {
        if(doc.setContent(&file)) {
            domElement= doc.documentElement();
            traverseNode(domElement);
        }
        file.close();
    }


    return a.exec();
}


