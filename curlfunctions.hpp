#ifndef CURLFUNCTIONS_HPP_
#define CURLFUNCTIONS_HPP_

#include <string>
#include <jsoncpp/json/json.h>
#include <curl/curl.h>

std::string get_price(const std::string &ticker_symbol, const std::string &api); 
Json::Value get_stock_quote(const std::string &ticker_symbol, const std::string &api); 

#endif
