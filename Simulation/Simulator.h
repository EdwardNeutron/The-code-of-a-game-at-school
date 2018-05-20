#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Element
{
	bool Marked;
};

typedef vector<Element> element_set;

struct Scale
{
	int Real;
	double Percentage;	//in 2-digits
	friend ostream& operator<<(ostream& os, Scale s)
	{
		return (os << s.Real << "," << s.Percentage << "%");
	}
};

typedef vector<Scale> scale_set;

class Simulator
{
private:

	element_set elements = element_set();
	int elementCount = 0;
	int markCount = 0;
	int approachElementCount = 0;


private:

	void Initialize(int ElementCount, int MarkCount, int ApproachElementCount)
	{
		elementCount = ElementCount;
		markCount = MarkCount;
		approachElementCount = ApproachElementCount;

		if (markCount >= elementCount)
		{
			throw exception("Simulator can't be initialized because the marks are more than the elements");
		}

		for (int i = 0; i < elementCount; i++)
		{
			elements.push_back(Element());
		}
	}

	void MarkRandomly()
	{
		//You can also use rand() to do that, but this way is easier.
		for (int i = 0; i < markCount; i++)
		{
			elements[i].Marked = true;
		}
		random_shuffle(elements.begin(), elements.end());
	}

	int ApproachCount()
	{
		//Preparing
		element_set workingElements = elements;
		int countOfMarkedElements = 0;

		//Get the count of marked elements randomly.
		//You can also use rand() to get values randomly, but this way is easier.
		random_shuffle(workingElements.begin(), workingElements.end());
		int i = 0;
		for (auto e : workingElements)
		{
			if (i >= approachElementCount)
			{
				break;
			}
			if (e.Marked == true)
			{
				countOfMarkedElements++;
			}
			i++;
		}

		//Calculation
		double scale = double(approachElementCount) / double(countOfMarkedElements);
		double result = markCount * scale;

		//Rounding and return.
		return int(result + 0.5);
	}

	double Rounding(double NumberToRound, int Exponential)
	{
		double RoundingDigit = pow(10, Exponential);
		double temp = NumberToRound / RoundingDigit;
		temp = int(temp + 0.5);
		temp *= RoundingDigit;
		return temp;
	}

	Scale GetAverageScale(scale_set scales)
	{
		long long total_real = 0;
		double total_percentage = 0;

		for (auto a : scales)
		{
			total_real += a.Real;
			total_percentage += a.Percentage;
		}

		Scale scale =
		{
			double(total_real) / scales.size(),
			Rounding((double(total_real) / scales.size()) / elementCount * 100, -2)
		};

		return scale;
	}


public:

	const element_set &Elements = elements;
	const int &ElementCount = elementCount;
	const int &MarkCount = markCount;
	const int &ApproachElementCount = approachElementCount;

public:

	Scale Simulate(int ElementCount, int MarkCount, int ApproachElementCount, int TryCount)
	{
		scale_set set;
		for (int i = 0; i < TryCount; i ++)
		{
			//Simulating
			Initialize(ElementCount, MarkCount, ApproachElementCount);
			MarkRandomly();
			int resultInNumber = ApproachCount();

			//Formating
			double percentage = double(resultInNumber) / double(elementCount) * 100;
			Scale result =
			{
				resultInNumber,
				Rounding(percentage, -2)
			};
			//cout << "\t" << result << endl;
			set.push_back(result);
		}

		return GetAverageScale(set);
	}
};

