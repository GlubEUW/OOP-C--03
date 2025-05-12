#include <iostream>
#include <memory>
#include "InvestmentSimulator.h"

int main() {
    try {
        Bank bank("Poly Bank", 15000.0);
        std::cout << "Initial Bank:\n" << bank.getDetails() << "\n\n";

        bank.setStrategy(std::make_shared<InvestmentStrategy>("Base", 0.0));
        std::cout << "Using Base Strategy:\n";
        double baseResult = bank.executeInvestment(2000.0);
        std::cout << "Investment Result: " << baseResult << "\n";
        std::cout << bank.getDetails() << "\n\n";

        bank.setStrategy(std::make_shared<StockInvestment>(0.5, 0.15, 0.3, 0.04));
        std::cout << "Switched to Stock Strategy:\n";
        double stockResult = bank.executeInvestment(2000.0);
        std::cout << "Investment Result: " << stockResult << "\n";
        std::cout << bank.getDetails() << "\n\n";

        bank.setStrategy(std::make_shared<BondInvestment>(0.06, 7, 0.025, true));
        std::cout << "Switched to Bond Strategy:\n";
        double bondResult = bank.executeInvestment(2000.0);
        std::cout << "Investment Result: " << bondResult << "\n";
        std::cout << bank.getDetails() << "\n\n";
    }
    catch(const InvestmentException& ex) {
        std::cerr << "Investment Exception: " << ex.what() << "\n";
    }
    catch(const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }
    return 0;
}
