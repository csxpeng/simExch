#define BOOST_TEST_MODULE MyExchange test

#include "boost/test/included/unit_test.hpp"
#include "../MyExchange.hpp"
#include "ExchangeFixtures.hpp"

#include <tuple>
#include <vector>

using namespace std;

namespace Wisconsin { namespace Exchange { namespace Test {
      
      BOOST_FIXTURE_TEST_SUITE(ExchangeTests, ExchangeFixtures)
      
      BOOST_AUTO_TEST_CASE(TestInvalidStockCode) {
	const int clientOrderId = 1;
	mExchange.AddOrder("XXX", true, 100, 10, clientOrderId);
	
	BOOST_REQUIRE(!mOrderAddedEvents.empty());
	BOOST_CHECK_EQUAL(get<1>(mOrderAddedEvents.front()), clientOrderId);
	BOOST_CHECK_EQUAL(get<2>(mOrderAddedEvents.front()), IExchange::eUNKNOWN_STOCK_CODE);
      }

      BOOST_AUTO_TEST_CASE(TestInvalidPrice) {
	const int clientOrderId = 1;
	mExchange.AddOrder("BHP", true, 0, 10, clientOrderId);

        BOOST_REQUIRE(!mOrderAddedEvents.empty());
        BOOST_CHECK_EQUAL(get<1>(mOrderAddedEvents.front()), clientOrderId);
        BOOST_CHECK_EQUAL(get<2>(mOrderAddedEvents.front()), IExchange::eINVALID_ORDER_PRICE);
      }

      BOOST_AUTO_TEST_CASE(TestInvalidVolume) {
	const int clientOrderId = 1;
        mExchange.AddOrder("BHP", true, 10, 0, clientOrderId);

        BOOST_REQUIRE(!mOrderAddedEvents.empty());
        BOOST_CHECK_EQUAL(get<1>(mOrderAddedEvents.front()), clientOrderId);
        BOOST_CHECK_EQUAL(get<2>(mOrderAddedEvents.front()), IExchange::eINVALID_ORDER_VOLUME);
      }

      BOOST_AUTO_TEST_CASE(TestOrderAdd) {
	const int clientOrderId = 1;
        mExchange.AddOrder("BHP", true, 10, 10, clientOrderId);

        BOOST_REQUIRE(!mOrderAddedEvents.empty());
        BOOST_CHECK_EQUAL(get<1>(mOrderAddedEvents.front()), clientOrderId);
        BOOST_CHECK_EQUAL(get<2>(mOrderAddedEvents.front()), IExchange::eNO_ERROR);
      }

      BOOST_AUTO_TEST_CASE(TestOrderRemove) {
	const int clientOrderId = 1;
        mExchange.AddOrder("BHP", true, 10, 10, clientOrderId);

        BOOST_REQUIRE(!mOrderAddedEvents.empty());
        BOOST_CHECK_EQUAL(get<1>(mOrderAddedEvents.front()), clientOrderId);
        BOOST_CHECK_EQUAL(get<2>(mOrderAddedEvents.front()), IExchange::eNO_ERROR);

	int exchOrderId = get<0>(mOrderAddedEvents.front());
	mExchange.RemoveOrder(exchOrderId);
	BOOST_CHECK_EQUAL(get<0>(mOrderRemovedEvents.front()), exchOrderId);
        BOOST_CHECK_EQUAL(get<1>(mOrderRemovedEvents.front()), IExchange::eNO_ERROR);
      }

      BOOST_AUTO_TEST_CASE(TestRemoveNonExistOrder) {
	const int clientOrderId = 1;
        mExchange.AddOrder("BHP", true, 10, 10, clientOrderId);

        BOOST_REQUIRE(!mOrderAddedEvents.empty());
        BOOST_CHECK_EQUAL(get<1>(mOrderAddedEvents.front()), clientOrderId);
        BOOST_CHECK_EQUAL(get<2>(mOrderAddedEvents.front()), IExchange::eNO_ERROR);

        const int exchOrderId = 999;
        mExchange.RemoveOrder(exchOrderId);
        BOOST_CHECK_EQUAL(get<0>(mOrderRemovedEvents.front()), exchOrderId);
        BOOST_CHECK_EQUAL(get<1>(mOrderRemovedEvents.front()), IExchange::eNONEXISTENT_ORDER);
      }

      BOOST_AUTO_TEST_CASE(TestBestPriceFeed) {
	const int clientOrderId = 1;

        mExchange.AddOrder("BHP", true, 10, 10, clientOrderId);
        BOOST_REQUIRE(!mBestPriceFeedEvents.empty());
        BOOST_CHECK_EQUAL(get<1>(mBestPriceFeedEvents.front()), 10);
        BOOST_CHECK_EQUAL(get<2>(mBestPriceFeedEvents.front()), 10);
	BOOST_CHECK_EQUAL(get<3>(mBestPriceFeedEvents.front()), 0);
        BOOST_CHECK_EQUAL(get<4>(mBestPriceFeedEvents.front()), 0);
	mBestPriceFeedEvents.clear();

	mExchange.AddOrder("BHP", true, 60, 60, clientOrderId);
        BOOST_REQUIRE(!mBestPriceFeedEvents.empty());
        BOOST_CHECK_EQUAL(get<1>(mBestPriceFeedEvents.front()), 60);
        BOOST_CHECK_EQUAL(get<2>(mBestPriceFeedEvents.front()), 60);
        BOOST_CHECK_EQUAL(get<3>(mBestPriceFeedEvents.front()), 0);
        BOOST_CHECK_EQUAL(get<4>(mBestPriceFeedEvents.front()), 0);
	mBestPriceFeedEvents.clear();

	mExchange.AddOrder("BHP", false, 10, 10, clientOrderId);
        BOOST_REQUIRE(!mBestPriceFeedEvents.empty());
        BOOST_CHECK_EQUAL(get<1>(mBestPriceFeedEvents.front()), 60);
        BOOST_CHECK_EQUAL(get<2>(mBestPriceFeedEvents.front()), 60);
        BOOST_CHECK_EQUAL(get<3>(mBestPriceFeedEvents.front()), 10);
        BOOST_CHECK_EQUAL(get<4>(mBestPriceFeedEvents.front()), 10);
      }

      BOOST_AUTO_TEST_SUITE_END()
      
      
    } } }
