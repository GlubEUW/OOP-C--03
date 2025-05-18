#ifndef INVESTMENT_SIMULATOR_H
#define INVESTMENT_SIMULATOR_H

#include <string>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <sstream>

class InvestmentException : public std::runtime_error {
public:
    explicit InvestmentException(const std::string& message);
};

class InvestmentStrategy;
class StockInvestment;
class BondInvestment;
class Bank;


class InvestmentStrategy {
protected:
    std::string strategyName;
    double riskRating;
public:
    InvestmentStrategy(const std::string& name, double risk);
    virtual ~InvestmentStrategy();
    
    virtual double invest(double amount) const;
    virtual double calculatePotentialReturn(double amount) const;
    virtual double calculateRisk() const;
    
    virtual std::string getStrategyName() const;
    virtual double getRiskRating() const;
    virtual void setRiskRating(double risk);
    virtual std::string getInvestmentDetails(double amount) const;
};

class StockInvestment : public InvestmentStrategy {
private:
    double expectedReturn;
    double volatilityFactor;
    double dividendYield;
public:
    StockInvestment(double risk = 0.5, double returnRate = 0.12, double volatility = 0.2, double divYield = 0.03);
    double invest(double amount) const override;
    double calculatePotentialReturn(double amount) const override;
    double calculateRisk() const override;
    double getExpectedReturn() const;
    void setExpectedReturn(double returnRate);
    double getVolatilityFactor() const;
    void setVolatilityFactor(double volatility);
    double getDividendYield() const;
    void setDividendYield(double divYield);
};

class BondInvestment : public InvestmentStrategy {
private:
    double interestRate;
    int termYears;
    double inflationRate;
    bool callable;

    // Internal configuration variables
    double callableAdjustment;
    double baseRiskWeight;
    double inflationAdjustment;

public:
    BondInvestment(double rate = 0.05, int years = 5, double inflation = 0.02, bool isCallable = false,
                   double callableAdj = 0.9, double riskWeight = 0.8, double inflationAdj = 1.0);

    double invest(double amount) const override;
    double calculatePotentialReturn(double amount) const override;
    double calculateRisk() const override;

    double getInterestRate() const;
    void setInterestRate(double rate);
    int getTermYears() const;
    void setTermYears(int years);
    double getInflationRate() const;
    void setInflationRate(double inflation);
    bool isCallable() const;
    void setCallable(bool isCallable);

    // Getters and setters for new variables
    double getCallableAdjustment() const;
    void setCallableAdjustment(double adj);
    double getBaseRiskWeight() const;
    void setBaseRiskWeight(double weight);
    double getInflationAdjustment() const;
    void setInflationAdjustment(double adj);

    std::string getInvestmentDetails(double amount) const override;
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
    
    std::string getDetails() const;
};


#endif // INVESTMENT_SIMULATOR_H
