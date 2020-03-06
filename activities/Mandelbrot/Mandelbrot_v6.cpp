/* 
Sixieme itération du code:
*/

#include <math.h>
#include <cmath>
#include <stdio.h>  
#include <stdlib.h> 
#include <fstream>
#include <iostream>
#include <string>

// Constante Mathématique
#define _USE_MATH_DEFINES

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
#define MAX_ITER 2048
#define MAX_NORM 4.0
#define ZOOM 2048.0


using namespace std;

/* Structures pour différents encodages d'un pixel */
// Structure RGB
struct RGB {
    int r;
    int g;
    int b;
};
// Structure HSV
struct HSV {
    double h;
    double s;
    double v;
};

/* Fonction pour la récursion de Mandelbrot */
int Mandelbrot(double, double);

/* Fonction pour modifier la valeur obtenue par Mandelbrot */
double ScalingFunction(int);

/* Fonctions pour allouer de la mémoire */
int * AllocateMemory1D(int);
int ** AllocateMemory2D(int, int);
int *** AllocateMemory3D(int, int, int);

/* Fonction pour initialiser un array */
void Initialize2DArray(int**, int, int);
void Initialize3DArray(int***, int, int, int);

/* Fonction pour sauvegarder un array en image */
void SaveArrayAsImage(int**, int, int, string);
void SaveArrayAsImage(int***, int, int, int, string);
void SaveArrayAsGreyImage(int***, int, int, int, string);

/* Fonction pour passer de l'encodage 'HSV' à 'RGB' */
void HSVtoRGB(HSV*, RGB*);

int main() {
    // Nom de l'image
    string file_name = "Images/image_6_9.ppm";
    string file_name_GS = "Images/image_6_9_gs.ppm";

    // Centre de l'image
    double centre_x = -0.748;
    double centre_y = 0.094;
    // Zoom
    double zoom = ZOOM;
    // Range et Aspect ratio
    double range_x = 2.0 / zoom;
    double range_y = range_x / RATIO;
    // Position (x,y) dans le domaine
    double x, y;
    // Variable pour stocker la valeur de Mandelbrot
    int val;

    // Structures pour stocker la couleur d'un pixel
    RGB pixelRGB;
    HSV pixelHSV;

    // Initialise la couleur
    pixelHSV.v = 1.0;
    pixelHSV.s = 1.0;

    // Initialise le array
    int *** array;
    // Alloue de la mémoire
    array = AllocateMemory3D(DEPTH, HEIGHT, WIDTH);
    
    // Remplie le array si l'allocation a réussi
    if (array != nullptr) {
        // Initialise les cases du array
        Initialize3DArray(array, DEPTH, WIDTH, HEIGHT);

        // Boucle sur les rangés
        for (int i = 0; i < HEIGHT; i++) {
            // Obtient la position réelle à partir du pixel
            y = centre_y + (1.0 - ((2.0 * i)/HEIGHT)) * range_y;
            // Boucle sur les colonnes
            for (int j = 0; j < WIDTH; j++) {
                // Obtient la position réelle à partir du pixel
                x = centre_x + (((2.0 * j)/WIDTH) - 1.0) * range_x;
                // Obtient la valeur associée au nombre 'C = x + iy'
                val = Mandelbrot(x, y);
                // Colorie le pixel selon la valeur obtenue
                if (val != 0) {
                    // Obtient la valeur entre 0.0 et 1.0
                    pixelHSV.h = 360.0 * ScalingFunction(val);
                    // Obtient les valeurs RGB
                    HSVtoRGB(&pixelHSV, &pixelRGB);
                    /// Colorie le pixel
                    array[0][i][j] = pixelRGB.r;
                    array[1][i][j] = pixelRGB.g;
                    array[2][i][j] = pixelRGB.b;
                } else {
                    /// Colorie le pixel en noir
                    array[0][i][j] = 0;
                    array[1][i][j] = 0;
                    array[2][i][j] = 0;
                }
            }
        }
        // Crée l'image
        SaveArrayAsImage(array, DEPTH, WIDTH, HEIGHT, file_name);
        SaveArrayAsGreyImage(array, DEPTH, WIDTH, HEIGHT, file_name_GS);
    }

    // FIN
    return 0;
}

// Fonction de Mandelbrot
int Mandelbrot(double x, double y) {
    // Nombre complexe 'C'
    double c_re = x;
    double c_im = y;
    // Valeur initiale du nombre complexe 'Z'
    double z_re = 0.0;
    double z_im = 0.0;
    // Variables 'tampons'
    double re = 0.0;
    double im = 0.0;
    // Boucle
    int iter = 1;
    while (iter < MAX_ITER) {
        // Nouvelle valeur réelle/imaginaire
        re = z_re*z_re - z_im*z_im + c_re;
        im = 2*z_re*z_im + c_im;
        // Condition sur la norme
        if (re*re + im*im >= MAX_NORM) return iter;
        // Met à jour le nombre 'Z'
        z_re = re;
        z_im = im;
        // Augmente la variable itérative
        iter++;
    }
    return 0;
}

// Fonction pour modifier la valeur obtenue par Mandelbrot; [0.0, 1.0]
double ScalingFunction(int val) {
    double _val = 0.5 * sin(6.0 * M_PI * val / MAX_ITER);
    return 0.5 + _val;
}

// Fonction pour allouer de la mémoire pour un array 1D
int * AllocateMemory1D(int length) {
    int * arr = (int*) malloc(length * sizeof(int));
    if (arr == nullptr) printf("//>    Allocation mémoire 1D échouée.\n");
    return arr;
}

// Fonction pour allouer de la mémoire pour un array 2D
int ** AllocateMemory2D(int size, int length) {
    int ** arr = (int**) malloc(size * sizeof(int*));
    if (arr != nullptr) {
        for (int i = 0; i < size; i++) arr[i] = AllocateMemory1D(length);
    } else {
        printf("\\>  Allocation mémoire 2D échouée.\n");
    }
    return arr;
}

// Fonction pour allouer de la mémoire pour un array 3D
int *** AllocateMemory3D(int depth, int size, int length) {
    int *** arr = (int***) malloc(depth * sizeof(int**));
    if (arr != nullptr) {
        for (int i = 0; i < depth; i++) arr[i] = AllocateMemory2D(size, length);
    } else {
        printf("\\>Allocation mémoire 3D échouée.\n");
    }
    return arr;
}

// Fonction pour initialiser un array 2D
void Initialize2DArray(int ** arr, int width, int height) {
    // Boucle pour remplir le array
    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) arr[i][j] = 0; //(i*i+j*j)%NORMALIZATION_VALUE;
}

// Fonction pour initialiser un array 3D
void Initialize3DArray(int *** arr, int depth, int width, int height) {
    // Boucle pour initialiser le array
    for (int d = 0; d < DEPTH; d++) Initialize2DArray(arr[d], width, height);
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

// Fonction pour passer de 'HSV' à 'RGB'
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
	pixel->r = (Rs + m) * NORMALIZATION_VALUE;
	pixel->g = (Gs + m) * NORMALIZATION_VALUE;
	pixel->b = (Bs + m) * NORMALIZATION_VALUE;
}