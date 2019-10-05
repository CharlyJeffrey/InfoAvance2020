/*

*/

#include "Image.h"

// Default constructor
Image::Image() {}

// Constructor with specified width/height
Image::Image(int w, int h, int d) {
    width = w;
    height = h;
    depth = d;
    // Allocate memory
    arr = (int ***) malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++) {
        arr[i] = (int **) malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++) {
            arr[i][j] = (int *) malloc(d * sizeof(int));
        }
    }
    // *Optionnal* | Shouldn't be necessary
    if (arr == nullptr) printf("Memory allocation failed.\n");
    // *Not Optionnal* 
    else {
        // Initialize the array to {0}
        for (int i = 0; i < h; i++) 
            for (int j = 0; j < w; j++)
                for (int k = 0; k < d; k++) arr[i][j][k] = 0;
    }
}


/* Getters */
int Image::GetWidth() {return width;}
int Image::GetHeight() {return height;}
int *** Image::GetArray() {return arr;}

/* Setters */
void Image::SetPixelAt(int i, int j, int val) {arr[j][i][0] = val;}
void Image::SetPixelAt(int i, int j, RGB * pixel) {
    arr[j][i][0] = pixel->r;
    arr[j][i][1] = pixel->g;
    arr[j][i][2] = pixel->b;
}

// Method to save the array as an image using 'P2' encoding.
void Image::SaveAs(string file_name) {
    // "Construct" an ofstream object to store the image.
    ofstream img(file_name);
    // P2 Encoding
    img << "P2\n";
    // Image resolution
    img << width << " " << height << endl;
    // Normalization value
    img << 255 << endl;
    // Fill image
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) img << arr[j][i][0] << " ";
        img << endl;
    }
}

void Image::SaveAsRGB(string file_name, int normal) {
    // "Construct" an ofstream object to store the image.
    ofstream img(file_name);
    // P3 Encoding
    img << "P3\n";
    // Image resolution
    img << width << " " << height << endl;
    // Normalization value
    img << normal << endl;
    // Fill image
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            img << arr[j][i][0] << " " << arr[j][i][1] << " " << arr[j][i][2] << " ";
        }
        img << endl;
    }
}

void Image::SaveAsGSV(string file_name, int normal) {
    // Construct an ofstream object to store the image
    ofstream img(file_name);
    // P2 encodint
    img << "P2\n";
    // Image resolution
    img << width << " " << height << endl;
    // Normalisation value
    img << normal << endl;
    // Mean value
    int mean;
    // Fill the image
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            // Mean value
            mean = (int) (1.0*(arr[j][i][0]+arr[j][i][1]+arr[j][i][2])/depth);
            img << mean << " ";
        }
        img << endl;
    }
}