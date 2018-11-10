#include <iostream>
#include <vector>
#include <memory>
#include "dyn.h"
#include "../millipedes/millipedes.h"


constexpr int count = 100;
static void dyn()
{


	std::vector<std::unique_ptr<ICalculator>> calculators;

	for (int i = 0; i < count; ++i)
	{
		calculators.emplace_back(new Calculator1());
		calculators.emplace_back(new Calculator2());
	}

	int total = 0;

	kindergarten::detail::TestSuite testSuite;

	testSuite.add([&]() {

	for(auto& cal : calculators)
	{
		total +=cal->calculate(5,6);
	}
	});

	testSuite.run(1000);
	
	std::cout << "total is " << total << std::endl;
}


static void flat() 
{
	int total = 0;
	

	std::vector<Calculator1> calculator1s;
	std::vector<Calculator2> calculator2s;

	calculator1s.reserve(count);
	calculator2s.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		calculator1s.emplace_back(Calculator1());
		calculator2s.emplace_back(Calculator2());
	}
	
	kindergarten::detail::TestSuite testSuite;

	testSuite.add([&]() {

			for(auto& cal : calculator1s)
			{
			total +=cal.calculate(5,6);
			}
			for(auto& cal : calculator2s)
			{
			total +=cal.calculate(5,6);

			}
	
			} );

	testSuite.run(1000);

	std::cout << "total is " << total << std::endl;
}



int main()
{
	dyn();
	flat();
}
