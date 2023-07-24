#include "cli_monitor.h"
#include "common.h"

cli_monitor::cli_monitor(QObject *parent) : QObject(parent)
{
    connect(&mProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
    connect(&mProcess,SIGNAL(readyReadStandardError()),this,SLOT(readyReadStandardError()));
}

cli_monitor::~cli_monitor()
{

}

void cli_monitor::sendCommand(QString command)
{
     mProcess.start(command);
     mProcess.waitForFinished(-1);
}

void cli_monitor::readyReadStandardOutput()
{
    Log()<< QString::fromStdString(mProcess.readAllStandardOutput().toStdString());
}

void cli_monitor::readyReadStandardError()
{
    Log()<< QString::fromStdString(mProcess.readAllStandardOutput().toStdString());
}
