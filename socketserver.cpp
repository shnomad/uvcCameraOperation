#include "common.h"
#include "socketserver.h"
#include "deviceinfo.h"
//#include "global.h"

SocketServer::SocketServer(QObject *parent) : QObject(parent)
{
    deviceInfo m_dev_info;

    m_server = new QTcpServer(this);

    m_server->setMaxPendingConnections(1);

    //if(m_server->listen(QHostAddress::Any, 60001))
    if(m_server->listen(QHostAddress::Any, m_dev_info.get_ServerPort().toUShort()))
    {
       connect(this, &SocketServer::newMessage, this, &SocketServer::displayMessage);
       connect(m_server, &QTcpServer::newConnection, this, &SocketServer::newConnection);
    }
    else
    {
        exit(0);
    }
}

SocketServer::~SocketServer()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }
    m_server->close();
    m_server->deleteLater();
}

void SocketServer::newConnection()
{
    while (m_server->hasPendingConnections())
              appendToSocketList(m_server->nextPendingConnection());
/*
    QTcpSocket *clientConnection = m_server->nextPendingConnection();
        connect(clientConnection, &QAbstractSocket::disconnected,
                clientConnection, &QObject::deleteLater);
*/
}

void SocketServer::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &SocketServer::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &SocketServer::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &SocketServer::displayError);
    connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);
    displayMessage(QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor()));     
}

void SocketServer::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

       buffer = buffer.mid(128);

       if(fileType=="attachment")
       {
           QString fileName = header.split(",")[1].split(":")[1];
           QString ext = fileName.split(".")[1];
           QString size = header.split(",")[2].split(":")[1].split(";")[0];

//         if (QMessageBox::Yes == QMessageBox::question(this, "QTCPServer", QString("You are receiving an attachment from sd:%1 of size: %2 bytes, called %3. Do you want to accept it?").arg(socket->socketDescriptor()).arg(size).arg(fileName)))
           if(1)
           {
//             QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+fileName, QString("File (*.%1)").arg(ext));
               QString filePath="";

               QFile file(filePath);

               if(file.open(QIODevice::WriteOnly))
               {
                   file.write(buffer);

                   QString message = QString("INFO :: Attachment from sd:%1 successfully stored on disk under the path %2").arg(socket->socketDescriptor()).arg(QString(filePath));
                   emit newMessage(message);
               }
               else
               {
                   Log()<<"QTCPServer", "An error occurred while trying to write the attachment.";
               }
           }
           else
           {
               QString message = QString("INFO :: Attachment from sd:%1 discarded").arg(socket->socketDescriptor());
               emit newMessage(message);
           }
       }
       else if(fileType=="message")
       {
           QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
           emit newMessage(message);
       }
}

void SocketServer::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);

    if (it != connection_set.end())
    {
        displayMessage(QString("INFO :: A client has just left the room").arg(socket->socketDescriptor()));
        connection_set.remove(*it);
    }
//    refreshComboBox();

//    socket->abort();
//    socket->close();
//    socket->deleteLater();
      socket->disconnectFromHost();
}

void SocketServer::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;

        case QAbstractSocket::HostNotFoundError:
//            QMessageBox::information(this, "QTCPServer", "The host was not found. Please check the host name and port settings.");
        break;

        case QAbstractSocket::ConnectionRefusedError:
            //QMessageBox::information(this, "QTCPServer", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;

        default:
          QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    //      QMessageBox::information(this, "QTCPServer", QString("The following error occurred: %1.").arg(socket->errorString()));
       break;
    }
}

void SocketServer::displayMessage(const QString& str)
{
    Log()<<str;
}

void SocketServer::sendMessage_click()
{
    QString receiver="";

    if(receiver=="Broadcast")
    {
        foreach (QTcpSocket* socket,connection_set)
        {
            sendMessage(socket);
        }
    }
    else
    {
        foreach (QTcpSocket* socket,connection_set)
        {
            if(socket->socketDescriptor() == receiver.toLongLong())
            {
                sendMessage(socket);
                break;
            }
        }
    }
}

void SocketServer::sendAttachment_click(void *img, QString img_name, quint32 img_size, quint8 capture_mode)
{
    Log();
/*
    FILE *fp;

    fp = fopen(img_name.toStdString().c_str(), "w");

    fwrite(img, 1, img_size, fp);

    fclose(fp);
*/
    QString receiver="", filePath="";

//  if(receiver=="Broadcast")
    if(1)
    {
        Log()<<"start Transfer";

        foreach (QTcpSocket* socket,connection_set)
        {
            sendAttachment(socket, img, img_name, img_size, capture_mode);
        }

        Log()<<"end Transfer";
    }
    else
    {        
        foreach (QTcpSocket* socket, connection_set)
        { 
            if(socket->socketDescriptor() == receiver)
            {
                 sendAttachment(socket, img, img_name, img_size, capture_mode);
                 break;
            }
        }
    }

}

void SocketServer::sendMessage(QTcpSocket* socket)
{
    if(socket)
        {
            if(socket->isOpen())
            {
//              QString str = ui->lineEdit_message->text();
                QString str ="";

                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                QByteArray header;
                header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = str.toUtf8();
                byteArray.prepend(header);

                socketStream.setVersion(QDataStream::Qt_5_15);
                socketStream << byteArray;
            }
            else
            {
                Log()<<"QTCPServer","Socket doesn't seem to be opened";
            }
        }
        else
        {
            Log()<<"QTCPServer, Not connected";
        }
}

void SocketServer::sendAttachment(QTcpSocket* socket, void *file, QString file_name, quint32 file_size, quint8 capture_mode)
{
    if(socket)
      {
        if(socket->isOpen())
          {                        
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;

            header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2,mode:%3;").arg(file_name).arg(file_size).arg(capture_mode).toUtf8());
            header.resize(128);

            QByteArray bytearray = QByteArray(static_cast<const char*>(file), file_size);

            bytearray.prepend(header);

            socketStream << bytearray;
#if 0
            bytearray = bytearray.mid(128);

            Log()<<"capture_mode :"<<capture_mode;

            if(capture_mode == 0)
            {
                capture_count++;

                if(capture_count<101)
                {
                    global.jpg_file_buffer_0.push_back(bytearray);
                    global.img_file_name_buffer_0.push_back(file_name);

                   if(global.jpg_file_buffer_0.length() ==100 && global.img_file_name_buffer_0.length()==100)
                       emit sig_image_post_process();
                }
                else if(capture_count>100 && capture_count<201)
                {
                    global.jpg_file_buffer_1.push_back(bytearray);
                    global.img_file_name_buffer_1.push_back(file_name);
                }
                else
                {
                    global.jpg_file_buffer_2.push_back(bytearray);
                    global.img_file_name_buffer_2.push_back(file_name);

                    if(global.jpg_file_buffer_2.length() ==100 && global.img_file_name_buffer_2.length()==100)
                    {
                        capture_count=0;
                    }
                }
            }
#endif
          }
          else
          {
                Log()<<"QTCPServer","Socket doesn't seem to be opened";
          }
     }
     else
     {
               Log()<<"QTCPServer","Not connected";
     }

}
