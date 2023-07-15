#include "stdlib.h"
#include "time.h"
#include "math.h"


void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}


void red(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        *(temp_img + 1) = 0;
        *(temp_img + 2) = 0;
    }
}

void blue(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        *(temp_img + 1) = 0;
        *(temp_img) = 0;
    }
}

void green(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        *(temp_img + 2) = 0;
        *(temp_img) = 0;
    }
}

void vivid_cool(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        if (*(temp_img + 1) + 10 > 255)
            *(temp_img + 1) = 245;
        if (*(temp_img + 2) + 25 > 255)
            *(temp_img + 2) = 230;
        *temp_img = *temp_img;
        *(temp_img + 1) += 10;
        *(temp_img + 2) += 25;
    }
}

void vivid_warm(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        if (*(temp_img + 1) + 10 > 255)
            *(temp_img + 1) = 245;
        if (*(temp_img) + 25 > 255)
            *(temp_img) = 230;
        *temp_img += 25;
        *(temp_img + 1) += 10;
        *(temp_img + 2) = *(temp_img + 2);
    }
}

void vivid(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        if ((*temp_img + 15) > 255)
            *temp_img = 240;
        if (*(temp_img + 1) + 15 > 255)
            *(temp_img + 1) = 240;
        if (*(temp_img + 2) + 15 > 255)
            *(temp_img + 2) = 240;
        *temp_img += 15;
        *(temp_img + 1) += 15;
        *(temp_img + 2) += 15;
    }
}

void difference(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        *temp_img = 255 - *temp_img;
        *(temp_img + 1) = 255 - *(temp_img + 1);
        *(temp_img + 2) = 255 - *(temp_img + 2);
    }
}

void black_linear_noise(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += 2 * channels) {
        *(temp_img + 3) = 0;
        *(temp_img + 4) = 0;
        *(temp_img + 5) = 0;
    }
}

void gray_scale_test(unsigned char *img, int width, int height, int channels) { //for BMP.
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        int mid = (*temp_img + *(temp_img + 1) + *(temp_img + 2)) / 3;
        *temp_img = mid;
        *(temp_img + 1) = mid;
        *(temp_img + 2) = mid;
    }
}

unsigned char *gray_scale(unsigned char *img, int *width, int *height, int *channels) {
    int image_size = *width * *height * *channels;
    int gray_channel;
    if (*channels == 4)
        gray_channel = 2;
    else
        gray_channel = 1;
    int gray_size = *width * *height * gray_channel;
    unsigned char *gray_img = malloc(gray_size);
    for (unsigned char *temp_img = img, *temp_gray = gray_img;
         temp_img != img + image_size; temp_img += *channels, temp_gray += gray_channel) {
        *temp_gray = (*temp_img + *(temp_img + 1) + *(temp_img + 2)) / 3;
        if (*channels == 4)
            *(temp_gray + 1) = *(temp_img + 3);
    }
    *channels = gray_channel;
    free(img);
    return gray_img;
}

void dark_gray_scale(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        *(temp_img) = *(temp_img + 2);
        *(temp_img + 1) = *(temp_img);
        *(temp_img + 2) = *(temp_img + 1);
    }
}

void filter1(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    unsigned char temp;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        temp = *temp_img;
        *(temp_img) = *(temp_img + 2);
        *(temp_img + 2) = temp;
    }
}

void filter2(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    unsigned char temp;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        temp = *(temp_img + 1);
        *(temp_img + 1) = *(temp_img + 2);
        *(temp_img + 2) = temp;
    }
}

void filter4(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        *(temp_img) = *(temp_img + 1);
        *(temp_img + 1) = *(temp_img + 2);
        *(temp_img + 2) = *(temp_img);
    }
}

void filter3(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    unsigned char temp;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels) {
        temp = *(temp_img + 1);
        *(temp_img + 1) = *(temp_img);
        *(temp_img) = temp;
    }
}

void filter5(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels)
        *(temp_img + 1) = *(temp_img + 2);
}

void filter6(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels)
        *(temp_img) = *(temp_img + 2);
}

void filter7(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels)
        *(temp_img + 2) = *(temp_img + 1);
}

void filter8(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels)
        *(temp_img) = *(temp_img + 1);
}

void filter9(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels)
        *(temp_img + 1) = *(temp_img);
}

void filter10(unsigned char *img, int width, int height, int channels) {
    int image_size = width * height * channels;
    for (unsigned char *temp_img = img; temp_img != img + image_size; temp_img += channels)
        *(temp_img + 2) = *(temp_img);
}

