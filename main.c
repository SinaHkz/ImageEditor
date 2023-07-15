#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "Filters.c"
#include "URL_input.c"
#include "bmp_input.c"
#include "Email_input.c"

#define STB_IMAGE_IMPLEMENTATION

#include "Library/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Library/stb_image_write.h"

int read_int() {
    int c, num = 0;
    while ((c = getchar()) != '\n')
        num = num * 10 + (c - '0');
    return num;
}


int main() {
    int width, height, channels;
    int lan, inp_state, tool_state, filter, out_format, inp_format;
    char *address = malloc(150);
    char imag_url[150];
    int exit_code = 1;

    // Introduction to program.
    printf("Hello, this program is a photo editor developed by Sina Hakimzadeh and Arian Nouri in C programming language.\n"
           "First please select your language:\n"
           "1.English\n"
           "2.Persian\n");
    printf("سلام, این برنامه یک ادیتور عکس است که توسط سینا حکیم زاده و آرین نوری با زبان برنامه نویسی سی نوشته و توسعه یافته\n"
           "برای شروع لطفا زبان مورد نظر خود را وارد کنید :\n"
           "۱. انگلیسی\n"
           "۲.فارسی\n");
    lan = getchar() - '0';
    getchar();
    // ERROR.---------------------------------------------------------
    if (lan != 1 && lan != 2) {
        printf("Undefined state.\n");
        return 1;
    }





    // input format
    if (lan == 1)
        printf("Select your input format:\n"
               "1.JPG/JPEG\n"
               "2.PNG\n"
               "3.Bitmap(BMP)\n");
    else
        printf("لطفا فرمت مورد نظر را انتخاب کنید:\n"
               "1.JPG/JPEG\n"
               "2.PNG\n"
               "3.Bitmap(BMP)\n");
    inp_format = read_int();
    //ERROR
    if (inp_format > 3 || inp_format < 1) {
        if (lan == 1)
            printf("Undefined state\n");
        else
            printf("حالت تعریف نشده\n");
    }





    // Input method .
    if (lan == 1)
        printf("Please enter your input method:\n"
               "1.Local\n"
               "2.Internet\n"
               "3.Email\n");
    else
        printf("لطفا نحوه ی ورودی دادن را مشخص کنید:\n"
               "۱.فایل\n"
               "۲.اینترنت\n"
               "۳.ایمیل\n");

    inp_state = getchar() - '0';
    getchar();
    // ERROR.---------------------------------------------------------
    if (inp_state != 1 && inp_state != 2 && inp_state != 3) {
        if (lan == 1)
            printf("Undefined state\n");
        else
            printf("حالت تعریف نشده.\n");
        return 1;
    }




    // input image address.
    if (inp_state == 1) {
        if (lan == 1)
            printf("\nPrint your image address:\n");
        else
            printf("آدرس عکس خود را وارد کنید:\n");

        scanf("%s", address);
        getchar();

    } else if (inp_state == 2) {
        if (lan == 1)
            printf("\nPrint your image URL:\n");
        else
            printf("آدرس عکس خود را وارد کنید:\n");
        scanf("%s", imag_url);
        getchar();
        down_URL(imag_url);
        char *temp = "/Users/sina/Desktop/Project/image.jpg";
        free(address);
        address = temp;
    } else if (inp_state == 3) {
        printf("Please send your image to emailproject1401@gmail.com and then press ENTER/RETURN\n");
        getchar();
        inp_format = Download_email();
        char *temp;
        if (inp_format == 1)
            temp = "/Users/sina/Desktop/Project/IMAGE.jpg";
        if (inp_format == 2)
            temp = "/Users/sina/Desktop/Project/IMAGE.png";
        if (inp_format == 3)
            temp = "/Users/sina/Desktop/Project/IMAGE.bmp";
        free(address);
        address = temp;
    } else {
        if (lan == 1)
            printf("Undefined state.\n");
        else
            printf("حالت تعریف نشده.\n");
    }
    unsigned char *img;
    if (inp_format == 3)
        img = read_bmp(address, &width, &height, &channels);
    else {
        unsigned char *img_temp = stbi_load(address, &width, &height, &channels,
                                            0); //stb function work when the image pointer is decalered.
        img = img_temp;
    }





    // loading ERROR.---------------------------------------------------------
    if (img == NULL) {
        if (lan == 1)
            printf("Loading image failed.\n");
        else
            printf("بارگذازی ناموفق.\n");
        return 1;
    }
    while (exit_code) {
        //Tools selection part
        if (lan == 1)
            printf("\nSelect your edit tool:\n"
                   "1.Filter\n"
                   "2.Rotate\n"
                   "3.Crop\n"
                   "4.Add padding\n"
                   "5.Resize\n"
                   "6.Connect 2 images\n");
        else
            printf("لطفا ابزار اصلاح عکس خود را انتخاب کنید:\n"
                   "۱.فیلتر\n"
                   "۲.چرخاندن\n"
                   "۳.برش\n"
                   "۴.اضافه کردن حاشیه\n"
                   "۵.تغییر اندازه\n"
                   "۶.متصل کردن دو عکس\n");
        tool_state = getchar() - '0';
        getchar();

        // ERROR---------------------------------------------------------
        if (tool_state > 6 || tool_state < 1) {
            if (lan == 1)
                printf("Undefined state\n");
            else
                printf("حالت تعریف نشده.\n");
            return 1;
        }


        // Choose and applying filters.
        if (tool_state == 1) {
            if (lan == 1)
                printf("Select your filter:\n"
                       "1.Red color wash\n"
                       "2.Blue color wash\n"
                       "3.Green color wash\n"
                       "-------------------------------\n"
                       "4.Black linear noise\n"
                       "5.Vivid(Not recommended for bright photos)\n"
                       "6.Vivid Cool\n"
                       "7.Vivid Warm\n"
                       "-------------------------------\n"
                       "8.Mirror\n"
                       "9.Difference\n"
                       "10.Gray scale\n"
                       "11.Black and white(darker than Grayscale)\n"
                       "-------------------------------\n"
                       "12.filter\n"
                       "13.filter2\n"
                       "14.filter3\n"
                       "15.filter4\n"
                       "16.filter5\n"
                       "17.filter6\n"
                       "18.filter7\n"
                       "19.filter8\n"
                       "20.filter9\n"
                       "21.filter10\n"
                       "--------------------------------\n"
                       "22.Blur\n"
                       "23.Sharp Noise\n"
                       "24.Soft Noise\n"
                       "25.pixelate\n"
                       "26.Polaroid\n"
                       "27.Half tone\n");
            else
                printf("لطفا فیلتر خود را انتخاب کنید:\n"
                       "1.Red color wash\n"
                       "2.Blue color wash\n"
                       "3.Green color wash\n"
                       "-------------------------------\n"
                       "4.Black linear noise\n"
                       "5.Vivid (برای عکس های روشن پیشنهاد نمیشود)\n"
                       "6.Vivid Cool\n"
                       "7.Vivid Warm\n"
                       "-------------------------------\n"
                       "8.Mirror\n"
                       "9.Difference\n"
                       "10.Gray scale\n"
                       "11.Black and white(تیره تر از gray scale)\n"
                       "-------------------------------\n"
                       "12.filter\n"
                       "13.filter2\n"
                       "14.filter3\n"
                       "15.filter4\n"
                       "16.filter5\n"
                       "17.filter6\n"
                       "18.filter7\n"
                       "19.filter8\n"
                       "20.filter9\n"
                       "21.filter10\n"
                       "-------------------------------\n"
                       "22.Blur\n"
                       "23.Sharp Noise\n"
                       "24.Soft Noise\n"
                       "25.pixelate\n"
                       "26.Polaroid\n"
                       "27.Half tone\n");
            int filter = read_int();

            int img_size = width * height * channels;
            //int gray_size = width * height * channels;
            //unsigned char *gray_img = malloc(gray_size);
            if (filter == 1)
                red(img, width, height, channels);
            else if (filter == 2)
                blue(img, width, height, channels);
            else if (filter == 3)
                green(img, width, height, channels);
            else if (filter == 4)
                black_linear_noise(img, width, height, channels);
            else if (filter == 5)
                vivid(img, width, height, channels);
            else if (filter == 6)
                vivid_cool(img, width, height, channels);
            else if (filter == 7)
                vivid_warm(img, width, height, channels);
            else if (filter == 8)
                mirror(img, width, height, channels);
            else if (filter == 9)
                difference(img, width, height, channels);
            else if (filter == 10) {
                if (inp_state == 3)
                    gray_scale_test(img, width, height, channels);
                else
                    img = gray_scale(img, &width, &height, &channels);
            } else if (filter == 11)
                dark_gray_scale(img, width, height, channels);
            else if (filter == 12)
                filter1(img, width, height, channels);
            else if (filter == 13)
                filter2(img, width, height, channels);
            else if (filter == 14)
                filter3(img, width, height, channels);
            else if (filter == 15)
                filter4(img, width, height, channels);
            else if (filter == 16)
                filter5(img, width, height, channels);
            else if (filter == 17)
                filter6(img, width, height, channels);
            else if (filter == 18)
                filter7(img, width, height, channels);
            else if (filter == 19)
                filter8(img, width, height, channels);
            else if (filter == 20)
                filter9(img, width, height, channels);
            else if (filter == 21)
                filter10(img, width, height, channels);
            else if (filter == 22) {
                printf("\nPlease choose a blur level for your picture between '1' and '20'.\n");
                int blur_degree = read_int();
                img = blur(img, width, height, channels, blur_degree);
            } else if (filter == 23) {
                printf("\nPlease choose a noise level for your picture between '1' and '20'.\n");
                int noise_degree = 21 - read_int();
                noise(img, width, height, channels, noise_degree);
            } else if (filter == 24) {
                printf("\nPlease choose a noise level for your picture between '1' and '20'.\n");
                int noise_degree = 21 - read_int();
                noise(img, width, height, channels, noise_degree);
                img = blur(img, width, height, channels, 1);
            } else if (filter == 25) {
                printf("Please choose a pixelation level for your picture between '10' and '50'.\n");
                int block_size = read_int();
                img = pixelate(img, width, height, channels, block_size);
            } else if (filter == 26) {
                img = padding(img, height, width, 0.03 * width, 0.1 * width, channels);
                width += 0.06 * width;
                height += 0.03 * width + 0.1 * width;
            } else if (filter == 27) {
                img = half_tone(img, width, height, channels);
                channels = 1;
            }
                //ERROR---------------------------------------------------------
            else {
                if (lan == 1)
                    printf("Undefined state\n");
                else
                    printf("حالت تعریف نشده.\n");
                return 1;
            }
        }


        if (tool_state == 2) {
            printf("Please select a rotation degree for your picture.\n");
            float rotation_degree = read_int();
            float radians = rotation_degree * M_PI / 180.0f;
            int boundry[2];
            check_boundries(width, height, radians, boundry);
            img = rotate_image(img, width, height, channels, boundry[1], boundry[0], radians, 0);
            width = boundry[0];
            height = boundry[1];
        }
        if (tool_state == 3) {
            printf("Please choose a width for your cropped picture'.\n");
            int crop_width = read_int();
            printf("Please choose a height for your cropped picture.\n");
            int crop_height = read_int();

            if (crop_width > width || crop_height > height) {
                printf("x, y, width or height is not suitable for this picture.\n");
                return 1;
            }
            img = crop(img, width, height, channels, (width - crop_width) / 2, (height - crop_height) / 2,
                       crop_width, crop_height);
            width = crop_width;
            height = crop_height;
        }
        if (tool_state == 4) {
            printf("Please choose a padding for your image.\n");
            int padd = read_int();
            img = padding(img, height, width, padd, padd, channels);
            width += 2 * padd;
            height += 2 * padd;
        }
        if (tool_state == 5){
            printf("Please choose a additional width pixel for your image.\n");
            int add_width = read_int();
            printf("Please choose a additional height pixel for your image.\n");
            int add_height = read_int();
            img = resize(img,&height,&width,channels,add_width,add_height);
        }

        if (tool_state == 6){
            if (inp_state == 2 || inp_state == 3){
                printf("This part has a bug and you can't use this part when the first time you input your image with email or URL\n");
                return 1;
            }
            if (lan == 1)
                printf("Please enter your input method for second image:\n"
                       "1.Local\n"
                       "2.Internet\n"
                       "3.Email\n");
            else
                printf("لطفا نحوه ی ورودی دادن را مشخص کنید برای عکس دوم:\n"
                       "۱.فایل\n"
                       "۲.اینترنت\n"
                       "۳.ایمیل\n");

            inp_state = getchar() - '0';
            getchar();
            // ERROR.---------------------------------------------------------
            if (inp_state != 1 && inp_state != 2 && inp_state != 3) {
                if (lan == 1)
                    printf("Undefined state\n");
                else
                    printf("حالت تعریف نشده.\n");
                return 1;
            }

            // input image address.
            if (inp_state == 1) {
                if (lan == 1)
                    printf("\nPrint your image address:\n");
                else
                    printf("آدرس عکس خود را وارد کنید:\n");

                scanf("%s", address);
                getchar();

            } else if (inp_state == 2) {
                if (lan == 1)
                    printf("\nPrint your image URL:\n");
                else
                    printf("آدرس عکس خود را وارد کنید:\n");
                scanf("%s", imag_url);
                getchar();
                down_URL(imag_url);
                char *temp = "/Users/sina/Desktop/Project/image.jpg";
                free(address);
                address = temp;
            } else if (inp_state == 3) {
                printf("Please send your image to emailproject1401@gmail.com and then press ENTER/RETURN\n");
                getchar();
                inp_format = Download_email();
                char *temp;
                if (inp_format == 1)
                    temp = "/Users/sina/Desktop/Project/IMAGE.jpg";
                if (inp_format == 2)
                    temp = "/Users/sina/Desktop/Project/IMAGE.png";
                if (inp_format == 3)
                    temp = "/Users/sina/Desktop/Project/IMAGE.bmp";
                free(address);
                address = temp;
            } else {
                if (lan == 1)
                    printf("Undefined state.\n");
                else
                    printf("حالت تعریف نشده.\n");
            }
            unsigned char *img2;
            int width2,height2,channels2;
            if (inp_format == 3)
                img2 = read_bmp(address, &width2, &height2, &channels2);
            else {
                unsigned char *img_temp = stbi_load(address, &width2, &height2, &channels2,
                                                    0); //stb function work when the image pointer is declared.
                img2 = img_temp;
            }
            img = connect_images(img,&width,&height,channels,img2,&width2,&height2,channels2);
            img = padding(img,height,width,10,10,channels);
            width += 20;
            height +=20;
        }

        //writing image data
        if (inp_format == 3) {
            write_bmp(img, width, height, channels);
            exit_code = 0;
        } else {
            //Choose output format
            if (lan == 1)
                printf("Select your output format:\n");
            else
                printf("لطفا فرمت خروجی گرفتن را مشخص کنید:\n");
            printf("1.JPG/JPEG\n"
                   "2.PNG\n"
                   "3.BMP\n");
            out_format = read_int();


            //ERROR---------------------------------------------------------
            if (out_format < 1 || out_format > 3) {
                if (lan == 1)
                    printf("Undefined state\n");
                else
                    printf("حالت تعریف نشده.\n");
                return 1;
            }
            if (out_format == 1)
                stbi_write_jpg("output.jpg", width, height, channels, img, 100);
            else if (out_format == 2)
                stbi_write_png("output.png", width, height, channels, img, width * channels);
            else if (out_format == 3)
                stbi_write_bmp("output.bmp", width, height, channels, img);
            if (lan == 1)
                printf("\nYour edited picture is save and you can check it out.\nDo you want to continue editing the picture?\n"
                       "1.Yes\n"
                       "2.No\n");
            else
                printf("\nعکس ادیت شده شما ذخیره شده و شما میتوانید آن را ببینید. \nآیا میخواهید به ادیت عکس بپردازید؟\n"
                       "۱.بله\n"
                       "۲.خیر\n");
            if (read_int() != 1)
                exit_code = 0;
        }
    }


    if (lan == 1)
        printf("Your edited image has successfully saved in program file.");
    else
        printf("عکس شما در فایل برنامه با موفقیت سیو شد.");



    // free image.
    free(img);
    return 0;
}
