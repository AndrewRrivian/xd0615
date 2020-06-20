#define IN1 2
#define S1 8

#define LT 6
#define BT 7
void wrt(int pin,int income){
    digitalWrite(pin,LOW);
    for(int i=0;i<4;i++)
        digitalWrite(IN1+i,(income>>i)&0x01);
  	digitalWrite(pin,HIGH);
}

void setup(){
    for(int i=0;i<4;i++) {
        pinMode(IN1+i, OUTPUT);
        pinMode(S1+i, OUTPUT);
        digitalWrite(S1+i,HIGH);
    }
    pinMode(LT,OUTPUT);//测试
    pinMode(BT,OUTPUT);//消隐
    Serial.begin(9600);
    digitalWrite(LT,HIGH);
    digitalWrite(BT,HIGH);
}
void loop(){
    //if(!Serial.available())return;
    if(Serial.available())//如果像上面注释的写法, 反而会出bug
    for(int i=0;i<4;i++)
        wrt(S1+i,Serial.read()-'0');
    delay(500);//停留时间短了还不行
}