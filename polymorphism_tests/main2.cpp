
#include <iostream>
#include "dyn.h"

template <typename T...> class CalculatorPool {

public:
  template <typename CalT> bool addCalculator(CalT calculator) 
  {
  
  }

  void processEvent()
  {
      //loop through our tuple and process all
  }

private:
  static constexpr Tuple<T...> data_;

}



int main()
{
}




