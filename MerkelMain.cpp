#include <iostream>
#include <vector>
#include "MerkelMain.h"
#include <limits>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain():orderBook("test.csv"){
    
};

void MerkelMain::init(){
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC",10);
    wallet.insertCurrency("USDT",20);
    while (true) {
    printMenu();
     };
};

void MerkelMain:: printMenu(){
        // Print menu options
        std::cout << "1. Print help" << std::endl;
        std::cout << "2. Print exchange stats" << std::endl;
        std::cout << "3. Make an ask" << std::endl;
        std::cout << "4. Make a bid" << std::endl;
        std::cout << "5. Print wallet" << std::endl;
        std::cout << "6. Next time step (continue)" << std::endl;
        std::cout<< "The current time is: "<< currentTime<<std::endl;
        std::cout << "==================" << std::endl;
        std::cout << "Select an option (1-6): ";
        orderBook.getKnownProducts();
        // Get user input
        std::string userInput;
        std::getline(std::cin,userInput);
        try{
            userOption = std::stoi(userInput);
        }catch(const std::exception& e){
            std::cout << "Invalid input. Please enter a number between 1 and 6." << std::endl;
        }

        std::cout << "You chose: Option " << userOption << std::endl;
        if(userOption == 2){
            printMarketStats();
        }else if(userOption == 3){
            enterAsk();
        }else if(userOption == 5){
            printWallet();
        }else if(userOption == 6){
            goToNextTimeFrame();
        };
};


void MerkelMain::printMarketStats() {
    for (const std::string& product : orderBook.getKnownProducts()) {
        std::cout << "Product: " << product << std::endl;
        std::string date = currentTime;

        try {
            orderBook.bidEntries = orderBook.getOrders(OrderBookType::bid, product, date);
            orderBook.askEntries = orderBook.getOrders(OrderBookType::ask, product, date);

            // Check if entries are available
            if (orderBook.bidEntries.empty() || orderBook.askEntries.empty()) {
                std::cout << "No data available for bids or asks for product: " << product << " at time " << date << std::endl;
                continue; // Skip to the next product
            }

            // Display number of entries
            std::cout << "Number of bid entries: " << orderBook.bidEntries.size() << std::endl;
            std::cout << "Number of ask entries: " << orderBook.askEntries.size() << std::endl;

            // Get and display lowest ask and highest bid
            double lowestAsk = OrderBook::getLowestOrder(orderBook.askEntries);
            double highestBid = OrderBook::getHighestOrder(orderBook.bidEntries);
            std::cout << "Lowest Ask Price: " << lowestAsk << std::endl;
            std::cout << "Highest Bid Price: " << highestBid << std::endl;
            std::cout << "Spread: " << (lowestAsk - highestBid) << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Error processing product " << product << ": " << e.what() << std::endl;
            continue; // Skip to the next product if an error occurs
        }
    }
}


void MerkelMain::enterAsk(){
    std::string userAsk;
    std::cout<< "Enter your ask: product,price,amount. E.g: ETH/BTC,200,0.5"<<std::endl;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin,userAsk);

    try{
        std::vector<std::string> tokenizedUserAsk = CSVReader::tokenise(userAsk,',');

        if(tokenizedUserAsk.size()!=3){
            std::cout<< "Bad tokenized input!"<<std::endl;
        }else{
            OrderBookEntry obe = CSVReader::stringstoOBE(tokenizedUserAsk[1],tokenizedUserAsk[2],currentTime,tokenizedUserAsk[0],OrderBookType::ask);
            std::cout<< "You entered: "<< userAsk<< std::endl;
            orderBook.insertOrder(obe);

            if(wallet.canFufillOrder(obe)){
                std::cout<< "Wallet looks good"<<std::endl;
                orderBook.insertOrder(obe);
            }else{
                std::cout<<"Not enough funds!"<<std::endl;
            }
        }
    } catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
};

void MerkelMain::printWallet(){
    std::cout<< wallet.printWallet();
};

void MerkelMain::goToNextTimeFrame(){
    std::vector<OrderBookEntry> sales= orderBook.matchAsktoBids("ETH/BTC",currentTime);
    std::cout<<"sales: "<<sales.size()<<std::endl;
    for(OrderBookEntry& sale: sales){
        std::cout<< "sale price: "<< sale.price<<" Sale amount: "<<sale.amount<<std::endl;
    }
    currentTime = orderBook.getNextTime(currentTime);
}


// double MerkelMain:: computeAveragePrice(std::vector<OrderBookEntry>& entries){
//     double totalSum;
//     for(unsigned int i = 0; i<entries.size();++i){
//         totalSum += entries[i].price;
//     };
//     return totalSum/entries.size();
// };
    
// double MerkelMain:: computeLowestPrice(std::vector<OrderBookEntry>& entries){
//     double lowestPrice = entries[0].price;
//     for(OrderBookEntry& entry:entries){
//         if (entry.price<lowestPrice){
//             lowestPrice = entry.price;
//         };
//     }
//     return lowestPrice;
// };

// double MerkelMain::computeHighestPrice(std::vector<OrderBookEntry>& entries){
//     double highestPrice = entries[0].price;
//     for(OrderBookEntry& entry:entries){
//         if (entry.price>highestPrice){
//             highestPrice = entry.price;
//         };
//     }
//     return highestPrice;
// };

// double MerkelMain::computeSpread(std::vector<OrderBookEntry>& entries){
//     double spread = computeHighestPrice(entries)-computeLowestPrice(entries);
//     return spread;
// };

// void MerkelMain::compute(){
    
//     // std::cout <<MerkelMain::computeAveragePrice(orderBookEntries)<<std::endl;
//     // std::cout <<MerkelMain::computeLowestPrice(orderBookEntries)<<std::endl;
//     // std::cout <<MerkelMain::computeHighestPrice(orderBookEntries)<<std::endl;
//     // std::cout <<MerkelMain::computeSpread(orderBookEntries)<<std::endl;
// };

