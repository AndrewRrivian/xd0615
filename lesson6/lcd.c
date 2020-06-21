#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("hello, world!");
}
void loop() {
    //static int edge = 13;//sizeof("hellow world")
    if(Serial.available()){
        lcd.begin(16, 2);
        // lcd.setCursor(0, 1); 总是会发生一些奇妙的事情的
        for(int i=0;Serial.available()/*i<edge*/;i++)// if(Serial.available())
                lcd.print((char)Serial.read());//因为神奇的被指向了print(int)
        //else edge = i;
    }//至于为什么不是readString之类的, 主要是看起来简单些
    // 所以我也没有用 pin:6~9
}
 