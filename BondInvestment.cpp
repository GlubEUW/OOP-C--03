#include "InvestmentSimulator.h"
#include <cmath>
#include <sstream>

BondInvestment::BondInvestment(double rate, int years, double inflation, bool isCallable,
                               double callableAdj, double riskWeight, double inflationAdj)
    : InvestmentStrategy("Bond", 0.2), interestRate(rate), termYears(years),
      inflationRate(inflation), callable(isCallable),
      callableAdjustment(callableAdj), baseRiskWeight(riskWeight), inflationAdjustment(inflationAdj)
{
    if (rate < 0.0)
        throw InvestmentException("Interest rate cannot be negative");
    if (years <= 0)
        throw InvestmentException("Term years must be positive");
    if (inflation < 0.0)
        throw InvestmentException("Inflation rate cannot be negative");
    if (callableAdj <= 0.0 || callableAdj > 1.0)
        throw InvestmentException("Callable adjustment must be in (0, 1]");
    if (riskWeight < 0.0)
        throw InvestmentException("Base risk weight cannot be negative");
    if (inflationAdj <= 0.0)
        throw InvestmentException("Inflation adjustment must be positive");
}

double BondInvestment::invest(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");

    double effectiveRate = interestRate;
    if (callable)
        effectiveRate *= callableAdjustment;

    if (effectiveRate > inflationRate)
        effectiveRate -= inflationRate * inflationAdjustment;

    return amount * std::pow(1.0 + effectiveRate, termYears);
}

double BondInvestment::calculatePotentialReturn(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");

    double effectiveRate = interestRate;
    if (callable)
        effectiveRate *= callableAdjustment;

    if (effectiveRate > inflationRate)
        effectiveRate -= inflationRate * inflationAdjustment;

    return amount * effectiveRate * termYears;
}

double BondInvestment::calculateRisk() const {
    return baseRiskWeight * riskRating + (callable ? 0.1 : 0.0) + inflationRate * inflationAdjustment;
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

double BondInvestment::getCallableAdjustment() const {
    return callableAdjustment;
}

void BondInvestment::setCallableAdjustment(double adj) {
    if (adj > 0.0 && adj <= 1.0)
        callableAdjustment = adj;
    else
        throw InvestmentException("Callable adjustment must be in (0, 1]");
}

double BondInvestment::getBaseRiskWeight() const {
    return baseRiskWeight;
}

void BondInvestment::setBaseRiskWeight(double weight) {
    if (weight >= 0.0)
        baseRiskWeight = weight;
    else
        throw InvestmentException("Base risk weight cannot be negative");
}

double BondInvestment::getInflationAdjustment() const {
    return inflationAdjustment;
}

void BondInvestment::setInflationAdjustment(double adj) {
    if (adj > 0.0)
        inflationAdjustment = adj;
    else
        throw InvestmentException("Inflation adjustment must be positive");
}

std::string BondInvestment::getInvestmentDetails(double amount) const {
    std::stringstream ss;
    ss << InvestmentStrategy::getInvestmentDetails(amount)
       << " with " << interestRate * 100 << "% nominal interest over "
       << termYears << " years, Inflation Rate: " << inflationRate * 100
       << "%, Callable: " << (callable ? "Yes" : "No")
       << ", Callable Adjustment: " << callableAdjustment
       << ", Base Risk Weight: " << baseRiskWeight
       << ", Inflation Adjustment: " << inflationAdjustment;
    return ss.str();
}
