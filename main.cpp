#include "curlfunctions.hpp"
#include "otherfunctions.hpp"
#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <thread>
#include <chrono>

int main()
{
	std::string ticker;// ticker is company_ticker_symbol like for APPLE ticker symbol is APLE, for SAMSUMG ticker symbol is SAM 
	std::cout<<"\n\n----------------------------------------------------------------------*--------------------------------------------------------------*----------------------------------------------------";
	std::cout<<"\n Enter ticker symbol of the company: ";
	std::cin>>ticker; 
	bool flag=false;

	while(true)  //in this while loop, we will read "config.json" file. This is predefined file which contains user API key. This API key will help us to access the stock info from twelvedata website. 
	{
		if(flag==true)
		{
	 		std::string new_ticker;// ticker is company_ticker_symbol like for APPLE ticker symbol is APLE, for SAMSUMG ticker symbol is SAM 
			std::cout<<"\n Enter ticker symbol of the company: ";
			std::cin>>new_ticker; 
			ticker=new_ticker; 
		}		

		Json::Value config; //we declare variable of json::value type
		std::ifstream config_file("config.json", std::ifstream::binary); // we create an ifstream variable namely config_file. Now we will 
								       // 1) convert the "config.json" file to binary and
								       // 2) store the binary config.json file content to config_file variable

		if(!config_file.is_open()) //if the file is not opened, throw error
		{
			std::cerr<<" Failed to open config.json file"<<"\n"; 
			return 1; 
		}

		config_file >> config; // transfer line by line the contents of config_file to config variable
		config_file.close();   // close config_file variable
	


		std::string api_key= config["api_key"].asString(); //from the Json::Value variable we extract the "api_key" and then convert it to c++ string and store it in std::string variable api_key
	
		std::string name, exchange, currency, ans; //name is company_name and ans is user response
		float open, high, low, close, change, price, volume; //ope is stock_opening_price, high is stock highest_price, low is stock_lowest_price, change is stock_change, price is stock_current_price, volume is stock_volume 
		int amount; //amount is stock amount 


		price= std::stof(get_price(ticker, api_key)); //called getprice() function to retrieve the current price of the stock. Also the return type is converted to float type
	
		Json::Value stock_data= get_stock_quote(ticker, api_key); //call get_stock_quote() function to retrieve all stock info
		if(!stock_data.empty())
		{
			name = stock_data["name"].asString(); //from stock_data json variable, extract company_name and convert it to string and store it in company_name variable
			exchange = stock_data["exchange"].asString();
            		currency = stock_data["currency"].asString();
            		open = stof(stock_data["open"].asString());
            		high = stof(stock_data["high"].asString());
            		low = stof(stock_data["low"].asString());
            		close = stof(stock_data["close"].asString());
            		volume = stof(stock_data["volume"].asString());
            		change = stof(stock_data["change"].asString());

		}else 
		{
			std::cerr<<"\n Error in fetching info"<<"\n"; 
			return 1; 
		}



		//call the three functions for printing stock info, profit loss and printing complete stock portfolio info
		print_data(name, exchange, currency, open, close, high, low, volume, change, price); 
		ProfitLoss(open, price, name); 
		Sendsignal(price, high, low, ans, amount); 

		std::cout<<"\n\n---------------------------------------------*---------------------------------------------------------------*---------------------------------------------------------------------";
		std::string user_response; 
		std::cout<<"\n\n"<<" Do you want to     => EXIT      => CONTINUE WITH SAME STOCK       => SEARCH DIFFERENT STOCK"<<"\n";                 
		std::cout<<" select from 3 options(exit/same/diff): ";  
		std::cin>>user_response; 

		std::transform(user_response.begin(), user_response.end(), user_response.begin(), ::toupper); 
		
		if(user_response=="EXIT") break; 
		else if(user_response=="SAME") { flag=false; continue;  }
		else if(user_response=="DIFF") { flag=true; continue; }
		else { std::cout<<" INVALID RESPONSE!!!"<<"\n"; break; }
	}
	return 0; 
}
