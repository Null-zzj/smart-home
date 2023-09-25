#include <cstddef>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <memory>
#include <string>
#include "face_recognition.h"
#include "../tools/base64/base64.h"

inline size_t onWriteData(void *buffer, size_t size, size_t nmemb, void *userp)
{
    std::string *str = dynamic_cast<std::string *>((std::string *)userp);
    str->append((char *)buffer, size * nmemb);
    return nmemb;
}

double json_parse(std::string jsonStr)
{
    Json::Value root;
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errors;
    bool parsingSuccessful = reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &root, &errors);
    delete reader;

    if (!parsingSuccessful) {
        std::cerr << "Failed to parse JSON: " << errors << std::endl;
        return 1;
    }

    int errorCode = root["error_code"].asInt();
    if (errorCode == 0) {
        double score = root["result"]["user_list"][0]["score"].asDouble();
        std::cout << "Score: " << score << std::endl;
        return score;
    } else {
        std::cerr << "Error: " << root["error_msg"].asString() << std::endl;
        return -1;
    }
}

double face_recognition(const unsigned char *pic, size_t len)
{
    std::string base64 = base64_encode(pic, len, false);

    std::string result;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    double score;
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL,
                         "https://aip.baidubce.com/rest/2.0/face/v3/"
                         "search?access_token=24.f070273410a38f2184ddb1ad24507cdf.2592000.1697463129.282335-39376742");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string data = "{\"group_id_list\":\"user1\",\"image\":\"" + base64 + "\",\"image_type\":\"BASE64\"}";

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
        res = curl_easy_perform(curl);
        std::cout << result << std::endl;

        score = json_parse(result);
        std::cout << "识别成功：辨识度为"  << score << std::endl;
        printf("printf socre %.10lf\n", score);
    }
    curl_easy_cleanup(curl);

  
    return score * 100;
}
