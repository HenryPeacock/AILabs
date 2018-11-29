#include <iostream>
#include <Windows.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//Defining e
#define e 2.71828
#define delta 0.0000001

// Function declaration
// Step function
float StepFunc(float &_w1, float &_w2, float _theta, int _iterations, float _alpha);
// Multi Neuron Function
float MultiNeuron(int _iterations, float _alpha);
// Genetic algorithm function
void GeneticAlgorithm(std::vector<std::vector<int>> _currentLevel);
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
	/* Old
	// Initialiase variables
	int iterations = 20;
	int mnIterations = 10000000;
	float theta = 0.2f;
	float w1 = 0.3f;
	float w2 = -0.1f;
	float alpha = 0.1f;
	float y;
	*/

	// Multineural Network
	//multiNeuron(mnIterations, alpha);

	// Genetic algorithm
	// Loading the file:
	//std::ifstream levelFile("level1.txt");	
	

	// Initial variable declaration
	std::vector<std::vector<int>> levelMatrix;
	std::ifstream levelFiles[10];
	std::string tempLevelQuantity;
	bool correct = FALSE;
	int levelQuantity;

	// Requesting level amount with data validation
	std::cout << "How many Levels do you want to load? (Maximum 5) ";
	while (correct == FALSE)																							// Loop when the input is invalid
	{
		std::getline(std::cin, tempLevelQuantity);																		// Take User Input as string
		std::stringstream convert(tempLevelQuantity);																	// Convert to String Stream
		std::cout << std::endl;																						
		if (convert >> levelQuantity && !(convert >> tempLevelQuantity) && levelQuantity <= 5 && levelQuantity > 0)		// Test if it is an integer, and if it's between 1 and 5
		{
			levelQuantity = std::stoi(tempLevelQuantity);																// Convert string to int and store
			correct = TRUE;																								// Exit loop
		}
		else
		{
			std::cin.clear();																							// Clear the user input
			std::cerr << "Please enter an integer of between 1 and 5: ";												// Output the error message
		}
	}
	

	// Loading Levels
	for (int j = 0; j < levelQuantity; j++)
	{
		std::stringstream ss;						// Create stringstream
		ss << "level" << j + 1 << ".txt";			// Merge level file format with current iteration
		levelFiles[j].open(ss.str().c_str());		// Open the level file into the current iteration of the level files array
		if (levelFiles[j].is_open() == false)		// Check that the file has sucessfully opened, if not throw an exception
		{
			throw std::exception();
		}
	}

	// Resize the level matrix based on how many files the user wishes to load
	levelMatrix.resize(levelQuantity, std::vector<int>(0));

	// Declaring the variables for fully creating the levels
	char placeHolder;
	std::vector<char> tempLevel;
	char legalChars[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	std::vector<std::vector<int>> currentLevel;
	bool isLoaded = FALSE;
	int val;
	
	// Validating the level files and saving to a final level matrix
	for (int l = 0; l < levelQuantity; l++)														// Loop for all levels
	{
		tempLevel.clear();																		// Clear the temporary level vector
		while (levelFiles[l].get(placeHolder))													// Load the file into the temporary level vector
		{
			tempLevel.push_back(placeHolder);
		}
		for (int i = 0; i < (tempLevel.size()); i++)											// Loop to the size of the temporary level vector
		{
			for (int j = 0; j < 10; j++)														// Loop 10 times to check against all legal characters (numbers 1 to 10, declared on line 89)
			{
				isLoaded = FALSE;																// Set the load check to 0
				if (tempLevel[i] == legalChars[j])												// Test whether the current space is a legal character
				{
					for (int k = 0; k < 10; k++)												// Loop 10 times to check if the next character is a number, this tests whether we are taking a 2 digit number
					{
						if ((i + 2) < tempLevel.size())											// Check that we are remaining within the array size to avoid vertex errors 
						{
							if (tempLevel[i + 2] == legalChars[k])								// Check if the next character (2 away due to file loading format) is a number
							{
								std::stringstream css;											// Create stringstream
								css << (tempLevel[i] - 48) << (tempLevel[i + 2] - 48);			// Concatenate numbers
								val = atoi(css.str().c_str());									// Convert to integer
								levelMatrix[l].push_back(val);									// Save in level matrix
								i += 3;															// Increment i
								isLoaded = TRUE;												// Avoid the number being saved again
							}
						}
					}
					if (isLoaded == FALSE)														// Test if a 2 digit number was loaded
					{
						levelMatrix[l].push_back(tempLevel[i] - 48);							// Save in level matrix
					}
					
				}

			}
		}
	}

	// Load levels into a matrix and perform the genetic alorithm
	for (int i = 0; i < levelMatrix.size(); i++)												// Loop for every level
	{
		currentLevel.resize(levelMatrix[i][0], std::vector<int>(levelMatrix[i][1]));			// Resize the current level to the size of the first 2 numbers, which are always the dimensions
		val = 0;																				/* Set an integer to 0 to count which part of the level matrix we should pull from since the level matrix
																								   stores each level on one line and the current will store it in 2 dimensions */
		for (int j = 0; j < currentLevel.size(); j++)											// Loops for the x size of the level
		{
			for (int k = 0; k < currentLevel[j].size(); k++)									// Loops for the y size of the level
			{
				currentLevel[j][k] = levelMatrix[i][val+2];										// Loads the values into the correct part of currentLevel
				val++;																			// Increments val
			}
		}
		GeneticAlgorithm(currentLevel);															// Run the genetic algorithm for the current level
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

void GeneticAlgorithm(std::vector<std::vector<int>> _currentLevel)
{

}

float StepFunc(float &_w1, float &_w2, float _theta, int _iterations, float _alpha)
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

float MultiNeuron(int _iterations, float _alpha)
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