#define BOOST_TEST_MODULE MyExchange test

#include "boost/test/included/unit_test.hpp"
#include "../MyExchange.hpp"

#include <tuple>
#include <vector>

using namespace std;

namespace Wisconsin { namespace Exchange { namespace Test {

      class ExchangeFixtures {
      public:
        MyExchange mExchange;
	vector<tuple<int, int, int> > mOrderAddedEvents;
	vector<tuple<int, int> > mOrderRemovedEvents;
	vector<tuple<string, double, long, double, long> > mBestPriceFeedEvents;

	ExchangeFixtures() {
	  using placeholders::_1;
	  using placeholders::_2;
	  using placeholders::_3;
          using placeholders::_4;
          using placeholders::_5;
	  
	  mExchange.registerOnOrderAdded(bind(&ExchangeFixtures::OrderAddedHandler,
					      this, _1, _2, _3));
	  mExchange.registerOnOrderRemoved(bind(&ExchangeFixtures::OrderRemovedHandler,
						this, _1, _2));
	  mExchange.registerOnBestPriceFeed(bind(&ExchangeFixtures::BestPriceFeedHandler,
						 this, _1, _2, _3, _4, _5));
	}
	
	void OrderAddedHandler(int exchOrderId, int clientOrderId, int errorCode) {
	  mOrderAddedEvents.push_back(make_tuple(exchOrderId, clientOrderId, errorCode));
	}
	
	void OrderRemovedHandler(int exchOrderId, int errorCode) {
	  mOrderRemovedEvents.push_back(make_tuple(exchOrderId, errorCode));
	}
	
	void BestPriceFeedHandler(string stock, double bidPrice, long bidVol,
				  double askPrice, long askVol) {
	  mBestPriceFeedEvents.push_back(make_tuple(stock, bidPrice, bidVol,
					      askPrice, askVol));
	}
      };
      
    } } }
