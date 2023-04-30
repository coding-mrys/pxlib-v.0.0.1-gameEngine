using namespace std;
#include<windows.h>

class display {
public:
	//3D
	vector<float>xvalues = { 0 };
	vector<float>yvalues = { 0 };
	vector<float>zvalues = { 0 };

	vector<u32>colorvalues = { 0xffffff};

	//2D
	vector<vector<float>>stored_pos;
	

};
display screen;