void mirror(unsigned char *img, int width, int height, int channels) {
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width * channels / 2; j += channels) {
            swap(img + (i * width * channels) + j, img + (i * width * channels) + (width * channels) - j - 1);
        }
        for (j = 1; j < width * channels / 2; j += channels) {
            swap(img + (i * width * channels) + j, img + (i * width * channels) + (width * channels) - j - 1);
        }
        for (j = 2; j < width * channels / 2; j += channels) {
            swap(img + (i * width * channels) + j, img + (i * width * channels) + (width * channels) - j - 1);
        }
    }
    filter1(img, width, height, channels);//red and blue color is converted and use it to fix it.
}

unsigned char *blur(unsigned char *img, int width, int height, int channels, int degree) {
    printf("\nplease waite!!\n");
    unsigned char *temp = malloc(width * height * channels);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                int sum = 0;
                for (int j = -1 * degree; j <= degree; j++) {
                    for (int i = -1 * degree; i <= degree; i++) {
                        int X = x + i;
                        int Y = y + j;
                        if (X >= 0 && X < width && Y >= 0 && Y < height) {
                            sum += img[(Y * width + X) * channels + c];
                        }
                    }
                }
                temp[(y * width + x) * channels + c] = sum / ((2 * degree + 1) * (2 * degree + 1));
            }
        }
    }
    free(img);
    return temp;
}

void noise(unsigned char *img, int width, int height, int channels, int degree) {
    srand(time(NULL)); //making random number with srand and time functions to make a noisy image.
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < channels; k++) {
                int noise = rand() % 256;
                if (((i * width + j) * channels + k) % (noise % degree) == 0)
                    img[(i * width + j) * channels + k] += noise;
            }
        }
    }
}


unsigned char *pixelate(unsigned char *img, int width, int height, int channels, int block_size) {
    unsigned char *output = malloc(width * channels * height);
    int r, b, g, x, y, count, i, j;
    for (y = 0; y < height; y += block_size) {
        for (x = 0; x < width; x += block_size) {
            r = b = g = count = 0;
            for (j = 0; j < block_size; j++) {
                for (i = 0; i < block_size; i++) {
                    if ((x + i) >= 0 && (x + i) < width && (y + j) >= 0 && (y + j) < height) {
                        r += img[((y + j) * width + (x + i)) * channels];
                        g += img[((y + j) * width + (x + i)) * channels + 1];
                        b += img[((y + j) * width + (x + i)) * channels + 2];
                        count++;
                    }
                }
            }
            int final_r, final_b, final_g;
            final_r = (count > 0) ? r / count : img[(y * width + x) * channels];
            final_g = (count > 0) ? g / count : img[(y * width + x) * channels + 1];
            final_b = (count > 0) ? b / count : img[(y * width + x) * channels + 2];
            for (j = 0; j < block_size; j++) {
                for (i = 0; i < block_size; i++) {
                    output[((y + j) * width + (x + i)) * channels] = final_r;
                    output[((y + j) * width + (x + i)) * channels + 1] = final_g;
                    output[((y + j) * width + (x + i)) * channels + 2] = final_b;
                }
            }
        }
    }
    free(img);
    return output;
}


unsigned char *
crop(unsigned char *img, int width, int height, int channels, int x, int y, int crop_width, int crop_height) {

    int i, j, k;
    int cropped_size = crop_width * crop_height * channels;
    unsigned char *cropped = malloc(cropped_size);

    if (cropped == NULL) {
        printf("unable to allocate memory.");
        return NULL;
    }
    for (j = 0; j < crop_height; j++) {
        for (i = 0; i < crop_width; i++) {
            for (k = 0; k < channels; k++) {
                cropped[(i + j * crop_width) * channels + k] =
                        img[(i + x + (j + y) * width) * channels + k];
            }
        }
    }
    free(img);
    return cropped;
}


void check_boundries(int width, int height, float angle, int boundry[]) {
    float sinAngle = sinf(angle);
    float cosAngle = cosf(angle);

    float centerX = width / 2.0f;
    float centerY = height / 2.0f;


    float cornersX[4] = {-centerX, -centerX, width - centerX, width - centerX};
    float cornersY[4] = {-centerY, height - centerY, -centerY, height - centerY};

    float rotatedCornersX[4];
    float rotatedCornersY[4];
    for (int i = 0; i < 4; i++) {
        rotatedCornersX[i] = cornersX[i] * cosAngle - cornersY[i] * sinAngle;
        rotatedCornersY[i] = cornersX[i] * sinAngle + cornersY[i] * cosAngle;
    }

    float minX = rotatedCornersX[0];
    float maxX = rotatedCornersX[0];
    float minY = rotatedCornersY[0];
    float maxY = rotatedCornersY[0];
    for (int i = 1; i < 4; i++) {
        if (rotatedCornersX[i] < minX) { minX = rotatedCornersX[i]; }
        if (rotatedCornersX[i] > maxX) { maxX = rotatedCornersX[i]; }
        if (rotatedCornersY[i] < minY) { minY = rotatedCornersY[i]; }
        if (rotatedCornersY[i] > maxY) { maxY = rotatedCornersY[i]; }
    }
    int newWidth = (int) ceil(maxX - minX);
    int newHeight = (int) ceil(maxY - minY);
    boundry[0] = newWidth;
    boundry[1] = newHeight;
}


