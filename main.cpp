#include <iostream>
#include <functional>

#include "boost/algorithm/string.hpp"
#include "boost/any.hpp"

#include "MyHelper.hpp"
#include "MyExchange.hpp"
#include "MyExchangeEvents.hpp"

using namespace std;
using namespace Wisconsin::Exchange;

int main(int argc, char *argv[]) {

  Wisconsin::Exchange::MyExchange myExchange;
  Wisconsin::Exchange::MyExchangeEvents myEvents;
  myExchange.registerOnOrderAdded(bind(&MyExchangeEvents::orderAddedCallback,
				       &myEvents, placeholders::_1,
				       placeholders::_2, placeholders::_3));
  myExchange.registerOnOrderRemoved(bind(&MyExchangeEvents::orderRemovedCallback,
					 &myEvents, placeholders::_1,
					 placeholders::_2));
  myExchange.registerOnBestPriceFeed(bind(&MyExchangeEvents::bestPriceFeedCallback,
					  &myEvents, placeholders::_1,					  
					  placeholders::_2, placeholders::_3,
					  placeholders::_4, placeholders::_5));
  
  string line;
  while(getline(cin, line)) {
    vector<string> elements;
    boost::split(elements, line, boost::is_any_of(" "));
    bool adding = true;
    vector<boost::any> params;

    if(!Helper::inputValid(elements, adding, params)) {
      continue;
    }
    
    if(adding) {
      bool bidSide = boost::any_cast<bool>(params[0]);
      string stock = boost::any_cast<string>(params[1]);
      double price = boost::any_cast<double>(params[2]);
      long qty = boost::any_cast<long>(params[3]);
      int clientId = boost::any_cast<int>(params[4]);
      
      myExchange.AddOrder(stock, bidSide, price, qty, clientId);
    } else {
      int exchOrderId = boost::any_cast<int>(params[0]);
      myExchange.RemoveOrder(exchOrderId);
    }
    
  }
  
  return 0;
}

