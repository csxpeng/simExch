#ifndef _MYHELPER_HPP_
#define _MYHELPER_HPP_

#include <map>
#include <string>
#include <vector>
#include <functional>

#include "boost/algorithm/string.hpp"
#include "boost/any.hpp"

using namespace std;

/**
 ** helper variables, functions etc
 **/
namespace Helper {
  typedef bool (*funcPointer)(vector<string>&, vector<boost::any>&);
  
  bool addOrder(vector<string>& elements, vector<boost::any>& params) {
    if(elements.size() < 5)
      return false;
    
    bool bidSide = true;
    if(elements[0] == "sell")
      bidSide = false;

    string expectCode = elements[1];
    string expectPrice = elements[2];
    string expectQty = elements[3];
    string expectClientId = elements[4];
    params.push_back(bidSide);
    params.push_back(expectCode);
    params.push_back(atof(expectPrice.c_str()));
    params.push_back(atol(expectQty.c_str()));
    params.push_back(atoi(expectClientId.c_str()));
    
    return true;
  }

  bool removeOrder(vector<string>& elements, vector<boost::any>& params) {
    if(elements.size() < 2)
      return false;
    
    string expectId = elements[1];
    params.push_back(atoi(expectId.c_str()));
    
    return true;
  }
  
  map<string, funcPointer> actionMap = {
    {"buy", &addOrder},
    {"sell", &addOrder},
    {"remove", &removeOrder}
  };
  
  bool inputValid(vector<string>& elements, bool& adding, vector<boost::any>& params) {
    if(elements.size() < 2)
      return false;
    
    string action = elements[0];
    if(action.compare("buy")!=0 && action.compare("sell")!=0 && action.compare("remove")!=0)
      return false;
    
    if(action == "remove")
      adding = false;
    
    return actionMap[action](elements, params);
  }
  
}

#endif
