/* 
Extra:
    * Mandelbrot en utilisant un produit scalaire
*/

#include <stdio.h>  
#include <stdlib.h> 
#include <fstream>
#include <iostream>
#include <string>

#include "Outils.cpp"


// Resolution:
//> 1080 x 720
//> 2048 x 1080
//> 3840 x 2160
#define DEPTH 3
#define WIDTH 3840
#define HEIGHT 2160
// Aspect ratio
#define RATIO ((1.0*WIDTH)/HEIGHT)
// Valeur de normalisation pixel
#define NORMALIZATION_VALUE 255

// Mandelbrot variables
#define MAX_ITER 1024
#define MAX_NORM 4.0
#define ZOOM 1024.0

// MISC
#define W 0.1

using namespace std;


/* Fonction pour la récursion de Mandelbrot */
int Mandelbrot(double, double);
bool MandelbrotDotProduct(double, double, double*);

/* Fonction pour modifier la valeur obtenue par Mandelbrot */
double ScalingFunction(double);

/* Fonction pour faire un dot-product normalisé */
double NormalizedDotProduct(double, double, double, double);

/* Fonctions pour allouer de la mémoire */
int**  AllocateMemory(int, int);
int*** AllocateMemory(int, int, int);

/* Fonctions pour libérer la mémoire */
void FreeMemory(int**, int);
void FreeMemory(int***, int, int);

/* Fonction pour sauvegarder un array en image */
void SaveArrayAsImage(int**, int, int, string);
void SaveArrayAsImage(int***, int, int, int, string);
void SaveArrayAsGreyImage(int***, int, int, int, string);

/* Fonction pour passer de l'encodage 'HSV' à 'RGB' */
void HSVtoRGB(HSV*, RGB*);

int main() {
    // Nom de l'image
    string file_name = "Images/image_dot.ppm";
    string file_name_GS = "Images/image_dot_gs.ppm";

    // Centre de l'image
    double centre_x = -1.245; //-0.748;
    double centre_y =  0.093; // 0.094;
    // Zoom
    double zoom = ZOOM;
    // Range et Aspect ratio
    double range_x = 2.0 / zoom;
    double range_y = range_x / RATIO;
    // Position (x,y) dans le domaine
    double x, y;
    // Variable pour stocker la valeur de Mandelbrot
    double dot;

    // Structures pour stocker la couleur d'un pixel
    RGB pixelRGB;
    HSV pixelHSV;

    // Initialise la couleur
    pixelHSV.v = 1.0;
    pixelHSV.s = 1.0;

    // Initialise le array
    int *** array;
    // Alloue de la mémoire
    array = AllocateMemory(DEPTH, HEIGHT, WIDTH);

    // Boucle sur les rangés
    for (int i = 0; i < HEIGHT; i++) {
        // Obtient la position réelle à partir du pixel
        y = centre_y + (1.0 - ((2.0 * i)/HEIGHT)) * range_y;
        // Boucle sur les colonnes
        for (int j = 0; j < WIDTH; j++) {
            // Obtient la position réelle à partir du pixel
            x = centre_x + (((2.0 * j)/WIDTH) - 1.0) * range_x;
            // Colorie le pixel selon la valeur obtenue
            if (MandelbrotDotProduct(x, y, &dot)) {
                pixelHSV.h = 360.0 * NormalizedSinus(dot, W);
                // Obtient les valeurs RGB
                HSVtoRGB(&pixelHSV, &pixelRGB);
                // Colorie le pixel
                array[0][i][j] = pixelRGB.r;
                array[1][i][j] = pixelRGB.g;
                array[2][i][j] = pixelRGB.b;
            }
        }
    }
    // Crée l'image
    SaveArrayAsImage(array, DEPTH, WIDTH, HEIGHT, file_name);
    SaveArrayAsGreyImage(array, DEPTH, WIDTH, HEIGHT, file_name_GS);

    // Libère mémoire
    FreeMemory(array, DEPTH, HEIGHT);
    
    // FIN
    return 0;
}

bool MandelbrotDotProduct(double x, double y, double * dot) {
    // Nombre complex C
    double c_re = x;
    double c_im = y;
    // Valeur initiale du nombre complexe Z
    double z_re = 0.0;
    double z_im = 0.0;
    // Variable tampons
    double re = 0.0;
    double im = 0.0;
    // Boucle
    int iter = 0;
    while (iter < MAX_ITER) {
        // Nouvelle valeur réelle/imaginaire
        re = z_re*z_re - z_im*z_im + c_re;
        im = 2*z_re*z_im + c_im;
        // Condition sur la norme
        if (re*re + im*im >= MAX_NORM) {
            *dot = NormalizedDotProduct(z_re, z_im, c_re, c_im);
            return true;
        }
        // Met à jour le nombre 'Z'
        z_re = re;
        z_im = im;
        // Augmente la variable itérative
        iter++;
    }
    return false;
}

// Fonction pour allouer de la mémoire pour un array 2D
int** AllocateMemory(int w, int h) {
    int ** arr = (int**) malloc(w * sizeof(int*));
    for (int i = 0; i < w; i++) {
        arr[i] = (int*) malloc(h * sizeof(int));
        for (int j = 0; j < h; j++)
            arr[i][j] = 0;
    }
    return arr;
}

// Fonction pour allouer de la mémoire pour un array 3D
int*** AllocateMemory(int d, int w, int h) {
    int *** arr = (int***) malloc(d * sizeof(int**));
    for (int k = 0; k < d; k++) 
        arr[k] = AllocateMemory(w, h);
    return arr;
}

// Fonction pour libérer la mémoire d'un array 2d
void FreeMemory(int** arr, int w) {
    for (unsigned int i = 0; i < w; i++)
        free(arr[i]);
    free(arr);
}

// Fonction pour libérer la mémoire d'un array 3d
void FreeMemory(int*** arr, int d, int w) {
    for (unsigned int i = 0; i < d; i++)
        FreeMemory(arr[i], w);
    free(arr);
}

// Fonction pour sauvegarder le array en image (B&W)
void SaveArrayAsImage(int ** arr, int width, int height, string file_name) {
    // Initialise l'image 
    ofstream image(file_name);
    // Écrit l'en-tête
    image << "P2\n";
    image << width << " " << height << endl;
    image << NORMALIZATION_VALUE << endl;
    // Écrit les valeurs de chaque pixel
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) image << arr[i][j] << " ";
        image << endl;
    }
}

// Fonction pour sauvegarder le array en image (RGB)
void SaveArrayAsImage(int *** arr, int depth, int width, int height, string file_name) {
    // Initialise l'image
    ofstream image(file_name);
    // Écrit l'en-tête
    image << "P3\n";
    image << width << " " << height << endl;
    image << NORMALIZATION_VALUE << endl;
    // Écrit les valeurs de chaque pixel (R G B)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int d = 0; d < depth; d++) {
                image << arr[d][i][j] << " ";
            }
        }
        image << endl;
    }
}

// Fonction pour sauvegarder l'image en greyscale
void SaveArrayAsGreyImage(int *** arr, int depth, int width, int height, string file_name) {
    // Initialise l'image
    ofstream image(file_name);
    // Écrit l'en-tête
    image << "P2\n";
    image << width << " " << height << endl;
    image << NORMALIZATION_VALUE << endl;
    // Variable pour obtenir la moyenne des couleurs
    int grey = 0;
    // Écrit les valeurs de chaque pixel (R G B)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int d = 0; d < depth; d++) grey = grey + arr[d][i][j];
            grey = grey / depth;
            image << grey  << " ";
        }
        image << endl;
    }
}