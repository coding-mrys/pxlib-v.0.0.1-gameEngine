#include<vector>
#include"tools.h"
Line line;

class triangle {

private:
	double position[3] = { 0,0,0 };
	double rotation[3] = { 0,0,0 };

	double p = 1;
	//double pMatrix[3][3];

	double pi = 3.1415926535;

	double nodes[3][3] = {
		{0,0,1},
		{1,0,1},
		{1,1,1}
	};

	double thick = 1;

public:

	void build(double x, double y, double z, double width, double height, u32 color) {


		for (int i = 0; i < 3; i++) {

			double* rotatedX = math::matrices.x_rotation_matrix(rotation[0], nodes[i]);
			double* rotatedY = math::matrices.y_rotation_matrix(rotation[1], rotatedX);
			double* rotatedZ = math::matrices.z_rotation_matrix(rotation[2], rotatedY);

			//p = 2 / (2.5 - rotatedZ[2]);
			p = 1;
			float pMatrix[3][3] = {
				{p,0,0},
				{0,p,0},
				{0,0,0}  
			};

			for (int j = 0; j < 3; j++) {
				rotatedZ[j] = rotatedZ[0] *pMatrix[j][0] + rotatedZ[1] * pMatrix[j][1] + rotatedZ[2] * pMatrix[j][2];
			}


			position[0] = x + rotatedZ[0] * width;
			position[1] = y + rotatedZ[1] * height;
			position[2] = z + rotatedZ[2];
			
			//to screen
			screen.xvalues.push_back(position[0]);
			screen.yvalues.push_back(position[1]);
			screen.zvalues.push_back(position[2]);
			screen.colorvalues.push_back(color);
		}
		

	}

	void rotate(double x, double y, double z) {
		rotation[0] = x; rotation[1] = y; rotation[2] = z;
	}
};

