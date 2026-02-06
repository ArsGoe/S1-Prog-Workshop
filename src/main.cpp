#include "glm/geometric.hpp"
#include "random.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sil/sil.hpp>
#include <cmath>
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>

void clean_image() {
    sil::Image image{"images/photo.jpg"};
    
    image.save("output/pouet.png");
}

// Done
void make_green() {
    sil::Image image{"images/logo.png"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        pixel.r = 0;
        pixel.b = 0;
    }
    
    image.save("output/green.png");
}

// Done
void shuffle_channels() {
    sil::Image image{"images/logo.png"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        float tmp_g = pixel.g;

        pixel.g = pixel.r;
        pixel.r = pixel.b;
        pixel.b = tmp_g;
    }
    
    image.save("output/shuffle.png");
}

// Done
void to_black_and_white(){
    sil::Image image{"images/logo.png"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        float moy = (pixel.b + pixel.g + pixel.r) / 3;
        pixel.b = moy;
        pixel.r = moy;
        pixel.g = moy;
    }
    
    image.save("output/black_and_white.png");
}

// Done
void to_negative(){
    sil::Image image{"images/logo.png"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        pixel.b = 1 - pixel.b;
        pixel.r = 1 - pixel.r;
        pixel.g = 1 - pixel.g;
    }
    
    image.save("output/negative.png");
}

// Done
void buzz_cut(){
    sil::Image image{"images/logo.png"};
    for (float i{0}; i < image.width(); i++)
    {
        float float_i = i/ image.width();
        for (float j{0}; j < image.height(); j++)
        {
            glm::vec3 &pixel = image.pixel(i, j);
            pixel.b = float_i;
            pixel.g = float_i;
            pixel.r = float_i;
        }
        
    }
    
    
    image.save("output/buzz_cut.png");
}

// Done
void noising() {
    sil::Image image{"images/logo.png"};
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            int noise = rand() % 3;
            if (noise == 1)
            {
                glm::vec3 &pixel = image.pixel(i, j);
                float rand_r = rand() % 256;
                float rand_g = rand() % 256;
                float rand_b = rand() % 256;

                pixel.b = rand_b / 255;
                pixel.g = rand_g / 255;
                pixel.r = rand_r / 255;
            }
            
        }
        
    }
    image.save("output/noise.png");
}

// Done
void rotate_image() {
    sil::Image image{"images/logo.png"};
    sil::Image rotated_image = sil::Image(image.height(), image.width());
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            rotated_image.pixel(image.height() - j - 1, i) = image.pixel(i, j);
        }
    }

    
    rotated_image.save("output/rotate.png");
}

// Done
void rgb_split() {
    sil::Image image{"images/logo.png"};
    sil::Image split_rgb_image = sil::Image(image.width(), image.height());
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            glm::vec3 &pixel = image.pixel(i, j);
            if (i - 30 > 0)
            {
                glm::vec3 &pixel_offset = split_rgb_image.pixel(i - 30, j);
                pixel_offset.b = pixel.b;
            }
            if (i + 30 < image.width())
            {
                glm::vec3 &pixel_offset = split_rgb_image.pixel(i + 30, j);
                pixel_offset.r = pixel.r;
            }
            glm::vec3 &pixel_offset = split_rgb_image.pixel(i, j);
            pixel_offset.g = pixel.g;
        }
        
    }
    split_rgb_image.save("output/rgb_split.png");
}

// Done
void light_up(){
    sil::Image image{"images/photo.jpg"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        pixel.r = pixel.r + (30.0/255.0);
        pixel.g = pixel.g + (30.0/255.0);
        pixel.b = pixel.b + (30.0/255.0);
    }
    
    image.save("output/light_up.png");
}

// Done
void light_down(){
    sil::Image image{"images/photo.jpg"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        pixel.r = pixel.r - (30.0/255.0);
        pixel.g = pixel.g - (30.0/255.0);
        pixel.b = pixel.b - (30.0/255.0);
    }
    
    image.save("output/light_down.png");
}

// Disc
void disc() {
    sil::Image image{500, 500};
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-250, 2) + pow(j - 250, 2) < pow(100, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
    image.save("output/disc.png");
}

