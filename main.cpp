#include <QCoreApplication>
#include "http4.h"
#include <QtXml>

void traverseNode(const QDomNode& node)
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

int main(int argc, char *argv[])
{
    qDebug()<<QSslSocket::sslLibraryBuildVersionString();
    QCoreApplication a(argc, argv);

    Downloader d;
    d.doDownload();

    QDomDocument doc("title");
    QDomElement  domElement = doc.createElement("title");
    doc.appendChild(domElement);
 //   QFile file("C:\\Qt\\Dummy\\downloaded.txt");                               // "...xml"
    if(d.file->open(QIODevice::ReadOnly)) {
        qDebug() << "1 if\n" ;                            //
        if(doc.setContent(d.file)) {
            qDebug() << "2 if\n" ;                            //
            domElement= doc.documentElement();
            traverseNode(domElement);
        }
        d.file->close();
    if(d.file->open(QIODevice::WriteOnly)) {
        qDebug() << "3 if\n" ;                            //
        QTextStream(d.file) << doc.toString();
        d.file->close();
    }


    }


    return a.exec();
}


