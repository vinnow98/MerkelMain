#pragma once
#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include <iostream>

class CSVReader{
    public:
        CSVReader(); 
        static std::vector<OrderBookEntry> readCSV(std::string fileName);

        static std::vector<std::string> tokenise(std::string csvLine,char seperator);

        static OrderBookEntry stringstoOBE( std::string _price,std::string _amount,std::string _timeStamp,std::string _product,OrderBookType _orderType);
        
    private:
        static OrderBookEntry stringstoOBE(std::vector<std::string> strings);
};