
struct Type
{
    int type1;
    int type2;
    int type3;
};

struct CORP_DATA
{
    int revenue[100];
    Type expense[100];
};

struct EMP_DATA
{
};

struct COLOR_TYPE
{
};

enum StatusType
{
    SUCCESS
};

Type corpExpense[100][100];

void UpdateCorpDatabase([[maybe_unused]] EMP_DATA empRec)
{
}

int profit[12];

// 低质量的子程序
void HandleStuff(CORP_DATA& inputRec, int crntQtr, EMP_DATA empRec,
                 double& estimRevenue, double ytdrevenue, int screenX, int screenY,
                 COLOR_TYPE& newColor, COLOR_TYPE& prevColor, StatusType& status,
                 int expenseType)
{
    for (int i = 0; i < 100; i++)
    {
        inputRec.revenue[i] = 0;
        inputRec.expense[i] = corpExpense[crntQtr][i];
    }

    UpdateCorpDatabase(empRec);
    estimRevenue = ytdrevenue * 4.0 / (double)crntQtr;
    newColor = prevColor;
    status = SUCCESS;

    if (expenseType == 1)
    {
        for (int i = 0; i < 12; i++)
        {
            profit[i] = inputRec.revenue[i] - inputRec.expense[i].type1;
        }
    }
    else if (expenseType == 2)
    {
        for (int i = 0; i < 12; i++)
        {
            profit[i] = inputRec.revenue[i] - inputRec.expense[i].type2;
        }
    }
    else if (expenseType == 3)
    {
        for (int i = 0; i < 12; i++)
        {
            profit[i] = inputRec.revenue[i] - inputRec.expense[i].type3;
        }
    }
}
