#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

int ReadHowManyQuestions()
{
    int NumberOfQuestions;
    do{
        cout << "How many questions do you want to answer? (1-10): ";
        cin >> NumberOfQuestions;
        if (NumberOfQuestions < 1 || NumberOfQuestions > 10)
            cout << "Invalid number! Please enter a number between 1 and 10: ";
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
    int Level;
    do {
        cout << "Select question level (1: Easy, 2: Medium, 3: Hard, 4: Mixed): ";
        cin >> Level;
        if (Level < 1 || Level > 4)
            cout << "Invalid level! Please select a valid level (1-4): ";
    } while (Level < 1 || Level > 4);

    return (enQuestionsLevel)Level;
}

enOperationType ReadOperationType()
{
    int OpType;

    do{
        cout << "Select operation type (1: Add, 2: Subtract, 3: Multiply, 4: Divide, 5: Mixed): ";
        cin >> OpType;
        if (OpType < 1 || OpType > 5)
            cout << "Invalid operation type! Please select a valid option (1-5): ";
	} while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "x";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
    return arrQuestionLevelText[QuestionLevel - 1];
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return (Number2 != 0) ? (Number1 / Number2) : 0;
    default:
        return Number1 + Number2;
    }
}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};


stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }

    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    } 

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
        break;
    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;

        break;
    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;

        break;
    }



    return Question;
}

void GenerateQuestionQuizz(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

int ReadPlayerAnswer()
{
    int PlayerAnswer;
    cout << "Your answer: ";
    cin >> PlayerAnswer;
    return PlayerAnswer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << " "
        << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << " "
        << Quizz.QuestionList[QuestionNumber].Number2 << " = ";
}

void CorrectPlayerAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        cout << "Wrong answer :-("
            << "\n The correct answer is : "
            << Quizz.QuestionList[QuestionNumber].CorrectAnswer << "\n";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        cout << "Correct answer! :-)\n";
	}
    cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
 
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
		CorrectPlayerAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultText(bool pass)
{
    if(pass)
		return "passed";
	else
		return "failed";
}

void PrintQuizResult(stQuizz& Quizz)
{
    cout << "\n ";
	cout << "\n----------------------------------\n\n";
	cout << " Final Result Is " << GetFinalResultText(Quizz.isPass) << "!\n";
	cout << "\n----------------------------------\n";

    cout << "Number of Questions: " << Quizz.NumberOfQuestions << "\n";
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << "\n";
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << "\n";
    cout << "Questions Level: " << GetQuestionLevelText(Quizz.QuestionsLevel) << "\n";
	cout << "Operation Type: " << GetOpTypeSymbol(Quizz.OpType) << "\n";
    cout << "----------------------------------\n\n";
    if (Quizz.isPass)
        cout << "Great job! You did well!\n";
    else
        cout << "Don't worry! Keep practicing and try again.\n";
	cout << "\n----------------------------------\n";
	SetScreenColor(Quizz.isPass);
}

void PlayMathGame()
{
    stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOperationType();


	GenerateQuestionQuizz(Quizz);

    AskAndCorrectQuestionListAnswers(Quizz);

	PrintQuizResult(Quizz);

    cout << (Quizz.isPass ? "You Passed the Quiz!\n" : "You Failed the Quiz!\n");
}

void ResetScreen()
{
	system("cls");
    system("color 0F");
}

void StartGame()
{
   
	char choice='y';
    do{

		ResetScreen();
        PlayMathGame();

        cout << "Do you want to play again? (y/n): ";
        cin >> choice;

	} while (choice == 'y' || choice == 'Y');
   
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}