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
int**  AllocateMemory2D(int, int);

/* Fonction pour initialiser un array 2D */
void FunkyFunction(int**, int, int);

/* Fonction pour sauvegarder un array en image */
void SaveArrayAsImage(int**, int, int, string);

int main() {
    // Nom de l'image
    string file_name = "Images/image_2.ppm";

    // Array de l'image finale
    int ** array;
    // Alloue de la mémoire
    array = AllocateMemory2D(HEIGHT, WIDTH);
    
    // Modifie le array
    FunkyFunction(array, HEIGHT, WIDTH);
    
    // Crée l'image
    SaveArrayAsImage(array, WIDTH, HEIGHT, file_name);

    // Libère la mémoire
    for (int i = 0; i < HEIGHT; i++)
        free(array[i]);
    free(array);
    // FIN
    return 0;
}

// Fonction pour allouer de la mémoire pour un array 2D
int** AllocateMemory2D(int w, int h) {
    int ** arr = (int**) malloc(w * sizeof(int*));
    for (int i = 0; i < w; i++) {
        arr[i] = (int*) malloc(h * sizeof(int));
        for (int j = 0; j < h; j++)
            arr[i][j] = 0;
    }
    return arr;
}

void FunkyFunction(int ** array, int w, int h) {
    for (unsigned int i = 0; i < w; i++) 
        for (int j = 0; j < h; j++) 
            array[i][j] = (i*i + j*j) % NORMALIZATION_VALUE;
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