// Done
void ring(int center_x, int center_y, int rayon, sil::Image& image) {
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-center_x, 2) + pow(j - center_y, 2) < pow(rayon, 2) && pow(i-center_x, 2) + pow(j - center_y, 2) > pow(rayon - 5, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
}

// Done
void animated_disc() {
    sil::Image image{500, 500};
    for (int k = 0; k < image.width(); k=k+10)
    {
        for (float i{0}; i < image.width(); i++)
        {
            for (float j{0}; j < image.height(); j++)
            {
                if (pow(i-k, 2) + pow(j - 250, 2) < pow(100, 2))
                {
                    glm::vec3 &pixel = image.pixel(i, j);
                    pixel.r = 1;
                    pixel.g = 1;
                    pixel.b = 1;
                }
                else {
                    glm::vec3 &pixel = image.pixel(i, j);
                    pixel.r = 0;
                    pixel.g = 0;
                    pixel.b = 0;
                }
            }
            
        }
        std::string chemin = "output/animation/";
        std::string file_name = "animation.png";
        std::string string_k = std::to_string(k);
        image.save(chemin + string_k + file_name);
    }
}

// Done
void polar_rosace() {
    sil::Image image{500, 500};
    int angle = 360 / 10;
    for (int i = 0; i < 10; i++)
    {
        int true_angle = (angle * i);
        int x = cos(true_angle * (M_PI / 180 )) * 100 + 250;
        int y = sin(true_angle * (M_PI / 180 )) * 100 + 250;
        ring(x, y, 100, image);
    }
    image.save("output/rosace.png");
}

// Done
void mosaimac() {
    sil::Image image{"images/logo.png"};
    sil::Image mosaic_image = sil::Image(image.width() * 5, image.height() * 5);
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            for (float k{0}; k < 5; k++)
            {
                for (float l{0}; l < 5; l++)
                {
                    mosaic_image.pixel(i + image.width() * k, j + image.height() * l) = image.pixel(i, j);
                }
                
            }   
        }
        
    }
    mosaic_image.save("output/mosaic.png");
}

sil::Image mirror(sil::Image& image){
    sil::Image mirror_image = sil::Image(image.width(), image.height());
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            mirror_image.pixel(image.width() - i - 1, j) = image.pixel(i, j);
        }
        
    }
    return mirror_image;
}


sil::Image upside_down(sil::Image& image) {
    sil::Image upside_down_image = sil::Image(image.width(), image.height());
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            upside_down_image.pixel(i, image.height() - j - 1) = image.pixel(i, j);
        }
        
    }
    return upside_down_image;
}

// Done
void mirrored_mosaimac() {
    sil::Image image{"images/logo.png"};
    sil::Image mirror_image = mirror(image);
    sil::Image upside_down_image = upside_down(image);
    sil::Image upside_down_mirror_image = upside_down(mirror_image);
    sil::Image mosaic_image = sil::Image(image.width() * 5, image.height() * 5);
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            for (int k{0}; k < 5; k++)
            {
                for (int l{0}; l < 5; l++)
                {
                    if ( l % 2 == 0) {
                        if ( k % 2 == 0)
                        {
                            mosaic_image.pixel(i + image.width() * k, j + image.height() * l) = image.pixel(i, j);
                        }
                        else {
                            mosaic_image.pixel(i + image.width() * k, j + image.height() * l) = mirror_image.pixel(i, j);
                        }
                    } else {
                        if ( k % 2 == 0)
                        {
                            mosaic_image.pixel(i + image.width() * k, j + image.height() * l) = upside_down_image.pixel(i, j);
                        }
                        else {
                            mosaic_image.pixel(i + image.width() * k, j + image.height() * l) = upside_down_mirror_image.pixel(i, j);
                        }
                    }
                }
            }   
        }
    }
    mosaic_image.save("output/mirror_mosaic.png");
}

