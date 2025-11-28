#include <iostream>
#include <iomanip>
#include <random>

void showBalance(double balance);
double depositMoney();
double withdrawMoney(double balance);
double highLowGame(double balance);
double rps(double balance);

int main() {

    std::string name;
    double balance = 1000.0;

    std::cout << "******* Welcome to the Casino *******" << '\n';
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Hello " << name << "! Your starting balance is $" << std::fixed << std::setprecision(2) << balance << '\n';
    int choice;
    do {
        if(balance <= 0) {
            std::cout << "You are out of money :(. Please deposit more before playing again." << '\n';
            std::cout << "Enter 1 to deposit more money: ";
            int in;
            std::cin >> in;
            while(in != 1) {
                std::cout << "Please Enter 1 to deposit more money: ";
                std::cin >> in;
            }
            balance += depositMoney();
            showBalance(balance);
        }
        std::cout << "***** Casino Menu ***** \n";
        std::cout << "Enter your choice..." << '\n';
        std::cout << "1. Check your balance" << '\n';
        std::cout << "2. Deposit Money" << '\n';
        std::cout << "3. Withdraw Money" << '\n';
        std::cout << "4. Play High-Low" << '\n';
        std::cout << "5. Play Rock-Paper-Scissors" << '\n';
        std::cout << "6. Exit the game" << '\n';
        std::cin >> choice;
        switch(choice) {
            case 1:
                showBalance(balance);
                break;
            case 2:
                balance += depositMoney();
                showBalance(balance);
                break;
            case 3: 
                balance -= withdrawMoney(balance);
                showBalance(balance);
                break;
            case 4:
                balance = highLowGame(balance);
                showBalance(balance);
                break;
            case 5:
                balance = rps(balance);
                showBalance(balance);
                break;
            case 6:
                std::cout << "Thank you for playing at the Casino. We are always happy to take your money :)\n";
                break;
            default:
                std::cout << "Please enter a valid choice!\n";
        }
    } while(choice != 6);

    std::cout << "You left with $" << balance << ".\n";
    std::cout << "*************************************" << '\n';
}

void showBalance(double balance) {
    std::cout << "\nYour current balance is: $" << balance << '\n';
}

double depositMoney() {
    double amount;
    std::cout << "Please enter the amount you would like to deposit: ";
    std::cin >> amount;

    if(amount < 0) {
        while(amount < 0) {
            std::cout << "Please enter a valid amount: ";
            std::cin >> amount;
        }
        
    }
    return amount;
}

double withdrawMoney(double balance) {
    double amount;
    std::cout << "Please enter the amount you would like to withdraw: ";
    std::cin >> amount;

    while(amount < 0 || amount > balance) {
        std::cout << "Please enter a valid amount(between 0 and your current balance: "<< balance << " ): ";
        std::cin >> amount;
    }
        
    return amount;
}

double highLowGame(double balance) {
    std::cout << "Welcome to the High-Low game!!\n";
    char cont = 'Y';
    while(cont == 'Y') {
        double betAmount;
        std::cout << "Please enter your bet amount: ";
        std::cin >> betAmount;

        while (betAmount <= 0 || betAmount > balance) {
            std::cout << "Please enter a valid bet amount(more than 0 and less than your balance: " << balance << ")";
            std::cin >> betAmount;
        }

        balance -= betAmount;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100);
        int num = dist(gen);

        char guess;
        std::cout << "I have picked a random number between 1 and 100. ";
        std::cout << "You must now guess which half of the set it resides in: High(51-100) as H or Low(1-50) as L" << '\n';
        std::cin >> guess;

        while(guess != 'H' && guess != 'h' && guess != 'L' && guess != 'l') {
            std::cout << "Please enter a valid guess H(high) or L(low): ";
            std::cin >> guess;
        }

        guess = (guess == 'H' || guess == 'h')  ? 'h' : 'l';

        bool correct = (guess == 'h' && num >= 51) || (guess == 'l' && num < 51) ? true : false;
        std::cout << "The random number was: " << num << " and lies in " << (num >= 51 ? "high" : "low") << " half." << '\n';
        std::cout << "Your guess of " << ((guess == 'h') ? "high" : "low") << " was " << (correct ? "correct! You win!\n" : "incorrect. You lose.\n");

        balance += correct ? 2 * betAmount : 0;
        if(balance <= 0) return balance;
        showBalance(balance);
  

        std::cout << "Would you like to play again? Y/N: ";
        std::cin >> cont;
        while(cont != 'Y' && cont != 'N') {
            std::cout << "Please enter Y or N for yes or no. \n";
            std::cin >> cont;
        }

    }
    std::cout << "Thank you for playing!\n";

    return balance;
}

double rps(double balance) {
    char cont = 'Y';
    std::cout << "Welcome to Rock-Paper-Scissors!!\n";
    while(cont == 'Y') {
        double betAmount;
        std::cout << "Please enter your bet amount: ";
        std::cin >> betAmount;
        while(betAmount <= 0 || betAmount > balance) {
            std::cout << "Please enter a valid bet amount(between 0 and your balance of " << balance << "): ";
            std::cin >> betAmount;
        }

        balance -= betAmount;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 3);
        int num = dist(gen);

        char compChoice;
        switch(num) {
            case 1:
                compChoice = 'R';
                break;
            case 2:
                compChoice = 'P';
                break;
            default:
                compChoice = 'S';
        }
        char choice;
        std::cout << "Please enter your choice of Rock(R), Paper(P), or Scissors(S): ";
        std::cin >> choice;

        while(choice != 'R' && choice != 'P' && choice != 'S') {
            std::cout << "Please enter your choice of Rock(R), Paper(P), or Scissors(S)[Make sure you are capitalizing!]: ";
            std::cin >> choice;
        }

        std::string res;
        if(compChoice == 'R') {
            if(choice == 'R') {
                res ="tied";
            } else if (choice == 'P'){
                res = "won";
            } else {
                res = "lost";
            }
        } else if (compChoice == 'P'){
            if(choice == 'P') {
                res ="tied";
            } else if (choice == 'S'){
                res = "won";
            } else {
                res = "lost";
            }
        } else {
            if(choice == 'S') {
                res ="tied";
            } else if (choice == 'R'){
                res = "won";
            } else {
                res = "lost";
            }
        }

        std::cout << "I chose " << compChoice << ". You chose " << choice << ".\n";
        if(res == "tied") {
            std::cout << "We tied!! Your bet has been returned!\n";
            balance += betAmount;
            showBalance(balance);
        } else if (res == "won") {
            std::cout << "You won!!\n";
            balance += betAmount * 2;
        } else {
            std::cout << "You lost. :(\n";
        }
        
        if(balance <= 0) return balance;
        showBalance(balance);
        char ans;
        std::cout << "Would you like to play again? Y/N: ";
        std::cin >> ans;

        while(ans != 'Y' && ans != 'N') {
            std::cout << "Would you like to play again? Y/N(Please enter valid input): ";
            std::cin >> ans;
        }

        cont = ans;

    }

    std::cout << "Thank you for playing Rock-Paper-Scissors";

    return balance;
}