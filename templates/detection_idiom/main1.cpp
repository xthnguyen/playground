#include <iostream>

namespace detail {
template <class T>
auto calculate(const T& t, int) -> decltype(t.custom_cal()) {
	std::cout << "Call special method" << std::endl;	
	return t.custom_cal();
}

template <class T>
int calculate(const T& t, ...) {
	std::cout << "Call generic method " << std::endl;
	return 1000;
}
}

template <class T>
int calculate(const T& t) {
	std::cout << "Start calling impl" << std::endl;
	return detail::calculate(t, 0);
}

class NormalCalculator {
};

class SpecialCalculator {
public:
	int custom_cal() const {
		return 200;
	}
};


int main() {
	NormalCalculator c1;
	SpecialCalculator c2;

	std::cout << "Normal cal " << calculate(c1) << std::endl;
	std::cout << "Special cal " << calculate(c2) << std::endl;
}
