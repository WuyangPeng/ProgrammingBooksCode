// �������Լ���IN��OUT�ؼ���

#define IN
#define OUT

class Matrix
{
};

class StringCase
{
};

class Sentence
{
};

enum class StatusType
{

};

void InvertMatrix(IN Matrix originalMatrix, OUT Matrix* resultMatrix);
void ChangeSentenceCase(IN StringCase desiredCase, IN OUT Sentence* sentenceToEdit);
void PrintPageNumber(IN int pageNumber, OUT StatusType& status);