#ifndef OTHERFUNCTIONS_HPP
#define OTHERFUNCTIONS_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <jsoncpp/json/json.h>

void ProfitLoss(float open, float close, std::string name); 
void wantTransact(std::string ans, int amount, float price); 
void print_data(std::string name, std::string exchange, std::string currency, float open, float close, float high, float low, float volume, float change, float price);
void Sendsignal(float price, float high, float low, std::string ans, int amount);

#endif

