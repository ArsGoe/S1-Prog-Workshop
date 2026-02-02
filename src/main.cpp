#include <iostream>
#include <cstdlib>
#include <sil/sil.hpp>
#include <cmath>

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

void mirror(){
    sil::Image image{"images/logo.png"};
    sil::Image mirror_image = sil::Image(image.width(), image.height());
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            mirror_image.pixel(image.width() - i - 1, j) = image.pixel(i, j);
        }
        
    }
    mirror_image.save("output/pouet.png");
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

void ring() {
    sil::Image image{500, 500};
    for (float i{0}; i < image.width(); i++)
    {
        for (float j{0}; j < image.height(); j++)
        {
            if (pow(i-250, 2) + pow(j - 250, 2) < pow(100, 2) && pow(i-250, 2) + pow(j - 250, 2) > pow(90, 2))
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

int main()
{
    rosace();
} 