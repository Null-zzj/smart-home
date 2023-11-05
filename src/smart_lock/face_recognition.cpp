#include <cstddef>
#include <curl/curl.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../tools/base64/base64.h"
#include "face_recognition.h"
#include <fstream>
#include <memory>
#include <string>

inline size_t onWriteData(void *buffer, size_t size, size_t nmemb, void *userp)
{
    std::string *str = dynamic_cast<std::string *>((std::string *)userp);
    str->append((char *)buffer, size * nmemb);
    return nmemb;
}

int getscore(std::string json)
{
    // 获取score的值

    int start = json.find("score\":");
    if(start == std::string::npos)
    {
        return 0;
    }
    std::string score_str = json.substr(start + 7, 6);

    // 将score的值转换为整数
    int score = std::stoi(score_str);

    // 输出score的值
    std::cout << "score: " << score << std::endl;
    return score;
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
                         "search?access_token=24.5371a42f3cdb554efc30d0745aa30047.2592000.1699336287.282335-40689721");
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

        score = getscore(result);
        // std::cout << "识别成功：辨识度为"  << score << std::endl;
        // printf("printf socre %.10lf\n", score);
    }
    curl_easy_cleanup(curl);

    return score;
}
