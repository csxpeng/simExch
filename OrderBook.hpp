#ifndef _ORDERBOOK_HPP_
#define _ORDERBOOK_HPP_

#include <string>
#include <map>
#include <utility>

#include "LevelInfo.hpp"

using namespace std;

namespace Wisconsin { namespace Exchange {
    
    class BidOrdering {
    public:
      bool operator()(const double lhs, const double rhs) const {
	return lhs > rhs;
      }
    };
    
    
    class OrderBook {
    private:
      typedef map<double, LevelInfo, BidOrdering> BidQueue;
      typedef map<double, LevelInfo> AskQueue;
      typedef map<int, pair<bool, double> > IdToPair;
      
      string mStockCode;
      BidQueue mBidQueue;
      AskQueue mAskQueue;
      IdToPair mExchOrderIdToSidePrice;
      
    public:
      OrderBook(string stockCode);
      
      bool addOrder(bool bidSide, double price, long qty, 
		    int clientOrderId, int exchOrderId);
      
      bool removeOrder(int exchOrderId);

      string getStockCode() const;

      double getTopBidPrice() const;

      long getTopBidVolume() const;

      double getTopAskPrice() const;

      long getTopAskVolume() const;

    };
    
  } }

#endif