// Done
void glitch() {
    sil::Image image{"images/logo.png"};
    int number = rand() % 30 + 15;
    for (int i = 0; i < number; i++)
    {
        int size_x = rand() % 30 + 5;
        int size_y = rand() % 30 + 5;

        int x1 = rand() % (image.width() - size_x);
        int y1 = rand() % (image.height() - size_y);
        int x2 = rand() % (image.width() - size_x);
        int y2 = rand() % (image.height() - size_y);

        for (int x = 0; x < size_x; x++)
        {
            for (int y = 0; y < size_y; y++)
            {
                glm::vec3 tmp_pixel = image.pixel(x2 + x, y2 + y);
                image.pixel(x2 + x, y2 + y) = image.pixel(x1 + x, y1 + y);
                image.pixel(x1 + x, y1 + y) = tmp_pixel;
            }
        }
    }
    image.save("output/glitch.png");
}

// Done
void pixel_sort() {
    sil::Image image{"images/logo.png"};
    int number = 300;
    for (int i = 0; i < number; i++)
    {
        int size_x = rand() % 20 + 45 ;

        int x_begin = rand() % (image.width() - size_x);
        int y = rand() % (image.height());

        std::vector<glm::vec3> v;
        for (int x = x_begin; x < size_x + x_begin; x++)
        {
             glm::vec3& pixel = image.pixel(x, y);
             v.push_back(pixel);
        }
        std::sort(v.begin(), v.end(),  [](glm::vec3 const& color1, glm::vec3 const& color2){
            float moy = (color1.b + color1.g + color1.r) / 3;
            float moy2 = (color2.b + color2.g + color2.r) / 3;
            return moy < moy2;
        });
        for (int x = x_begin; x < size_x + x_begin; x++)
        {
             image.pixel(x, y) = v.at(x - x_begin);
        }
        
    }
    image.save("output/pixel_sort.png");
}

// Done
void mandelbrot(){
    sil::Image image{500, 500};
    for (float i{0}; i < image.width(); i++)        
    {
        for (float j{0}; j < image.height(); j++)
        {
            float x = (i / 125) - 2;
            float y = (j / 125) - 2;
            std::complex<float> c{x, y};
            std::complex<float> z = c;
            float compteur = 0;
            while (std::abs(z) < 2)
            {
                z = z * z + c;
                if (compteur == 30)
                {
                    break;
                }
                compteur++;
            }
            glm::vec3& pixel = image.pixel(i, j);
            pixel.r = compteur / 30;
            pixel.g = compteur / 30;
            pixel.b = compteur / 30;

        }           
    }
    image.save("output/mandelbrot.png");
}

glm::vec3 to_linear(glm::vec3 color) {
    if (color.r <= 0.04045)
    {
        color.r = color.r / 12.92;
    } else {
        color.r = pow((color.r + 0.055) / 1.055, 2.4);
    }
    
    if (color.g <= 0.04045)
    {
        color.g = color.g / 12.92;
    } else {
        color.g = pow((color.g + 0.055) / 1.055, 2.4);
    }

    if (color.b <= 0.04045)
    {
        color.b = color.b / 12.92;
    } else {
        color.b = pow((color.b + 0.055) / 1.055, 2.4);
    }

    return color;
}


glm::vec3 to_lab(glm::vec3 const& c) {
    glm::vec3 lab_color;
    // r est le L
    lab_color.r = 0.4122214708f * c.r + 0.5363325363f * c.g + 0.0514459929f * c.b;
    // g est le m
    lab_color.g = 0.2119034982f * c.r + 0.6806995451f * c.g + 0.1073969566f * c.b;
	// b est le s
    lab_color.b = 0.0883024619f * c.r + 0.2817188376f * c.g + 0.6299787005f * c.b;

    lab_color.r = cbrtf(lab_color.r);
    lab_color.g = cbrtf(lab_color.g);
    lab_color.b = cbrtf(lab_color.b);

    return {
        0.2104542553f*lab_color.r + 0.7936177850f*lab_color.g - 0.0040720468f*lab_color.b,
        1.9779984951f*lab_color.r - 2.4285922050f*lab_color.g + 0.4505937099f*lab_color.b,
        0.0259040371f*lab_color.r + 0.7827717662f*lab_color.g - 0.8086757660f*lab_color.b,
    };
}

