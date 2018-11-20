#include <iostream>
#include <Windows.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
//Defining e
#define e 2.71828
#define delta 0.0000001

// Function declaration
// Step function
float stepFunc(float &_w1, float &_w2, float _theta, int _iterations, float _alpha);
float multiNeuron(int _iterations, float _alpha);
/*
// Sign function
float signFunc(int _x, float _theta);
// Sigmoid function
float sigmoidFunc(float _x, float _theta);
// Linear function
float linearFunc(float _x, float _theta);
*/
int main()
{
	// Initialiase variables
	int iterations = 20;
	int mnIterations = 10000000;
	float theta = 0.2f;
	float w1 = 0.3f;
	float w2 = -0.1f;
	float alpha = 0.1f;
	float y;

	// Multineural Network
	//multiNeuron(mnIterations, alpha);

	// Genetic algorithm
	// Loading the file:
	//std::ifstream levelFile("level1.txt");
	std::ifstream levelFiles[2];
	for (int j = 0; j < 2; j++)
	{
		std::stringstream ss;
		ss << "level" << j + 1 << ".txt";
		levelFiles[j].open(ss.str().c_str());
		if (levelFiles[j].is_open() == false)
		{
			throw std::exception();
		}
	}


	char ph;
	char tempLevel[51] = {0};
	int level[2][26] = {0};
	char legalChars[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int k = 0;
	int i;

	for (int l = 0; l < 2; l++)
	{
		i = 0;
		while (levelFiles[l].get(ph))
		{
			tempLevel[i] = ph;
			i++;
		}
		for (i = 0; i < 51; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (tempLevel[i] == legalChars[j])
				{
					level[l][k] = tempLevel[i] - 48;
					k++;
				}
			}
		}
	}



	/*
	// Step Function
	stepFunc(w1, w2, theta, iterations, alpha);

	// Sign function test
	std::cout << "Input theta value for sign function" << std::endl;
	std::cin >> theta;
	y = signFunc(finalx, theta);
	std::cout << "Sign function outputs: " << y << std::endl;

	// Sigmoid function test
	std::cout << "Input theta value for sigmoid function" << std::endl;
	std::cin >> theta;
	y = sigmoidFunc(finalx, theta);
	std::cout << "Sigmoid function outputs: " << y << std::endl;

	// Linear function test
	std::cout << "Input theta value for linear function" << std::endl;
	std::cin >> theta;
	y = linearFunc(finalx, theta);
	std::cout << "Linear function outputs: " << y << std::endl;
	*/

	// Program end after pause
	system("PAUSE");
	return 0;
}

float stepFunc(float &_w1, float &_w2, float _theta, int _iterations, float _alpha)
{
	float x1[4] = { 0.0f, 0.0f, 1.0f, 1.0f};
	float x2[4] = { 0.0f, 1.0f, 0.0f, 1.0f};
	float Yd[4] = { 0.0f, 0.0f, 0.0f, 1.0f};
	float bigX;
	float bigY;
	float error;
	int i = 0;

	for (int p = 0; p < _iterations; p++)
	{
		// Index for training data
		i = p % 4;
		// Work out Y
		bigX = (x1[i] * _w1) + (x2[i] * _w2);
		if (bigX >= (_theta - delta))
		{
			bigY = 1;
		}
		else
		{
			bigY = 0;
		}
		// Calculate the error
		error = Yd[i] - bigY;
		// Update the weights due to error
		_w1 = _w1 + (_alpha * x1[i] * error);
		_w2 = _w2 + (_alpha * x2[i] * error);
	}
	std::cout << "w1 = " << _w1 << std::endl << "w2 = " << _w2 << std::endl;
	return 0;

	/*Old stuff
	if (_x >= (_theta - delta))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	*/
}

