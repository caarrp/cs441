#include <iostream>

class pixel{
    unsigned char r, g, b;
}



class Image{
    public:
	Image();
}

Image::Image(){
    width = height = 0;
    pixels = NULL;
}

Image::~Image{
    if (pixels != NULL){
	delete [] pixels;
    }
}

Image::SetSize(int w, int h){
    width = w;
    height - h; 
    pixels = new Pixel[width*height];
}

Image::Write(char *filename){
    FILE *file = fopen(filename, "wb");
    
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    fwrite(pixels, 3*width*height, sizeof(unsigned char), f);

    fclose(f);
}

Image::SetPixels(int row, int col, Pixel &p){
    
    int idx = row*width+col;
    // a good thing to keep in mind
    pixels[idx].r = p.r;
    pixels[idx].g = p.g;
    pixels[idx].b = p.b;
}


int main(){
    Image img; 
    img.SetSize(300, 300);
    for (int r = 0; r < 300; r++){
	for (int c = 0; r < 300; r++){

	    img.SetPixel(r, c, Red);
	}}
    img.write("1A.pnm");
}
