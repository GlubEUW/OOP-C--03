#include "InvestmentSimulator.h"

BondInvestment::BondInvestment(double rate, int years)
    : InvestmentStrategy("Bond", 0.2), interestRate(rate), termYears(years) {
    if (rate < 0.0)
        throw InvestmentException("Interest rate cannot be negative");
    if (years <= 0)
        throw InvestmentException("Term years must be positive");
}

double BondInvestment::invest(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");
    return amount * std::pow(1.0 + interestRate, termYears);
}

double BondInvestment::calculatePotentialReturn(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");
    return amount * interestRate * termYears;
}

double BondInvestment::calculateRisk() const {
    return getRiskRating() * 0.8;
}

double BondInvestment::getInterestRate() const {
    return interestRate;
}

void BondInvestment::setInterestRate(double rate) {
    if (rate >= 0.0)
        interestRate = rate;
    else
        throw InvestmentException("Interest rate cannot be negative");
}

int BondInvestment::getTermYears() const {
    return termYears;
}

void BondInvestment::setTermYears(int years) {
    if (years > 0)
        termYears = years;
    else
        throw InvestmentException("Term years must be positive");
}

std::string BondInvestment::getInvestmentDetails(double amount) const {
    std::stringstream ss;
    ss << InvestmentStrategy::getInvestmentDetails(amount)
       << " with " << interestRate * 100 << "% interest over " 
       << termYears << " years";
    return ss.str();
}
