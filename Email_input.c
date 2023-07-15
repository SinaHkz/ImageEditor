#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <curl/curl.h>
#include "libb64-1.2.1/include/b64/cdecode.h"

char *merge(char *str1, char *str2) {
    char *str = malloc(50);
    int i, j, k;
    for (i = 0; str1[i] != '\0'; i++)
        str[i] = str1[i];
    for (j = i, k = 0; str2[k] != '\0'; j++, k++)
        str[j] = str2[k];
    str[j] = '\0';
    return str;
}

int UID() {
    char *command = "curl -u \"emailproject1401@gmail.com:lakmaixovgopczxn\" --url \"imaps://imap.gmail.com/INBOX/\" --request \"FETCH 1:* (FLAGS BODY.PEEK[])\" > response.txt ";
    int status = system(command);
    if (status == -1) {
        printf("System command failed\n");
        return 1;
    } else {
        printf("UID numbers fetched successfully\n");
        return 0;
    }
}

void parsUID(int *x) {
    FILE *fp = fopen("./response.txt", "r");
    if (fp == NULL) {
        printf("Failed to open response text!");
        return;
    }
    char c;
    int count = 0;
    for (int i = 0; (c = getc(fp)) != EOF; i++)
        if (c == '*')
            count++;
    fclose(fp);
    *x = count;
}


int write_callback(char *ptr, int size, int nmemb, void *userdata) {
    FILE *file = (FILE *) userdata;
    return fwrite(ptr, size, nmemb, file);
}

int Fetch(char *UID_num) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize curl\n");
        return 1;
    }

    char *IMAP_URL = merge("imaps://imap.gmail.com/INBOX/;UID=", UID_num);


    //Set IMAP URL
    char url[256];
    snprintf(url, sizeof(url), IMAP_URL);

    curl_easy_setopt(curl, CURLOPT_USERNAME, "emailproject1401@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "lakmaixovgopczxn");

    FILE *outputFile = fopen("Fetched.txt", "w");
    if (!outputFile) {
        fprintf(stderr, "Failed to open output file\n");
        return 1;
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, outputFile);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    //curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) { //ERROR---------------------------------------------------------
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        fclose(outputFile);
        return 1;
    }
    fclose(outputFile);
    curl_easy_cleanup(curl);

    return 0;
}


int pars(char *res, int *format) { //format is image format and res is the array contain image encoded data.
    FILE *fp = fopen("./Fetched.txt", "r");
    if (fp == NULL) {
        printf("can't open the file");
        return 0;
    }
    int flag = 1, i;
    char *line = malloc(200);
    char h, c; //to hold the first format character
    while (flag) {
        fgets(line, 200, fp);
        int len = strlen(line);
        if (line[0] == '-' && line[1] == '-' && line[len - 3] == '-' && line[len - 4] == '-')
            flag = 0;
    }
    fscanf(fp, "%s\n", line); //baraye radshodan as data ezafe.
    fscanf(fp, "%*s %s\n", line);
    for (i = 0; i < strlen(line) && line[i] != '/'; i++);
    h = line[i + 1];
    line[i] = '\0';
    if (strcmp(line, "image") == 0) {
        if (h == 'j' || h == 'J')
            *format = 1;
        else if (h == 'p' || h == 'P')
            *format = 2;
        else if (h == 'b' || h == 'B')
            *format = 3;
        else {
            printf("Format is not support!");
            return 0;
        }
    } else {
        printf("The email attachment is not an image!");
        return 0;
    }
    int count = 0;
    while ((c = getc(fp)) && count < 6){
        if (c == '\n')
            count++;
    }    
    res[0] = c;
    for (i = 1; (c = getc(fp)) != '-'; i++)
        res[i] = c;
    free(line);
    return 1;
}


unsigned char *decodeBase64Image(const char *encodedData, size_t *imageSize) {
    size_t inputLength = strlen(encodedData);
    size_t outputLength = (inputLength * 3) / 4; // estimated output size
    unsigned char *outputBuffer = (unsigned char *) malloc(outputLength);
    if (outputBuffer == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    base64_decodestate state;
    base64_init_decodestate(&state);
    *imageSize = base64_decode_block(encodedData, inputLength, (char *) outputBuffer, &state);

    return outputBuffer;
}

void writeImageDataToFile(const char *filename, unsigned char *imageData, size_t imageDataLength) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(imageData, sizeof(wchar_t), imageDataLength, file);
        fclose(file);
        printf("Image file '%s' created successfully.\n", filename);
    } else {
        printf("Failed to create image file '%s'.\n", filename);
    }
}

int Base64ToImage(char *encodedImage, int format) {
    size_t imageSize;
    unsigned char *decodedImage = decodeBase64Image(encodedImage, &imageSize);
    if (decodedImage == NULL) {
        printf("Image decoding failed.\n");
        return 1;
    }
    if (format == 1)
        writeImageDataToFile("IMAGE.jpg", decodedImage, imageSize);
    if (format == 2)
        writeImageDataToFile("IMAGE.png", decodedImage, imageSize);
    if (format == 3)
        writeImageDataToFile("IMAGE.bmp", decodedImage, imageSize);

    free(decodedImage);
    free(encodedImage);

    return 0;
}


int Download_email() {
    int UID_num, i;
    char *encodedImage = malloc(10000000);
    int format;
    char UID_str[10];
    if (!UID()) {
        parsUID(&UID_num);
    }else
        return 1;



    for (i = 0; UID_num != 0; i++) {
        UID_str[i] = UID_num % 10 + '0';
        UID_num = UID_num / 10;
    }
    UID_str[i] = '\0';
    i--;
    for (int j = 0; j <= i; j++, i--) {
        char temp = UID_str[j];
        UID_str[j] = UID_str[i];
        UID_str[i] = temp;
    }


    int result = Fetch(UID_str);
    if (result == 0) {
        printf("Email fetched successfully!\n");
        pars(encodedImage, &format);
        Base64ToImage(encodedImage, format);
    } else {
        printf("Failed to fetch email.\n");
        return 1;
    }
    return format;
}