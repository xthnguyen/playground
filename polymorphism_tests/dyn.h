

class ICalculator {

	public:
		virtual ~ICalculator() {}

		virtual int calculate(int x, int y) const = 0;


};


class Calculator1 final : public ICalculator
{
	public:
		int calculate(int x, int y) const final
		{
			return x + y;
		}

};


class Calculator2 final : public ICalculator
{
	public:
		int calculate(int x, int y) const final
		{
			return x * y;
		}
};

