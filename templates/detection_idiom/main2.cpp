#include <iostream>
#include <type_traits>


template <class... Ts> using void_t = void;

template<class T, class=void>
struct support_special_cal : std::false_type {};

template <class T>
struct support_special_cal<T, void_t<decltype(std::declval<T>().custom_cal())>> : std::true_type {};

template<class T, std::enable_if_t<support_special_cal<T>::value>* = nullptr>
auto calculate(const T& t) {
	return t.custom_cal();
}

template<class T, std::enable_if_t<!support_special_cal<T>::value>* = nullptr>
int calculate(const T& t) {
	return 1000;
}



class NormalCalculator {
};


class SpecialCalculator {
public:
	int custom_cal() const  {
		return 200;
	}
};
int main() {
	NormalCalculator c1;
	SpecialCalculator c2;

	std::cout << "Normal cal " << calculate(const_cast<const NormalCalculator&>(c1)) << std::endl;
	std::cout << "Special cal " << calculate(const_cast<const SpecialCalculator&>(c2)) << std::endl;


}
