/*
音调跟随器
使用tone()命令产生一个随着模拟输入值变化的音调。使用光敏电阻，Arduino或者Genuino变成一个简化的光感泰勒明（theremin）。
+ Arduino 或者 Genuino 开发板   + 8欧扬声器
+ 光敏电阻                      + 4.7K电阻
+ 100 欧电阻                    + 导线
+ 面包板
*/
int sensorReading = 0;
void setup () {
    // A0 是模拟信号端口
    pinMode(A0, INPUT);
    Serial.begin(9600);
    pinMode(9, OUTPUT);
}
void loop () {
    // analogRead() 从参数中获得需要读取的引脚,
    // 并返回引脚对应信号的映射值(在0~1023之间)
    sensorReading = analogRead(A0);
    Serial.println(sensorReading);
//1:                                      sensorReading
//2:                              int(map(↑, 0, 1023, 36, 84))
//3:                   (constrain(↑, 35, 127) - 57) / 12.0
//4:       440*pow(2.0,↑)
//5:tone(9,↑,1000);

//*1&2: sensorReading 并不是一个可枚举的类型
//      这里的map并非一般意义上的 ((item->item)->(list)->list) 类型的函数
//      而是 ARDUINO 的特有函数, map(value,fromLow,fromHigh,toLow,toHigh)
//      意味着将一个 unary 数据进行(非齐次线性)变换
//      另外, 这里 int 的强制转换意义是什么?
//          map 的原型声明并不严格, 是视作为 int 还是 long 了?
// # define l1:0; h1:1023; l2:36; h2:84;
// # define _len(i):((h##i)-(l##i));
// //不应当命名 _map 而应命名 _transform 或者 _linearTransform
// # define _transform(i):  ((_len(2)*(i-l1))/_len(1))+l2;
//          按理说, 是这么个意思
//                          ((_len(2)*(i-l1))+(_len(1)*l2))/(_len(1));
//          至于把除法放在最后执行能不能解决精度问题, 我是怀疑的
//                          ((((long)_len(2)*i)/_len(1))+l2)
//          在0~1023是经过枚举证明正确的, 其他的写法会因为溢出等出现错误
//              if(map(...)!=_transform(i)||i==1023)Serial.println(i);
//end 1&2;
//3:    constrain(x, a, b)
//      对数据 x 做区间隔断, 限制其在 a~b 之间, 但是这个区间令人迷惑:
//          为什么不是 36~84 ? 127 方便优化为位运算吗?
//          那么何必用 map 呢? 声明里也没说它会 inline 展开
//end 3;
//4:    pow(base, exponent)就没什么好说的了, math.h 是通用的
//end 4;
//5:    tone(pin,frequency,duration)
//      tone()函数可以产生固定频率的PWM信号来驱动扬声器发声
//      如果前面的计算过程都清晰了, 那这里也没什么好说的了
//      问题在于为什么要这么算
//      另外一个问题是: 它应当是异步的:
//          tone(xxx,xxx,n);Serial.println(i++);delay(m);
//          其中, n>m 时, 如 n=m=1000, 串口的输出与模拟计时是同步的

    tone(9, 440 * pow(2.0, (constrain(int(map(sensorReading, 0, 1023, 36, 84)), 35, 127) - 57) / 12.0), 1000);
    delay(10);
}