unsigned char *
rotate_image(unsigned char *img, int width, int height, int channels, int newHeight, int newWidth, float angle,
             int flag) {
    if (flag == 1)
        angle = 2 * M_PI - angle;
    float newCenterX = (float) newWidth / 2.0;
    float newCenterY = (float) newHeight / 2.0;
    float centerX = (float) width / 2.0;
    float centerY = (float) height / 2.0;
    unsigned char *out = (unsigned char *) malloc(newHeight * newWidth * channels);
    int x, y;
    for (y = 0; y < newHeight; y++) {
        for (x = 0; x < newWidth; x++) {
            float srcX = (x - newCenterX) * cosf(angle) + (y - newCenterY) * sinf(angle) + centerX;
            float srcY = -(x - newCenterX) * sinf(angle) + (y - newCenterY) * cosf(angle) + centerY;
            int destIndex = y * newWidth * channels + x * channels;
            if (srcX >= 0 && srcX < width && srcY >= 0 && srcY < height) {
                int srcIndex = (int) srcY * width * channels + (int) srcX * channels;
                out[destIndex] = img[srcIndex];
                out[destIndex + 1] = img[srcIndex + 1];
                out[destIndex + 2] = img[srcIndex + 2];
            } else {
                out[destIndex] = 255;
                out[destIndex + 1] = 255;
                out[destIndex + 2] = 255;
            }
        }
    }
    return out;
}


unsigned char *color_to_gray(unsigned char *img, int height, int width, int channels) {//for half tone filter.
    int r, g, b, i, j;
    double gray;
    unsigned char *gray_img = malloc(sizeof(unsigned char) * width * height);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Get the red, green, and blue channels of the pixel
            r = img[(i * width + j) * channels];
            g = img[(i * width + j) * channels + 1];
            b = img[(i * width + j) * channels + 2];

            // Calculate the grayscale value using the luminosity method
            gray = 0.21 * r + 0.72 * g + 0.07 * b;

            // Set the red, green, and blue channels of the pixel to the grayscale value
            gray_img[i * width + j] = (unsigned char) gray;

        }
    }
    return gray_img;
}

