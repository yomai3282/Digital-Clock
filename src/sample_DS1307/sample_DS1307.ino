#include <Wire.h>
#define RTC_address 0x68
char *week[] = {"日","月","火","水","木","金","土"};

uint8_t REG_table[7];

void setup() {
Wire.begin();
Serial.begin(9600);

//RTCにデータを書き込む
Wire.beginTransmission(RTC_address);
Wire.write(0x00);//Register 先頭アドレス
Wire.write(0x00);//second
Wire.write(0x35);//minute
Wire.write(0x16);//hour
Wire.write(0x03);//week
Wire.write(0x20);//day
Wire.write(0x02);//month
Wire.write(0x24);//year
Wire.endTransmission();
}

void loop() {
Wire.beginTransmission(RTC_address);
Wire.write(0x00);//Register 先頭アドレス
Wire.endTransmission();

//RTCデータの読み込み
Wire.requestFrom(RTC_address,7);
for(int i=0;i<=7;i++){
REG_table[i]=Wire.read();
}

//RTCデータ表示
Serial.print("20");
Serial.print(REG_table[6],HEX);//year
Serial.print("/");
Serial.print(REG_table[5],HEX);//month
Serial.print("/");
Serial.print(REG_table[4],HEX);//day
Serial.print("(");
Serial.print(week[REG_table[3]]);//week
Serial.print(") ");
Serial.print(REG_table[2],HEX);//hour
Serial.print(":");
Serial.print(REG_table[1],HEX);//minute
Serial.print(":");
Serial.print(REG_table[0],HEX);//second
Serial.println();
delay(1000);
}