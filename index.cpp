#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <map>
#include <vector>
#include "curl/curl.h"

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

int main() {
	CURL* curl;
	CURLcode response;
	std::string result;
	

	std::string details = "{\"username\": \"Praisecodes\", \"password\": \"Praise@042\"}";

	json json_details = json::parse(details);
	curl = curl_easy_init();
	if (curl) {
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "Cache-Control: max-age=0, no-cache");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, "https://practiceapii.herokuapp.com/login.php");
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, json_details.dump().c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

		response = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (response != CURLE_OK) {
			std::cout << "Failed Request: " << curl_easy_strerror(response) << std::endl;
		}
		else {
			json json_result = json::parse(result);

			std::vector<std::string> resultArr;
			resultArr = json_result;
			std::cout << resultArr[0] << std::endl;
		}
	}
	else {
		std::cerr << "Error Initialize cURL\n";
	}

	return 0;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);

	return size * nmemb;
}