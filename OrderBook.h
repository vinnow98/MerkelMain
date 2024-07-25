#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "string"

class OrderBook
{
private:
    std::vector<OrderBookEntry> orders;
public:
    std::vector<OrderBookEntry> bidEntries;
    std::vector<OrderBookEntry> askEntries;

    OrderBook(std::string filename);
    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry> getOrders(
        OrderBookType type,
        std::string product, 
        std::string timestamp);
    static double getLowestOrder (std::vector<OrderBookEntry>);
     static double getHighestOrder (std::vector<OrderBookEntry>);
     /**Gets earliest time stamp */
     std::string getEarliestTime();
     /** Gets next time stamp.When it reaches the end, it loops back to the earliest time stamp. */
     std::string getNextTime(std::string currentTime);
     void insertOrder(OrderBookEntry& order);
    
     std::vector<OrderBookEntry> matchAsktoBids(std::string product,std::string timestamp);

};

