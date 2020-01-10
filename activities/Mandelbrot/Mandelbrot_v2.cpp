/* 
Deuxième itération du code:
    * Définir une fonction pour l'allocation de mémoire
    * Définir une fonction pour initialiser un array 2D
    * Définir une fonction pour sauvegarder l'image
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

using namespace std;

/* Fonctions pour allouer de la mémoire */
int * AllocateMemory1D(int);
int** AllocateMemory2D(int, int);

/* Fonction pour initialiser un array 2D */
void Initialize2DArray(int**, int, int);

/* Fonction pour sauvegarder un array en image */
void SaveArrayAsImage(int**, int, int, string);

int main() {
    // Nom de l'image
    string file_name = "Images/image_2.ppm";

    // Initialise le array
    int ** array;
    // Alloue de la mémoire
    array = AllocateMemory2D(HEIGHT, WIDTH);
    
    // Remplie le array si l'allocation a réussi
    if (array != nullptr) {
        // Initialise les cases du array
        Initialize2DArray(array, WIDTH, HEIGHT);
        // Crée l'image
        SaveArrayAsImage(array, WIDTH, HEIGHT, file_name);
    }

    // FIN
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