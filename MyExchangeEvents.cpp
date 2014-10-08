#include "MyExchangeEvents.hpp"

void Wisconsin::Exchange::MyExchangeEvents::orderAddedCallback(int exchOrderId,
							       int clientOrderId,
							       int errorCode) {
  switch(errorCode) {
  case Wisconsin::Exchange::IExchange::eNO_ERROR:
    cout << "[Added] exch id: " << exchOrderId
	 << "; client id: " << clientOrderId
	 << endl;
    break;

  case Wisconsin::Exchange::IExchange::eINTERNAL_SYSTEM_FAILURE:
    
  case Wisconsin::Exchange::IExchange::eNONEXISTENT_ORDER:
    cout << "[Add failed] Internal error or nonexistent order" 
	 << endl;
    break;

  case Wisconsin::Exchange::IExchange::eUNKNOWN_STOCK_CODE:
    cout << "[Add failed] unknown stock code"
	 << endl;
    break;
    
  case Wisconsin::Exchange::IExchange::eINVALID_ORDER_PRICE:
    cout << "[Add failed] invalid price"
	 << endl;
    break;
    
  case Wisconsin::Exchange::IExchange::eINVALID_ORDER_VOLUME:
    cout << "[Add failed] invalid volume"
	 << endl;
    break;

  default:
    cout << "[Add failed] other unknown reasons"
	 << endl;
    break;    
  }
}


void Wisconsin::Exchange::MyExchangeEvents::orderRemovedCallback(int exchOrderId,
							     int errorCode) {
  switch(errorCode) {
  case Wisconsin::Exchange::IExchange::eNO_ERROR:
    cout << "[Removed] exch id: " << exchOrderId
         << endl;
    break;

  case Wisconsin::Exchange::IExchange::eINTERNAL_SYSTEM_FAILURE:
    cout << "[Remove failed] internal failure"
	 << endl;
    break;

  case Wisconsin::Exchange::IExchange::eNONEXISTENT_ORDER:
    cout << "[Remove failed] nonexistent order"
         << endl;
    break;

  case Wisconsin::Exchange::IExchange::eUNKNOWN_STOCK_CODE:
    cout << "[Remove failed] unknown stock code"
         << endl;
    break;

  case Wisconsin::Exchange::IExchange::eINVALID_ORDER_PRICE:
    cout << "[Remove failed] invalid price"
         << endl;
    break;

  case Wisconsin::Exchange::IExchange::eINVALID_ORDER_VOLUME:
    cout << "[Remove failed] invalid volume"
         << endl;
    break;

  default:
    cout << "[Remove failed] other unknown reasons"
         << endl;
    break;
  }

}

void Wisconsin::Exchange::MyExchangeEvents::bestPriceFeedCallback(const string& stockCode,
							      double bidPrice,
							      long bidVolume,
							      double askPrice,
							      long askVolume) {
  cout << "[Best Price Updated]: " << stockCode
       << "; bid: " << bidPrice
       << "; vol: " << bidVolume
       << "; ask: " << askPrice
       << "; vol: " << askVolume
       << endl;
}
