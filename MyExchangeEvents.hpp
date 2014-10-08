#ifndef _MYEXCHANGEEVENTS_HPP_
#define _MYEXCHANGEEVENTS_HPP_

#include <string>
#include <iostream>

#include "IExchange.hpp"

using namespace std;

namespace Wisconsin { namespace Exchange {
    
    class MyExchangeEvents {
    public:
      
      void orderAddedCallback(int exchOrderId,
			      int clientOrderId,
			      int errorCode);
      
      void orderRemovedCallback(int exchOrderId,
				int errorCode);
      
      void bestPriceFeedCallback(const string& stockCode,
				 double bidPrice,
				 long bidVolume,
				 double askPrice,
				 long askVolume);
    };
    
  } }

#endif

