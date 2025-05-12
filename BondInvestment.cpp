#include "InvestmentSimulator.h"

BondInvestment::BondInvestment(double rate, int years, double inflation, bool isCallable)
    : InvestmentStrategy("Bond", 0.2), interestRate(rate), termYears(years), inflationRate(inflation), callable(isCallable)
{
    if (rate < 0.0)
        throw InvestmentException("Interest rate cannot be negative");
    if (years <= 0)
        throw InvestmentException("Term years must be positive");
    if (inflation < 0.0)
        throw InvestmentException("Inflation rate cannot be negative");
}

double BondInvestment::invest(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");
    double effectiveRate = interestRate;
    if (callable)
        effectiveRate *= 0.9;
    if (effectiveRate > inflationRate)
        effectiveRate -= inflationRate;
    return amount * std::pow(1.0 + effectiveRate, termYears);
}

double BondInvestment::calculatePotentialReturn(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");
    double effectiveRate = interestRate;
    if (callable)
        effectiveRate *= 0.9;
    if (effectiveRate > inflationRate)
        effectiveRate -= inflationRate;
    return amount * effectiveRate * termYears;
}

double BondInvestment::calculateRisk() const {
    return riskRating * 0.8 + (callable ? 0.1 : 0.0) + inflationRate;
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

double BondInvestment::getInflationRate() const {
    return inflationRate;
}

void BondInvestment::setInflationRate(double inflation) {
    if (inflation >= 0.0)
        inflationRate = inflation;
    else
        throw InvestmentException("Inflation rate cannot be negative");
}

bool BondInvestment::isCallable() const {
    return callable;
}

void BondInvestment::setCallable(bool isCallable) {
    callable = isCallable;
}

std::string BondInvestment::getInvestmentDetails(double amount) const {
    std::stringstream ss;
    ss << InvestmentStrategy::getInvestmentDetails(amount)
       << " with " << interestRate * 100 << "% nominal interest over "
       << termYears << " years, Inflation Rate: " << inflationRate * 100
       << "%, Callable: " << (callable ? "Yes" : "No");
    return ss.str();
}