glm::vec3 oklab_to_linear_(glm::vec3 c) 
{
    float l_ = c.r + 0.3963377774f * c.g + 0.2158037573f * c.b;
    float m_ = c.r - 0.1055613458f * c.g - 0.0638541728f * c.b;
    float s_ = c.r - 0.0894841775f * c.g - 1.2914855480f * c.b;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;

    return {
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

glm::vec3 linear_to_rgb(glm::vec3 color){
    if (color.r <= 0.0031308)
    {
        color.r = color.r * 12.92;
    } else {
        color.r = pow(color.r, 1/2.4) * 1.055 - 0.055;
    }
    
    if (color.g <= 0.0031308)
    {
        color.g = color.g * 12.92;
    } else {
        color.g = pow(color.g, 1/2.4) * 1.055 - 0.055;
    }

    if (color.b <= 0.0031308)
    {
        color.b = color.b * 12.92;
    } else {
        color.b = pow(color.b, 1/2.4) * 1.055 - 0.055;
    }

    return color;
}

// Done
void color_buzz_cut() {
    sil::Image image{"images/logo.png"};

    glm::vec3 color1_lab = to_lab(to_linear(glm::vec3{1, 0, 0}));
    glm::vec3 color2_lab = to_lab(to_linear(glm::vec3{0, 1, 0}));

    for (float i{0}; i < image.width(); i++)
    {
        float percentage1 = (image.width() - i) /   image.width();
        float percentage2 = i / image.width();
        glm::vec3 new_lab_color = percentage1 * color1_lab + percentage2 * color2_lab;
        glm::vec3 new_color = linear_to_rgb(oklab_to_linear_(new_lab_color));
        for (float j{0}; j < image.height(); j++)
        {
            image.pixel(i, j) = new_color;
        }
        
    }
    
    
    image.save("output/color_buzz_cut.png");
}

// Done
sil::Image basic_convolution(int blur_size) {
    sil::Image image{"images/logo.png"};
    sil::Image blurred_image = { image.width(), image.height()};
    for (float x{0}; x < image.width(); x++)        
    {
        for (float y{0}; y < image.height(); y++)
        { 
            std::vector<glm::vec3> v;
            for (int i = -1 * blur_size; i < blur_size + 1; i++)
            {
                for (int j = -1 * blur_size; j < blur_size + 1; j++)
                {
                    if (x + i >= 0 && x + i < image.width() && y + j >= 0 && y + j < image.height())
                    {
                        v.push_back(image.pixel(x + i, y + j));
                    }
                    else{
                        v.push_back(glm::vec3(0.));
                    }
                }
            }
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            for (glm::vec3 pixel : v)
            {
                sum_red = sum_red + pixel.r;
                sum_green = sum_green + pixel.g;
                sum_blue = sum_blue + pixel.b;
            }
            float moy_red = sum_red / v.size();
            float moy_green = sum_green / v.size();
            float moy_blue = sum_blue / v.size();
            glm::vec3 newColor = {moy_red, moy_green, moy_blue};
            blurred_image.pixel(x, y) = newColor;
        }
    }
    return blurred_image;
}

// Done
void matrix_convolution() {
    sil::Image image{"images/logo.png"};
    sil::Image sharpened_image = { image.width(), image.height()};
    int blur_size = 1;
    std::vector<int> matrix = {
         -1, -1,  -1,
         -1,  8, -1,
         -1,  -1,  -1};
    for (float x{0}; x < image.width(); x++)        
    {
        for (float y{0}; y < image.height(); y++)
        { 
            std::vector<glm::vec3> v;
            for (int i = -1 * blur_size; i < blur_size + 1; i++)
            {
                for (int j = -1 * blur_size; j < blur_size + 1; j++)
                {
                    if (x + i >= 0 && x + i < image.width() && y + j >= 0 && y + j < image.height())
                    {
                        v.push_back(image.pixel(x + i, y + j));
                    }
                    else{
                        v.push_back(glm::vec3(0.));
                    }
                }
            }
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            for (int i = 0; i < v.size(); i++)
            {
                sum_red = sum_red + v.at(i).r * matrix.at(i);
                sum_green = sum_green + v.at(i).g * matrix.at(i);
                sum_blue = sum_blue + v.at(i).b * matrix.at(i);
            }
            glm::vec3 newColor = {sum_red, sum_green, sum_blue};
            sharpened_image.pixel(x, y) = newColor;
        }
    }
    sharpened_image.save("output/matrix_outline.png");
}

// Done
sil::Image box_blur_convolution(int blur_size) {
    sil::Image image{"images/logo.png"};
    sil::Image tmp_image = { image.width(), image.height()};
    sil::Image final_image = { image.width(), image.height()};
    for (float x{0}; x < image.width(); x++)        
    {
        for (float y{0}; y < image.height(); y++)
        { 
            std::vector<glm::vec3> v;
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            int compteur = 0;
            for (int i = -1 * blur_size; i < blur_size + 1; i++)
            {
                if (x + i >= 0 && x + i < image.width())
                {
                    sum_red = sum_red + image.pixel(x + i, y).r;
                    sum_green = sum_green + image.pixel(x + i, y).g;
                    sum_blue = sum_blue + image.pixel(x + i, y).b;
                }
                else{
                    sum_red = sum_red + 0;
                    sum_green = sum_green + 0;
                    sum_blue = sum_blue + 0;
                }
                compteur++;
            }
            glm::vec3 newColor = {sum_red / compteur, sum_green / compteur, sum_blue / compteur};
            tmp_image.pixel(x, y) = newColor;
        }
    }

    for (float x{0}; x < image.width(); x++)        
    {
        for (float y{0}; y < image.height(); y++)
        { 
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            int compteur = 0;
            for (int i = -1 * blur_size; i < blur_size + 1; i++)
            {
                if (y + i >= 0 && y + i < image.height())
                {
                    sum_red = sum_red + tmp_image.pixel(x, y + i).r;
                    sum_green = sum_green + tmp_image.pixel(x, y + i).g;
                    sum_blue = sum_blue + tmp_image.pixel(x, y + i).b;
                }
                else{
                    sum_red = sum_red + 0;
                    sum_green = sum_green + 0;
                    sum_blue = sum_blue + 0;
                }
                compteur++;
            }
            glm::vec3 newColor = {sum_red / compteur, sum_green / compteur, sum_blue / compteur};
            final_image.pixel(x, y) = newColor;
        }
    }
    return final_image;
}

// Done
void gauss_diff(){
    sil::Image image{"images/logo.png"};
    sil::Image image1 = basic_convolution(1);
    sil::Image image2 = box_blur_convolution(3);

    for (float x{0}; x < image1.width(); x++)        
    {
        for (float y{0}; y < image1.height(); y++)
        { 
            image.pixel(x, y) = image1.pixel(x, y) - image2.pixel(x, y);
        }
    }
    image.save("output/gauss_diff.png");
}

// Done
void normalize() {
    sil::Image image{"images/photo_faible_contraste.jpg"};
    glm::vec3 brightest = image.pixel(0,0);
    glm::vec3 darkest = image.pixel(0,0);
    for (glm::vec3 pixel : image.pixels())
    {
        if (pixel.r + pixel.g + pixel.b > brightest.r + brightest.g + brightest.b)
        {
            brightest = pixel;
        } else if (pixel.r + pixel.g + pixel.b < darkest.r + darkest.g + darkest.b) {
            darkest = pixel;
        }
    }
    float moy_light = (brightest.r + brightest.g + brightest.b) / 3;
    float moy_dark = (darkest.r + darkest.g + darkest.b) / 3;
    for (float x{0}; x < image.width(); x++)        
    {
        for (float y{0}; y < image.height(); y++)
        {
                image.pixel(x,y).r = (image.pixel(x, y).r - moy_dark) / (moy_light - moy_dark) ;
                image.pixel(x,y).g = (image.pixel(x, y).g - moy_dark) / (moy_light - moy_dark);
                image.pixel(x,y).b = (image.pixel(x, y).b - moy_dark) / (moy_light - moy_dark);
            
        }
    }
    image.save("output/normalize.png");
}

// Done
void dithering() {
    sil::Image image{"images/photo.jpg"};
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {   -0.5,       0,  -0.375,   0.125},
        {   0.25,   -0.25,   0.375,  -0.125},
        {-0.3125,  0.1875, -0.4375,  0.0625},
        { 0.4375, -0.0625,  0.3125, -0.1875},
    };
    for (int x{0}; x < image.width(); x++)        
    {
        for (int y{0}; y < image.height(); y++)
        {
            float color_base = (image.pixel(x, y).r + image.pixel(x, y).g + image.pixel(x, y).b) /3;
            float bayer_value = bayer_matrix_4x4[y % bayer_n][x % bayer_n];
            float output_color = color_base + bayer_value;
            if (output_color > 0.5)
            {
                image.pixel(x, y) = glm::vec3{1.};
            } else {
                image.pixel(x, y) = glm::vec3{0.};
            }
            
        }
    }
    image.save("output/dithering.png");
}

// Done
void k_means(int k){
    sil::Image image{"images/photo.jpg"};
    sil::Image k_proximity = {image.width(), image.height()};
    glm::vec3 k_means[k];
    for (int i = 0; i < k; i++)
    {
        float random_r = random_float(0, 1);
        float random_g = random_float(0, 1);
        float random_b = random_float(0, 1);
        k_means[i] = glm::vec3{random_r, random_g, random_b};
    }
    for (int j = 0; j < 10; j++)
    {
        for (int x{0}; x < image.width(); x++)        
        {
            for (int y{0}; y < image.height(); y++)
            {
                glm::vec3 closest = k_means[0];
                float closest_mean = 10.0;
                for (glm::vec3 color : k_means) {
                    float dist = glm::distance(color, image.pixel(x, y));
                    if(dist < closest_mean) {
                        closest = color;
                        closest_mean = dist;
                    }
                }
                k_proximity.pixel(x, y) = closest; 
            }
        }

    // k_proximity.save("output/pouet.png");

        for (int i = 0; i < k; i++)
        {
            float new_k_red = 0;
            float new_k_green = 0;
            float new_k_blue = 0;
            int compteur = 0;
            for (int x{0}; x < image.width(); x++)        
            {
                for (int y{0}; y < image.height(); y++)
                {
                    if (k_proximity.pixel(x, y) == k_means[i])
                    {
                        new_k_red = new_k_red + image.pixel(x, y).r;
                        new_k_green = new_k_green + image.pixel(x, y).g;
                        new_k_blue = new_k_blue + image.pixel(x, y).b;
                        compteur++;
                    }
                    
                }
            }
            k_means[i] = glm::vec3{new_k_red / compteur, new_k_green/ compteur, new_k_blue/ compteur};
        }
    }
    
    for (int x{0}; x < image.width(); x++)        
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = k_proximity.pixel(x, y);                
        }
    }
    image.save("output/k_means.png");
}

