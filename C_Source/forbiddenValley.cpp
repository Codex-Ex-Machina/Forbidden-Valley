/*
1. Add ability to work for money and pay off loan over time.
2. Remove ability to deposit money without working for it.
3. Implement a more complex date system that accounts for different month lengths and leap years.
4. Introduce random events that can affect the player's balance (e.g., unexpected expenses)
*/

#include <iostream>
#include <iomanip>
#include <limits>

// Structure to hold the date
struct gameDate {
    int day;
    int month;
    int year;
};

// Function to get date input from user
bool getDate(gameDate &d) {
    std::cout << "Enter the date (MM/DD/YY): ";
    char slash {};

    // Input validation for date format
    if (!(std::cin >> d.month >> slash >> d.day >> slash >> d.year)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    // Basic validation for month and day ranges
    if (d.month < 1 || d.month > 12 || d.day < 1 || d.day > 31) {
        return false;
    }

    return true;
}

// Function to apply interest to the balance
void applyInterest(double &loan, double rate) {
    loan *= (1 + rate);
}

// Function to advance to the next day and apply interest
void nextDay(gameDate &d, double &loan, double rate) {
    d.day++;

    // Simple month/year rollover logic
    if (d.day > 30) {
        d.day = 1;
        d.month++;
    }
    if (d.month > 12) {
        d.month = 1;
        d.year++;
    }

    applyInterest(loan, rate);

    std::cout << "Date: " << d.month << "/" << d.day << "/" << d.year << " | Loan: $" << std::fixed << std::setprecision(2) << loan << "\n";
}

// Function to display the current balance
void showBalance(double balance, double loan, double dailyRate) {
    std::cout << "Your balance is $" << std::fixed << std::setprecision(2) << balance << "\n";
    std::cout << "Loan remaining: $" << std::fixed << std::setprecision(2) << loan << "\n";
    std::cout << "Daily interest rate: " << std::fixed << std::setprecision(2) << (dailyRate * 100) << "%\n";
}

// Function to add money to the balance
double deposit() {
    double amount;
    std::cout << "Enter amount to deposit: ";
    std::cin >> amount;

    if (amount > 0)
        return amount;

    std::cout << "Invalid amount.\n";
    return 0;
}

// Function to choose a loan amount to start with
double chooseLoan() {
    int choice;

    while (true) {
        std::cout << "\nChoose your loan amount:\n";
        std::cout << "1. $1000\n";
        std::cout << "2. $5000\n";
        std::cout << "3. $10000\n";
        std::cout << "Select option: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter 1, 2, or 3.\n";
            continue;
        }

        switch (choice) {
            case 1: return 1000;
            case 2: return 5000;
            case 3: return 10000;
            default:
                std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }
}

void payLoan(double &balance, double &loan){
    if(loan <= 0){
        std::cout << "No loan to pay off.\n";
        return;
    }

    double amount;
    std::cout << "Enter amount to pay towards loan: ";
    std::cin >> amount;

    if(std::cin.fail() || amount <= 0){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid amount.\n";
        return;
    }

    if(amount > balance){
        std::cout << "Insufficient funds to pay loan.\n";
        return;
    }

    if(amount > loan){
        amount = loan;
        std::cout << "You paid off the entire loan of $" << std::fixed << std::setprecision(2) << loan << ".\n";
    }

    balance -= amount;
    loan -= amount;

    std::cout << "Payment successful. Remaining loan: $" << std::fixed << std::setprecision(2) << loan << "\n";
}

int main() {
    // Initial setup
    double balance = {0};
    double dailyRate = {0.01};
    int choice {};
    double loan {0};

    // Get starting date
    gameDate date;

    // Input validation for date
    bool dateEntered = getDate(date);

    // Exit if date is invalid
        if (!dateEntered) {
            std::cout << "Invalid date entered. Exiting.\n";
            return 0;
        }

    // Choose loan amount
    loan += chooseLoan();
    balance += loan;
    showBalance(balance, loan, dailyRate);

    // Advance 5 days to demonstrate interest application
    std::cout << "\nAdvancing 5 days...\n";
    for (int i {0}; i < 5; i++) {
        nextDay(date, loan, dailyRate);
    }

    // Main menu loop
    do {
        std::cout << "\n************* MENU *************\n";
        std::cout << "1. Show balance\n";
        std::cout << "2. Deposit money\n";
        std::cout << "3. Pay loan\n";
        std::cout << "4. Exit\n";
        std::cout << "\n********************************\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Handle menu choices
        switch (choice) {
            case 1:
                showBalance(balance, loan, dailyRate);
                break;

            case 2:
                balance += deposit();
                showBalance(balance, loan, dailyRate);
                break;

            case 3:
                payLoan(balance, loan);
                showBalance(balance, loan, dailyRate);
                break;

            case 4:
                std::cout << "Thanks for visiting!\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
