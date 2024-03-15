#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void randomCharacters(int elements) {
    char characters[] {'x','y','z','(',')','+','-','*','/'};
    for (int i=0; i<=elements; i++){
        int randomNumber = rand()%9;
        cout << characters[randomNumber];
        //zwrocic tablice, koncepcyjnie uzyc wskaznikow??
    }
}

int main(){
    srand( time( NULL ) );
    int numberOfElements;
    cout << "Podaj ilosc elementow: "; //naprawic polskie znaki
    cin >> numberOfElements;
    randomCharacters(numberOfElements);

}
