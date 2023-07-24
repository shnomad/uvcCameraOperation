#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QDateTime>

#define Log() qDebug() <<"["<<QDateTime::currentDateTime().toString("MM.dd hh:mm:ss,zzz") << __PRETTY_FUNCTION__ << __LINE__ << "]"

#endif // COMMON_H
