// CurlTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define CURL_STATICLIB
#include <iostream>
#include "curl/curl.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

int main()
{
    CURL* curl;
    CURLcode response;
    std::string result;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://practiceapii.herokuapp.com/login.php");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        response = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (response != CURLE_OK) {
            std::cerr << "Request Failed: " << curl_easy_strerror(response) << std::endl;
        }
        else {
            std::cout << result << std::endl;
        }
    }
    return 0;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return (size * nmemb);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
