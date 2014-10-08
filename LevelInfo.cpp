#include "LevelInfo.hpp"

void Wisconsin::Exchange::LevelInfo::addOrder(int exchOrderId, 
					  double price, long qty) {
  Order* order = new Order(exchOrderId, price, qty);
  mOrders.push_back(pair<int, Order*>(exchOrderId, order));
}

void Wisconsin::Exchange::LevelInfo::removeOrder(int exchOrderId) {
  OrderQueue::iterator it = find_if(mOrders.begin(),
				    mOrders.end(), FindOrder(exchOrderId));
  if(it != mOrders.end()) {
    delete it->second;
    mOrders.erase(it);
  } else {
    /**
     ** this should not happend;
     ** can make better by creating an exception class
    **/
    throw "order not found";
  }
}

long Wisconsin::Exchange::LevelInfo::getVolume() const {
  long volume = 0;
  for(OrderQueue::const_iterator it = mOrders.begin();
      it != mOrders.end(); it++) {
    volume += it->second->getQty();
  }

  return volume;
}
