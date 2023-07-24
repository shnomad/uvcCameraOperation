#ifndef CLI_MONITOR_H
#define CLI_MONITOR_H

#include <QObject>
#include <QProcess>

class cli_monitor : public QObject
{
    Q_OBJECT
public:
    explicit cli_monitor(QObject *parent = nullptr);
        ~cli_monitor();

     void sendCommand(QString command);

signals:

public slots:
     void readyReadStandardOutput();
     void readyReadStandardError();

private:
         QProcess mProcess;
};

#endif // CLI_MONITOR_H
