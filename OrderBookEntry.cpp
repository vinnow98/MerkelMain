#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
        double _price,
        double _amount,
        std::string _timeStamp,
        std::string _product,
        OrderBookType _orderType)
:price(_price),
amount(_amount),
timeStamp(_timeStamp),
product(_product),
orderType(_orderType)
{};

//Sorting functions
bool OrderBookEntry::compareTimeStamp(OrderBookEntry& e1,OrderBookEntry& e2){
    return e1.timeStamp<e2.timeStamp;
};

bool OrderBookEntry::sortPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2){
    return e1.price<e2.price;
};
bool OrderBookEntry::sortPriceDsc(OrderBookEntry& e1, OrderBookEntry& e2){
    return e1.price>e2.price;
};