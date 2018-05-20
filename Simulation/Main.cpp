#include <fstream>
#include <valarray>
#include "Simulator.h"

using namespace std;

int main()
{
	ofstream fout("data.csv");
	cout << "Please enter element minimum count(over 1000, Q to quit):";
	int elementMin;
	cin >> elementMin;
	cout << "Please enter element maximum count(over "<< elementMin <<", Q to quit):";
	int elementMax;
	cin >> elementMax;

	while (cin.good())
	{
		cout << "Please wait...";
		int elementCount = elementMin;
		try
		{
			cout << endl;
			do
			{
				fout << elementCount << "," << Simulator().Simulate(elementCount, 1000, 300, 10) << endl;
				cout << elementCount << "," << Simulator().Simulate(elementCount, 1000, 300, 10) << endl;
				elementCount+=50;
			} while (elementCount <= elementMax);
		}
		catch (exception e)
		{
			cout << e.what() << endl;
		}
		cout << "Please enter element minimum count(over 1000, Q to quit):";
		int elementMin;
		cin >> elementMin;
		cout << "Please enter element maximum count(over " << elementMin << ", Q to quit):";
		int elementMax;
		cin >> elementMax;
	}

}