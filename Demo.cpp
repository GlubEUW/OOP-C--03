#include <iostream>
#include <fstream>
#include <memory>
#include "InvestmentSimulator.h"

int main() {
    std::ofstream outFile("demo.txt");
    if (!outFile) {
        std::cerr << "Could not open demo.txt for writing." << std::endl;
        return 1;
    }

    try {
        Bank bank("Demo Bank", 10000.0);
        bank.depositFunds(5000.0);
        outFile << "Initial Bank Details:\n" << bank.getDetails() << "\n\n";

        // Set up and use a StockInvestment strategy.
        std::shared_ptr<InvestmentStrategy> stockStrategy = std::make_shared<StockInvestment>(0.5, 0.10);
        bank.setStrategy(stockStrategy);
        outFile << "Stock Investment Details: " << stockStrategy->getInvestmentDetails(3000.0) << "\n";
        double stockInvestmentAmount = 3000.0;
        double stockResult = bank.executeInvestment(stockInvestmentAmount);
        outFile << "After investing $" << stockInvestmentAmount
                << " in stocks, the investment grew to $" << stockResult << "\n";
        outFile << "Bank Details:\n" << bank.getDetails() << "\n\n";

        
        stockStrategy->setRiskRating(0.7);
        outFile << "Updated Stock Risk Rating to " << stockStrategy->getRiskRating() << "\n";
        double stockPotentialReturn = stockStrategy->calculatePotentialReturn(3000.0);
        outFile << "Potential return on $3000 investment in stocks: $" << stockPotentialReturn << "\n\n";

        // Switch to a BondInvestment strategy.
        std::shared_ptr<InvestmentStrategy> bondStrategy = std::make_shared<BondInvestment>(0.04, 3);
        bank.setStrategy(bondStrategy);
        outFile << "Bond Investment Details: " << bondStrategy->getInvestmentDetails(2000.0) << "\n";
        double bondInvestmentAmount = 2000.0;
        double bondResult = bank.executeInvestment(bondInvestmentAmount);
        outFile << "After investing $" << bondInvestmentAmount
                << " in bonds, the investment grew to $" << bondResult << "\n";
        outFile << "Bank Details:\n" << bank.getDetails() << "\n\n";

        BondInvestment* bondPtr = dynamic_cast<BondInvestment*>(bondStrategy.get());
        if (bondPtr) {
            bondPtr->setTermYears(5);
            bondPtr->setInterestRate(0.045);
            outFile << "Updated Bond Terms: Interest Rate = " << bondPtr->getInterestRate() * 100 
                    << "%, Term = " << bondPtr->getTermYears() << " years\n";
            double bondPotentialReturn = bondPtr->calculatePotentialReturn(2000.0);
            outFile << "New potential return for $2000 in bonds: $" << bondPotentialReturn << "\n\n";
        }

        // Extended multi-year simulation with alternating strategies.
        outFile << "Extended Multi-Year Simulation:\n";
        for (int year = 1; year <= 5; ++year) {
            outFile << "Year " << year << ":\n";
            // Deposit additional funds annually.
            bank.depositFunds(1000.0);
            if (year % 2 == 1) {
                bank.setStrategy(stockStrategy);
                double investAmount = 1500.0;
                double result = bank.executeInvestment(investAmount);
                outFile << "Invested $" << investAmount << " in stocks; result: $" << result << "\n";
                outFile << "Stock Details for investment: " << stockStrategy->getInvestmentDetails(investAmount) << "\n";
            } else {
                bank.setStrategy(bondStrategy);
                double investAmount = 1500.0;
                double result = bank.executeInvestment(investAmount);
                outFile << "Invested $" << investAmount << " in bonds; result: $" << result << "\n";
                outFile << "Bond Details for investment: " << bondStrategy->getInvestmentDetails(investAmount) << "\n";
            }
            outFile << "Bank Details at End of Year " << year << ":\n" << bank.getDetails() << "\n\n";
        }

        if (bank.withdrawFunds(1000.0)) {
            outFile << "Withdrawal of $1000.0 was successful.\n";
        } else {
            outFile << "Withdrawal of $1000.0 failed due to insufficient funds.\n";
        }
        outFile << "Final Bank Details:\n" << bank.getDetails() << "\n\n";
    }
    catch (const InvestmentException& ex) {
        outFile << "Investment error: " << ex.what() << "\n";
    }
    catch (const std::exception& ex) {
        outFile << "Unexpected error: " << ex.what() << "\n";
    }

    outFile.close();
    return 0;
}