float multiNeuron(int _iterations, float _alpha)
{
	// Initialising the variables
	float _w[5][5] = {
		0.0f, 0.0f, 0.5f, 0.9f, 0.0f,
		0.0f, 0.0f, 0.4f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,-1.2f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.1f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,};
	float _wTemp[5][5] = {
		0.0f, 0.0f, 0.5f, 0.9f, 0.0f,
		0.0f, 0.0f, 0.4f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,-1.2f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.1f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, };
	float _theta[5] = { 0.0f, 0.0f, 0.8f, -0.1f, 0.3f};
	float _bigX[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float _bigY[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float _tX[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float _tY[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float _x1[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float _x2[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float _Yd[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
	float _error[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float _tError[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float _delta[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float _EpocSumError;
	int _p = 1;
	
	// Main loop
	while (_p <= (_iterations - 4))
	{
		_EpocSumError = 0.0f;

		for (int i = 0; i < 4; i++)
		{

			// Neuron 3 Calculation
			_bigX[2] = (_x1[i] * _w[0][2]) + (_x2[i] * _w[1][2]);
			_bigY[2] = 1 / (1 + pow(e, -(_bigX[2] - _theta[2])));

			// Neuron 4 Calculation
			_bigX[3] = (_x1[i] * _w[0][3]) + (_x2[i] * _w[1][3]);
			_bigY[3] = 1 / (1 + pow(e, -(_bigX[3] - _theta[3])));

			// Neuron 5 Calculation
			_bigX[4] = (_bigY[2] * _w[2][4]) + (_bigY[3] * _w[3][4]);
			_bigY[4] = 1 / (1 + pow(e, -(_bigX[4] - _theta[4])));

			// Back propagate the error and use the learning rule to update the weights
			// Neuron 5 Error
			_error[4] = _Yd[i] - _bigY[4];
			_delta[4] = _bigY[4] * (1 - _bigY[4]) * _error[4];
			_wTemp[2][4] = _w[2][4];
			_wTemp[3][4] = _w[3][4];
			_w[2][4] = _w[2][4] + (_alpha * _bigY[2] * _delta[4]);
			_w[3][4] = _w[3][4] + (_alpha * _bigY[3] * _delta[4]);
			_theta[4] = _theta[4] + (_alpha * -1 * _delta[4]);

			// Neuron 3 Error
			_delta[2] = _bigY[2] * (1 - _bigY[2]) * _delta[4] * _wTemp[2][4];
			_w[0][2] = _w[0][2] + (_alpha * _x1[i] * _delta[2]);
			_w[1][2] = _w[1][2] + (_alpha * _x2[i] * _delta[2]);
			_theta[2] = _theta[2] + (_alpha * -1 * _delta[2]);

			// Neuron 4 Error
			_delta[3] = _bigY[3] * (1 - _bigY[3]) * _delta[3] * _wTemp[3][4];
			_w[0][3] = _w[0][3] + (_alpha * _x1[i] * _delta[3]);
			_w[1][3] = _w[1][3] + (_alpha * _x2[i] * _delta[3]);
			_theta[3] = _theta[3] + (_alpha * -1 * _delta[3]);

			// Accumulating the sum of errors in the Epoc
			// Recalculate the error at the end _error[5] after updating all the weights and thetas
			_tX[2] = (_x1[i] * _w[0][2]) + (_x2[i] * _w[1][2]);
			_tY[2] = 1 / (1 + pow(e, (-(_tX[2] - _theta[2]))));
			_tX[3] = (_x1[i] * _w[0][3]) + (_x2[i] * _w[1][3]);
			_tY[3] = 1 / (1 + pow(e, (-(_tX[3] - _theta[3]))));
			_tX[4] = (_tY[2] * _w[2][4]) + (_tY[3] * _w[3][4]);
			_tY[4] = 1 / (1 + pow(e, (-(_tX[4] - _theta[4]))));
			_tError[4] = _Yd[i] - _tY[4];
			// Squared error
			_EpocSumError += pow(_tError[4], 2);
			_p++;
			if ((_p % 10000) == 0)
			{
				std::cout << _p << std::endl;
				std::cout << _EpocSumError << std::endl;
			}
		}
		if (_EpocSumError < 0.001)
		{
			std::cout << _EpocSumError << std::endl;
			return 0;
		}

	}
	std::cout << _p << std::endl;
	std::cout << _EpocSumError << std::endl;
	return 0;
}

/*
float signFunc(int _x, float _theta)
{
	if (_x >= (_theta - delta))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}


float sigmoidFunc(float _x, float _theta)
{
	/*
	float _y;
	float _power;
	_power = -(_x - _theta);
	_y = 1 / (1+ pow(e, _power));
	return _y;

}

float linearFunc(float _x, float _theta)
{
	return (_x - _theta);
}*/