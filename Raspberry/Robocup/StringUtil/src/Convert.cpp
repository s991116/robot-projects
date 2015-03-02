#include <Convert.h>
#include <iostream>
#include <sstream>

std::string Convert::IntToString(int number)
{
  std::string numberString;
  std::stringstream out;
  out << static_cast<int> (number);
  numberString = out.str();
  return numberString;
}

std::string Convert::FloatToString(float number)
{
  std::string numberString;
  std::stringstream out;
  out << static_cast<float> (number);
  numberString = out.str();
  return numberString;
}

std::string Convert::IntVectorToString(std::vector<int> result)
{
  std::string resultString = "[";
  for (std::vector<int>::iterator it = result.begin(); it != result.end(); ++it) {
    int number = *it;
    std::string numberString = IntToString(number);
    resultString += numberString + " ,";
  }
  resultString = "]";
  return resultString;
}
