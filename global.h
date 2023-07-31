#ifndef GLOBAL_H
#define GLOBAL_H

#pragma once

#include <QObject>
#include <QVector>
#include <QByteArray>

class Global
{
public:
//    int i = 100;
//    float f = 20.0f;
//    and other "global" variable

    QVector<QString>img_file_name_buffer_0, img_file_name_buffer_1, img_file_name_buffer_2;
    QVector<QByteArray>jpg_file_buffer_0, jpg_file_buffer_1, jpg_file_buffer_2;

public:
    Global() = default;
    Global(const Global&) = delete;
    Global(Global&&) = delete;

    static Global& Instance()
    {
        static Global global;
        return global;
    }
};

namespace
{
    Global& global = Global::Instance();
}

#endif // GLOBAL_H
