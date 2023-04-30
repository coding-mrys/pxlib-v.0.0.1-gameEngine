#include "triangle.h"
#include <string>

class renderer {
private:
	double rotation[3] = { 0,0,0 };
	double position[3] = { 0,0,0 };
	double vec[3] = { 0,0,1 };
	float tol = 1;
	float render_dist;
	double rendered[3] = {0, 0, 0};

public:
	void init(double x, double y, double z, float render_distance, float fov) {
		position[0] = x; position[1] = y; position[2] = z;
		render_dist = render_distance;
	} 

	void simulate() {

		for (int k = 0; k < screen.xvalues.size(); k++) {

			rendered[0] = screen.xvalues[k] - position[0];
			rendered[1] = screen.yvalues[k] - position[1];

			rect.build(rendered[0], rendered[1], 1, 1, screen.colorvalues[k]);
		}	

		screen.xvalues.clear();
		screen.yvalues.clear();
		screen.zvalues.clear();
		screen.colorvalues.clear();
	}

	void rotate(double x, double y, double z){
		rotation[0] = x; rotation[1] = y; rotation[2] = z;
	}
};
renderer cam;

namespace physics {

	class objects {
		
	private:
		//default values
		double position[2] = { 0,0 };
		int Size = 100;
		u32 Color = 0xffffff;
		double gradient;
		double step = 1;
		float accuracy = 5;

		vector<float>x_val;
		vector<float>y_val;

	public:
		bool collision = false;

		void build(double x, double y, int size, u32 color){
			position[0] = x;
			position[1] = y;
			Size = size;
			Color = color;
		}

		void push(double angle,float speed){
			gradient = tan(angle*pi/180); //calculate gradient

			//push ball
			if (angle == 270) {
				position[1] += step;
			}
			else if (angle == 90) {
				position[1] -= step;
			}
			else {
				if (angle > 270 && angle < 360 || angle > 0 && angle < 90) {
					step += speed;
				}
				else if (angle > 90 && angle < 270) {
					step -= speed;
				}
				position[0] += step;
				position[1] += step * gradient;
			}

			if (position[1] > 400) {
				collision = true;
			}

			//store values
			x_val.push_back(position[0]);
			y_val.push_back(position[1]);

			screen.stored_pos.push_back(x_val);
			screen.stored_pos.push_back(y_val);

		}

		void show() {
			circle.build(position[0],position[1],Size,1,Color);
		}

		bool is_collision() {
			return collision;
		}

		double* get_pos() {
			return position;
		}

	};

	void update() {
		screen.stored_pos.clear();
	}
}



/*
____________  ____      ____   ___           ___     ___ 
|###########| \###\    /###/  |###|         |###|   |###|
|###|   |###|  \###\  /###/   |###|         |###|   |###|
|###|___|###|   \###\/###/    |###|         |###|   |###|
|##########/     \######/     |###|         |###|   |###|_______
|###|            /######\     |###|         |###|   |###########|
|###|           /###/\###\    |###|_____    |###|   |###|   |###|
|###|          /###/  \###\   |#########\   |###|   |###|___|###|
|###|         /###/    \###\   \#########|  |###|   |###########/

v 0.1 - mrys.exe

*/