double standardDeviation(const std::vector<glm::vec3>& arr)
{
    glm::vec3 mean, sum = {0, 0, 0};
    float standardDeviation = 0.0;

    int size = arr.size();

    // Calculate the sum of elements in the vector
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }

    // Calculate the mean
    mean.r = sum.r / size;
    mean.g = sum.g / size;
    mean.b = sum.b / size;

    // Calculate the sum of squared differences from the
    // mean
    for (int i = 0; i < size; ++i) {
        standardDeviation += pow(glm::distance(arr[i], mean), 2);
    }

    // Calculate the square root of the variance to get the
    // standard deviation
    return sqrt(standardDeviation / size);
}

// Done
void kuwahara(int kuwahara_size) {
    sil::Image image{"images/photo.jpg"};
    sil::Image kuwahara_image = {image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)        
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::vector<glm::vec3> up_left;
            std::vector<glm::vec3> up_righ;
            std::vector<glm::vec3> down_left;
            std::vector<glm::vec3> down_right;
            float up_left_number = 0;
            float up_righ_number = 0;
            float down_left_number = 0;
            float down_right_number = 0;
            for (int i = -1 * kuwahara_size; i < kuwahara_size + 1; i++)
            {
                for (int j = -1 * kuwahara_size; j < kuwahara_size + 1; j++)
                {
                    if ( i < 0 && j < 0 && x + i >= 0 && x + i < image.width() && y + j >= 0 && y + j < image.height())
                    {
                        up_left.push_back(image.pixel(x + i, y + j));
                        up_left_number++;
                    } else if (i < 0 && j > 0 && x + i >= 0 && x + i < image.width() && y + j >= 0 && y + j < image.height()) {
                        up_righ.push_back(image.pixel(x + i, y + j));
                        up_righ_number++;
                    } else if (i > 0 && j > 0 && x + i >= 0 && x + i < image.width() && y + j >= 0 && y + j < image.height()) {
                        down_left.push_back(image.pixel(x + i, y + j));
                        down_left_number++;
                    } else if (i > 0 && j < 0 && x + i >= 0 && x + i < image.width() && y + j >= 0 && y + j < image.height()) {
                        down_right.push_back(image.pixel(x + i, y + j));
                        down_right_number++;
                    }
                }
            }

            if (standardDeviation(up_left) < standardDeviation(up_righ) 
        && standardDeviation(up_left) < standardDeviation(down_left)
        && standardDeviation(up_left) < standardDeviation(down_right))
            {
                glm::vec3 moyenne = {0, 0, 0};
                for(glm::vec3 v : up_left) {
                    moyenne = moyenne + v;
                }
                moyenne.r = moyenne.r / up_left.size();
                moyenne.g = moyenne.g / up_left.size();
                moyenne.b = moyenne.b / up_left.size();
                kuwahara_image.pixel(x, y) = moyenne;
            } else if (standardDeviation(up_righ) < standardDeviation(up_left) 
        && standardDeviation(up_righ) < standardDeviation(down_left)
        && standardDeviation(up_righ) < standardDeviation(down_right))
            {
                glm::vec3 moyenne = {0, 0, 0};
                for(glm::vec3 v : up_righ) {
                    moyenne = moyenne + v;
                }
                moyenne.r = moyenne.r / up_righ.size();
                moyenne.g = moyenne.g / up_righ.size();
                moyenne.b = moyenne.b / up_righ.size();
                kuwahara_image.pixel(x, y) = moyenne;
            } else if (standardDeviation(down_left) < standardDeviation(up_righ) 
        && standardDeviation(down_left) < standardDeviation(up_left)
        && standardDeviation(down_left) < standardDeviation(down_right))
            {
                glm::vec3 moyenne = {0, 0, 0};
                for(glm::vec3 v : down_left) {
                    moyenne = moyenne + v;
                }
                moyenne.r = moyenne.r / down_left.size();
                moyenne.g = moyenne.g / down_left.size();
                moyenne.b = moyenne.b / down_left.size();
                kuwahara_image.pixel(x, y) = moyenne;
            } else {
                glm::vec3 moyenne = {0, 0, 0};
                for(glm::vec3 v : down_right) {
                    moyenne = moyenne + v;
                }
                moyenne.r = moyenne.r / down_right.size();
                moyenne.g = moyenne.g / down_right.size();
                moyenne.b = moyenne.b / down_right.size();
                kuwahara_image.pixel(x, y) = moyenne;
            }
        }
    }
    kuwahara_image.save("output/kuwahara.png");
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

// Done
void vortex() {
    sil::Image image{"images/logo.png"};
    sil::Image vortexed_image = {image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)        
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 positions = rotated({x, y}, {image.width() / 2, image.height() / 2}, -0.1 * glm::distance(glm::vec2{x, y}, glm::vec2{image.width() / 2, image.height() / 2}));
            if (positions.x >= 0 && positions.x < image.width() && positions.y >= 0 && positions.y < image.height())
            {
                vortexed_image.pixel(x, y) = image.pixel(positions.x, positions.y);
            }
        }
    }
    vortexed_image.save("output/vortex.png");
}


int main()
{
    sil::Image image{"images/logo.png"};
    sil::Image image2 = mirror(image);
    image2.save("output/mirror.png");
} 