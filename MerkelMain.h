#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain{
    public:
    MerkelMain();
    /** Call this to start the sim */
    void init();

    private:
    void printMenu();
    void printMarketStats();
    void enterAsk();
    void printWallet();
    void goToNextTimeFrame();

    // double computeAveragePrice(std::vector<OrderBookEntry>& entries);
    // double computeLowestPrice(std::vector<OrderBookEntry>& entries);
    // double computeHighestPrice(std::vector<OrderBookEntry>& entries);
    // double computeSpread(std::vector<OrderBookEntry>& entries);
    // void compute();
    int userOption=0;
    std::string currentTime;
    
    OrderBook orderBook;
    Wallet wallet;
};