#include <DS1307Lib.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setLCD(){
  // ここにI2Cアドレスを設定
  display.begin(SSD1306_SWITCHCAPVCC,0x3C); 
  display.setTextColor(WHITE);  
  display.setTextSize(2);
  display.clearDisplay();
}

void showTimeDataLCD(DS1307 self){
  int* timeData=self.getTimeData();
  display.clearDisplay();    //画面クリア   
  display.setCursor(0,0);    //左上にカーソルを移動
  display.print("20");
  display.print(self.hex2string(timeData[0]));//year
  display.print("/");
  display.print(self.hex2string(timeData[1]));//month
  display.print("/");
  display.print(self.hex2string(timeData[2]));//day
  display.setCursor(0,16);    //左中にカーソルを移動
  display.print(self.weeklist[timeData[3]]);//week
  display.setCursor(0,32);    //左下にカーソルを移動
  display.print(self.hex2string(timeData[4]));//hour
  display.print(":");
  display.print(self.hex2string(timeData[5]));//minute
  display.print(":");
  display.print(self.hex2string(timeData[6]));//second
  display.println();display.println();  //文字列挿入
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

  //初期化を行わない場合
  static DS1307 rtc;
  
  //初期化してインスタンスを作成
  //初期化パラメータは左から
  //year,month,day,week,hour,minute,second
  //static DS1307 rtc(0x24,0x02,0x21,0x03,0x02,0x51,0x00);
  
  rtc.read(); //RTCからデータを受信

  showTimeDataLCD(rtc); //LCDに時刻を表示
  rtc.showTimeDataSerial(); //シリアルモニタに時刻を表示

  delay(1000);
}