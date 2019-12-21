# 資料結構作業八

## 程式作業二 - ksp.cpp

### 流程說明
1. 讀取所需資料（ # of vertices -> # of links -> info of links ）
2. 將links的權重儲存進二維相鄰矩陣
3. 利用遞迴，嘗試出所有由1走至終點N的路線，並在路線完成時將結果之cost和path存入linked list，並插入時使cost保持小至大之順序
4. 輸出結果