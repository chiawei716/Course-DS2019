# 資料結構作業八

## 程式作業一 - single_source.cpp

### 流程說明
1. 讀取所需資料（ # of vertices -> # of edges -> info of edges ）
2. 將edges的權重儲存進二維相鄰矩陣
3. 建立三個陣列

    > visited  - 紀錄vertice是否已經被使用過
    > distance - 紀錄截至目前該vertice的最短距離，預設為無限大（無法到達）
    > path - 紀錄截至目前該vertice的最短路徑

4. 以0點為開頭，藉相鄰矩陣更新每點之最短距離及最短路逕
5. 接著挑選未使用過之vertice，並為最近者，並再由其更新其餘點的最短距離及路徑
6. 重複上述步驟至每一點皆使用過，或已無點可到時停止
7. distance及path及為每點之最短距離及路徑

## 程式作業二 - all_pair.cpp

### 流程說明
與作業一近乎相同，但會使用各點作為開頭重複上方 3~7 步驟。