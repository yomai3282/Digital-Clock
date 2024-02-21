#include <Wire.h> 
#include <Adafruit_SSD1306.h> 

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // ここにI2Cアドレスを設定
  display.begin(SSD1306_SWITCHCAPVCC,0x3C); 
  display.setTextColor(WHITE);  
  display.setTextSize(1);
  display.clearDisplay();
  display.clearDisplay(); 
}
 
void loop() {
  for(int i=0;i<64;i+=8){
  display.clearDisplay();    //画面クリア   
  display.setCursor(0,i);    //左上にカーソルを移動
  display.print(i);
  display.print(" ");
  display.println("Hello World");  //文字列挿入
  display.display();         //描画バッファの内容を画面に表示
  delay(1000);               //1秒間待ち
  }
}