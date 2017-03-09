//	Made by Alex Mytnyk
//	28.02.2017
//	All rights reserved
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <algorithm>

using namespace std;

template <typename A, typename B>
struct Keys
{
	std::vector<A> aa;
	std::vector<B> bb;
};

template <typename C, typename A, typename B>
struct Record
{
	C _data;
	Keys<A, B> _keys;
};

template <typename T>
double _Match(const std::vector<T>& input, const std::vector<T>& record)
{
	if (record.size() == 0)
		return 100.0;

	for (const auto& key : input)
	{
		auto it = std::find(record.begin(), record.end(), key);
		if (it == record.end())
			return 0.0;
	}

	return 100.0 * input.size() / record.size();
}


template <typename C, typename A, typename B>
C _FindBest(const std::vector<Record<C, A, B>>& records, const Keys<A, B>& keys)
{
	vector<double> procs;
	for (const auto& record : records)
	{
		double percentA = _Match(keys.aa, record._keys.aa);
		double percentB = _Match(keys.bb, record._keys.bb);
		
		double percent;
		percent = (percentA + percentB) / 2;
		procs.push_back(percent);
	}

	size_t index = std::distance(procs.begin(), std::max_element(procs.begin(), procs.end()));
	
	return records[index]._data;
}
enum Resolution
{
	Small,
	Average,
	Big
};

enum Quality
{
	bad,
	soso,
	Quite_good,
	good,
	very_good,
};

enum RefreshRate
{
	Sparse,
	Middle,
	Frequent,
};
void tests1()
{
	std::vector<Record<Quality, Resolution, RefreshRate>> records =
	{
		{ bad,{ { Small },{} } },
		{ soso,{ { Average },{ Sparse, Middle } } },
		{ Quite_good,{ { Average },{ Frequent } } },
		{ good,{ { Big },{ Sparse, Middle } } },
		{ very_good,{ { Big },{ Frequent } } },
	};
	Quality result = _FindBest(records, { { Small }, { Frequent } });
	if (result != bad)
		throw std::logic_error("test1 failed");
	result = _FindBest(records, { { Average },{ Middle } });
	if (result != soso)
		throw std::logic_error("test2 failed");
	result = _FindBest(records, { { Average },{ Frequent } });
	if (result != Quite_good)
		throw std::logic_error("test3 failed");
	result = _FindBest(records, { { Big },{ Middle } });
	if (result != good)
		throw std::logic_error("test4 failed");
	result = _FindBest(records, { { Big },{ Frequent } });
	if (result != very_good)
		throw std::logic_error("test5 failed");
}

enum Money
{
	few,
	abit,
	many,
	Alotof,
	muchalot,
};

enum Processor
{
	I3,
	I5,
	I7,
};

enum Monitor_Diametr
{
	D10,
	D15,
	D20,
	D25,
	D35
};

void tests2()
{
	std::vector<Record<Money, Processor, Monitor_Diametr>> records =
	{
		{ few,{ { I3 },{D10, D15} } },
		{ abit,{ { I3 },{ D20, D25, D35 } } },
		{ many,{ { I5 },{ } } },
		{ Alotof,{ { I7 },{ D10, D15, D20, D25 } } },
		{ muchalot,{ { I7 },{ D35 } } },
	};
	Money result = _FindBest(records, { { I3 },{ D15 } });
	if (result != few)
		throw std::logic_error("test1 failed");
	result = _FindBest(records, { { I3 },{ D35 } });
	if (result != abit)
		throw std::logic_error("test2 failed");
	result = _FindBest(records, { { I5 },{ D10 } });
	if (result != many)
		throw std::logic_error("test3 failed");
	result = _FindBest(records, { { I7 },{ D10 } });
	if (result != Alotof)
		throw std::logic_error("test4 failed");
	result = _FindBest(records, { { I7 },{ D35 } });
	if (result != muchalot)
		throw std::logic_error("test5 failed");
}

int main()
{
	tests1();
	tests2();
	//system("pause");
    return 0;
}
