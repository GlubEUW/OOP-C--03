#include "InvestmentSimulator.h"

StockInvestment::StockInvestment(double risk, double returnRate, double volatility, double divYield)
    : InvestmentStrategy("Stock", risk), expectedReturn(returnRate), volatilityFactor(volatility), dividendYield(divYield)
{
    if (returnRate < 0.0)
        throw InvestmentException("Expected return cannot be negative");
    if (volatility < 0.0)
        throw InvestmentException("Volatility factor cannot be negative");
    if (divYield < 0.0)
        throw InvestmentException("Dividend yield cannot be negative");
}

double StockInvestment::invest(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");
    double baseGrowth = amount * expectedReturn * (1.0 + calculateRisk());
    double dividendContribution = amount * dividendYield;
    double volatilityAdjustment = amount * volatilityFactor * 0.05;
    return amount + baseGrowth + dividendContribution + volatilityAdjustment;
}

double StockInvestment::calculatePotentialReturn(double amount) const {
    if (amount <= 0)
        throw InvestmentException("Investment amount must be positive");
    return amount * (expectedReturn + dividendYield + volatilityFactor * 0.05);
}

double StockInvestment::calculateRisk() const {
    return riskRating * 1.5 + volatilityFactor;
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

double StockInvestment::getVolatilityFactor() const {
    return volatilityFactor;
}

void StockInvestment::setVolatilityFactor(double volatility) {
    if (volatility >= 0.0)
        volatilityFactor = volatility;
    else
        throw InvestmentException("Volatility factor cannot be negative");
}

double StockInvestment::getDividendYield() const {
    return dividendYield;
}

void StockInvestment::setDividendYield(double divYield) {
    if (divYield >= 0.0)
        dividendYield = divYield;
    else
        throw InvestmentException("Dividend yield cannot be negative");
}
