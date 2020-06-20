void setup(){
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
}
void loop(){
  static char b;
  if(!Serial.available())return;
  Serial.print(b);
  b = Serial.read();
	Serial.println(b);
  switch(b){
    #define _(a,b) digitalWrite(a, HIGH);digitalWrite(b, LOW)
    case 'f': _(6,7);_(8,9); break;
    case 'b': _(7,6);_(9,8); break;
	case 'r': _(7,6);_(8,9); break;
    case 'l': _(6,7);_(9,8); break;
    case 's':
    	digitalWrite(6, LOW);digitalWrite(7, LOW);
    	digitalWrite(8, LOW);digitalWrite(9, LOW);
    break;
    default:break;
  }
  Serial.println(b);
  delay(500);
}
/*
讲道理, 我是希望连 fbrls 这几行都可以省掉的
但是在硬件上这么搞太蠢, 不好调试
用goto的话, 代码也没简洁到哪去

另外, 我一开始选的端口是0123
*/