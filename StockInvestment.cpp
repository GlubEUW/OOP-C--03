#include "InvestmentSimulator.h"

StockInvestment::StockInvestment(double risk, double returnRate)
    : InvestmentStrategy("Stock", risk), expectedReturn(returnRate) {
    if (returnRate < 0.0)
        throw InvestmentException("Expected return cannot be negative");
}

double StockInvestment::invest(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");
    return amount * (1.0 + expectedReturn * (1.0 + calculateRisk()));
}

double StockInvestment::calculatePotentialReturn(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");
    return amount * expectedReturn;
}

double StockInvestment::calculateRisk() const {
    return getRiskRating() * 1.5;
}

double StockInvestment::getExpectedReturn() const {
    return expectedReturn;
}

void StockInvestment::setExpectedReturn(double returnRate) {
    if (returnRate >= 0.0)
        expectedReturn = returnRate;
    else
        throw InvestmentException("Expected return cannot be negative");
}
