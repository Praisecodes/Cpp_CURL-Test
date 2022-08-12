#define CURL_STATICLIB
#include <iostream>
#include "curl/curl.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

int main()
{
    CURL* curl;
    CURLcode response;
    std::string result;
    std::string fields = "{\"username\": \"raisecodes\", \"password\": \"Praise\"}";

    struct curl_slist *hs = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://practiceapii.herokuapp.com/login.php");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        hs = curl_slist_append(hs, "Content-Type: application/json");
        hs = curl_slist_append(hs, "Cache-Control: no-cache");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        response = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (response != CURLE_OK) {
            std::cerr << "Request Failed: " << curl_easy_strerror(response) << std::endl;
        }
        else {
            std::cout << result << fields << std::endl;
        }
    }
    return 0;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return (size * nmemb);
}

