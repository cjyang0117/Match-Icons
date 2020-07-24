//---------------------------------------------------------------------------

#ifndef EXIUH
#define EXIUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TComboBox *nxn;
        TComboBox *CTime;
        TButton *adpic;
        TButton *replay;
        TOpenPictureDialog *OpenPic;
        TPanel *LCard;
        TPanel *RCard;
        TPanel *ImgBox;
        TImage *Image1;
        TButton *start;
        TTimer *Timer1;
        TImage *Image2;
        TTimer *GTime;
        TLabel *LTime;
        TButton *reset;
        TGroupBox *BasisPic;
        TTimer *deleTime;
        void __fastcall adpicClick(TObject *Sender);
        void __fastcall delepicClick(TObject *Sender);
        void __fastcall nxnChange(TObject *Sender);
        void __fastcall Card1Click(TObject *Sender);
        void __fastcall Card2Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall startClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall replayClick(TObject *Sender);
        void __fastcall GTimeTimer(TObject *Sender);
        void __fastcall CTimeChange(TObject *Sender);
        void __fastcall resetClick(TObject *Sender);
        void __fastcall addpicClick(TObject *Sender);
        void __fastcall deleTimeTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
