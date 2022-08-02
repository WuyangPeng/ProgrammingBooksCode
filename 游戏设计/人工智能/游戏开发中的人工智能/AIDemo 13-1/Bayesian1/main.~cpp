//---------------------------------------------------------------------------
/*
Book:           AI for Game Developers
Authors:        David M. Bourg & Glenn Seemann
Example:        Bayesian techniques, Chapter 13
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void TForm1::Initialize(void)
{
        int     i, j;

        for(i=0; i<9; i++)
        {
                NAB[i] = 100;
                for(j=0; j<3; j++)
                {
                        NCAB[i][j] = 33;
                }
        }

        AB[0] = Punch;
        AB[1] = Punch;

        ProbPunch = 0.33;
        ProbLowKick = 0.33;
        ProbHighKick = 0.33;
        N = 0;
        NSuccess = 0;
        NRandomSuccess = 0;
        UpdateForm();
}

TStrikes TForm1::ProcessMove(TStrikes move)
{
        int     i, j;

        N++;
        if(move == Prediction) NSuccess++;
        if(move == RandomPrediction) NRandomSuccess++;

        if((AB[0] == Punch) && (AB[1] == Punch)) i = 0;
        if((AB[0] == Punch) && (AB[1] == LowKick)) i = 1;
        if((AB[0] == Punch) && (AB[1] == HighKick)) i = 2;

        if((AB[0] == LowKick) && (AB[1] == Punch)) i = 3;
        if((AB[0] == LowKick) && (AB[1] == LowKick)) i = 4;
        if((AB[0] == LowKick) && (AB[1] == HighKick)) i = 5;

        if((AB[0] == HighKick) && (AB[1] == Punch)) i = 6;
        if((AB[0] == HighKick) && (AB[1] == LowKick)) i = 7;
        if((AB[0] == HighKick) && (AB[1] == HighKick)) i = 8;

        if(move == Punch) j = 0;
        if(move == LowKick) j = 1;
        if(move == HighKick) j = 2;

        NAB[i]++;
        NCAB[i][j]++;

        AB[0] = AB[1];
        AB[1] = move;


        if((AB[0] == Punch) && (AB[1] == Punch)) i = 0;
        if((AB[0] == Punch) && (AB[1] == LowKick)) i = 1;
        if((AB[0] == Punch) && (AB[1] == HighKick)) i = 2;

        if((AB[0] == LowKick) && (AB[1] == Punch)) i = 3;
        if((AB[0] == LowKick) && (AB[1] == LowKick)) i = 4;
        if((AB[0] == LowKick) && (AB[1] == HighKick)) i = 5;

        if((AB[0] == HighKick) && (AB[1] == Punch)) i = 6;
        if((AB[0] == HighKick) && (AB[1] == LowKick)) i = 7;
        if((AB[0] == HighKick) && (AB[1] == HighKick)) i = 8;

        ProbPunch = (double) NCAB[i][0] / (double) NAB[i];
        ProbLowKick = (double) NCAB[i][1] / (double) NAB[i];
        ProbHighKick = (double) NCAB[i][2] / (double) NAB[i];

        if((ProbPunch > ProbLowKick) && (ProbPunch > ProbHighKick)) return Punch;
        if((ProbLowKick > ProbPunch) && (ProbLowKick > ProbHighKick)) return LowKick;
        if((ProbHighKick > ProbPunch) && (ProbHighKick > ProbLowKick)) return HighKick;

        return (TStrikes) rand() % 3;

}
void __fastcall TForm1::Button1Click(TObject *Sender)
{


        Prediction = ProcessMove(Punch);
        RandomPrediction =  (TStrikes) rand() % 3;
        UpdateForm();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        

        Prediction = ProcessMove(LowKick);
        RandomPrediction =  (TStrikes) rand() % 3;
        UpdateForm();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Prediction = ProcessMove(HighKick);
        RandomPrediction =  (TStrikes) rand() % 3;
        UpdateForm();
}
//---------------------------------------------------------------------------

void    TForm1::UpdateForm(void)
{
        StringGrid1->Cells[0][0] = "A";
        StringGrid1->Cells[1][0] = "B";
        StringGrid1->Cells[2][0] = "C: Punch";
        StringGrid1->Cells[3][0] = "C: Low Kick";
        StringGrid1->Cells[4][0] = "C: High Kick";

        StringGrid1->Cells[0][1] = "Punch";
        StringGrid1->Cells[0][2] = "Punch";
        StringGrid1->Cells[0][3] = "Punch";
        StringGrid1->Cells[0][4] = "Low Kick";
        StringGrid1->Cells[0][5] = "Low Kick";
        StringGrid1->Cells[0][6] = "Low Kick";
        StringGrid1->Cells[0][7] = "High Kick";
        StringGrid1->Cells[0][8] = "High Kick";
        StringGrid1->Cells[0][9] = "High Kick";

        StringGrid1->Cells[1][1] = "Punch";
        StringGrid1->Cells[1][2] = "Low Kick";
        StringGrid1->Cells[1][3] = "High Kick";
        StringGrid1->Cells[1][4] = "Punch";
        StringGrid1->Cells[1][5] = "Low Kick";
        StringGrid1->Cells[1][6] = "High Kick";
        StringGrid1->Cells[1][7] = "Punch";
        StringGrid1->Cells[1][8] = "Low Kick";
        StringGrid1->Cells[1][9] = "High Kick";

        for(int i=0; i<9; i++)
            for(int j=0; j<3; j++)
            {
                double  tmp = (double) NCAB[i][j]/(double) NAB[i];
                StringGrid1->Cells[j+2][i+1] = FloatToStrF(tmp, ffFixed, 15, 3);
            }

        switch(AB[0])
        {
                case Punch: Label6->Caption = "Punch"; break;
                case LowKick: Label6->Caption = "LowKick"; break;
                case HighKick: Label6->Caption = "HighKick"; break;
        }
        switch(AB[1])
        {
                case Punch: Label5->Caption = "Punch"; break;
                case LowKick: Label5->Caption = "LowKick"; break;
                case HighKick: Label5->Caption = "HighKick"; break;
        }

        switch(Prediction)
        {
                case Punch: Label8->Caption = "Punch"; break;
                case LowKick: Label8->Caption = "LowKick"; break;
                case HighKick: Label8->Caption = "HighKick"; break;
        }

        switch(RandomPrediction)
        {
                case Punch: Label7->Caption = "Punch"; break;
                case LowKick: Label7->Caption = "LowKick"; break;
                case HighKick: Label7->Caption = "HighKick"; break;
        }

        if(N>0)
        {
                Label9->Caption = FloatToStrF((double) NSuccess / (double) N, ffFixed, 15, 3);
                Label10->Caption = FloatToStrF((double) NRandomSuccess / (double) N, ffFixed, 15, 3);
        } else {
                Label9->Caption = "na";
                Label10->Caption = "na";
        }






}

void __fastcall TForm1::FormActivate(TObject *Sender)
{
        Initialize();
}
//---------------------------------------------------------------------------

