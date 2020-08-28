#include <math.h>
#include <cmath>

#define _USE_MATH_DEFINES
#define EPS 0.001

/* Fonctions misc */

/* Fonctions normalisées => [0.0, 1.0] */
double NormalizedRootOf(int, int, int);
double NormalizedSinus(int, double);
double NormalizedSinus(double, double);
double NormalizedCosin(int, double);
double NormalizedCosin(double, double);

/* Produit scalaire */
double DotProduct(double, double, double, double);
double NormalizedDotProduct(double, double, double, double);


double NormalizedSinus(int val, double frequency) {
	return 0.5 + 0.5 * sin(frequency * M_PI * val);
}

double NormalizedCosin(int val, double frequency) {
	return 0.5 + 0.5 * cos(frequency * M_PI * val);
}

double NormalizedSinus(double val, double frequency) {
	return 0.5 + 0.5 * sin(frequency * M_PI * val);
}

double NormalizedCosin(double val, double frequency) {
	return 0.5 + 0.5 * cos(frequency * M_PI * val);
}


double DotProduct(double u_x, double u_y, double v_x, double v_y) {
    double u_norm = sqrt(u_x*u_x + u_y*u_y);
    double v_norm = sqrt(v_x*v_x + v_y*v_y);
    if (u_norm < EPS || v_norm < EPS) return 0.0;
	return (u_x*v_x + u_y*v_y) / (u_norm * v_norm);
}

double NormalizedDotProduct(double u_x, double u_y, double v_x, double v_y) {
	return 0.5 * ( 1.0 + DotProduct(u_x, u_y, v_x, v_y) );
}

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

// Fonction pour passer de l'encodage 'HSV' à 'RGB'
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
	pixel->r = (Rs + m) * 255;
	pixel->g = (Gs + m) * 255;
	pixel->b = (Bs + m) * 255;
}