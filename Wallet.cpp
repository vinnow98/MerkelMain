#include "Wallet.h"
#include "iostream"
#include "CSVReader.h"

Wallet::Wallet(){

};

/** Inserts currency into the wallet */
void Wallet::insertCurrency(std::string type, double amount){
    double balance;
    if (amount<0){
        throw std::exception{};
    }
    if(mapOfWallet.count(type)==0){
        balance = 0 ;
    }else{
        balance = mapOfWallet[type];
    }
    balance+= amount;
    mapOfWallet[type]= balance;
};

 bool Wallet::removeCurrency(std::string type, double amount){
    if(containsCurrency(type,amount)){
        mapOfWallet[type]-=amount;
        return true;
    }else{
        std::cout<<"Not enough "<<type<<"!"<<std::endl;
        return false;
    }
 };
/** Checks if the wallet contains this much currency or more */
bool Wallet::containsCurrency(std::string type, double amount){
    if(mapOfWallet.count(type)==0){
        return false;
    }else{
        return mapOfWallet[type]>=amount;
    }
};

//Ask: I will sell
//ETH/BTC,0.01,0.5 translate to I have 0.5 ETH, I want to sell them at 0.01 BTC each
//Bid: I will buy 
//ETH/BTC,0.01,0.5 translate to I want to buy 0.5 ETH at 0.01 BTC
bool Wallet::canFufillOrder(const OrderBookEntry order){
    std::vector<std::string> tokenizedCurrency = CSVReader ::tokenise(order.product,'/');
    if(order.orderType == ask){
        double amount = order.amount;
        std::string product = tokenizedCurrency[0];
        return containsCurrency(product,amount);
    }else if(order.orderType == bid){
        double amount = order.amount*order.price;
        std::string product = tokenizedCurrency[1];
        return containsCurrency(product,amount);
    }
    return false;
};
/**Prints out what is in the wallet */
std::string Wallet::printWallet(){
    std::string s;
    for(std::pair<std::string,double> pair:mapOfWallet){
        std::string currency = pair.first;
        double amount = pair.second;
        s+= currency + " : " + std::to_string(amount)+ "\n";
    }
    return s;
};