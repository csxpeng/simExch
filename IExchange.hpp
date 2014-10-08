#ifndef _EXCHANGE_HPP_
#define _EXCHANGE_HPP_

#include <string>
#include <functional>

using namespace std;

namespace Wisconsin { namespace Exchange {

    class IExchange {
    protected:
      function<void (int exchOrderId,
                     int clientOrderId,
                     int errorCode)> onOrderAdded;
      
      function<void (int exchOrderId,
		     int errorCode)> onOrderRemoved;
    
      function<void (const string& stockCode,
		     double bidPrice,
		     long bidVolume,
		     double askPrice,
		     long askVolume)> onBestPriceFeed;
      
      
    public:
      virtual ~IExchange() {}

      virtual void AddOrder(const string& stockCode,
			    bool bidSide,
			    double price,
			    long qty,
			    int clientOrderId) = 0;
      
      virtual void RemoveOrder(int exchOrderId) = 0;

      enum tCallBackErrorCodes {
	eNO_ERROR = 0,
	eINTERNAL_SYSTEM_FAILURE = 1,
	eNONEXISTENT_ORDER = 2,
	eUNKNOWN_STOCK_CODE = 3,
	eINVALID_ORDER_PRICE = 4,
	eINVALID_ORDER_VOLUME = 5,
      };
  };
  
} }

#endif
