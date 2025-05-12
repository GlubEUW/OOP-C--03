#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include "InvestmentSimulator.h"  // Assumes StockInvestment, BondInvestment, CryptoInvestment, and Bank are declared here

int main() {
    std::ofstream testFile("test.txt");
    if (!testFile.is_open()) {
        std::cerr << "Failed to open test.txt for writing" << std::endl;
        return 1;
    }

    double amount = 1000.0;

    // StockInvestment Tests
    try {
        auto stock = std::make_shared<StockInvestment>(0.5, 0.15, 0.2, 0.03);

        double investResult = stock->invest(amount);
        assert(investResult > amount);
        testFile << "StockInvestment invest returns > principal PASSED\n";

        double potential = stock->calculatePotentialReturn(amount);
        assert(potential > 0);
        testFile << "StockInvestment calculatePotentialReturn > 0 PASSED\n";

        double risk = stock->calculateRisk();
        assert(risk > 0);
        testFile << "StockInvestment calculateRisk > 0 PASSED\n";

        std::string details = stock->getInvestmentDetails(amount);
        assert(!details.empty());
        testFile << "StockInvestment getInvestmentDetails not empty PASSED\n";

        stock->setExpectedReturn(0.20);
        assert(stock->getExpectedReturn() == 0.20);
        testFile << "StockInvestment set/getExpectedReturn PASSED\n";

        stock->setVolatilityFactor(0.25);
        assert(stock->getVolatilityFactor() == 0.25);
        testFile << "StockInvestment set/getVolatilityFactor PASSED\n";

        stock->setDividendYield(0.04);
        assert(stock->getDividendYield() == 0.04);
        testFile << "StockInvestment set/getDividendYield PASSED\n";
    } catch (const std::exception &e) {
        testFile << "StockInvestment Tests FAILED: " << e.what() << "\n";
        assert(false);
    }

    // BondInvestment Tests
    try {
        auto bond = std::make_shared<BondInvestment>(0.05, 5, 0.02, true);

        double investResult = bond->invest(amount);
        assert(investResult > amount);
        testFile << "BondInvestment invest returns > principal PASSED\n";

        double potential = bond->calculatePotentialReturn(amount);
        assert(potential > 0);
        testFile << "BondInvestment calculatePotentialReturn > 0 PASSED\n";

        double risk = bond->calculateRisk();
        assert(risk > 0);
        testFile << "BondInvestment calculateRisk > 0 PASSED\n";

        std::string details = bond->getInvestmentDetails(amount);
        assert(!details.empty());
        testFile << "BondInvestment getInvestmentDetails not empty PASSED\n";

        double oldRate = bond->getInterestRate();
        bond->setInterestRate(oldRate + 0.01);
        assert(std::abs(bond->getInterestRate() - (oldRate + 0.01)) <= 0.001);

        testFile << "BondInvestment set/getInterestRate PASSED\n";

        int oldTerm = bond->getTermYears();
        bond->setTermYears(oldTerm + 1);
        assert(bond->getTermYears() == oldTerm + 1);
        testFile << "BondInvestment set/getTermYears PASSED\n";

        double oldInfl = bond->getInflationRate();
        bond->setInflationRate(oldInfl + 0.005);
        assert(bond->getInflationRate() - (oldInfl + 0.005) <= 0.001);
        testFile << "BondInvestment set/getInflationRate PASSED\n";

        bool oldCallable = bond->isCallable();
        bond->setCallable(!oldCallable);
        assert(bond->isCallable() != oldCallable);
        testFile << "BondInvestment set/getCallable PASSED\n";
    } catch (const std::exception &e) {
        testFile << "BondInvestment Tests FAILED: " << e.what() << "\n";
        assert(false);
    }

    // CryptoInvestment Tests
    try {
        auto crypto = std::make_shared<CryptoInvestment>("Bitcoin", 0.9, 1.0, 1.2);

        double investResult = crypto->invest(amount);
        assert(investResult > amount);
        testFile << "CryptoInvestment invest returns > principal PASSED\n";

        double potential = crypto->calculatePotentialReturn(amount);
        assert(potential > 0);
        testFile << "CryptoInvestment calculatePotentialReturn > 0 PASSED\n";

        double risk = crypto->calculateRisk();
        assert(risk > 0);
        testFile << "CryptoInvestment calculateRisk > 0 PASSED\n";

        std::string details = crypto->getInvestmentDetails(amount);
        assert(!details.empty());
        testFile << "CryptoInvestment getInvestmentDetails not empty PASSED\n";

        std::string origName = crypto->getCryptoName();
        crypto->setCryptoName("Ethereum");
        assert(crypto->getCryptoName() == "Ethereum");
        testFile << "CryptoInvestment set/getCryptoName PASSED\n";

        double oldVol = crypto->getCryptoVolatility();
        crypto->setCryptoVolatility(oldVol + 0.3);
        assert(crypto->getCryptoVolatility() - (oldVol + 0.3) <= 0.001);
        testFile << "CryptoInvestment set/getCryptoVolatility PASSED\n";

        double oldHype = crypto->getHypeFactor();
        crypto->setHypeFactor(oldHype + 0.2);
        assert(crypto->getHypeFactor() - (oldHype + 0.2) <= 0.001);
        testFile << "CryptoInvestment set/getHypeFactor PASSED\n";
    } catch (const std::exception &e) {
        testFile << "CryptoInvestment Tests FAILED: " << e.what() << "\n";
        assert(false);
    }

    // Bank Polymorphism Test
    try {
        Bank bank("TestBank", 15000);
        bank.setStrategy(std::make_shared<StockInvestment>(0.5, 0.15, 0.2, 0.03));
        double res1 = bank.executeInvestment(2000);

        bank.setStrategy(std::make_shared<BondInvestment>(0.05, 5, 0.02, false));
        double res2 = bank.executeInvestment(2000);

        bank.setStrategy(std::make_shared<CryptoInvestment>("Bitcoin", 0.9, 1.0, 1.2));
        double res3 = bank.executeInvestment(2000);

        assert(res1 > 0 && res2 > 0 && res3 > 0);
        testFile << "Bank Polymorphism executeInvestment > 0 PASSED\n";
    } catch (const std::exception &e) {
        testFile << "Bank Polymorphism Tests FAILED: " << e.what() << "\n";
        assert(false);
    }

    testFile.close();
    return 0;
}
