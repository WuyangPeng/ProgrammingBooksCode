//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------

enum TStrikes {Punch, LowKick, HighKick};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label8;
        TLabel *Label2;
        TLabel *Label7;
        TLabel *Label9;
        TLabel *Label10;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        int             NAB[9];
        int             NCAB[9][3];
        TStrikes        AB[2];
        double          ProbPunch;
        double          ProbLowKick;
        double          ProbHighKick;
        TStrikes        Prediction;
        TStrikes        RandomPrediction;

        int             N;
        int             NSuccess;
        int             NRandomSuccess;

        void Initialize(void);
        TStrikes ProcessMove(TStrikes move);
        void UpdateForm(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
