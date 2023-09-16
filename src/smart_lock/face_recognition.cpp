#include "face_recognition.h"


inline size_t onWriteData(void * buffer, size_t size, size_t nmemb, void * userp)
{
    std::string * str = dynamic_cast<std::string *>((std::string *)userp);
    str->append((char *)buffer, size * nmemb);
    return nmemb;
}


int face_recognition(std::string base64)
{
    std::string result;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, "https://aip.baidubce.com/rest/2.0/face/v3/search?access_token=24.f070273410a38f2184ddb1ad24507cdf.2592000.1697463129.282335-39376742");
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
        std::cout<<result;
    }
    curl_easy_cleanup(curl);
    return (int)res;
}