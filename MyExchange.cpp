#include "MyExchange.hpp"

int Wisconsin::Exchange::MyExchange::mNextId = 0;

Wisconsin::Exchange::MyExchange::MyExchange() {
  vector<string> symbols;
  symbols.push_back("BHP");
  symbols.push_back("RIO");
  symbols.push_back("ANZ");

  for(vector<string>::const_iterator it = symbols.begin();
      it != symbols.end(); it++) {
    OrderBook* book = new OrderBook(*it);
    
    mOrderBooks.insert(pair<string, OrderBook*>(*it, book));
    mSupportedStockCodes.push_back(*it);
  }
}

Wisconsin::Exchange::MyExchange::MyExchange(vector<string>& symbols) {
  for(vector<string>::const_iterator it = symbols.begin();
      it != symbols.end(); it++) {
    OrderBook* book = new OrderBook(*it);
    
    mOrderBooks.insert(pair<string, OrderBook*>(*it, book));
    mSupportedStockCodes.push_back(*it);
  } 
}


Wisconsin::Exchange::MyExchange::~MyExchange() {
  for(OrderBooks::const_iterator it = mOrderBooks.begin();
      it != mOrderBooks.end(); it++) {
    delete it->second;
  }
}


void Wisconsin::Exchange::MyExchange::AddOrder(const string& stockCode,
					   bool bidSide,
					   double price,
					   long qty,
					   int clientOrderId) {
  int exchOrderId = getNextId();
  
  if(find(mSupportedStockCodes.begin(), mSupportedStockCodes.end(),
	  stockCode) == mSupportedStockCodes.end()) {
    
    if(onOrderAdded) {
      onOrderAdded(exchOrderId, clientOrderId, 
		   Wisconsin::Exchange::IExchange::eUNKNOWN_STOCK_CODE);
    }
    
    return;
  }
  
  if(price <= 0) {
    if(onOrderAdded) {
      onOrderAdded(exchOrderId, clientOrderId, 
		   Wisconsin::Exchange::IExchange::eINVALID_ORDER_PRICE);
    }
    return;
  }
  
  if(qty <= 0) {
    if(onOrderAdded) {
      onOrderAdded(exchOrderId, clientOrderId, 
		   Wisconsin::Exchange::IExchange::eINVALID_ORDER_VOLUME);
    }
    return;
  }
  
  mExchOrderIdToStockCode[exchOrderId] = stockCode;
  
  OrderBooks::iterator it = mOrderBooks.find(stockCode);
  if(it != mOrderBooks.end()) {
    OrderBook* book = it->second;
    bool ret = book->addOrder(bidSide, price, qty, clientOrderId, exchOrderId);
    
    if(ret && onBestPriceFeed) {
      onBestPriceFeed(stockCode, book->getTopBidPrice(),
		      book->getTopBidVolume(), book->getTopAskPrice(),
		      book->getTopAskVolume());
    }
  } else {
    /** 
	this should not happen; 
	can make this better by self defined exception 
    **/
    throw "no matched order book";
  }

  if(onOrderAdded) {
    onOrderAdded(exchOrderId, clientOrderId, 
		 Wisconsin::Exchange::IExchange::eNO_ERROR);
  }
}


void Wisconsin::Exchange::MyExchange::RemoveOrder(int exchOrderId) {
  map<int, string>::iterator it = mExchOrderIdToStockCode.find(exchOrderId);
  if(it != mExchOrderIdToStockCode.end()) {
    OrderBooks::iterator bit = mOrderBooks.find(it->second);
    if(bit != mOrderBooks.end()) {
      OrderBook* book = bit->second;
      bool ret = book->removeOrder(exchOrderId);
      string stockCode = it->second;
      mExchOrderIdToStockCode.erase(exchOrderId);
      
      if(ret && onBestPriceFeed) {
	onBestPriceFeed(stockCode, book->getTopBidPrice(),
			book->getTopBidVolume(), book->getTopAskPrice(),
			book->getTopAskVolume());
      }
    }

    if(onOrderRemoved) {
      onOrderRemoved(exchOrderId, Wisconsin::Exchange::IExchange::eNO_ERROR);
    }
  } else {
    if(onOrderRemoved) {
      onOrderRemoved(exchOrderId, Wisconsin::Exchange::IExchange::eNONEXISTENT_ORDER);
    }
  }
}


void Wisconsin::Exchange::MyExchange::registerOnBestPriceFeed(function<void (const string& stockCode,
									 double bidPrice,
									 long bidVolume,
									 double askPrice,
									 long askVolume)> _onBestPriceFeed) {
  onBestPriceFeed = _onBestPriceFeed;
}

void Wisconsin::Exchange::MyExchange::unregisterOnBestPriceFeed() {
  onBestPriceFeed = NULL;
}

void Wisconsin::Exchange::MyExchange::registerOnOrderAdded(function<void (int exchOrderId,
								      int clientOrderId,
								      int errorCode)> _onOrderAdded) {
  onOrderAdded = _onOrderAdded;
}

void Wisconsin::Exchange::MyExchange::unregisterOnOrderAdded() {
  onOrderAdded = NULL;
}

void Wisconsin::Exchange::MyExchange::registerOnOrderRemoved(function<void (int exchOrderId,
									int errorCode)> _onOrderRemoved) {
  onOrderRemoved = _onOrderRemoved;
}

void Wisconsin::Exchange::MyExchange::unregisterOnOrderRemoved() {
  onOrderRemoved = NULL;
}
