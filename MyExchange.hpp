#ifndef _MYEXCHANGE_HPP_
#define _MYEXCHANGE_HPP_

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <functional>
#include <algorithm>

#include "IExchange.hpp"
#include "OrderBook.hpp"

using namespace std;

namespace Wisconsin { namespace Exchange {

    class MyExchange: public IExchange {
    private:
      typedef map<string, OrderBook*> OrderBooks;

      OrderBooks mOrderBooks;
      map<int, string> mExchOrderIdToStockCode;
      vector<string> mSupportedStockCodes;

      static int mNextId;

      int getNextId() {
	return mNextId++;
      }

    public:
      MyExchange();

      MyExchange(vector<string>& symbols);

      ~MyExchange();

      void AddOrder(const std::string& stockCode,
		    bool bidSide,
		    double price,
		    long volume,
		    int clientOrderId);

      void RemoveOrder(int exchOrderId);


      void registerOnOrderAdded(function<void (int exchOrderId,
                                               int clientOrderId,
                                               int errorCode)> _onOrderAdded);

      void unregisterOnOrderAdded();
      
      void registerOnOrderRemoved(function<void (int exchOrderId,
						 int errorCode)> _onOrderRemoved);
    
      void unregisterOnOrderRemoved();
    
      void registerOnBestPriceFeed(function<void (const string& stockCode,
						  double bidPrice,
						  long bidVolume,
						  double askPrice,
						  long askVolume)> _onBestPriceFeed);

      void unregisterOnBestPriceFeed();


    };

  } }

#endif
