#include "InvestmentSimulator.h"

InvestmentException::InvestmentException(const std::string& message)
    : std::runtime_error(message) {}
