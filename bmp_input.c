#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



#pragma pack(push, 1)
struct BMPHeaderfile {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
};

struct BMPHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t totalColors;
    uint32_t importantColors;
};
#pragma pack(pop)

static struct BMPHeaderfile headerfile;
static struct BMPHeader header;


unsigned char *read_bmp(char *filename, int *width, int *height, int *channels) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file!");
        return NULL;
    }

    int Error = fread(&headerfile, sizeof(struct BMPHeaderfile), 1, file);
    if (Error != 1) {
        printf("Reading BMP file header failed!");
        fclose(file);
        return NULL;
    }
    if (headerfile.signature != 0x4D42) {
        printf("This file isn't a standard Bitmap!");
        fclose(file);
        return NULL;
    }

    Error = fread(&header, sizeof(struct BMPHeader), 1, file);
    if (Error != 1) {
        printf("Reading BMP header failed!");
        fclose(file);
        return NULL;
    }
    *width = header.width;
    *height = header.height;
    *channels = header.bitsPerPixel / 8;

    unsigned char *img = malloc(*width * (*height) * (*channels));

    fseek(file, headerfile.dataOffset, 0);
    Error = fread(img, *width * *height * *channels, 1, file);
    if (Error != 1) {
        printf("Failed to load image data!");
        fclose(file);
        free(img);
        return NULL;
    }

    fclose(file);
    return img;
}

int write_bmp(unsigned char *img, int width, int height, int channels) {
    int Error;
    FILE *file = fopen("output1.bmp", "wb");
    if (!file) {
        printf("Failed to open a output file!");
        return 1;
    }
    Error = fwrite(&headerfile, sizeof(struct BMPHeaderfile), 1, file);
    if (Error != 1) {
        printf("Failed to write headerfile!");
        fclose(file);
        return 1;
    }
    Error = fwrite(&header, sizeof(struct BMPHeader), 1, file);
    if (Error != 1) {
        printf("Failed to write headerfile!");
        fclose(file);
        return 1;
    }

    fseek(file, headerfile.dataOffset, 0);
    Error = fwrite(img, width * height * channels, 1, file);
    if (Error != 1) {
        printf("Failed to save the output image data!");
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}