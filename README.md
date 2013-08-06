﻿## SplitChapters : 文字檔切分章節程式
----------------------------------------

### 主要功能：
> 將大文字檔依其章節區分方式，by 章節切成個別的檔案。  
> 程式會在該大文字檔的目錄下產生子目錄 txtsrc，各章節以數字為檔名，存到個別的檔案中。  
> 其中，0.txt 為目錄檔，可由此檢查切分章節是否正確。製作電子書時不須包含此檔案。  

### 支援的章節區分方式：
   * 依各章節開頭與結尾的特定關鍵字切分。
   * 各章節以純數字開頭時。
   * 無法區分時，以固定長度切檔。

### 支援的文字檔編碼方式：
 - UTF-8
 - GB
 - Big5 （預設，未勾選以上2項時）

----------------------------------------

### 各項設定說明：  

- 補滿檔名： 
> 各章節存檔時，檔名由1開始，依序累加，此選項會將檔名以0補滿4位數，例如0001.txt。

- 一檔章數： 
> 當文字檔案太大，章節數太多，造成切分的檔案過多時，可在此設定一個檔案內包含幾個章節，來減少檔案數。

- 數字章節：
> 當章節以純數字區分，無前後關鍵字時，可以此選項來切分檔案，但該行開頭必須為數字，不可有其他文字

- 定長：
> 當無法以關鍵字或數字切分檔案時，可以此選項用固定長度 20KBytes 切分檔案。

----------------------------------------

### 關鍵字切檔的設定
> 未勾選數字章節及定長時，則預設以關鍵字切檔。  
> 可調整下列設定值來改變切分章節的準確性。

- 首字章節：
> 限定該行的第一個字必須為關鍵字，才視爲是章節。

- 章名長：
> 限定兩個關鍵字之間的字數不超過此設定值，才可認定為章節。

- 標題長：
> 限定該行的總長度不超過此設定值，才可認定為章節。

- 去同章節：
> 有時檔案中會連續兩行相同章節名稱，可以此選項去除。


----------------------------------------

## Issue:  
- 無法開啓 unicode 編碼的文字檔。







