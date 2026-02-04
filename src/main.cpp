#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <sil/sil.hpp>
#include <cmath>
#include <complex>

void clean_image() {
    sil::Image image{"images/photo.jpg"};
    
    image.save("output/pouet.png");
}


void make_green() {
    sil::Image image{"images/logo.png"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        pixel.r = 0;
        pixel.b = 0;
    }
    
    image.save("output/pouet.png");
}

void shuffle_channels() {
    sil::Image image{"images/logo.png"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        float tmp_g = pixel.g;

        pixel.g = pixel.r;
        pixel.r = pixel.b;
        pixel.b = tmp_g;
    }
    
    image.save("output/pouet.png");
}

void to_black_and_white(){
    sil::Image image{"images/logo.png"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        float moy = (pixel.b + pixel.g + pixel.r) / 3;
        pixel.b = moy;
        pixel.r = moy;
        pixel.g = moy;
    }
    
    image.save("output/pouet.png");
}

void to_negative(){
    sil::Image image{"images/logo.png"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        pixel.b = 1 - pixel.b;
        pixel.r = 1 - pixel.r;
        pixel.g = 1 - pixel.g;
    }
    
    image.save("output/pouet.png");
}

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
    
    
    image.save("output/pouet.png");
}


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
    image.save("output/pouet.png");
}

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

    
    rotated_image.save("output/pouet.png");
}

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
    split_rgb_image.save("output/pouet.png");
}

void light_up(){
    sil::Image image{"images/photo.jpg"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        pixel.r = pixel.r + (30.0/255.0);
        pixel.g = pixel.g + (30.0/255.0);
        pixel.b = pixel.b + (30.0/255.0);
    }
    
    image.save("output/pouet.png");
}

void light_down(){
    sil::Image image{"images/photo.jpg"};
    for ( glm::vec3 &pixel : image.pixels())
    {
        pixel.r = pixel.r - (30.0/255.0);
        pixel.g = pixel.g - (30.0/255.0);
        pixel.b = pixel.b - (30.0/255.0);
    }
    
    image.save("output/pouet.png");
}

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
    image.save("output/pouet.png");
}

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
        image.save("output/pouet.png");
    }
}

void rosace() {
    sil::Image image{500, 500};
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-250, 2) + pow(j - 250, 2) < pow(100, 2) && pow(i-250, 2) + pow(j - 250, 2) > pow(95, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
    image.save("output/pouet.png");
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-152, 2) + pow(j - 250, 2) < pow(100, 2) && pow(i - 152, 2) + pow(j - 250, 2) > pow(95, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
    image.save("output/pouet.png");
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-348, 2) + pow(j - 250, 2) < pow(100, 2) && pow(i - 348, 2) + pow(j - 250, 2) > pow(95, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
    image.save("output/pouet.png");

    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-299, 2) + pow(j - 165, 2) < pow(100, 2) && pow(i - 299, 2) + pow(j - 165, 2) > pow(95, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
    image.save("output/pouet.png");
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-299, 2) + pow(j - 335, 2) < pow(100, 2) && pow(i - 299, 2) + pow(j - 335, 2) > pow(95, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
    image.save("output/pouet.png");

    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-201, 2) + pow(j - 165, 2) < pow(100, 2) && pow(i - 200, 2) + pow(j - 165, 2) > pow(95, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
    image.save("output/pouet.png");
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-201, 2) + pow(j - 335, 2) < pow(100, 2) && pow(i - 200, 2) + pow(j - 335, 2) > pow(95, 2))
            {
                glm::vec3 &pixel = image.pixel(i, j);
                pixel.r = 1;
                pixel.g = 1;
                pixel.b = 1;
            }
            
        }
        
    }
    image.save("output/pouet.png");
}

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
    image.save("output/pouet.png");
}

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
    mosaic_image.save("output/pouet.png");
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
    mosaic_image.save("output/pouet.png");
}

void glitch() {
    sil::Image image{"images/logo.png"};
    int number = rand() % 30 + 15;
    std::cout << number << std::endl;
    for (int i = 0; i < number; i++)
    {
        std::cout << i << std::endl;
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
    image.save("output/pouet.png");
}

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
    image.save("output/pouet.png");
}

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
    image.save("output/pouet.png");
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
    
    
    image.save("output/pouet.png");
}

int main()
{
    mandelbrot();
} 