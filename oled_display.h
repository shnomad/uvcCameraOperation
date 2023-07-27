#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <QObject>
#include <QTimer>

class oled_display : public QObject
{
    Q_OBJECT
public:
    explicit oled_display(QObject *parent = nullptr);
    ~oled_display();

signals:

public slots:
    void status_display();

private:
    QTimer *oled_display_timer;
    unsigned char symbol_count =0;
};

#endif // OLED_DISPLAY_H
