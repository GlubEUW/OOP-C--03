#ifndef INVESTMENT_SIMULATOR_H
#define INVESTMENT_SIMULATOR_H

#include <string>
#include <memory>
#include <iostream>
#include <cmath>

class InvestmentStrategy;
class StockInvestment;
class BondInvestment;
class Bank;

class InvestmentStrategy {
public:
    virtual ~InvestmentStrategy() = default;
    virtual double invest(double amount) const = 0;
    virtual std::string getStrategyName() const = 0;
};

class StockInvestment : public InvestmentStrategy {
private:
    double riskFactor;
    double expectedReturn;

public:
    StockInvestment(double risk = 0.5, double returnRate = 0.12);
    double invest(double amount) const override;
    std::string getStrategyName() const override;
    double getRiskFactor() const;
    void setRiskFactor(double risk);
    double getExpectedReturn() const;
    void setExpectedReturn(double returnRate);
};

class BondInvestment : public InvestmentStrategy {
private:
    double interestRate;
    int termYears;

public:
    BondInvestment(double rate = 0.05, int years = 5);
    double invest(double amount) const override;
    std::string getStrategyName() const override;
    double getInterestRate() const;
    void setInterestRate(double rate);
    int getTermYears() const;
    void setTermYears(int years);
};

class Bank {
private:
    std::shared_ptr<InvestmentStrategy> strategy;
    std::string name;
    double availableFunds;

public:
    Bank(const std::string& bankName, double initialFunds = 0.0);
    void setStrategy(std::shared_ptr<InvestmentStrategy> newStrategy);
    double executeInvestment(double amount);
    std::string getCurrentStrategyName() const;
    std::string getName() const;
    void setName(const std::string& bankName);
    double getAvailableFunds() const;
    void depositFunds(double amount);
    bool withdrawFunds(double amount);
};

#endif