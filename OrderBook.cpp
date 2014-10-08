#include "OrderBook.hpp"

Wisconsin::Exchange::OrderBook::OrderBook(string stockCode): mStockCode(stockCode) {
}


bool Wisconsin::Exchange::OrderBook::addOrder(bool bidSide, double price, long qty,
					  int clientOrderId, int exchOrderId) {
  
  bool topUpdated = false;
  long topQty = 0;
  double topPrice = 0.0;

  if(bidSide) {
    if(!mBidQueue.empty()) {
      topQty = mBidQueue.begin()->second.getVolume();
      topPrice = mBidQueue.begin()->first;
    }
    
    mBidQueue[price].addOrder(exchOrderId, price, qty);
    mExchOrderIdToSidePrice[exchOrderId] = pair<bool, double>(bidSide, price);
    if(mBidQueue.begin()->second.getVolume() != topQty
       || mBidQueue.begin()->first != topPrice) {
      topUpdated = true;
    }
  } else {
    if(!mAskQueue.empty()) {
      topQty = mAskQueue.begin()->second.getVolume();
      topPrice = mAskQueue.begin()->first;
    }

    mAskQueue[price].addOrder(exchOrderId, price, qty);
    mExchOrderIdToSidePrice[exchOrderId] = pair<bool, double>(bidSide, price);
    if(mAskQueue.begin()->second.getVolume() != topQty
       || mAskQueue.begin()->first != topPrice) {
      topUpdated = true;
    }
  }

  return topUpdated;
}

bool Wisconsin::Exchange::OrderBook::removeOrder(int exchOrderId) {
  int topUpdated = false;
  IdToPair::iterator it = mExchOrderIdToSidePrice.find(exchOrderId);
  if(it != mExchOrderIdToSidePrice.end()) {
    bool bidSide = it->second.first;
    double price = it->second.second;

    long topQty = 0;
    double topPrice = 0.0;
    if(bidSide) {
      if(!mBidQueue.empty()) {
	topQty = mBidQueue.begin()->second.getVolume();
	topPrice = mBidQueue.begin()->first;
      }

      BidQueue::iterator qit = mBidQueue.find(price);
      if(qit != mBidQueue.end()) {
	qit->second.removeOrder(exchOrderId);
	if(qit->second.getVolume() <= 0) {
	  mBidQueue.erase(qit);
	}

	if(mBidQueue.empty() || (mBidQueue.begin()->first != topPrice
				 || mBidQueue.begin()->second.getVolume() != topQty)) {
	  topUpdated = true;
	}
      }
    } else {
      if(!mAskQueue.empty()) {
	topQty = mAskQueue.begin()->second.getVolume();
	topPrice = mAskQueue.begin()->first;
      }

      AskQueue::iterator qit = mAskQueue.find(price);
      if(qit != mAskQueue.end()) {
	qit->second.removeOrder(exchOrderId);
	if(qit->second.getVolume() <= 0) {
	  mAskQueue.erase(qit);
	}

	if(mAskQueue.empty() || (mAskQueue.begin()->first != topPrice
				 || mAskQueue.begin()->second.getVolume() != topQty)) {
	  topUpdated = true;
	}
      }
    }

    mExchOrderIdToSidePrice.erase(it);
  } else {
    /**
     ** this should not happen
     **/
    throw "order not found";
  }
  
  return topUpdated;
}

string Wisconsin::Exchange::OrderBook::getStockCode() const {
  return mStockCode;
}

double Wisconsin::Exchange::OrderBook::getTopBidPrice() const {
  if(!mBidQueue.empty()) {
    return mBidQueue.begin()->first;
  }

  return 0.0;
}

long Wisconsin::Exchange::OrderBook::getTopBidVolume() const {
  if(!mBidQueue.empty()) {
    return mBidQueue.begin()->second.getVolume();
  }

  return 0;
}

double Wisconsin::Exchange::OrderBook::getTopAskPrice() const {
  if(!mAskQueue.empty()) {
    return mAskQueue.begin()->first;
  }

  return 0.0;
}

long Wisconsin::Exchange::OrderBook::getTopAskVolume() const {
  if(!mAskQueue.empty()) {
    return mAskQueue.begin()->second.getVolume();
  }

  return 0;
}
