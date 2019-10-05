/*
    Header file for the class 'Image'
*/

#include <stdio.h>  
#include <stdlib.h> 
#include <fstream>
#include <iostream>
#include <string>

#include "Pixel.cpp"

using namespace std;

// Image class object
class Image {
    public:
        Image();
        Image(int, int);
        Image(int, int, int);
        /* Getter Methods */
        int GetWidth();
        int GetHeight();
        int *** GetArray();
        /* Setter Methods */
        void SetPixelAt(int, int, int);
        void SetPixelAt(int, int, RGB*);
        /* General Methods */
        void SaveAs(string);
        void SaveAsRGB(string, int normal);
        void SaveAsGSV(string, int normal);

    private:
        int width;
        int height;
        int depth;
        int *** arr;

};