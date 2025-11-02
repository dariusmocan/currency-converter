
#include <iostream>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <iomanip>
#include "json.hpp"
using json = nlohmann::json;

void show_currencies(json currencyData) {
    double baseAmount = 1.0;
    std::string baseCurrency = "eur";
    std::cout << "\nConversion Table for euro\n";
    std::cout << "------------------------\n";

    for (auto& [currency, rate] : currencyData.items()) {
        double converted = baseAmount * (rate / 1.0);
        std::cout << baseAmount << ": " << baseCurrency << " = " << converted << " " << currency << '\n';
    }
}


int main()
{
    std::string fromCurrency;
    std::string toCurrency;
    const char ESC = 27;
    char key = ' ';
    std::cout << std::fixed << std::setprecision(2);

    // opening file 'currencies.json'
    std::ifstream file("currencies.json");
    if (!file.is_open()) {
        std::cerr << "Cannot open currencies.json\n";
        return 1;
    }

    // open json type variable currencyData 
    json currencyData;
    // transfer the file to the json variable
    file >> currencyData;
    file.close();

    // show currencies on 's'
    std::cout << "Press 's' to show the currencies exchanges from euro! Press any other key if not";

    do{
        key = _getch();
        if (key == 's') {
            show_currencies(currencyData);
        }


        // get the currencies wanted
        std::cout << "Enter the currency you have : ";
        std::cin >> fromCurrency;
        // transform all the chars into lower to match the ones from the json file
        std::transform(fromCurrency.begin(), fromCurrency.end(), fromCurrency.begin(), ::tolower);
        // if fromCurrency doesn't exist user is asked to insert a valid one
        while (!currencyData.contains(fromCurrency)) {
            std::cout << "Invalid source currency! Try again : ";
            std::cin >> fromCurrency;
        }

        std::cout << "Enter the currency you want : ";
        std::cin >> toCurrency;
        // transform all the chars into lower to match the ones from the json file
        std::transform(toCurrency.begin(), toCurrency.end(), toCurrency.begin(), ::tolower);
        // if tocurrency doesn't exist user is asked to insert a valid one
        while (!currencyData.contains(toCurrency)) {
            std::cout << "Invalid exchangable currency! Try again : ";
            std::cin >> toCurrency;
        }

        double from = currencyData[fromCurrency];
        double to = currencyData[toCurrency];
        double amount;


        std::cout << "Introduce amount to change : ";
        while (!(std::cin >> amount) || amount <= 0) {
            std::cout << "Introduce a valid amount : ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        double exchanged = amount * (to / from);

        std::cout << amount << " " << fromCurrency << " = " << exchanged << " " << toCurrency << '\n';

        std::cout << "Press any key to exchange other currencies or ESC to exit...\n";
        key = _getch();
    }while (key != ESC);
    
    std::cout << "Pressed 'Esc' : Program exited";
}
