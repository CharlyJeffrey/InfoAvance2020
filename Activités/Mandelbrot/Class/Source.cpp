#include <math.h>
#include "Image.cpp"

// Resolution:
// 1k: 1080 x 720
// 2k: 2048 x 1080
// 4k: 3840 x 2160
#define WIDTH 3840
#define HEIGHT 2160
#define RATIO ((1.0*WIDTH)/HEIGHT)
// Mandelbrot iteration
#define MAX_ITER 1024
#define MAX_NORM 4.0
// Normalisation value
#define NORMAL_VAL 255

using namespace std;

double func(int);
int mandelbrot(double, double);
void HSVtoRGB(HSV*, RGB*);

int main() {
    // Files name
    string GSV_file_name = "GSV_1.ppm";
    string RGB_file_name = "RGB_1.ppm";
    // Centered at
    double cx =  0.0;
    double cy =  0.0;
    // Zoom
    double zoom = 1.0;
    // Range and aspect ratio
    double x_range = 2.0 / zoom;
    double y_range = x_range / RATIO;
    // Creates an Image object
    Image Img = Image(WIDTH, HEIGHT, 3);
    // Fills the image
    int val;
    double x, y;
    RGB RGBpixel;
    HSV HSVpixel;
    // Initialize HSV pixel
    HSVpixel.s = 1.0;
    HSVpixel.v = 1.0;

    for (int j = 0; j < HEIGHT; j++) {
        // Map from pixel space to real space
        y = cy + (1.0 - ((2.0 * j)/HEIGHT)) * y_range;
        for (int i = 0; i < WIDTH; i++) {
            // Map from pixel space to real space
            x = cx + (((2.0 * i)/WIDTH) - 1.0) * x_range;
            // Get value from Mandelbrot recursion
            val = mandelbrot(x, y);
            // Color the pixel depending on the case
            if (val != 0) {
                HSVpixel.h = func(val) * 360.0;
                HSVtoRGB(&HSVpixel, &RGBpixel);
            } else {
                RGBpixel.r = 0;
                RGBpixel.g = 0;
                RGBpixel.b = 0;
            }
            // Update pixel
            Img.SetPixelAt(i, j, &RGBpixel);
        }
        //cout << endl;
    }

    // Saves Images
    Img.SaveAsRGB(RGB_file_name, NORMAL_VAL);
    Img.SaveAsGSV(GSV_file_name, NORMAL_VAL);
    return 0;
}

// TODO:
double func(int val) {
    double _val;
    //_val = ((double) val) / MAX_ITER;
    //_val = 1.0 - cbrt((1.0 * val) / (1.0 * MAX_ITER));
    _val = sqrt((1.0 * val) / MAX_ITER);
    //_val = 1.0 - sqrt(sqrt((1.0 * val) / MAX_ITER));
    //_val = (1.0 * val*val) / (1.0 * MAX_ITER*MAX_ITER);
    return _val;    
}

// TODO:
int mandelbrot(double x, double y) {
    // Complex number C
    double cx = x;
    double cy = y;
    // Initial values of Z
    double zx = 0.0;
    double zy = 0.0;
    // Real part
    double re = 0.0;
    // Imaginary part
    double im = 0.0;
    // Iterative loop
    int iter = 1;
    while (iter < MAX_ITER) {
        // Real part Z
        re = zx*zx - zy*zy + cx;
        // Imaginary part of Z
        im = 2*zx*zy + cy;
        // Norm condition
        if (re*re + im*im >= MAX_NORM) return iter;
        // Update Z
        zx = re;
        zy = im;
    
        iter++;
    }
    return 0;
}


void HSVtoRGB(HSV * hsv, RGB * pixel) {
    // Get HSV values
    double H = hsv->h;
    double S = hsv->s;
    double V = hsv->v;
    // Some shit
	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if(H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;	
	}
	else if(H >= 60 && H < 120) {	
		Rs = X;
		Gs = C;
		Bs = 0;	
	}
	else if(H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;	
	}
	else if(H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;	
	}
	else if(H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;	
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;	
	}
	// Update RGB pixel values
	pixel->r = (Rs + m) * NORMAL_VAL;
	pixel->g = (Gs + m) * NORMAL_VAL;
	pixel->b = (Bs + m) * NORMAL_VAL;
}