#ifndef CONVERT_H
#define	CONVERT_H

#include <string>
#include <vector>

class Convert {
public:
  static std::string IntToString(int number);
  static std::string FloatToString(float number);
  static std::string IntVectorToString(std::vector<int> result);

};

#endif	/* CONVERT_H */

