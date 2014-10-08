#ifndef _LEVELINFO_HPP_
#define _LEVELINFO_HPP_

#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>

#include "Order.hpp"

using namespace std;


namespace Wisconsin { namespace Exchange {

    class FindOrder: public unary_function<pair<int, Order*>, bool> {
    private:
      int mId;

    public:
      FindOrder(int id): mId(id) {
      }

      bool operator()(const pair<int, Order*> obj) const {
	return mId == obj.first;
      }
    };


    class LevelInfo {
    private:
      typedef vector<pair<int, Order*> > OrderQueue; /* orders are queued instead of a map */

      double mPrice;
      OrderQueue mOrders;
      
    public:
      void addOrder(int exchOrderId, double price, long qty);

      void removeOrder(int exchOrderId);
      
      long getVolume() const;
    };
    
  } }

#endif
