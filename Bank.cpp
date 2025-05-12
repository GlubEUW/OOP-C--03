#include "InvestmentSimulator.h"

Bank::Bank(const std::string& bankName, double initialFunds)
    : name(bankName), availableFunds(initialFunds) {
    if (initialFunds < 0.0)
        throw InvestmentException("Initial funds cannot be negative");
}

void Bank::setStrategy(std::shared_ptr<InvestmentStrategy> newStrategy) {
    if (!newStrategy)
        throw InvestmentException("Strategy cannot be null");
    strategy = newStrategy;
}

double Bank::executeInvestment(double amount) {
    if (!strategy)
        throw InvestmentException("No investment strategy set");
    if (amount > availableFunds)
        throw InvestmentException("Insufficient funds for investment");
    availableFunds -= amount;
    return strategy->invest(amount);
}

std::string Bank::getCurrentStrategyName() const {
    if (!strategy)
        return "No strategy set";
    return strategy->getStrategyName();
}

std::string Bank::getName() const {
    return name;
}

void Bank::setName(const std::string& bankName) {
    name = bankName;
}

double Bank::getAvailableFunds() const {
    return availableFunds;
}

void Bank::depositFunds(double amount) {
    if (amount <= 0)
        throw InvestmentException("Deposit amount must be positive");
    availableFunds += amount;
}

bool Bank::withdrawFunds(double amount) {
    if (amount <= 0)
        throw InvestmentException("Withdrawal amount must be positive");
    if (amount > availableFunds)
        return false;
    availableFunds -= amount;
    return true;
}

std::string Bank::getDetails() const {
    std::stringstream ss;
    ss << "Bank: " << name << "\n"
       << "Available Funds: $" << availableFunds << "\n"
       << "Current Strategy: " << getCurrentStrategyName();
    return ss.str();
}
