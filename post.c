#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <user_id>\n", argv[0]);
        return 1;
    }

    CURL *curl;
    CURLcode res;

    // Format the JSON data with the provided user_id
    char json_data[200];
    snprintf(json_data, sizeof(json_data), "{\"user_id\":\"%s\",\"password\":\"sdfsdfsrew\"}", argv[1]);

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set the URL for the POST request
        curl_easy_setopt(curl, CURLOPT_URL, "https://acas.edu.bd/api/security/signin");

        // Set the formatted JSON data as POST fields
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

        // Set custom headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Host: acas.edu.bd");
        headers = curl_slist_append(headers, "Sec-Ch-Ua-Platform: \"Linux\"");
        headers = curl_slist_append(headers, "Accept-Language: en-US,en;q=0.9");
        headers = curl_slist_append(headers, "Accept: application/json, text/plain, */*");
        headers = curl_slist_append(headers, "Sec-Ch-Ua: \"Not?A_Brand\";v=\"99\", \"Chromium\";v=\"130\"");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Sec-Ch-Ua-Mobile: ?0");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.6723.70 Safari/537.36");
        headers = curl_slist_append(headers, "Origin: https://acas.edu.bd");
        headers = curl_slist_append(headers, "Sec-Fetch-Site: same-origin");
        headers = curl_slist_append(headers, "Sec-Fetch-Mode: cors");
        headers = curl_slist_append(headers, "Sec-Fetch-Dest: empty");
        headers = curl_slist_append(headers, "Referer: https://acas.edu.bd/signin");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, br");
        headers = curl_slist_append(headers, "Priority: u=1, i");
        headers = curl_slist_append(headers, "Connection: keep-alive");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        printf("\n");
        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    // Global cleanup
    curl_global_cleanup();

    return 0;
}
