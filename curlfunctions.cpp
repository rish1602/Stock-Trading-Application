#include "curlfunctions.hpp"
#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <curl/curl.h>



size_t WriteCallback(void* received_string, size_t size_each_element, size_t num_elements, std::string* final_string)
{
        size_t final_received_size= size_each_element * num_elements;
        final_string->append(static_cast<char*>(received_string), final_received_size);
        return final_received_size;
}




//getprice() function is used to retrieve the current price of the stock using the stock ticker symbol and TWELVE DATA API
std::string get_price(const std::string& ticker_symbol, const std::string &api) //parameters- stock ticker symbol and TWELVW DATA API
{
	//initialize the curl session
	CURL *curl= curl_easy_init(); //the curl session is initialized using curl_easy_init() function. it will make web requests to TWELVE DATA API to fetch stock price. 
	if(!curl)
	{
		std::cerr<<" Failed to initialize cURL"<<"\n";
		return ""; 
	}		
	
	


	//string named 'url' is created for TWELVE DATA API. this is just a URL that might look like this "https://api.twelvedata.com/price?symbol=AAPL&apikey=your_api_key"
	std::string url= "https://api.twelvedata.com/price?symbol=" + ticker_symbol + "&apikey=" + api;
	
	//using cURL's predefined function curl_easy_setopt(), we will send the http request to TWELVE DATA API. 
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //parameters: curl is the pointer to the curl session. 
							  //CURLOPT_URL specifies that URL is there to send the request. 
							  //url.c_str() converts string url to C-style string and this is the URL to which the request is sent

	
	//using cURL's predefined function curl_easy_setopt(), specifies that we will call WriteCallback() to handle the response from the URL website 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //again we use predefined function curl_easy_setopt. The parameters are-
								      //curl specifies a curl session
								      //CURLOPT_WRITEFUNCTION specifies a writeback function that handles the response that we get from URL
								      //This specifies that we have made a function WriteCallback(). We have made WriteCallback.hpp function
	

	//now we will make a string. the data from URL is collected by WriteCallback(). We will pass this string jsonResponse to this WriteCallback() that will store the result in this string 
	std::string jsonResponse; 									
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse); //here we specify that when we are calling WriteCallback(), its last parameter is address of string jsonResponse
								 //CURLOPT_WRITEDATA specifies that there is a parameter for the WriteCallback() function


	//perform HTTP request
	CURLcode code= curl_easy_perform(curl); //we send the curl session pointer, which we specified above, and make HTTP request. Code will store the HTTP response
	if(code!= CURLE_OK)
	{
		std::cerr<<" HTTP response failed"<<"\n"; 
		return ""; 
	}


	//cleanup curl session and release the resources
	curl_easy_cleanup(curl);  //this is predefined function to cleanup the surl session and any held resources. We are sending the curl session pointer as its parameter


	//we use the library jsoncpp to understand the data in json format
	//parse the json data using jsoncpp
	Json::CharReaderBuilder builder;
    	Json::CharReader* reader = builder.newCharReader();
    	Json::Value root;
	std::string errors;
    	if (!reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errors)) 
	{
		std::cerr<<" Failed to parse JSON"<<"\n";
		delete reader; 
		return ""; 
    	}

	delete reader; 

	// Check if "price" key exists in JSON response
    	if (!root.isMember("price")) 
	{
        	std::cerr<<" Price not found in response"<<"\n";
        	return "";
    	}

	//extract and return stock price as string
	std::string price= root["price"].asString();
	return price;

}






//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




//this program is used to fetch detailed stock info. Using cURL we send HTTP request to twelvedata API and we get json response. We will then parse the json response


Json::Value get_stock_quote(const std::string &ticker_symbol, const std::string &api) //this function takes the stock ticker value and api and returns json::value
{
	//create curl session
	CURL *curl= curl_easy_init(); 
	if(!curl)
	{
		std::cerr<<" Failed to initialize cURL"<<"\n"; 
		return Json::Value(); 
		//return Json::Value(); //this is call jsoncpp library constructor. Since no argument is given to the constructor so this returns empty value
	}


	//string named 'url' is created for TWELVE DATA API. this is just a URL that might look like this "https://api.twelvedata.com/price?symbol=AAPL&apikey=your_api_key"
	std::string url="https://api.twelvedata.com/quote?symbol=" + ticker_symbol + "&apikey=" + api; 
	
	//using cURL's predefined function curl_easy_setopt(), we will send the http request to TWELVE DATA API.	
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //parameters: curl is the pointer to the curl session. 
							  //CURLOPT_URL specifies that URL is there to send the request.
							  //url.c_str() converts string url to C-style string and this is the URL to which the request is sent


	//using cURL's predefined function curl_easy_setopt(), specifies that we will call WriteCallback() to handle the response from the URL website 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //again we use predefined function curl_easy_setopt. The parameters are-
                                                                      //curl specifies a curl session
                                                                      //CURLOPT_WRITEFUNCTION specifies a writeback function that handles the response that we get from URL
                                                                      //This specifies that we have made a function WriteCallback(). We have made WriteCallback.hpp function
	

	std::string jsonResponse; //string to store json response from the website
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse); // Set data pointer for response
	
	//perform http request
	CURLcode code= curl_easy_perform(curl); //using the predefined function curl_easy_perform, send the http request
	if(code!= CURLE_OK) //if http request failed, return empty object
	{
		std::cerr<<" http request failed"<<"\n"; 
		curl_easy_cleanup(curl); //if http request failed so cleanup the curl session
		return Json::Value();
	}


	//after the http request complete, cleanup the cURL resources using predefined function curl_easy_cleanup
	curl_easy_cleanup(curl); 




	// Parse the JSON data using JsonCpp
    	Json::CharReaderBuilder builder;
    	Json::CharReader* reader = builder.newCharReader();
    	Json::Value root;
    	std::string errors;
    
	if (!reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errors)) 
	{
		std::cerr<<" Failed to parse JSON: "<<errors<<"\n";
        	delete reader;
        	return Json::Value(); // Return an empty JSON value on error
    	}
    	
	delete reader;

    	return root; //return json value

	
}
