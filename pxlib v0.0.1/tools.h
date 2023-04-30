#include"setup.h"
#include"display.h"
#include<vector>
using namespace std;

const double pi = 3.1415926535;

class rectangle {

public:
    void build(double x, double y, double width, float height, u32 color) {

        for (int i = 0; i <= width; i++) {
            for (int j = 0; j <= height; j++) {
                pixel(x + i, y + j, color);
            }
        }
    }
};
rectangle rect;

class Circle {
private:
    rectangle square;

    float density = 1; //default
    float xp; float yp; float rad; u32 c;

public:
    void build(float x, float y, float radius, float thickness, u32 color) {
        xp = x; yp = y; rad = radius; c = color;

        for (int i = 0; i <= 360; i+=density) {
            square.build(x + cos(i * pi / 180) * radius, y + sin(i * pi / 180) * radius, thickness, thickness, color);

        }

    }
    void set_pixel_desity(float pixel_desity) {
        if (pixel_desity >= 0.001) {
            density = pixel_desity;
        }
    }
    void fill() {
        for (int r = 0; r <= rad; r++) {
            for (int i = 0; i <= 360; i++) {
                square.build(xp + cos(i * pi / 180) * r, yp + sin(i * pi / 180) * r, 1, 1, c);

            }
        }
    }
};
Circle circle;

class Line {
private:
    double radient;
    float density = 0.01; //default

    rectangle rect;

public:
    void build(float x1, float y1, float x2, float y2, float thickness, u32 color) { 
        radient = (y2 - y1) / (x2 - x1);

        if (x2 > x1) {

            for (float j = 0; j <= x2 - x1; j+= density) {
                rect.build(x1 + j, y1 + j * radient, thickness, thickness, color);
            }
        }
        else if(x1>x2){
            for (float j = 0; j <= x1 - x2; j+= density) {
                rect.build(x1 - j, y1 + j * -radient, thickness, thickness, color);
            }
        }
        else if (x2 == x1) {
            if (y2 > y1) {
                for (float k = 0; k <= y2 - y1; k++) {
                    rect.build(x1, y1 + k, thickness, thickness, color);
                }
            }
            else {
                for (float k = 0; k <= y1 - y2; k++) {
                    rect.build(x1, y1 - k, thickness, thickness, color);
                }
            }
        }   
    }
    void set_pixel_desity(float pixel_desity) {
        if (pixel_desity >= 0.001) {
            density = pixel_desity;
        }
    }
};

class Ell{

private:
    float m;
    float density = 1;//default

public:
    void set_pixel_desity(float pixel_desity) {
        if (pixel_desity >= 0.05) {
            density = pixel_desity;
        }
    }

    void build(float x1, float x2, float y, float size, float thickness, u32 color) {
        m = x1 + (x2 - x1) / 2;

        for (float i = 0; i < 360; i+=density) {
            rect.build(m+cos(i*pi/180)*((x2-x1)+size), y+sin(i*pi/180) * size, thickness, thickness, color);
        }
    }

};
Ell ellipse;

namespace math {
    class matrix {

    private:
        double vector_x[3] = { 0,0,0 };
        double vector_y[3] = { 0,0,0 };
        double vector_z[3] = { 0,0,0 };

    public:
        double* x_rotation_matrix(double angle, double* vec) {
            double xrot[3][3] = {
                {1,0,0},
                {0,cos(angle * pi / 180),-sin(angle * pi / 180)},
                {0,sin(angle * pi / 180),cos(angle * pi / 180)}
            };

            for (int i = 0; i < 3; i++) {
                vector_x[i] = xrot[i][0]*vec[0] + xrot[i][1] *vec[1] + xrot[i][2]*vec[2];
            }
            return vector_x;
        }

        double* y_rotation_matrix(double angle, double* vec) {
            double yrot[3][3] = {
                {cos(angle * pi / 180),0,sin(angle * pi / 180)},
                {0,1,0},
                {-sin(angle * pi / 180),0,cos(angle * pi / 180)}
            };

            for (int i = 0; i < 3; i++) {
                vector_y[i] = yrot[i][0] * vec[0] + yrot[i][1] * vec[1] + yrot[i][2] * vec[2];
            }
            return vector_y;
        }

        double* z_rotation_matrix(double angle, double* vec) {
            double zrot[3][3] = {
                {cos(angle * pi / 180),-sin(angle * pi / 180),0},
                {sin(angle * pi / 180),cos(angle * pi / 180),0},
                {0,0,1}
            };

            for (int i = 0; i < 3; i++) {
                vector_z[i] = zrot[i][0] * vec[0] + zrot[i][1] * vec[1] + zrot[i][2] * vec[2];
            }
            return vector_z;
        }
    };
    matrix matrices;
}