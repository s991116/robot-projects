#pragma once

#include <string>
#include <vector>

class Convert
{
public:
	static std::string IntToString(int number);
        static int StringToInt(std::string number);
	static std::string FloatToString(float number);
	static std::string IntVectorToString(std::vector<int> result);
};

