#include "Order.hpp"

Wisconsin::Exchange::Order::Order(int exchOrderId, double price, long qty): 
  mExchOrderId(exchOrderId), mPrice(price), mQty(qty) {
}

Wisconsin::Exchange::Order::Order(const Order& order) {
  mExchOrderId = order.mExchOrderId;
  mPrice = order.mPrice;
  mQty = order.mQty;
}


int Wisconsin::Exchange::Order::getId() const {
  return mExchOrderId;
}

double Wisconsin::Exchange::Order::getPrice() const {
  return mPrice;
}

long Wisconsin::Exchange::Order::getQty() const {
  return mQty;
}
