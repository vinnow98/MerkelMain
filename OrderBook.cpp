#include "OrderBook.h"
#include "CSVReader.h"
#include "string"
#include "map"

/** reads a csv file */
OrderBook::OrderBook(std::string filename){
    orders = CSVReader::readCSV(filename);
};
/**return vector of all known products in the dataset */
std::vector<std::string> OrderBook::getKnownProducts(){
    std::vector<std::string> products;
    std::map<std::string,bool> productMap;
    for (OrderBookEntry& e:orders){
        productMap[e.product] = true;
    }

    //flatten the map into a vector of strings
    for(auto const& e :productMap){
        products.push_back(e.first);
        
    }
    return products;
};
/**return vector of Orders according to the sent filters */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,std::string product, std::string timestamp){
    std::vector<OrderBookEntry> order_sub;
    for (OrderBookEntry e: orders){
        if(e.orderType== type&& e.product == product&&e.timeStamp==timestamp){
            order_sub.push_back(e);
        }
    }
    return order_sub;
};

double OrderBook::getLowestOrder (std::vector<OrderBookEntry> orders){
    double min = orders[0].price;
    for(OrderBookEntry e : orders){
        if (min> e.price) min = e.price;
    }
    return min;
};

double OrderBook::getHighestOrder (std::vector<OrderBookEntry> orders){
    double max = orders[0].price;
    for(OrderBookEntry e : orders){
        if (max< e.price) max = e.price;
    }
    return max;
};

std::string OrderBook::getEarliestTime(){
    if (orders.empty()){
        std::cerr<<"No orders available"<<std::endl;
        return "";
    }
    return orders[0].timeStamp;
};

std::string OrderBook::getNextTime(std::string currentTime) {
    std::string nextTimeStamp = "";

    // Find the next time step after currentTime
    for (OrderBookEntry& e : orders) {
        if (e.timeStamp > currentTime) {
            nextTimeStamp = e.timeStamp;
            break;
        }
    }

    // If no next time step is found, wrap around to the start
    if (nextTimeStamp == "") {
        nextTimeStamp = orders.empty() ? "" : orders[0].timeStamp;
    }

    return nextTimeStamp;
}
void OrderBook::insertOrder(OrderBookEntry& order){
    orders.push_back(order);
    std::sort(orders.begin(),orders.end(),OrderBookEntry::compareTimeStamp);
};

std::vector<OrderBookEntry> OrderBook::matchAsktoBids(std::string product,std::string timestamp){
    askEntries = OrderBook::getOrders(OrderBookType::ask,product,timestamp);
    bidEntries = OrderBook::getOrders(OrderBookType::bid,product,timestamp);

    std::vector<OrderBookEntry> sales ;
    
    std::sort(askEntries.begin(),askEntries.end(),OrderBookEntry::sortPriceAsc);
    std::sort(bidEntries.begin(),bidEntries.end(),OrderBookEntry::sortPriceDsc);

    for(OrderBookEntry& ask :askEntries){
        for(OrderBookEntry& bid : bidEntries){
            if (bid.price>= ask.price){
                //we have a match!
                OrderBookEntry sale{ask.price,0,timestamp,product,OrderBookType::sale};

                if(bid.amount==ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }

                if (bid.amount>ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount-ask.amount;
                    break;
                }
                if (bid.amount< ask.amount){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount=ask.amount-bid.amount;
                    bid.amount=0;
                    continue;
                }
            }
        }
    }
    return sales;
};