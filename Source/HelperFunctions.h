#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace HelperFunctions {
	inline std::string DoubleToStringWithPrecision(double value, int precision = 4)
	{
		std::ostringstream oss;
		oss.precision(precision);
		oss << value;
		std::string s = oss.str();

		return s;
	}
}