#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <initializer_list>
#include <cstdlib>

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
    // for (int i = 0; i < w*h; i++){
 }

void Image::write(const char *filename){
     FILE *f = fopen(filename, "wb");

     fprintf(f, "P6\n%d %d\n255\n", width, height);
     fwrite(pixels, 3*width*height, sizeof(unsigned char), f);
     fclose(f);
  }

void Image::setPixels(int row, int col, Pixel &p){
    if (row < 0 || row >= height || col < 0 || col >= width) {
        return;}  
     int idx = row*width+col;
     // a good thing to keep in mind
     pixels[idx].r = p.r;
     pixels[idx].g = p.g;
     pixels[idx].b = p.b;
 }


using namespace std;


double C441(double f){
    return ceil(f-0.00001);
}

double F441(double f){
    return floor(f+0.00001);
}

class Triangle{
public:
    double	    x[3];
    double	    y[3];
    unsigned char color[3];
    
    void print(int idx){

    cout << "triangle " << idx << endl;
    cout<<x[0] << " " <<y[0] << endl;
    cout<< x[1] << " " << y[1] << endl;
    cout<< x[2] << " " << y[2] << endl;

    }

    int topv(){
	
	double p0 = y[0]; double p1 = y[1]; double p2 = y[2];
	double max  = std::max({p0, p1, p2});
	
	if(max == p1) return 1;
	else if(max == p2) return 2;
	else return 0;
    }

    int lleftv(){
	//im checking for lowestval != top idx => idx
	int top_idx = this->topv();
	
	double p0 = x[0]; double p1 = x[1]; double p2 = x[2];
	
	if (top_idx == 0){
	    return (p1 < p2) ? 1 : 2;}
	    //if p1 is less than p2 return 1, otherwise return 2
	else if (top_idx == 1){
	    return (p0 < p2) ? 0 : 2;}
	else{//idx 2
	    return (p1 < p0) ? 1 : 0;} 
    }

    int lrightv(){
	//not top, not lower left=> idx
	return 3 - this->topv() - this->lleftv();
    }//this does mean these have to happen sequentially thoh
};



class TriangleList{
public:
    int numTriangles;
    Triangle *triangles;
};

TriangleList *GetTriangles();

void RasterizeGoingUpTriangle(Triangle* t, Image &img){
    //maybe i over defined some things here
    //cout << "in rasterize" << endl;
    int top_idx = t->topv();
    int left_idx = t->lleftv();
    int right_idx = t->lrightv();
    //cout << top_idx << right_idx << left_idx << endl;

    double top_x = t->x[top_idx]; double top_y = t->y[top_idx];
    double left_x = t->x[left_idx]; double left_y = t->y[left_idx];
    double right_x = t->x[right_idx]; double right_y = t->y[right_idx];

    double left_slope = (top_x - left_x) / (top_y - left_y);
    double right_slope = (top_x - right_x) / (top_y - right_y);
    //cout << left_slope << " and " << right_slope << endl;
    
    double row_min = C441(left_y);
    double row_max = F441(top_y);

    double left_intercept = top_x;
    double right_intercept = top_x;

    // cout << "Row range: " << row_min << " to " << row_max << endl;
    Pixel color(t->color[0], t->color[1], t->color[2]);

    for (int r = row_min; r <= row_max; r++){
	
	//if ( r <= top_y){
	    left_intercept = top_x + left_slope * (r-top_y);
	    right_intercept = top_x + right_slope * (r-top_y);
	//}

	//else{continue;}
	int left_end = C441(left_intercept);    
        int right_end = F441(right_intercept);  
	//cout << "Row " << r << ": " << left_end << " to " << right_end << endl;
	for (int c = left_end; c <= right_end; c++){
	    img.setPixels(1000 - r - 1, c, color);
	   // cout << "coloring pixel "<< r << " " << c << endl;
    }}
}


int main(){

   Image image;
   //int r = 1000; int c = 1000;
   image.setSize(1000, 1000);
    
   TriangleList *t = GetTriangles();
	    	    
    // some useful code that goes in your main loop:
    for (int i = 0 ; i < t->numTriangles ; i++)
	    RasterizeGoingUpTriangle(t->triangles+i, image);
    //for (int i = 0 ; i < 1 ; i++)
//	    RasterizeGoingUpTriangle(t->triangles+i, image);
    
   image.write("proj1B_out.pnm");

}

//rasterizeGoingUpTriangle(t1->triangles+i, &image);
//rasterizeGoingDownTriangle(t1->triangle+i, &image);



TriangleList *GetTriangles(void){
    //cout<< " in get triangles " << endl;
    TriangleList *tl = (TriangleList *) malloc(sizeof(TriangleList));
    tl->numTriangles = 100;
    tl->triangles = (Triangle *) malloc(sizeof(Triangle)*tl->numTriangles);
    
    unsigned char colors[6][3] = { {255,128,0}, {255, 0, 127}, {0,204,204},
    {76,153,0}, {255, 204, 204}, {204, 204, 0}};
    
    for (int i = 0 ; i < 100 ; i++){
	int idxI = i%10;
	int posI = idxI*100;
	int idxJ = i/10;
	int posJ = idxJ*100;
	int firstPt = (i%3);
	tl->triangles[i].x[firstPt] = posI;
	//cout << idxI << " " << idxJ << endl;				

	if (i == 50)
	    tl->triangles[i].x[firstPt] = -10;
	    tl->triangles[i].y[firstPt] = posJ+10*(idxJ+1);
	    tl->triangles[i].x[(firstPt+1)%3] = posI+105;
	    tl->triangles[i].y[(firstPt+1)%3] = posJ;
	    tl->triangles[i].x[(firstPt+2)%3] = posI+i;
	    tl->triangles[i].y[(firstPt+2)%3] = posJ;
	
	if (i == 95)
	    tl->triangles[i].y[firstPt] = 1050;
	    tl->triangles[i].color[0] = colors[i%6][0];
	    tl->triangles[i].color[1] = colors[i%6][1];
	    tl->triangles[i].color[2] = colors[i%6][2];
	}

 	return tl;   
}

