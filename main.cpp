#include <iostream>
#include <string>

// sposob 2

// instrukcja if constexpr pozwala sprawdzac warunek ktory jej podano juz na etapie kompilacji
// zeby mozna bylo sprawdzic wtedy warunek nalezy dostarczyc warunek ktory tez jest constexpr
// z racji tego ze operator sizeof... zwraca wyrazenie constexpr mozemy uzyc jego wynik do pracy
// z if constexpr

// kiedy kompilator sprawdza nasz kod i natrafi na funkcje szablonowa zacznie ja i potrzebne
// jej metody generowac wlasnie na etapie kompilacji tam tez natrafi na if constexpr ktory bedzie
// w stanie sprawdzic na etapie kompilacji konczac tym samym generacje kolejnych wersji funkcji
// szablonowej juz na etapie kompilacji
template <typename U, typename ... T>
void get_params(U u, T ... t) {
    std::cout << "WARTOSC: " << u << " ROZMIAR: " << sizeof...(t) << std::endl;
    if constexpr (sizeof...(t) > 0) {
        get_params(t...);
    }
}

// praktyczny przyklad funkcji szablonowej o zmiennej ilosc parametrow do wyszukiwania max wartosci
template <typename U>
auto find_max_element(const U& u1, const U& u2) {
    return u1 > u2 ? u1 : u2;
}
template <typename U, typename ... T>
auto find_max(const U& u, T ... t) {
    if constexpr (sizeof...(t) > 0) {
        return find_max_element(u, find_max(t...));
    }
    return u;
}


int main() {

    get_params("ADAM", "EWA", 10, 20);

    std::cout << find_max(10, 43, 22, 11, 45, 22) << std::endl;
    std::cout << find_max(std::string("ADAM"),std::string("DAREK"),std::string("IZA"),std::string("EWA")) << std::endl;


    return 0;
}
