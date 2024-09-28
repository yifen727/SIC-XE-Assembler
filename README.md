OS: windows powershell
language: C++
我的組繹器架構:
首先有一個struct 名為NODE，裡面有對每一行location、symbol、instruction、reference、
objectcode，還有存在assembly_code中有幾個單詞，以便後面的處理。assem[500]是一個
struct的陣列，紀錄每一行的那些特徵，也是最後的輸出。
一開始先輸入assembly_code的檔案名稱，讀進檔案之後，先數每一行有幾個單字(以便他們
可以放到我想要的正確位置)，切一行的方式是用空白來切。如果只有有三個單字就會分別放
到symbol、instruction、reference，如果只有兩個就是放到instruction 和 refernce，以此類推。
接下來就是先做出每個statement的location，根據不同的instruction來決定不同的location。
做完location後就是做object code，根據每一行的location、symbol、instruction的opcode還有
refernce來決定每行的object code。另外也要檢查是要用base relative還是PC relative。
最後就是做object program，一開始先獨立做Head record，然後用迴圈將一行一行讀進來做
Text record，最後做Modification record和End record。
我將有location 和 source statement還有object code的部分放到名為ouput.txt的檔案中，
object program放到名為object_program.txt的檔案。
在實作過程學到的事物:
雖然之前在程設二有學過對字串的處理，但一些時間沒有用還是有些忘記，且當時是用c語言
，因為平常寫程式比較常用C++所以我就用C++來寫這次的專題，也學了一些C++中處理字串
的方式。我學會用getline()函式，一行一行的讀取資料內容。也利用物件istringstream以及運
算子 >>，可以方便地將文字分解成單詞，並將其存入變數中。每寫好一部分我就會push到我
的github上。
