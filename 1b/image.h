#include <iostream>

class Pixel{
public:
    unsigned char r, g, b;

    Pixel() : r(0), g(0), b(0) {}

    Pixel(unsigned char red, unsigned char green, unsigned char blue)
	: r(red), g(green), b(blue) {}
};

class Image{
public:
    Image();
    ~Image();
    void setSize(int w, int h);
    void write(const char *filename);
    void setPixels(int row, int col, Pixel &p);

private:
    int width, height;
    Pixel *pixels;	   
};


Image::Image(){
     width = height = 0;
     pixels = NULL;
 }

Image::~Image(){
     if (pixels != NULL){
         delete [] pixels;
     }
 }

void Image::setSize(int w, int h){
     width = w;
     height = h;
     pixels = new Pixel[width*height];
 }

void Image::write(const char *filename){
     FILE *f = fopen(filename, "wb");

     fprintf(f, "P6\n%d %d\n255\n", width, height);
     fwrite(pixels, 3*width*height, sizeof(unsigned char), f);
     fclose(f);
  }

void Image::setPixels(int row, int col, Pixel &p){
     int idx = row*width+col;
     // a good thing to keep in mind
     pixels[idx].r = p.r;
     pixels[idx].g = p.g;
     pixels[idx].b = p.b;
 }


