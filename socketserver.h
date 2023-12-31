#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>

class SocketServer : public QObject
{
    Q_OBJECT
public:
    explicit SocketServer(QObject *parent = nullptr);
    ~SocketServer();

signals:
     void newMessage(QString);
//   void sig_send_file(const QByteArray , QString);
     void sig_image_post_process();

public slots:
    void sendAttachment_click(void *img, QString img_name, quint32 img_size, quint8 mode);
    void sendMessage_click();

private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void displayMessage(const QString& str);

    void sendMessage(QTcpSocket* socket);
    //void sendAttachment(QTcpSocket* socket, QString filePath);
    void sendAttachment(QTcpSocket* socket, void *file, QString file_name, quint32 file_size, quint8 mode);

private:
     QTcpServer* m_server;
     QSet<QTcpSocket*> connection_set;
     QTcpSocket* recv_socket;

     quint32 capture_count =0;

//   QDataStream socketStream;
};

#endif // SOCKETSERVER_H
