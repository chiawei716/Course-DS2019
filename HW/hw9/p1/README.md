# 資料結構作業八

## 程式作業一 - aoe.cpp

### 流程說明
1. 讀取所需資料（ # of activities -> info of activities ）
2. 將edges的權重儲存進二維相鄰矩陣,並記錄最大event index
3. Events由 0~n 逐項更新與其相鄰之下一event，並取較大值，完成ee計算
4. Events由 n~0 逐項更新與其相鄰之上一event，並取較小值，完成le計算
5. Activities之e等於起始點的ee值，完成e計算
6. Activities之l等於終點的le值減去activity的duration，完成l計算
7. Slack值為每一activity的l減去e
8. 輸出結果