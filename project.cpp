#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <limits>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <set>
using namespace std;

bool isOperator(char c){
     return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isCharacter(char c){
     return c == 'x' || c == 'y' || c == 'z';
}

//funkcja losująca wyrażenie
vector<char> generateExpression(int elements) {
    srand( time( NULL ) );
    vector<char> characters = {'x', 'y', 'z', '(', ')', '+', '-', '*', '/'};
    vector<char> expression;
    char prevChar = '\0'; //poprzedni znak
    int openBracket = 0;

    for (int i=0; i<elements; i++){
            char nextChar;
            int attempts = 0;
            do {
                nextChar = characters[rand() % characters.size()];
                attempts++;
                if (attempts > 10000) {
                cerr << "Ups... Nie można wygenerowac wyrazenia, sprobuj ponownie" << endl;
                exit(1);
                }
            //zabezpieczenia
            } while (
                     (nextChar == '(' && (prevChar == ')' || prevChar == '\0') || //Nie możemy mieć '(' po ')', operatorze lub na początku
                     (nextChar == ')' && (isOperator(prevChar) || openBracket <= 0)) || // Nie możemy mieć ')' po operatorze lub jeśli brakuje otwartego nawiasu
                     (prevChar == '(' && (isOperator(nextChar))) || // Nie możemy mieć operatora po '('
                     (prevChar == ')' && (!isOperator(nextChar))) || // Musimy mieć operator po ')'
                     (prevChar == '(' &&  nextChar == '(') || // Nie możemy '(' obok '('
                     (nextChar == '(' && openBracket >= elements - i) ||
                     (nextChar == '(' && (!isOperator(prevChar))) || //musi być operator przed nawiasem
                     (isOperator(prevChar) && isOperator(nextChar)) || //przed występowaniem dwóch operatorów obok siebie
                     (isCharacter(prevChar) && isCharacter(nextChar)) || //przed występowaniem dwóch znaków (x,y,z) obok siebie
                     (isCharacter(prevChar)) && (nextChar == ')') && (expression[i - 2] == '(') || //nie może być jednoelementowego nawiasu, np. (y)
                     //(i == elements - 1 && (nextChar == '+' || nextChar == '-' || nextChar == '*' || nextChar == '/' || nextChar == '(')) || // Nie pozwól na wylosowanie operatora lub nawiasu otwierającego na końcu
                     (prevChar == '(' && nextChar == ')') || (prevChar == ')' && nextChar == '(') || //przed pustym nawiasem (i dwoma nawiasami obok siebie)
                    (i == elements - 1 && (isOperator(nextChar) || nextChar == '(')) || // na końcu nie może być operator ani nawias otwierający
                     (expression.empty() && isOperator(nextChar)) || (expression.empty() && nextChar == ')') // na początku nie może być +-/* i )
                     ));
        if (nextChar == '(') {
                openBracket++;
            }
        else if (nextChar == ')') {
                openBracket--;
            }
        expression.push_back(nextChar);
        prevChar = nextChar;
    }
    return expression;
}

vector<char> fixExpression(const vector<char>& expression, int elements) {
    vector<char> fixedExpression = expression;
    int openBracket = 0;
    int closeBracket = 0;
    int deletedChars = 0;

    // Zlicz otwarte i zamknięte nawiasy
    for (char c : fixedExpression) {
        if (c == '(') {
            openBracket++;
        } else if (c == ')') {
            openBracket--;
        }
    }

    //zrobienie miejsca na append nawiasów zamykających
     for (int i=0; i < openBracket; i++){
        if (fixedExpression.back() == ')'){
            openBracket++;
            //fixedExpression.erase(fixedExpression.end() - 2);
            fixedExpression.pop_back();
        }
        else if (fixedExpression.back() == '('){
            openBracket--;
            fixedExpression.pop_back();
        }
        else {
            fixedExpression.pop_back();
        }
        deletedChars++;
    }

        //usuwanie elementów, jeśli na końcu jest operator
     while (!fixedExpression.empty() && isOperator(fixedExpression.back())) {
        fixedExpression.pop_back();
        deletedChars++;
    }

    // zamykanie nawiasów (jeśli istnieją niezamknięte)
    for (int i = 0; i < openBracket; i++) {
        fixedExpression.push_back(')');
    }

    return fixedExpression;
    }

    set<char> getVariables(const vector<char>& expression) {
    set<char> variables;
    for (char c : expression) {
        if (c == 'x' || c == 'y' || c == 'z') {
            variables.insert(c);
        }
    }
    return variables;
}

//funkcja s³u¿¹ca do interakcji z u¿ytkownikiem i walidacji inputa
int userInput() {
    int numberOfElements;
    bool success = false;

    cout << "Podaj ilosc elementow: ";
    while (true) {
        if (!(cin >> numberOfElements)) {
            cout << "Podaj liczbe calkowita." << endl;
        } else if (cin.peek() != '\n') {
            cout << "Niedozwolone znaki, wprowadz liczbe calkowita." << endl;
        } else if (numberOfElements < 3) {
            cout << "Liczba musi byc wieksza/rowna 3." << endl;
        } else if (numberOfElements % 2 == 0) {
            cout << "Liczba musi byc nieparzysta." << endl;
        } else {
            break; // Wychodzimy z pętli, jeśli wszystkie warunki są spełnione.
        }

        // Czyszczenie strumienia wejściowego
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Podaj ilosc elementow: ";
    }

    /*do {
        cout << "Podaj ilosc elementow: ";
        cin >> numberOfElements;

        if (cin.fail()) {
            cout << "Error! Wprowadzono niepoprawna wartosc." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (numberOfElements < 3) {
            cout << "Error! Wprowadz liczbe większa od 3." << endl;
        } else if (numberOfElements % 2 == 0) {
            cout << "Error! Konstrukcja wyrazenia jest mozliwa tylko przy nieparzystej liczbie elementow." << endl;
        } else {
            success = true;
        }

    } while (!success); */

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

tuple<int, int, int> xyzValues(const vector<char>& expression){
    int x,y,z;
    set<char> variables = getVariables(expression);

    // Pobieranie x
    if (variables.count('x')){
        cout << "\nPodaj liczbe calkowita dla x: ";
        while (!(cin >> x) || cin.peek() != '\n') {
            cout << "Podano nieprawidlowa wartosc. x musi byc liczba calkowita." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podaj liczbe calkowita dla x: ";
        }
    }

    if (variables.count('y')) {
        cout << "Podaj liczbe calkowita dla y: ";
        while (!(cin >> y) || cin.peek() != '\n') {
            cout << "Podano nieprawidlowa wartosc. y musi byc liczba calkowita." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podaj liczbe calkowita dla y: ";
        }
    }

    if (variables.count('z')) {
        cout << "Podaj liczbe calkowita dla z: ";
        while (!(cin >> z) || cin.peek() != '\n') {
            cout << "Podano nieprawidlowa wartosc. z musi byc liczba calkowita." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podaj liczbe calkowita dla z: ";
        }
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

double evaluateRPN(const vector<char>& expression, int x, int y, int z) {
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
                    if (b==0)
                        throw invalid_argument("Niepoprawne wyrazenie: dzielenie przez zero");
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
    vector<char> expression = generateExpression(numberOfElements);

    /*for (size_t i = 0; i < expression.size(); ++i) {
        cout << expression[i] << " ";
        }*/

    vector<char> fixedExpression = fixExpression(expression, numberOfElements);
    saveFile(fixedExpression);
    string readExpression = readFile();
    cout << "WYGENEROWANE WYRAZENIE: " << readExpression;
    tie(x, y, z) = xyzValues(fixedExpression);
    vector<char> rpn_expression = infixToRPN(fixedExpression);
    double result = evaluateRPN(rpn_expression, x, y, z);
    cout << result;
}
