#pragma once
#include <string>
enum OrderBookType {ask,bid,sale};
class OrderBookEntry {
    public:
    OrderBookEntry(
        double _price,
        double _amount,
        std::string _timeStamp,
        std::string _product,
        OrderBookType _orderType);
    double price;
    double amount;
    std::string timeStamp;
    std::string product;
    OrderBookType orderType;
    //sorting functions
    static bool compareTimeStamp(OrderBookEntry& e1, OrderBookEntry& e2);
    static bool sortPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);
    static bool sortPriceDsc(OrderBookEntry& e1, OrderBookEntry& e2);
};
