# Generator i Ewaluator Wyrażeń

Ten projekt to narzędzie do generowania, naprawiania i ewaluacji wyrażeń matematycznych z wykorzystaniem zmiennych `x`, `y` i `z`. Narzędzie umożliwia generowanie losowych wyrażeń, naprawianie błędów składniowych, konwersję wyrażeń z notacji infiksowej na odwrotną notację polską (RPN) oraz obliczanie wyniku na podstawie danych wejściowych od użytkownika.

## Funkcje

- **Generowanie Wyrażeń**: Losowe generowanie wyrażenia matematycznego zawierającego zmienne `x`, `y`, `z` oraz operatory (`+`, `-`, `*`, `/`), przy zapewnieniu poprawności składniowej wyrażenia.
- **Walidacja Wyrażeń**: Automatyczna naprawa wyrażeń, które zawierają niedomknięte nawiasy lub niepoprawnie rozmieszczone operatory.
- **Przechowywanie Wyrażeń**: Zapisanie wygenerowanego wyrażenia do pliku tekstowego oraz jego odczyt przed ewaluacją.
- **Wejście Zmiennych**: Prośba o podanie przez użytkownika wartości zmiennych `x`, `y` i `z`.
- **Ewaluacja Wyrażeń**: Konwersja wyrażenia z notacji infiksowej na odwrotną notację polską (RPN) i obliczenie wyniku na podstawie wprowadzonych wartości zmiennych.
- **Obsługa Błędów**: Obsługuje typowe błędy, takie jak dzielenie przez zero oraz nieprawidłowe dane wejściowe od użytkownika.

## Wymagania

- C++11 lub nowszy
- Kompilator C++ (np. g++, clang++)
- Standardowa biblioteka C++ (nie wymagane zewnętrzne biblioteki)

## Instalacja

1. Sklonuj repozytorium lub pobierz pliki projektu.
2. Otwórz terminal lub wiersz poleceń.
3. Przejdź do katalogu projektu.
4. Skompiluj program za pomocą wybranego kompilatora C++. Na przykład używając `g++`
	```bash
   g++ -std=c++11 main.cpp -o expression_evaluator
   ```
	
##Użycie

1. Kompilacja programu: Po skompilowaniu, uruchom program z terminala:

	```bash
	./expression_evaluator
	```

2. Podaj liczbę elementów: Zostaniesz poproszony o podanie nieparzystej liczby elementów, które ma mieć wygenerowane wyrażenie (np. 7).

3. Generowanie i Naprawianie Wyrażeń: Program wygeneruje losowe wyrażenie matematyczne z wykorzystaniem zmiennych x, y, z oraz operatorów. Następnie program zwaliduje i naprawi błędy składniowe, takie jak niedomknięte nawiasy lub niepoprawne rozmieszczenie operatorów.

4. Wejście Zmiennych: Po wygenerowaniu wyrażenia, użytkownik zostanie poproszony o podanie wartości dla zmiennych x, y i z.

5. Ewaluacja Wyniku: Wyrażenie zostanie skonwertowane na odwrotną notację polską (RPN), a wynik obliczony na podstawie wprowadzonych przez użytkownika wartości zmiennych.

6. Zapis i Odczyt Wyrażenia: Wygenerowane i naprawione wyrażenie jest zapisywane do pliku tekstowego o nazwie expression.txt i odczytywane przed ewaluacją.

## Repozytorium
Link do repozytorium GitHub: [https://github.com/Boguszera/jezyki_programowania](https://github.com/Boguszera/jezyki_programowania)