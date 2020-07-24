//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EXIU.h"
#include <Jpeg.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TImage *Img[100];                          //選擇的圖
TImage *BasisImg[8];                       //基本圖庫
TImage *LAllCard[100],*RAllCard[100];      //左 右的牌

int sum=0,             //選圖的總圖數
    num=0,             //幾乘幾 num*num
    w,h,               //長 寬
    opentimes=0,       //判斷是否第二次翻牌
    time1=0,           //倒數計時
    lasttag,           //上一個翻的答案
    thishint,          //這一張翻的牌
    win=0,             //判斷是否獲勝
    deletetag,         //要刪除的圖
    lasthint;          //上一張翻的牌

String repeat[100],    //檢查圖是否重複
       checkLR;        //判斷左邊還右邊
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::adpicClick(TObject *Sender)
{
  w=ImgBox->Width/15;
  h=ImgBox->Height;
  TImage *AImg;
  if(OpenPic->Execute()==true){   //選擇圖檔 檢查是否有選圖
    nxn->Enabled=true;

    for(int i=0;i<sum;i++){
      if(repeat[i]==OpenPic->FileName){
        ShowMessage("請勿選擇重複的圖片");   //檢查有無選到重複的圖
        return;
      }
    }

    AImg=new TImage(Form1);                         //暫時的指標 圖形類
    AImg->Parent=ImgBox;                            //在ImgBox中顯示
    AImg->Picture->LoadFromFile(OpenPic->FileName); //圖片是上面選擇的圖檔
    AImg->Stretch=true;                             //圖片可以伸縮
    AImg->Width=w;                                  //圖寬
    AImg->Height=h;                                 //圖長
    AImg->Left=w*sum;                               //每增一圖 左右位置增加w
    AImg->Top=0;                                    //高都是0
    AImg->Tag=sum;                                  //代稱圖名
    AImg->Hint=OpenPic->FileName;                   //每張圖的檔名
    AImg->OnClick=delepicClick;                     //點擊這張圖相當於delepic的Click事件
    Img[sum]=AImg;                                  //將暫時的指標存入指標陣列
    repeat[sum]=OpenPic->FileName;                  //將選過的檔名存入陣列 檢查重複用
    sum++;                                          //新增一張圖 圖的總數加一
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::delepicClick(TObject *Sender)
{
  TImage *Delete=(TImage *)Sender;

  for(int i=Delete->Tag+1;i<sum;i++){
    repeat[i-1]=repeat[i];
    Img[i]->Left=Img[i]->Left-w;    //把要刪的圖後面"位置""代稱圖名""指標"全部往前移
    Img[i]->Tag--;                  //圖的總數減一
    Img[i-1]=Img[i];
  }
  sum--;

  deletetag=Delete->Tag;
  Img[deletetag+sum]=Delete;
  deleTime->Enabled=true;          //在timer中把點擊的指標刪掉
}
//---------------------------------------------------------------------------



void __fastcall TForm1::nxnChange(TObject *Sender)
{
  adpic->Enabled=false;
  BasisPic->Enabled=false;
  CTime->Enabled=true;
  for(int i=0;i<sum;i++){
    Img[i]->Enabled=false;
  }

  for(int i=0;i<num*num;i++){
    delete LAllCard[i];
    delete RAllCard[i];
    LAllCard[i]=NULL;
    RAllCard[i]=NULL;
  }

  TImage *ACard,*BCard;
  int Img1Tag=0,Img2Tag=0;
  num=nxn->ItemIndex+2;                  //EX: 0+2=2 nxn就是2x2
  w=LCard->Width/num;                    //圖寬 長
  h=LCard->Height/num;
  for(int i=0;i<num*num;i++){            //產生nxn張圖
    ACard=new TImage(Form1);
    ACard->Picture=Image1->Picture;      //牌背
    ACard->Stretch=true;                 //圖可伸縮
    ACard->Parent=LCard;                 //在LCard中顯示
    ACard->Width=w;                      //圖的長寬
    ACard->Height=h;
    ACard->Left=w*(i%num);               //2x2為範例 圖的left 0 1  top 0 0
    ACard->Top=h*(i/num);                //                   0 1      1 1
    ACard->Hint=i;                       //每張圖的代稱名字
    ACard->Tag=Img1Tag++;
    if(Img1Tag==sum) Img1Tag=0;          //將一開始選擇的圖片tag 先依順序放入牌裡
    ACard->OnClick=Card1Click;           //等於Card1的點擊事件
    LAllCard[i]=ACard;                   //暫時生成的牌存入陣列
  }
  for(int i=0;i<num*num;i++){
    BCard=new TImage(Form1);
    BCard->Picture=Image1->Picture;
    BCard->Stretch=true;
    BCard->Parent=RCard;
    BCard->Width=w;
    BCard->Height=h;
    BCard->Left=w*(i%num);
    BCard->Top=h*(i/num);
    BCard->Hint=i;
    BCard->Tag=Img2Tag++;
    if(Img2Tag==sum) Img2Tag=0;
    BCard->OnClick=Card2Click;
    RAllCard[i]=BCard;
  }
  for(int i=0;i<1000;i++){               //將tag交換洗亂一千次
    int t1,t11,t2,t22;
    for(int j=0;j<num*num;j++){
      t1=random(num*num);
      t2=random(num*num);
      t11=LAllCard[t1]->Tag;
      t22=RAllCard[t2]->Tag;
      LAllCard[t1]->Tag=LAllCard[j]->Tag;
      RAllCard[t2]->Tag=RAllCard[j]->Tag;
      LAllCard[j]->Tag=StrToInt(t11);
      RAllCard[j]->Tag=StrToInt(t22);
    }
  }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Card1Click(TObject *Sender)
{
  TImage *open1=(TImage *)Sender;
  LCard->Enabled=false;
  RCard->Enabled=true;

  int x;
  x=open1->Tag;
  open1->Picture=Img[x]->Picture;          //翻開的牌就是之前存放的tag 與Img連結

  opentimes++;
  if(opentimes==2){                        //檢查是否第二次翻牌
    opentimes=0;
    if(open1->Tag!=lasttag){               //兩張牌圖形是否不一樣
      RCard->Enabled=false;
      checkLR="L";                         //左邊翻第二次
      Timer1->Enabled=true;                //執行timer
      thishint=StrToInt(open1->Hint);      //記住這張牌的答案
    }else{
      open1->Enabled=false;
      RAllCard[lasthint]->Enabled=false;
      LCard->Enabled=true;
      win++;                              //翻的次數加一
    }
  }else{
    lasthint=StrToInt(open1->Hint);      //第一次翻牌
  }
  lasttag=open1->Tag;                    //上一次翻的圖
  if(win==num*num){                      //若翻的次數=nxn 獲勝
    GTime->Enabled=false;
    ShowMessage("WOW~恭喜您獲勝了!!");
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Card2Click(TObject *Sender)
{
  TImage *open2=(TImage *)Sender;
  LCard->Enabled=true;
  RCard->Enabled=false;

  int x;
  x=open2->Tag;
  open2->Picture=Img[x]->Picture;

  opentimes++;
  if(opentimes==2){
    opentimes=0;
    if(open2->Tag!=lasttag){
      LCard->Enabled=false;
      checkLR="R";
      Timer1->Enabled=true;
      thishint=StrToInt(open2->Hint);
    }else{
      open2->Enabled=false;
      LAllCard[lasthint]->Enabled=false;
      RCard->Enabled=true;
      win++;
    }
  }else{
    lasthint=StrToInt(open2->Hint);
  }
  lasttag=open2->Tag;
  if(win==num*num){
    GTime->Enabled=false;
    ShowMessage("WOW~恭喜您獲勝了!!");
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  for(int i=0;i<num*num;i++){
    delete LAllCard[i];
    delete RAllCard[i];
    LAllCard[i]=NULL;
    RAllCard[i]=NULL;
  }
  for(int i=0;i<sum;i++){
    delete Img[i];
    Img[i]=NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  randomize();
  w=BasisPic->Width/2;
  h=BasisPic->Height/4;
  TImage *CImg;
  for(int i=0;i<8;i++){
    CImg=new TImage(Form1);                                    //遊戲執行時一開始產生的基本圖庫
    CImg->Parent=BasisPic;                                     //產生方式與牌相似
    CImg->Picture->LoadFromFile("bg\\"+IntToStr(i)+".jpg");
    CImg->Width=w;
    CImg->Height=h;
    CImg->Left=w*(i%2);
    CImg->Top=h*(i/2);
    CImg->Stretch=true;
    CImg->Tag=i;
    CImg->OnClick=addpicClick;
    BasisImg[i]=CImg;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::startClick(TObject *Sender)
{
  RCard->Enabled=true;
  LCard->Enabled=true;
  CTime->Enabled=false;
  nxn->Enabled=false;
  replay->Enabled=true;
  reset->Enabled=true;
  start->Enabled=false;
  GTime->Enabled=true;
  time1=(CTime->ItemIndex+1)*10;   //EX: ItemIndex=0,10s (0+1)10=10秒
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  if(checkLR=="L"){                                 //左邊翻第二次
    LAllCard[thishint]->Picture=Image1->Picture;    //左邊的圖(這次翻) 蓋回去
    RAllCard[lasthint]->Picture=Image1->Picture;    //右邊的圖(上次翻) 蓋回去
  }else{                                            //右邊第二次
    LAllCard[lasthint]->Picture=Image1->Picture;    //左邊的圖(上次翻) 蓋回去
    RAllCard[thishint]->Picture=Image1->Picture;    //右邊的圖(這次翻) 蓋回去
  }
  Timer1->Enabled=false;
  LCard->Enabled=true;
  RCard->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::replayClick(TObject *Sender)
{
  nxnChange(Sender);                                 //重新開始 刺激nxnChange 重新產生牌

  LTime->Caption=IntToStr((CTime->ItemIndex+1)*10);
  time1=(CTime->ItemIndex+1)*10;
  GTime->Enabled=true;
  CTime->Enabled=false;
  start->Enabled=false;
  RCard->Enabled=true;
  LCard->Enabled=true;
  opentimes=0;
  win=0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::GTimeTimer(TObject *Sender)
{
  if(time1>0){                                  //時間到之前
    LTime->Caption=IntToStr(--time1);           //時間每秒減一 顯示在Label上
  }else{
    GTime->Enabled=false;
    LCard->Enabled=false;
    RCard->Enabled=false;
    ShowMessage("Game Over!!\n請重新開始新的一局");
  }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::CTimeChange(TObject *Sender)
{
  LTime->Caption=IntToStr((CTime->ItemIndex+1)*10);     //選擇遊戲時間
  nxn->Enabled=false;
  start->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::resetClick(TObject *Sender)    //重設按鈕
{
  for(int i=0;i<8;i++){
    BasisImg[i]->Enabled=true;
  }

  for(int i=0;i<sum;i++){
    delete Img[i];
    Img[i]=NULL;
    repeat[i]=NULL;
  }

  for(int i=0;i<num*num;i++){
    delete LAllCard[i];
    delete RAllCard[i];
    LAllCard[i]=NULL;
    RAllCard[i]=NULL;
  }

  adpic->Enabled=true;
  BasisPic->Enabled=true;
  reset->Enabled=false;
  replay->Enabled=false;
  RCard->Enabled=false;
  LCard->Enabled=false;
  GTime->Enabled=false;
  nxn->Text="選擇難度";
  CTime->Text="選擇時間";
  LTime->Caption=0;
  opentimes=0;
  win=0;
  sum=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::addpicClick(TObject *Sender)
{
  TImage *Add=(TImage *)Sender;
  nxn->Enabled=true;
  Add->Enabled=false;
  w=ImgBox->Width/15;
  h=ImgBox->Height;                     //點擊基本圖庫中的圖 新增圖

  Img[sum]=new TImage(Form1);
  Img[sum]->Parent=ImgBox;              //在ImgBox中顯示
  Img[sum]->Picture=Add->Picture;       //ImgBox中顯示的為此點擊的圖
  Img[sum]->Stretch=true;
  Img[sum]->Width=w;
  Img[sum]->Height=h;
  Img[sum]->Left=w*sum;
  Img[sum]->Top=0;
  Img[sum]->Tag=sum;
  Add->Tag=sum;
  Img[sum]->OnClick=delepicClick;
  repeat[sum]="bg\\"+IntToStr(Add->Tag);
  sum++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::deleTimeTimer(TObject *Sender)
{
  delete Img[deletetag+sum];
  deleTime->Enabled=false;
}
//---------------------------------------------------------------------------


