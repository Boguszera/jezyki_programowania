#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

void randomCharacters(int elements) {
    char characters[] {'x','y','z','(',')','+','-','*','/'};
    for (int i=0; i<=elements; i++){
        int randomNumber = rand()%9;
        cout << characters[randomNumber];
        //zwrocic tablice, koncepcyjnie uzyc wskaznikow??
    }
}

//funkcja s³u¿¹ca do interakcji z u¿ytkownikiem i walidacji inputa
void userInput() {
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
        else if(numberOfElements <= 0){
            cout << "B³¹d! WprowadŸ liczbê wiêksz¹ od 0. " << endl;
        }
        else {
            success = true;
        }
    } while (success==false);
}

int main(){
    srand( time( NULL ) );
    userInput();
    //randomCharacters(numberOfElements);
}
