# Currency Converter

A simple command-line currency converter application built in C++ that converts between different currencies using exchange rates stored in a JSON file.

## About This Project

This project was created as a refresher to:
- Relearn and practice C++ syntax
- Work with JSON parsing in C++ using the nlohmann/json library
- Experiment with keyboard input detection using `_getch()` and `_kbhit()`

## Features

- Convert between multiple currencies
- View all available currency exchange rates from EUR
- Input validation for currencies and amounts
- Case-insensitive currency input
- Exit at any time by pressing ESC
- Display exchange rates with 2 decimal precision

## Prerequisites

- C++20 compatible compiler (Visual Studio 2022 or later)
- [nlohmann/json](https://github.com/nlohmann/json) library (`json.hpp`)
- Windows OS (uses `<conio.h>` for keyboard input)

## Required Files

### currencies.json

Create a `currencies.json` file in the same directory as the executable with the following format:

```json
{
  "USD": 1.1,
  "GBP": 0.9,
  "EUR": 1.0
}
```

The values represent exchange rates relative to EUR. Adjust the rates as needed.

## How to Use

1. **Run the program**
2. **Press 's'** to view all currency exchange rates from EUR, or **any other key** to skip
3. **Press ESC** at any time to exit the program
4. **Enter the currency you have** (e.g., USD, EUR, GBP) - case insensitive
5. **Enter the currency you want** to convert to
6. **Enter the amount** to convert
7. **View the conversion result**
8. **Press any key** to perform another conversion, or **press ESC** to exit

## Compilation

### Visual Studio 2022

Open the solution file and build the project with C++20 standard enabled.

### Command Line

Ensure you have `json.hpp` in your include path, then compile with C++20:

## Platform Note

This application uses `<conio.h>` which is Windows-specific. For cross-platform compatibility, alternative input handling would be needed.

## Dependencies

- **nlohmann/json**: Modern C++ JSON library for parsing and manipulating JSON data
