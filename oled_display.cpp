#include "oled_display.h"
#include "display/ssd1306_i2c.h"
#include "common.h"

oled_display::oled_display(QObject *parent) : QObject(parent)
{
    /*OLED Display*/
    ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);      //LCD Screen initialization
    FirstGetIpAddress();                        //Get IP address
    LCD_Display(symbol_count);

    oled_display_timer = new QTimer(this);
    oled_display_timer->setSingleShot(true);

    oled_display_timer->start(3000);

    connect(oled_display_timer, &QTimer::timeout, [=]()
    {
        Log();

        LCD_Display(symbol_count);
        symbol_count++;

        if(symbol_count==3)
             symbol_count=0;

          oled_display_timer->start(5000);
    });
}

oled_display::~oled_display()
{

}

void oled_display::status_display()
{

}