unsigned char *half_tone(unsigned char *input_img, int height, int width, int channels) {
    int size = 8;
    unsigned char *img = malloc(sizeof(unsigned char) * width * height);
    int dot_pattern[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int cross_pattern[8][8] = {
            {1, 0, 0, 0, 0, 0, 0, 1},
            {0, 1, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0, 0, 1, 0},
            {1, 0, 0, 0, 0, 0, 0, 1}
    };
    img = color_to_gray(input_img, height, width, channels);
    unsigned char *output = malloc(sizeof(unsigned char) * width * height);
    memset(output, 0, width * height);
    int i, j, x, y, sum, num, average;
    for (y = 0; y < height; y += size) {
        for (x = 0; x < width; x += size) {
            sum = 0;
            num = 0;
            for (j = 0; j < size; j++) {
                for (i = 0; i < size; i++) {
                    int index_x = x + i;
                    int index_y = y + j;
                    if (index_x >= 0 && index_x < width && index_y >= 0 && index_y < height) {
                        num++;
                        sum += img[(index_y * width + index_x)];
                    }
                }
            }
            average = sum / num;
            //int threshold=(int)((average)/255.0*(size*size));
            for (j = 0; j < size; j++) {
                for (i = 0; i < size; i++) {
                    if ((y + j) >= 0 && (y + j) < height && (x + i) >= 0 && (x + i) < width) {
                        int index = ((y + j) * width + x + i);
                        int gray_value = img[index];
                        int threshold = (int) ((gray_value) / 255.0 * (size * size));
                        int *pattern = index < threshold ? dot_pattern[0] : cross_pattern[0];
                        unsigned char halftone_value = pattern[j * size + i] * gray_value;
                        output[index] = halftone_value;
                    }
                }
            }
        }
    }
    free(img);
    return output;
}

unsigned char *padding(unsigned char *img, int height, int width, int padding, int bottom_padding, int channels) {
    int new_width = width + 2 * padding, x, y;
    int new_height = height + padding + bottom_padding;
    unsigned char *output = malloc(sizeof(unsigned char) * new_height * new_width * channels);
    memset(output, 255, new_width * new_height * channels);
    for (x = 0; x < new_width; x++) {
        output[x * channels] = 0;
        output[x * channels + 1] = 0;
        output[x * channels + 2] = 0;
        output[(new_width + x) * channels] = 0;
        output[(new_width + x) * channels + 1] = 0;
        output[(new_width + x) * channels + 2] = 0;
        output[((new_height - 2) * new_width + x) * channels] = 0;
        output[((new_height - 2) * new_width + x) * channels + 1] = 0;
        output[((new_height - 2) * new_width + x) * channels + 2] = 0;
        output[((new_height - 1) * new_width + x) * channels] = 0;
        output[((new_height - 1) * new_width + x) * channels + 1] = 0;
        output[((new_height - 1) * new_width + x) * channels + 2] = 0;
    }

    for (y = 2; y < new_height - 2; y++) {
        output[(y * new_width) * channels] = 0;
        output[(y * new_width) * channels + 1] = 0;
        output[(y * new_width) * channels + 2] = 0;
        output[(y * new_width + 1) * channels] = 0;
        output[(y * new_width + 1) * channels + 1] = 0;
        output[(y * new_width + 1) * channels + 2] = 0;
        output[(y * new_width + new_width - 2) * channels] = 0;
        output[(y * new_width + new_width - 2) * channels + 1] = 0;
        output[(y * new_width - new_width - 2) * channels + 2] = 0;
        output[(y * new_width + new_width - 1) * channels] = 0;
        output[(y * new_width + new_width - 1) * channels + 1] = 0;
        output[(y * new_width + new_width - 1) * channels + 2] = 0;
    }

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            output[((padding + y) * new_width + x + padding) * channels] = img[(y * width + x) * channels];
            output[((padding + y) * new_width + x + padding) * channels + 1] = img[(y * width + x) * channels + 1];
            output[((padding + y) * new_width + x + padding) * channels + 2] = img[(y * width + x) * channels + 2];
        }
    }
    free(img);
    return output;
}

unsigned char *resize(unsigned char *img, int *height, int *width, int channels, int add_width, int add_height) {
    int res_width, res_height;
    res_width = *width + add_width;
    res_height = *height + add_height;
    unsigned char *output = malloc(res_height * res_width * channels);
    double x_ratio = (double) (*width) / (double) res_width;
    double y_ratio = (double) (*height) / (double) res_height;
    for (int y = 0; y < res_height; y++) {
        for (int x = 0; x < res_width; x++) {
            int src_x = (int) (x * x_ratio);
            int src_y = (int) (y * y_ratio);
            for (int c = 0; c <= 2; c++)
                output[(y * res_width + x) * channels + c] = img[(src_y * (*width) + src_x) * channels + c];
        }
    }
    *width = res_width;
    *height = res_height;
    free(img);
    return output;
}

unsigned char *
connect_images(unsigned char *img1, int *width1, int *height1, int channel1, unsigned char *img2, int *width2,
               int *height2,
               int channel2) {
    int newWidth = *width1 > *width2 ? *width1 : *width2;
    int newChannel = channel1 > channel2 ? channel1 : channel2;
    if (newWidth == *width1) {
        int diff = newWidth - *width2;
        int diff2 = *height2 * ((float) diff / (float) *width2);
        img2 = resize(img2, height2, width2, channel2, diff, diff2);
    } else if (newWidth == *width2) {
        int diff = newWidth - *width1;
        int diff2 = *height1 * ((float) diff / (float) *width1);
        img1 = resize(img1, height1, width1, channel1, diff, diff2);
    }
    img1 = padding(img1, *height1, *width1, 0, 10, channel1);
    *height1 += 10;

    int newHeight = *height1 + *height2;
    unsigned char *newImg = malloc(newWidth * newHeight * newChannel * sizeof(unsigned char));

    int i;
    for (i = 0; i < *width1 * *height1 * channel1; i++)
        newImg[i] = img1[i];
    for (int j = 0; j < *width2 * *height2 * channel2; j++, i++)
        newImg[i] = img2[j];

    *width1 = newWidth;
    *height1 = newHeight;
    free(img2);
    free(img1);
    return newImg;
}