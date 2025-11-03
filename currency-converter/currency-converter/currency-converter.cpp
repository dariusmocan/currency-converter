
#include <iostream>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <iomanip>
#include "json.hpp"
using json = nlohmann::json;

// function used to show all currencies at the beginning if 's' is pressed
void show_currencies(json currencyData) {
    double baseAmount = 1.0;
    std::string baseCurrency = "eur";
    std::string baseCurrencyUpper = "EUR";
    std::cout << "\nConversion Table for euro\n";
    std::cout << "------------------------\n";

    for (auto& [currency, rate] : currencyData.items()) {
        double rateVal = rate.get<double>();
        std::string currencyUpper = currency;
        // we want to display Currencie sin uppercase
        std::transform(currencyUpper.begin(), currencyUpper.end(), currencyUpper.begin(), ::toupper);
        // exclude very small insignificant currencies
        if (rateVal > 0.1) {
            double converted = baseAmount * rateVal;
            std::cout << baseAmount << ": " << baseCurrencyUpper << " = " << converted << " " << currencyUpper << '\n';
        }
    }
}


int main()
{
    std::string fromCurrency; // currency to be exchanged
    std::string toCurrency; // the currency  in which the old one is exchanged
    const char ESC = 27;
    char key = ' ';
    // only show 2 digits after .
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


    do{
        // show currencies on 's'
        std::cout << "Press 's' to show the currencies exchanges from euro! Press any other key if not :\n";

        key = _getch();
        if (key == 's') {
            show_currencies(currencyData);
        }
        else if (key == ESC) {
            std::cout << "\nPressed 'Esc' : Program exited";
            return 1;
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

        // get the currencies' exchange values
        double from = currencyData[fromCurrency];
        double to = currencyData[toCurrency];
        double amount;


        std::cout << "Introduce amount to change : ";
        // verify the amount to be valid
        while (!(std::cin >> amount) || amount <= 0) {
            std::cout << "Introduce a valid amount : ";
            // clear and ignore the buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        double exchanged = amount * (to / from);

        // display the currencies uppercase
        std::transform(fromCurrency.begin(), fromCurrency.end(), fromCurrency.begin(), ::toupper);
        std::transform(toCurrency.begin(), toCurrency.end(), toCurrency.begin(), ::toupper);

        std::cout << amount << " " << fromCurrency << " = " << exchanged << " " << toCurrency << '\n';

        std::cout << "Press any key to exchange other currencies or ESC to exit...\n";
        key = _getch();
    }while (key != ESC);
    
    std::cout << "Pressed 'Esc' : Program exited";
}
