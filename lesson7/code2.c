#define IN1 3
#define S2 7
#define LT 9
#define BT 8
#define Evanglion wrt
/* 至于课堂说到在中断处理过程中的变量要用 volatile 修饰
虽然我也不是很清楚它和最新的内存模型的关系,但也不是完全没概念
首先问题是 Arduino 有 cache 结构和多核吗?否则 volatile 修饰的意义是什么?
其次是明显: 示例程序中的 pinInterrupt 没有用 volatile 修饰?
*/
int pinInterrupt = 2; //接中断信号的脚
volatile int n=0;
void onChange() { //BGM: THE BEAST Ⅱ
//n = digitalRead(pinInterrupt) == LOW?-1:n;
    if ( digitalRead(pinInterrupt) == LOW ){
        Serial.print("NERV ");
        Serial.println(n);
        n=-1;
    }
}
void wrt(int pin,int income){
    digitalWrite(pin,LOW);
    for(int i=0;i<4;i++)
        digitalWrite(IN1+i,(income>>i)&0x01);
  	digitalWrite(pin,HIGH);
}
void setup() {
    for(int i=0;i<4;i++) pinMode(IN1+i, OUTPUT);
    pinMode(S2, OUTPUT);
    digitalWrite(S2,HIGH);
    pinMode(LT,OUTPUT);//测试
    pinMode(BT,OUTPUT);//消隐
    digitalWrite(LT,HIGH);
    digitalWrite(BT,HIGH);

    Serial.begin(9600); //打开DUMMY
    pinMode( pinInterrupt, INPUT);//停电警告
    attachInterrupt( digitalPinToInterrupt(pinInterrupt), onChange, CHANGE);
}
void loop() {
// 如果只是数码管显示的问题, 大可不必使用内源中断吧?
// 而且显示操作的代价相对来说也不算低, 不适合设计在中断内
// 不过仅仅将按时间更新 n 这个操作, 应当是值得写在内源中断内的
    // 为什么我非要埋个彩蛋呢? 主要是突然看见宏名叫 S2 了
    // 至于为什么会有这个名字呢? 是直接复用上次作业的
    // 倒着写主要是压迫感强一些
    Evanglion(S2,9-(n=(n+1)%10)); //这么写的话, 短一些, 要求12行为 n=-1
    /*如果对起始状态有洁癖的还可以如下, 然后 12 行改为 n=0
    Evanglion(S2,9-n);
    n=(n+1)%10;*/
    delay(1000);//非静止画面 
// 如果哪天闲着没事干, 魂魄启动器和初号机的头肯定要选一个实现一下
}//BGM: FLY ME TO THE MOON