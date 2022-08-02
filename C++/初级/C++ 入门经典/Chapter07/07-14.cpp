//DISPLAY 7.14 Two-Dimensional Array
//Reads quiz scores for each student into the two-dimensional array grade (but
//the input code is not shown in this display). Computes the average score
//for each student and the average score for each quiz. Displays the quiz scores
//and the averages.
#include <iostream>
#include <iomanip>
const int NUMBER_STUDENTS = 4, NUMBER_QUIZZES = 3;

void computeStAve(const int grade[][NUMBER_QUIZZES], double stAve[]);
//Precondition: Global constants NUMBER_STUDENTS and NUMBER_QUIZZES
//are the dimensions of the array grade. Each of the indexed variables
//grade[stNum-1, quizNum-1] contains the score for student stNum on quiz
//quizNum.
//Postcondition: Each stAve[stNum-1] contains the average for student
//number stu_num.


void computeQuizAve(const int grade[][NUMBER_QUIZZES], double quizAve[]);
//Precondition: Global constants NUMBER_STUDENTS and NUMBER_QUIZZES
//are the dimensions of the array grade. Each of the indexed variables
//grade[stNum-1, quizNum-1] contains the score for student stNum on quiz
//quizNum.
//Postcondition: Each quizAve[quizNum-1] contains the average for quiz number
//quizNum.


void display(const int grade[][NUMBER_QUIZZES],
                            const double stAve[], const double quizAve[]);
//Precondition: Global constants NUMBER_STUDENTS and NUMBER_QUIZZES are the
//dimensions of the array grade. Each of the indexed variables grade[stNum-1,
//quizNum-1] contains the score for student stNum on quiz quizNum. Each
//stAve[stNum-1] contains the average for student stu_num. Each
//quizAve[quizNum -1] contains the average for quiz number quizNum.
//Postcondition: All the data in grade, stAve, and quizAve has been output.


int main( )
{
    using namespace std;
    int grade[NUMBER_STUDENTS][NUMBER_QUIZZES];
    double stAve[NUMBER_STUDENTS];
    double quizAve[NUMBER_QUIZZES];

//The code for filling the array grade goes here, but is not shown.
    computeStAve(grade, stAve);
    computeQuizAve(grade, quizAve);
    display(grade, stAve, quizAve);
    return 0;
}

void computeStAve(const int grade[][NUMBER_QUIZZES], double stAve[])
{
    for (int stNum = 1; stNum <= NUMBER_STUDENTS; stNum++)
    {//Process one stNum:
        double sum = 0;
        for (int quizNum = 1; quizNum <= NUMBER_QUIZZES; quizNum++)
            sum = sum + grade[stNum -1][quizNum -1];
        //sum contains the sum of the quiz scores for student number stNum.
        stAve[stNum -1] = sum/NUMBER_QUIZZES;
        //Average for student stNum is the value of stAve[stNum-1]
    }
}


void computeQuizAve(const int grade[][NUMBER_QUIZZES], double quizAve[])
{
    for (int quizNum = 1; quizNum <= NUMBER_QUIZZES; quizNum++)
    {//Process one quiz (for all students):
        double sum = 0;
        for (int stNum = 1; stNum <= NUMBER_STUDENTS; stNum++)
            sum = sum + grade[stNum -1][quizNum -1];
        //sum contains the sum of all student scores on quiz number quizNum.
        quizAve[quizNum -1] = sum/NUMBER_STUDENTS;
        //Average for quiz quizNum is the value of quizAve[quizNum-1]
    }
}


//Uses iostream and iomanip:
void display(const int grade[][NUMBER_QUIZZES],
                         const double stAve[], const double quizAve[])
{
    using namespace std;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);
    cout << setw(10) << "Student"
         << setw(5) << "Ave"
         << setw(15) << "Quizzes\n";
    for (int stNum = 1; stNum <= NUMBER_STUDENTS; stNum++)
    {//Display for one stNum:
        cout << setw(10) << stNum
             << setw(5) << stAve[stNum-1] << " ";
        for (int quizNum = 1; quizNum <= NUMBER_QUIZZES; quizNum++)
            cout << setw(5) << grade[stNum -1][quizNum -1];
        cout << endl;
    }

    cout << "Quiz averages = ";
    for (int quizNum = 1; quizNum <= NUMBER_QUIZZES; quizNum++)
        cout << setw(5) << quizAve[quizNum -1];
    cout << endl;
}

