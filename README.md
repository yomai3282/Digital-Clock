DS1307(リアルタイムクロックモジュール)のクラスを自作した。
調べた感じすでにライブラリが存在するらしい。
[GitHub - makerhero/DS1307: Biblioteca DS1307 - Arduino](https://github.com/makerhero/DS1307/tree/master)
このライブラリは使わずにライブラリを自作する。

とりあえず単体で動くスケッチを作った。
[[class_DS1307.ino]]
### Arduino IDEでライブラリを自作するには?
参考：
[Arduino IDEの使い方(ライブラリの自作編) - NOBのArduino日記！](https://nobita-rx7.hatenablog.com/entry/28488026)
[Arduinoの自作ライブラリを作成するには？ – StupidDog's blog](https://stupiddog.jp/note/archives/266)
[Arduino用ライブラリを書く](https://garretlab.web.fc2.com/arduino.cc/docs/learn/contributions/arduino-creating-library-guide/)

1. クラスをヘッダファイルに記述
場所は`~/Documents/Arduino/libraries/DS1307Lib`
ファイル名は`DS1307Lib.h`
```cpp
#ifndef DS1307Lib
#define DS1307Lib
#include <Arduino.h>

class TimeData {
	...
};
class DS1307:public TimeData{
	...
};
#endif
```
2. メンバ関数の定義をソースファイルに記述
場所は`~/Documents/Arduino/libraries/DS1307Lib`
ファイル名は`Sample.cpp`
```cpp
#include <Arduino.h>
#include "Sample.h"

TimeData,DS1307のメンバ関数の定義
```
3. 新たに定義した型や関数をハイライトするためのファイルを用意
場所は`~/Documents/Arduino/libraries/DS1307Lib
ファイル名は`keywords.txt`
```txt
#######################################
# Syntax Coloring Map DS1307Lib
#######################################

#######################################
# Datatypes (KEYWORD1)
#######################################
DS1307			KEYWORD1
TimeData		KEYWORD1

#######################################
# Methods and Functions (KEYWORD2)
#######################################
year			KEYWORD2
month			KEYWORD2
day			KEYWORD2
week			KEYWORD2
hour			KEYWORD2
minute			KEYWORD2
second			KEYWORD2
setTimeData		KEYWORD2
getTimeData		KEYWORD2
showTimeDataSerial	KEYWORD2

address			KEYWORD2
RTC_address		KEYWORD2
write			KEYWORD2
read			KEYWORD2
```
4. ライブラリを利用する
[[DS1307_to_LCD.ino]] ※ソースコードはLCDへ出力できるよう変更済み
なお、使用したLCDは[[SSD1306]]

### 時刻と温度をLCDに表示
DS1307のライブラリ`DS1307Lib.h`とADT7410のライブラリ`ADT7410Lib.h`を自作して、SSD1306というOLEDディスプレイに表示するプログラムを作成した。

[[ADT7410_DS1307_to_LCD.ino]]

左からDS1307,ADT1307,SSD1306

![[2024-02-21_17-04-18_000.mov]]
画面構成はshowDataLCD()内を変更すれば変えられる。
デジタル時計っぽく表示してみた
![[Pasted image 20240221193408.png|400]]
すべてI2Cなので回路構成はシンプル…かと思いきやDS1307が5Vじゃないと駆動しないので3.3Vを電源に使うには[昇圧回路](https://akizukidenshi.com/catalog/g/g113065/) or [I2Cバスレベル変換](https://akizukidenshi.com/catalog/g/g105452/)が必要らしい。

昇圧回路の場合は3.3Vだけで駆動する。I2Cバスレベル変換の場合、3.3Vと5Vの両方必要。

| モジュール | 価格 |
| ---- | ---- |
| 3.3Vマイコン | 1000 |
| DS1307 | 560 |
| ADT7140 | 600 |
| 5V昇圧コンバーター | 300 |
| SSD1306 | 500 |
| 計 | 2960 |

3000円の時計は高いだろ…マイコンが高い
PICを使えば回路も小型化できて安くもなるだろうけど
Arduinoのライブラリが使えないと現状厳しそう(能力的に)
PICのお勉強をするべきなんでしょうか…