/* 
Troisième itération du code:
    * Définir les équations pour passer de (px, py) à (x, y)
    * Définir une fonction pour le fractale de Mandelbrot (BLANC-NOIRE)
*/

#include <math.h>
#include <stdio.h>  
#include <stdlib.h> 
#include <fstream>
#include <iostream>
#include <string>

// Resolution:
//> 1080 x 720
//> 2048 x 1080
//> 3840 x 2160
#define WIDTH 3840
#define HEIGHT 2160
#define RATIO ((1.0*WIDTH)/HEIGHT)
// Valeur de normalisation pixel
#define NORMALIZATION_VALUE 255

// Mandelbrot variables
#define MAX_ITER 256
#define MAX_NORM 4.0

using namespace std;

/* Fonction pour la récursion de Mandelbrot */
int Mandelbrot(double, double);

/* Fonctions pour allouer de la mémoire */
int * AllocateMemory1D(int);
int** AllocateMemory2D(int, int);

/* Fonction pour initialiser un array 2D */
void Initialize2DArray(int**, int, int);

/* Fonction pour sauvegarder un array en image */
void SaveArrayAsImage(int**, int, int, string);

int main() {
    // Nom de l'image
    string file_name = "Images/image_3.ppm";

    // Centre de l'image
    double centre_x = -0.75;
    double centre_y = 0.0;
    // Zoom
    double zoom = 1.0;
    // Range et Aspect ratio
    double range_x = 2.0 / zoom;
    double range_y = range_x / RATIO;
    // Position (x,y) dans le domaine
    double x, y;

    // Initialise le array
    int ** array;
    // Alloue de la mémoire
    array = AllocateMemory2D(HEIGHT, WIDTH);
    
    // Remplie le array si l'allocation a réussi
    if (array != nullptr) {
        // Initialise les cases du array
        Initialize2DArray(array, WIDTH, HEIGHT);

        // Boucle sur les rangés
        for (int i = 0; i < HEIGHT; i++) {
            // Obtient la position réelle à partir du pixel
            y = centre_y + (1.0 - ((2.0 * i)/HEIGHT)) * range_y;
            // Boucle sur les colonnes
            for (int j = 0; j < WIDTH; j++) {
                // Obtient la position réelle à partir du pixel
                x = centre_x + (((2.0 * j)/WIDTH) - 1.0) * range_x;
                // Colorie le pixel (i, j)
                array[i][j] = Mandelbrot(x, y);
            }
        }

        // Crée l'image
        SaveArrayAsImage(array, WIDTH, HEIGHT, file_name);
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
    int iter = 0;
    while (iter < MAX_ITER) {
        // Nouvelle valeur réelle/imaginaire
        re = z_re*z_re - z_im*z_im + c_re;
        im = 2*z_re*z_im + c_im;
        // Condition sur la norme
        if (re*re + im*im >= MAX_NORM) return 255;
        // Met à jour le nombre 'Z'
        z_re = re;
        z_im = im;
        // Augmente la variable itérative
        iter++;
    }
    return 0;
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
    }
    else {
        printf("\\>  Allocation mémoire 2D échouée.\n");
    }
    return arr;
}

// Fonction pour initialiser un array 2D
void Initialize2DArray(int ** arr, int width, int height) {
    // Boucle pour remplir le array
    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) arr[i][j] = (i*i+j*j)%NORMALIZATION_VALUE;
}

// Fonction pour sauvegarder le array en image
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