#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include "InvestmentSimulator.h"  // Assumes CryptoInvestment is declared here

std::ofstream testFile;

void reportTest(const std::string &testName, bool condition) {
    if (condition) {
        testFile << testName << " PASSED\n";
    } else {
        testFile << testName << " FAILED\n";
        assert(condition);
    }
}

int main() {
    testFile.open("test.txt");
    if (!testFile.is_open()) {
        std::cerr << "Failed to open test.txt for writing" << std::endl;
        return 1;
    }

    double amount = 1000.0;

    // --- StockInvestment Tests ---
    try {
        auto stock = std::make_shared<StockInvestment>(0.5, 0.15, 0.2, 0.03);
        double investResult = stock->invest(amount);
        reportTest("StockInvestment invest returns > principal", investResult > amount);

        double potential = stock->calculatePotentialReturn(amount);
        reportTest("StockInvestment calculatePotentialReturn > 0", potential > 0);

        double risk = stock->calculateRisk();
        reportTest("StockInvestment calculateRisk > 0", risk > 0);

        std::string details = stock->getInvestmentDetails(amount);
        reportTest("StockInvestment getInvestmentDetails not empty", !details.empty());

        // Test setters/getters
        stock->setExpectedReturn(0.20);
        reportTest("StockInvestment set/getExpectedReturn", stock->getExpectedReturn() == 0.20);

        stock->setVolatilityFactor(0.25);
        reportTest("StockInvestment set/getVolatilityFactor", stock->getVolatilityFactor() == 0.25);

        stock->setDividendYield(0.04);
        reportTest("StockInvestment set/getDividendYield", stock->getDividendYield() == 0.04);
    } catch (const std::exception &e) {
        testFile << "StockInvestment Tests FAILED: " << e.what() << "\n";
        assert(false);
    }

    // --- BondInvestment Tests ---
    try {
        auto bond = std::make_shared<BondInvestment>(0.05, 5, 0.02, true);
        double investResult = bond->invest(amount);
        reportTest("BondInvestment invest returns > principal", investResult > amount);

        double potential = bond->calculatePotentialReturn(amount);
        reportTest("BondInvestment calculatePotentialReturn > 0", potential > 0);

        double risk = bond->calculateRisk();
        reportTest("BondInvestment calculateRisk > 0", risk > 0);

        std::string details = bond->getInvestmentDetails(amount);
        reportTest("BondInvestment getInvestmentDetails not empty", !details.empty());

        double oldRate = bond->getInterestRate();
        bond->setInterestRate(oldRate + 0.01);
        reportTest("BondInvestment set/getInterestRate", bond->getInterestRate() == oldRate + 0.01);

        int oldTerm = bond->getTermYears();
        bond->setTermYears(oldTerm + 1);
        reportTest("BondInvestment set/getTermYears", bond->getTermYears() == oldTerm + 1);

        double oldInfl = bond->getInflationRate();
        bond->setInflationRate(oldInfl + 0.005);
        reportTest("BondInvestment set/getInflationRate", bond->getInflationRate() == oldInfl + 0.005);

        bool oldCallable = bond->isCallable();
        bond->setCallable(!oldCallable);
        reportTest("BondInvestment set/getCallable", bond->isCallable() != oldCallable);
    } catch (const std::exception &e) {
        testFile << "BondInvestment Tests FAILED: " << e.what() << "\n";
        assert(false);
    }

    // --- CryptoInvestment Tests ---
    try {
        auto crypto = std::make_shared<CryptoInvestment>("Bitcoin", 0.9, 1.0, 1.2);
        double investResult = crypto->invest(amount);
        reportTest("CryptoInvestment invest returns > principal", investResult > amount);

        double potential = crypto->calculatePotentialReturn(amount);
        reportTest("CryptoInvestment calculatePotentialReturn > 0", potential > 0);

        double risk = crypto->calculateRisk();
        reportTest("CryptoInvestment calculateRisk > 0", risk > 0);

        std::string details = crypto->getInvestmentDetails(amount);
        reportTest("CryptoInvestment getInvestmentDetails not empty", !details.empty());

        std::string origName = crypto->getCryptoName();
        crypto->setCryptoName("Ethereum");
        reportTest("CryptoInvestment set/getCryptoName", crypto->getCryptoName() == "Ethereum");

        double oldVol = crypto->getCryptoVolatility();
        crypto->setCryptoVolatility(oldVol + 0.3);
        reportTest("CryptoInvestment set/getCryptoVolatility", crypto->getCryptoVolatility() == oldVol + 0.3);

        double oldHype = crypto->getHypeFactor();
        crypto->setHypeFactor(oldHype + 0.2);
        reportTest("CryptoInvestment set/getHypeFactor", crypto->getHypeFactor() == oldHype + 0.2);
    } catch (const std::exception &e) {
        testFile << "CryptoInvestment Tests FAILED: " << e.what() << "\n";
        assert(false);
    }

    // --- Bank Polymorphism Test ---
    try {
        Bank bank("TestBank", 15000);
        bank.setStrategy(std::make_shared<StockInvestment>(0.5, 0.15, 0.2, 0.03));
        double res1 = bank.executeInvestment(2000);

        bank.setStrategy(std::make_shared<BondInvestment>(0.05, 5, 0.02, false));
        double res2 = bank.executeInvestment(2000);

        bank.setStrategy(std::make_shared<CryptoInvestment>("Bitcoin", 0.9, 1.0, 1.2));
        double res3 = bank.executeInvestment(2000);

        reportTest("Bank Polymorphism executeInvestment > 0", (res1 > 0 && res2 > 0 && res3 > 0));
    } catch (const std::exception &e) {
        testFile << "Bank Polymorphism Test FAILED: " << e.what() << "\n";
        assert(false);
    }

    testFile.close();
    return 0;
}
