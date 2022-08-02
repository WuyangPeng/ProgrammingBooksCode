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

#define NUM_RULES       27

enum TStrikes {Punch, LowKick, HighKick, sUnknown};

struct TWorkingMemory {
        TStrikes        strikeA; // previous, previous strike (data)
        TStrikes        strikeB; // previous strike (data)
        TStrikes        strikeC; // next, predicted, strike (assertion)
        // note: can add additional elements here for things such as which counter to throw etc...
};

TWorkingMemory  WorkingMemory;  // global working memory variable

class TRule {
public:
        TRule();
        void            SetRule(TStrikes A, TStrikes B, TStrikes C);
        
        bool            matched;
        int             weight;
        TStrikes        antecedentA;
        TStrikes        antecedentB;
        TStrikes        consequentC;
};

//#define SET_RULE(i, A, B, C) (Rules[i].antecedentA = A; Rules[i].antecedentB = B; Rules[i].consequentC = C;)

class TForm1 : public TForm
{
__published:	// IDE-managed Components
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
        TStringGrid *StringGrid1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        TRule           Rules[NUM_RULES];
        int             PreviousRuleFired;

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
