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
    //fixownie nawiasów
    int deletedChars = 0;
    while ((expression.back() == '(') || isOperator(expression.back())){ //do debuggera
        if (expression.back() == '('){
                openBracket--;
            }
        expression.erase(expression.length() - 1);
        deletedChars++;
        }
    /*
    if (expression.back() == '('){
        expression.erase(expression.length() - 1); //usuwanie elementu, jeśli wyrażenie kończy się '('
        openBracket--;
        }
    if (isOperator(expression.back())){
        expression.erase(expression.length() - 1); //usuwanie ostatniego elementu, jeśli wyrażenie kończy się operatorem
    } */

    /*
    if (openBracket>0){
        expression.erase(expression.length() - openBracket); //skrócenie wyrażenia o liczbę nawiasów, które chcemy dodać
        expression.append(openBracket, ')');
    } /*
    /*
    if (prevChar != '(' || isOperator(prevChar)){ //if unikający wygenerowania pustego nawiasu oraz operatora na końcu
            expression.append(openBracket, ')');
        } */

    return expression;
    }

//stworzyć funkcję, która będzie fixowała nawiasy i regulowała długość wyrażenia???

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

//funkcja parsująca wyrażenie

//funkcja robiąca odczyt z pliku

int main(){
    int numberOfElements = userInput();
    string expression = randomCharacters(numberOfElements);
    cout << expression;
    saveFile(expression);
    //randomCharacters(numberOfElements);
}
