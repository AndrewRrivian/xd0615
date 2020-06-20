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
        //去掉 17 行, 会在第 31 行(i==0)发生一些奇怪的bug
    }
    pinMode(LT,OUTPUT);//测试
    pinMode(BT,OUTPUT);//消隐
    Serial.begin(9600);
    digitalWrite(LT,HIGH);
    digitalWrite(BT,HIGH);
}
void loop(){
    static char income;
    if(Serial.available()>0) {
    income=Serial.read()-'0';
    for(int i=0;i<4;i++)
        if(i==4) wrt(S1+i,income);//迷惑行为大赏
    delay(1000);
    }
}
//我也不知道为啥三个作业对应俩文件