#pragma once
#include "string"
#include "map"
#include "OrderBookEntry.h"

class Wallet{
    
    private:
        /** A map of all the currencies in the wallet */
        std::map<std::string,double> mapOfWallet;
    public:
        Wallet();

        /** Inserts currency into the wallet */
        void insertCurrency(std::string type, double amount);

         /** Removes currency from the wallet */
        bool removeCurrency(std::string type, double amount);

        /** Checks if the wallet contains this much currency or more */
        bool containsCurrency(std::string type, double amount);

        bool canFufillOrder(const OrderBookEntry order);

        /**Prints out what is in the wallet */
        std::string printWallet();
};