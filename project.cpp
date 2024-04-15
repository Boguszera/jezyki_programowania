#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <string>
#include <limits>
#include <fstream>
#include <list>
using namespace std;

bool isOperator(char c){
     return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isCharacter(char c){
     return c == 'x' || c == 'y' || c == 'z';
}

//funkcja losująca wyrażenie
string randomCharacters(int elements) {
    srand( time( NULL ) );
    vector<char> characters = {'x', 'y', 'z', '(', ')', '+', '-', '*', '/'};
    string expression;
    char prevChar = '\0'; //poprzedni znak
    int openBracket = 0;

    for (int i=0; i<elements; i++){
            char nextChar;
            do {
                nextChar = characters[rand() % characters.size()];
            //zabezpieczenia
            } while (
                     (nextChar == '(' && (prevChar == ')' || prevChar == '\0') || //Nie możemy mieć '(' po ')', operatorze lub na początku
                     (nextChar == ')' && (isOperator(prevChar) || openBracket <= 0)) || // Nie możemy mieć ')' po operatorze lub jeśli brakuje otwartego nawiasu
                     (prevChar == '(' && (isOperator(nextChar))) || // Nie możemy mieć operatora po '('
                     (prevChar == ')' && (!isOperator(nextChar))) || // Musimy mieć operator po ')'
                     (prevChar == '(' &&  nextChar == '(') || // Nie możemy '(' obok '('
                     (nextChar == '(' && (!isOperator(prevChar))) || //musi być operator przed nawiasem
                     (isOperator(prevChar) && isOperator(nextChar)) || //przed występowaniem dwóch operatorów obok siebie
                     (isCharacter(prevChar) && isCharacter(nextChar)) || //przed występowaniem dwóch znaków (x,y,z) obok siebie
                     (isCharacter(prevChar)) && (nextChar == ')') && (expression[i - 2] == '(') || //nie może być jednoelementowego nawiasu, np. (y)
                     (prevChar == '(' && nextChar == ')') || (prevChar == ')' && nextChar == '(') || //przed pustym nawiasem (i dwoma nawiasami obok siebie)
                     (expression.empty() && isOperator(nextChar)) || (expression.empty() && nextChar == ')') // na początku nie może być +-/* i )
                     ));

    //liczenie nawiasów
        if (nextChar == '(') {
                openBracket++;
            }
        else if (nextChar == ')') {
                openBracket--;
            }
        expression.push_back(nextChar);
        prevChar = nextChar;
    }
    //usuwanie elementów, jeśli na końcu jest nawias otwierający lub operator (do momentu, w którym ich nie ma)
    int deletedChars = 0;
    while ((expression.back() == '(') || isOperator(expression.back())){ //do debuggera
        if (expression.back() == '('){
                openBracket--;
            }
        expression.erase(expression.length() - 1);
        deletedChars++;
        }

    // zamykanie nawiasów (jeśli istnieją niezamknięte)
    for (int i = 0; i < openBracket; i++) {
        expression.push_back(')');
    }

    return expression;
    }

//funkcja s³u¿¹ca do interakcji z u¿ytkownikiem i walidacji inputa
int userInput() {
    int numberOfElements;
    int isInputOk;
    bool success = false;
    do {
        cout << "Podaj ilosc elementow: "; //naprawic polskie znaki
        cin >> numberOfElements;
        isInputOk = cin.fail();
        if (isInputOk==1) {
            cout << "Nie podano liczby ca³kowitej" << endl;
            cin.clear();
            cin.ignore(numeric_limits < streamsize >::max(), '\n' );

        }
        else if(numberOfElements <= 3){
            cout << "B³¹d! WprowadŸ liczbê wiêksz¹ od 3. " << endl;
        }
        else if (numberOfElements % 2 == 0){
            cout << "B³¹d! Skonsturowanie wyrażenie jest możliwe tylko przy nieparzystej ilości elementów " << endl;
        }
        else {
            success = true;
        }
    } while (success==false);
    return numberOfElements;
}

void saveFile(string expression){
    fstream file;
    file.open("expression.txt", ios::out);
    file << expression;
    file.close();
}
string readFile(){
    fstream file;
    string readExpression;
    file.open("expression.txt", ios::in);
    if (file.good() == false){
        cout<< "Plik nie istnieje lub nie masz uprawnien." << endl;
        exit(0);
    }
    else {
        getline(file, readExpression);
        file.close();
    }
    return readExpression;
}

//funkcja parsująca wyrażenie



int main(){
    int numberOfElements = userInput();
    string expression = randomCharacters(numberOfElements);
    saveFile(expression);
    string readExpression = readFile();
    cout << readExpression;
}
