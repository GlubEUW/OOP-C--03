#include <iostream>
#include <memory>
#include "InvestmentSimulator.h"

int main() {
    double amount = 1000.0;

    InvestmentStrategy defaultStrategy("Base", 0.0);
    std::cout << "Default Strategy:\n";
    std::cout << defaultStrategy.getInvestmentDetails(amount) << "\n";
    std::cout << "Invest result: " << defaultStrategy.invest(amount) << "\n\n";

    auto stock = std::make_shared<StockInvestment>(0.5, 0.15, 0.2, 0.03);
    std::cout << "Stock Strategy:\n";
    std::cout << stock->getInvestmentDetails(amount) << "\n";
    std::cout << "Invest result: " << stock->invest(amount) << "\n\n";

    auto bond = std::make_shared<BondInvestment>(0.05, 5, 0.02, true);
    std::cout << "Bond Strategy:\n";
    std::cout << bond->getInvestmentDetails(amount) << "\n";
    std::cout << "Invest result: " << bond->invest(amount) << "\n\n";

    return 0;
}
