#include <DS1307Lib.h>
#include <ADT7410Lib.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setLCD(){
  // ここにI2Cアドレスを設定
  display.begin(SSD1306_SWITCHCAPVCC,0x3C); 
  display.setTextColor(WHITE);  
  display.clearDisplay();
}

void showDataLCD(DS1307 ds1307,float temp){
  int* timeData=ds1307.getTimeData();
  display.clearDisplay();    //画面クリア   
  display.setCursor(0,0);    //左上にカーソルを移動
  display.setTextSize(1);
  display.print(ds1307.hex2string(timeData[0]));//year
  display.print("/");
  display.print(ds1307.hex2string(timeData[1]));//month
  display.print("/");
  display.print(ds1307.hex2string(timeData[2]));//day
  display.print(" ");
  display.print(ds1307.weeklist[timeData[3]]);//week
  display.setCursor(16,20);    //左中上にカーソルを移動
  display.setTextSize(3);
  display.print(ds1307.hex2string(timeData[4]));//hour
  display.print(":");
  display.print(ds1307.hex2string(timeData[5]));//minute
  display.setCursor(104,36);
  display.setTextSize(1);
  display.print(":");
  display.print(ds1307.hex2string(timeData[6]));//second
  display.setCursor(0,56);    //左中下にカーソルを移動
  display.setTextSize(1);
  display.print("Temp: ");
  display.print(temp);
  display.print(" deg");
  display.display();         //描画バッファの内容を画面に表示
  delete[] timeData;
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  setLCD();
}

void loop() {
  // put your main code here, to run repeatedly:

  //DS1307の初期化を行わない場合
  static DS1307 ds1307;
  
  //初期化してインスタンスを作成
  //初期化パラメータは左から
  //year,month,day,week,hour,minute,second
  //static DS1307 ds1307(0x24,0x02,0x21,0x03,0x02,0x51,0x00);
  
  //ADT7410のコンストラクタを作成
  static ADT7410 adt7410;
  
  ds1307.read(); //ds1307からデータを受信
  float temp=adt7410.getTempData(); //ADT7410から温度データを取得
  showDataLCD(ds1307,temp); //LCDに時刻と気温を表示
  ds1307.showTimeDataSerial(); //シリアルモニタに時刻を表示
  adt7410.showTempDataSerial();//シリアルモニタに温度を表示

  delay(1000);
}