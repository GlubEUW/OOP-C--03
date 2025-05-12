CC = g++
CFLAGS = -Wall -Wextra -std=c++11
COMMON_SOURCES = InvestmentException.cpp InvestmentStrategy.cpp StockInvestment.cpp BondInvestment.cpp Bank.cpp

demo: demo.cpp $(COMMON_SOURCES) InvestmentSimulator.h
	$(CC) $(CFLAGS) -o demo.exe demo.cpp $(COMMON_SOURCES)

test: test.cpp $(COMMON_SOURCES) InvestmentSimulator.h
	$(CC) $(CFLAGS) -o test.exe test.cpp $(COMMON_SOURCES)

all: demo test

clean:
	del /F /Q demo.exe test.exe

.PHONY: all demo test clean
