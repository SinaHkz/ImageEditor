#include <stdio.h>
#include <curl/curl.h>

int down_URL(char *URL) {
    FILE *fp;
    CURL *curl;
    CURLcode res;
    char *url = URL;
    char *outputFile = "image.jpg"; 
    fp = fopen(outputFile, "wb");
    if (fp == NULL) {
        printf("Failed to open the output file.\n");
        return 1;
    }
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    printf("\nImage downloaded successfully.\n\n\n");
    return 0;
}
