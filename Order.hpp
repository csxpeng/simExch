#ifndef _ORDER_HPP_
#define _ORDER_HPP_

/**
 ** Dec 12, 2012
 ** Sean Peng
 **
 **/
namespace Wisconsin { namespace Exchange {

    class Order {
    private:
      int mExchOrderId;
      double mPrice;
      long mQty;

    public:
      Order(int exchOrderId, double price, long qty);

      Order(const Order& order);

      int getId() const;

      double getPrice() const;

      long getQty() const;
    };

  } }

#endif
