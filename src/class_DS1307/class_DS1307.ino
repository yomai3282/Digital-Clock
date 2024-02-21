#include <Wire.h>

class TimeData{
  /*
  RTCモジュールの時間データを管理するクラスです
  */
  protected:
    int year;
    int month;
    int day;
    int week;
    int hour;
    int minute;
    int second;
    const char *weeklist[7]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
  public:
    //デフォルトコンストラクタ
    TimeData(){}
    //変換コンストラクタ
    TimeData(int Year, int Month, int Day, int Week, int Hour, int Minute, int Second)
      : year(Year), month(Month), day(Day), week(Week), hour(Hour), minute(Minute), second(Second) {}
    void setTimeData(int Year, int Month, int Day, int Week, int Hour, int Minute, int Second);
    int* getTimeData();
    void showTimeData();
};

void TimeData::setTimeData(int Year, int Month, int Day, int Week, int Hour, int Minute, int Second) {
  /*
  TimeDataのインスタンスのメンバに値をセットします
  */
  year = Year;
  month = Month;
  day = Day;
  week = Week;
  hour = Hour;
  minute = Minute;
  second = Second;
}

int* TimeData::getTimeData(){
  /*
  TimeDataのインスタンスのメンバの値を格納した配列のポインタとして渡します
  動的に確保した配列を渡すので、関数の呼び出し側でdelete[]を行うこと。
  int* timeData=rtc.getTimeData();
  for(int i=0;i<7;i++){
    Serial.print(timeData[i],HEX);
    if(i!=6) Serial.print(",");
  }
  delete[] timeData;
  */
  int* timeData=new int[7];
  int values[7]={year,month,day,week,hour,minute,second};
  for(int i=0;i<7;i++){
    timeData[i]=values[i];
  }
  return timeData;
}

void TimeData::showTimeData(){
  /*
  TimeDataクラスのインスタンスのメンバを2024/2/20(火) 16:41:27の形で表示します
  */
  Serial.print("20");
  Serial.print(year,HEX);//year
  Serial.print("/");
  Serial.print(month,HEX);//month
  Serial.print("/");
  Serial.print(day,HEX);//day
  Serial.print("(");
  Serial.print(weeklist[week]);//week
  Serial.print(") ");
  Serial.print(hour,HEX);//hour
  Serial.print(":");
  Serial.print(minute,HEX);//minute
  Serial.print(":");
  Serial.print(second,HEX);//second
  Serial.println();
}

class DS1307: public TimeData{
  /*
  RTCモジュールDS1307用の自作クラスです
  TimeDataクラスから派生します
  */
  private:
    const int address=0x00; //先頭アドレス
    const int RTC_address=0x68; //I2Cアドレス
    uint8_t REG_table[7]; //レジスタテーブル
  public:
    DS1307():TimeData(){}
    DS1307(int Year,int Month,int Day,int Week,int Hour,int Minute,int Second)
      : TimeData(Year, Month, Day, Week, Hour, Minute, Second){
      setTimeData(Year,Month,Day,Week,Hour,Minute,Second);
      write();
    }
    void write();
    void read();
};

void DS1307::write(){
  /*
  RTCにデータを書き込みます
  */
  Wire.beginTransmission(RTC_address);
  Wire.write(address);//Register 先頭アドレス
  Wire.write(second);//second
  Wire.write(minute);//minute
  Wire.write(hour);//hour
  Wire.write(week);//week
  Wire.write(day);//day
  Wire.write(month);//month
  Wire.write(year);//year
  Wire.endTransmission();
}

void DS1307::read(){
  /*
  RTCからデータを読み込みます
  */
  Wire.beginTransmission(RTC_address);
  Wire.write(address);//Register 先頭アドレス
  Wire.endTransmission();
  
  Wire.requestFrom(RTC_address,7);
  for(int i=0;i<7;i++){
  REG_table[i]=Wire.read();
  }
  setTimeData(REG_table[6],REG_table[5],REG_table[4],REG_table[3],REG_table[2],REG_table[1],REG_table[0]);
  showTimeData();
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //初期化を行わない場合
  //static DS1307 rtc;
  //インスタンスを作成
  static DS1307 rtc(0x24,0x02,0x20,0x02,0x16,0x35,0x00);
  //RTCからデータを受信
  rtc.read();
  delay(1000);
}