#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <string>
#include <limits>
#include <fstream>
#include <list>
#include <stack>
#include <unordered_map>
using namespace std;

bool isOperator(char c){
     return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isCharacter(char c){
     return c == 'x' || c == 'y' || c == 'z';
}

//funkcja losująca wyrażenie
vector<char> randomCharacters(int elements) {
    srand( time( NULL ) );
    vector<char> characters = {'x', 'y', 'z', '(', ')', '+', '-', '*', '/'};
    vector<char> expression;
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
        expression.pop_back();
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

void saveFile(vector<char> expression){
    fstream file;
    file.open("expression.txt", ios::out);
    for (char c : expression) {
            file << c;
        }
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

tuple<int, int, int> xyzValues(){
    int x,y,z;
    // Pobieranie x
    cout << "\nPodaj liczbe calkowita dla x: ";
    while (!(cin >> x)) {
        cout << "Podano nieprawidlowa wartosc. x musi byc liczba calkowita." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Podaj liczbe calkowita dla x: ";
    }

    // Pobieranie y
    cout << "Podaj liczbe calkowita dla y: ";
    while (!(cin >> y)) {
        cout << "Podano nieprawidlowa wartosc. y musi byc liczba calkowita." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Podaj liczbe calkowita dla y: ";
    }

    // Pobieranie z
    cout << "Podaj liczbe calkowita dla z: ";
    while (!(cin >> z)) {
        cout << "Podano nieprawidlowa wartosc. z musi byc liczba calkowita." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Podaj liczbe calkowita dla z: ";
    }
    return make_tuple(x, y, z);
}

vector<char> infixToRPN(const vector<char>& infix) {
    vector<char> rpn;
    stack<char> operators;

    for (char c : infix) {
        if (isCharacter(c)) {
            rpn.push_back(c);
        } else if (isOperator(c)) {
            while (!operators.empty() && operators.top() != '(' && ((c != '*' && c != '/') || (operators.top() != '+' && operators.top() != '-'))) {
                rpn.push_back(operators.top());
                operators.pop();
            }
            operators.push(c);
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                rpn.push_back(operators.top());
                operators.pop();
            }
            operators.pop(); // Usuń otwierający nawias '('
        }
    }

    while (!operators.empty()) {
        rpn.push_back(operators.top());
        operators.pop();
    }

    return rpn;
}

double evaluateRPN(const vector<char>& expression, double x, double y, double z) {
    stack<double> stack;

    for (char c : expression) {
        if (isCharacter(c)) {
            if (c == 'x') stack.push(x);
            else if (c == 'y') stack.push(y);
            else if (c == 'z') stack.push(z);
        } else if (isOperator(c)) {
            double b = stack.top();
            stack.pop();
            double a = stack.top();
            stack.pop();
            switch (c) {
                case '+':
                    stack.push(a + b);
                    break;
                case '-':
                    stack.push(a - b);
                    break;
                case '*':
                    stack.push(a * b);
                    break;
                case '/':
                    stack.push(a / b);
                    break;
            }
        }
    }

    return stack.top();
}

int main(){
    int numberOfElements = userInput();
    int x, y, z;
    vector<char> expression = randomCharacters(numberOfElements);
    saveFile(expression);
    string readExpression = readFile();
    cout << "WYGENEROWANE WYRAZENIE: " << readExpression;
    tie(x, y, z) = xyzValues();
    vector<char> rpn_expression = infixToRPN(expression);
    double result = evaluateRPN(rpn_expression, x, y, z);
    cout << result;
}
