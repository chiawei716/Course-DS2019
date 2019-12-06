# 資料結構作業五

## 程式作業一 - max_heap.cpp

### 流程說明
1. 讀取所需資料（ # of test -> # of rows -> # of people -> # of vacant seats ）
2. 使用一維陣列儲存資料作為heap array
3. 使用 **maxheapify函式** 將其轉換為max heap，此heap的parent則將必大於child
4. 將root，此heap最大值，加總至結果並減一，並對其利用 **parent_child函式** 重新調整為max heap
5. 重複人數次數後，釋放記憶體空間
6. 重複計算測試次數後，將儲存於一維陣列中的結果統一print出來

#### parent_child函式
用途： 
>檢查一node其child是否比其大，是則交換並利用遞迴反覆檢查、交換至皆符合正確大小關係

作法： 
>利用兩判斷式判斷大小，若小於其child，進行交換，並重新call一次此函式進行遞迴，檢查目標則傳遞至該child

#### maxheapify函式
用途：
>將一個heap array轉換成max heap

作法：
>由heap array最後一項開始檢查，和其parent進行比較，若較parent大則交換，並對其parent執行 **parent_child函式** 重新檢查其原本的另一child是否仍較小，應需求重新調整。

## 程式作業二 - height_union.cpp

### 流程說明
1. 讀取所需資料（ # of tree -> # of nodes -> info of trees ）
2. 讀取指令進行對應動作
3. 若為UNION，使用 **heightUnion函式** 將兩tree進行union
4. 若為FIND，使用 **collapsingFind函式** 對集合做flatten，並回傳步數
5. 若為STOP，輸出所有結果，並結束程式
6. 若為EOF或其餘輸入，則將程式結束

#### heightUnion函式
用途：
>將兩tree進行height union

作法：
>藉儲存每一root的height之一維矩陣，比較兩樹的高度，將height值較小樹之根的parent值變更為另一樹之根的index值，並且若兩樹等高，將合成後的樹高加一。

#### collapsingFind函式
用途：
>將樹平坦化，並回傳使用步數

作法：
>由目標node之parent值一步步回推，直至根，並儲存該值。再重新由目標node回推，並於每個經過點皆更改parent值為儲存之根值。並於每次回推或改變值時記錄步數，最後回傳步數。

### heightUnion及weightUnion對collapsingFind的影響
height union及weight union的差別在於前者比較樹高，後者則比較node總數。
collapsingFind的步數主要取決於目標點和根的高度差，越高則需要越多次的回推和重置，若使用height union，可以在每次進行union時確保樹中最大高度的最小化，即不變或加一，而使用weight union的話則無法掌控。
因此使用height union產生的結果對collapsingFind方法較優。
