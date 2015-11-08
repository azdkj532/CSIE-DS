# Larry's editor

## 編譯環境
需要 `make` 指令以進行編譯，

* OS X
* Linux 

## 編譯方式
切換至程式碼所在路徑，執行 make
```
make
```
接下來將會自動將程式編譯成執行檔 `editor`

## 編譯器
* gcc

## 執行流程

執行後，程式會提示你輸入字串，以換行符號結束輸入。

接下來會提示你輸入命令 有三種可以使用

* `s/AA/BB/` 將字串中的 AA 取代成 BB
* `s/AA//` 將字串中的 AA 刪除
* `/AA` 尋找字串中的 AA 並輸出出現次數
* `q` 結束執行

## 截圖
![螢幕截圖](https://raw.githubusercontent.com/azdkj532/CSIE-DS/hw1/screenshot.png)
