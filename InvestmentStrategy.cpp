#include "InvestmentSimulator.h"

InvestmentStrategy::InvestmentStrategy(const std::string& name, double risk)
    : strategyName(name), riskRating(risk) {}

InvestmentStrategy::~InvestmentStrategy() {}

std::string InvestmentStrategy::getStrategyName() const {
    return strategyName;
}

double InvestmentStrategy::getRiskRating() const {
    return riskRating;
}

void InvestmentStrategy::setRiskRating(double risk) {
    if (risk >= 0.0 && risk <= 1.0)
        riskRating = risk;
    else
        throw InvestmentException("Risk rating must be between 0.0 and 1.0");
}

std::string InvestmentStrategy::getInvestmentDetails(double amount) const {
    std::stringstream ss;
    ss << "Investing $" << amount << " using " << strategyName
       << " strategy (Risk rating: " << riskRating << ")";
    return ss.str();
}
