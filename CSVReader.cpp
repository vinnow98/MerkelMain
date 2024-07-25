#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <fstream>
#include <iostream>


CSVReader ::CSVReader(){

}; 

std::vector<OrderBookEntry> CSVReader ::readCSV(std::string fileName){
    std::string newLine;
    static std::ifstream csvFile{fileName};
    std::vector<OrderBookEntry> orderBook;

    if(!csvFile.is_open()){
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return orderBook;
    };
    while (std::getline(csvFile,newLine)) {
        std::vector<std::string> tokens = tokenise(newLine, ',');
         if (tokens.size() == 5) {
            OrderBookEntry entry = stringstoOBE(tokens);
            orderBook.push_back(entry);
        }else if (newLine == ""){
            continue;
        }else{
            std::cout<<"Tokens are not 5! Problem line: "<<newLine<<std::endl;
        };
    };
    csvFile.close();
    return orderBook;
};

std::vector<std::string> CSVReader ::tokenise(std::string csvLine,char seperator){
    std::vector<std::string> tokens;
    unsigned int start = 0;

    std::string::size_type end = csvLine.find_first_of(seperator,start);

    while(end != std::string::npos){
        std::string token = csvLine.substr(start,end-start);
        tokens.push_back(token);
        start = end+1;
        end = csvLine.find_first_of(seperator,start);
    
    }
    std::string lastToken = csvLine.substr(start);
    tokens.push_back(lastToken);

    return tokens;
};

OrderBookEntry CSVReader::stringstoOBE(std::vector<std::string> tokens){
    double price = std::stod(tokens[3]);
    double amount = std::stod(tokens[4]);
    std::string timeStamp = tokens[0];
    std::string product = tokens[1];
    OrderBookType orderType;

    if (tokens[2] == "ask") {
        orderType = ask;
    } else {
        orderType = bid;
    }
    return OrderBookEntry {price, amount, timeStamp, product, orderType};
};

OrderBookEntry CSVReader::stringstoOBE(std::string _price,std::string _amount,std::string _timeStamp,std::string _product,OrderBookType _orderType){
    double price, amount;
    try{
        price = std::stod(_price);
        amount = std::stod(_amount);
    }catch(const std::exception& e){
        std::cout<< "CSVReader::stringstoOBE Bad Float!"<< price <<std::endl;
        std::cout<< "CSVReader::stringstoOBE Bad Float!"<< amount <<std::endl;
        throw;
    };

return OrderBookEntry{
    price, amount, _timeStamp, _product, _orderType
};
};