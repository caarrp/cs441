#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void make_pixel(unsigned char pixel_array[], unsigned char pixel[]);

int main(){
	FILE *file = fopen("proj1A_out.pnm", "wb");
	
	int width = 300;
	int height = 300;
	//unsigned char str_1[15] = "P6\n300 300\n255\n";
	//fwrite(str_1, sizeof(unsigned char), strlen(str_1), file);
	fprintf(file, "P6\n%d %d\n255\n", width, height);

	unsigned char black[3] = {0, 0, 0};
	unsigned char gray[3] = {128, 128, 128};
	unsigned char white[3] = {255, 255, 255};
	unsigned char red[3] = {255, 0, 0};
	unsigned char green[3] = {0, 255, 0};
	unsigned char blue[3] = {0, 0, 255};
	unsigned char pink[3] = {255, 0, 255};
	unsigned char cyan[3] = {0, 255, 255};
	unsigned char yellow[3] = {255, 255, 0};

	int thirds = width/3;

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			
			unsigned char *pixel = malloc(20);

			if(i < thirds && j < thirds) { 
			    //make_pixel(black, pixel);
			    fwrite(black, 1, 3, file);
			}

			else if (j < 2*thirds && i < thirds) {
			    //make_pixel(gray, pixel);
			    fwrite(gray, 1, 3, file);
			}

			else if (i < thirds) {
			   // make_pixel(white, pixel);
			    fwrite(white, 1, 3, file);
			}
			
			else if (i < 2*thirds && j < thirds) { 
			    //make_pixel(red, pixel);
			    fwrite(red, 1, 3, file);}

			else if (i < 2*thirds && j < 2*thirds) {
			    //make_pixel(green, pixel);
			    fwrite(green, 1, 3, file);}

			else if (i < 2*thirds) { 
			    //make_pixel(blue, pixel);
			    fwrite(blue, 1, 3, file);}   
			else if (j < thirds) { 
			    //make_pixel(pink, pixel);
			    fwrite(pink, 1, 3, file);}
			else if (j < 2*thirds) { 
			    //make_pixel(cyan, pixel);
			    fwrite(cyan, 1, 3, file);}
			else { 
			    //make_pixel(yellow, pixel);
			    fwrite(yellow, 1, 3, file);}


			//fwrite(pixel, sizeof(unsigned char), 3, file);
			free(pixel);
		}
	}

	//char *str_2 = '\0';
	//fwrite(str_2, sizeof(char), strlen(str_2), file);


	fclose(file);

}

void make_pixel(unsigned char pixel_array[], unsigned char pixel[]){
	//for formatting
    sprintf((char*)pixel, "%c %c %c", pixel_array[0], pixel_array[1], pixel_array[2]);
}
