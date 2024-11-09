#include "otherfunctions.hpp"
#include <iostream>
#include <string>
#include <algorithm> //for using transform(::toupper)


//this function calculates the profit and loss generated from the opening and closing price of the stock
void ProfitLoss(float open, float close, std::string name)   //open is stock_opening_price, close is stock_closing_price, name is company_name or stock_name
{
	float percentage_change= ((close - open) / open) * 100;   //simple percentage is calculated
	
	if(percentage_change >0) std::cout<<" "<<name<<" stock profit is "<<percentage_change<<"\n";
	else if(percentage_change<0) std::cout<<" "<<name<<" stock loss is "<<percentage_change<<"\n";
	else std::cout<<" "<<name<<" stock is in neutral state with "<<percentage_change<<"\n";

}



//this function asks if the user wants to buy/sell the stock. If "yes", then we ask the amount of stocks to buy/sell and for that amount, we calculate the total stock price.
void wantTransact(std::string ans, int amount, float price) //ans is user's response, amount is stock amount user enters and price is stock current price 
{
	std::cout<<"\n Enter the stock amount for buying/selling: "<<"\n";
	std::cin>>amount;
	std::cout<<"\n Enter YES/NO response if you want to know the total stock price for hat amount: "<<"\n";
	std::cin>>ans; 

	std::transform(ans.begin(), ans.end(), ans.begin(), ::toupper); 
	if(ans=="YES") std::cout<<"\n"<<price*amount<<"\n";
	else if(ans=="NO") std::cout<<"\n"<<"OK....no worries"<<"\n";
	else std::cout<<"\n INVALID RESPONSE....buddy!! \n"; 

}

 

//this function print_data prints various info about the stock like the company name, stock price, stock high price, stock low price etc etc....
void print_data(std::string name, std::string exchange, std::string currency, float open, float close, float high, float low, float volume, float change, float price) 
{
	//name is company_name
	//open is stoc_opening_price
	//close is stock_closing_price
	//high is stock_highest_price
	//low is stock_lowest_price
	//volume is stock_volume
	//change is stock_change
	//price is stock_current_price
	
	std::cout<<"\n\n-----------------------------------------*---------------------------------------------*---------------------------------------------------------*---------------------------------------------------";
	std::cout<<"\n\n\n"<<" Generating....."<<"\n";
	std::cout<<" NAME: "<<name<<"\n"<<
		   " EXCHANGE: "<<exchange<<"\n"<<
		   " CURRENCY: "<<currency<<"\n"<<
		   " CURRENT STOCK PRICE: "<<price<<"\n"<<
		   " OPEN PRICE: "<<open<<"\n"<<
		   " CLOSING PRICE: "<<close<<"\n"<<
		   " HIGH PRICE: "<<high<<"\n"<<
		   " LOW PRICE: "<<low<<"\n"<<
		   " VOLUME: "<<volume<<"\n"<<
		   " CHANGE: "<<change<<"\n";
}	





//this function checks if the current stock price is less than stock low threshold price, then calls wantTransact() asking user if they want to  buy more of that stocks. 
//if the current stock price is more than stock high threshold price, then calls wantTransact() asking user if they want to sell that stocks.
void Sendsignal(float price, float high, float low, std::string ans, int amount)
{
	if(price < low) //if current stock price < low threshold stock price so ask for more stock buying
	{
		std::cout<<"\n Sending BUYING signals....\n";
		wantTransact(ans, amount, price); 
	}
	else if(price > high) // if current stock price more than high stock price, ask user for stock selling
	{
		std::cout<<"\n Sending SELLING signals....\n";
		wantTransact(ans, amount, price); 
	}else
		std::cout<<"\n Not suitable for either buying or selling. HAPPY TRADING !!!!!!"<<"\n"; 
}










