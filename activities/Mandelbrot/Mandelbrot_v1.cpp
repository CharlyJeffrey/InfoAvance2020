/* 
Première itération du code:
    * Créer un array de dimension (HEIGHT, WIDTH)
    * Créer une image B&W à partir du array
    * Sauvegarder l'image
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

int main() {
    // Nom de l'image
    string file_name = "Images/image_1.ppm";

    /* Crée le array */
    // Initialise le array
    int ** array;
    // Remplie le array
    array = new int*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        array[i] = new int[WIDTH];
        for (int j = 0; j < WIDTH; j++)
            array[i][j] = (i*i + j*j) % NORMALIZATION_VALUE;
    }

    /* Crée l'image */
    // Initialise l'image
    ofstream image(file_name);
    // Écrit l'en-tête du fichier image
    image << "P2\n";                            // Format
    image << WIDTH << " " << HEIGHT << endl;    // Resolution
    image << NORMALIZATION_VALUE << endl;       // Normalisation
    // Écrit les valeurs des chaque pixels
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) image << array[i][j] << " ";
        image << endl;
    }

    // Libère mémoire
    for (int i = 0; i < HEIGHT; i++) 
        free(array[i]);
    free(array);

    // FIN
    return 0;
}