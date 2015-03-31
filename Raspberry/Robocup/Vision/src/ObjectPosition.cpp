#include <ObjectPosition.h>

ObjectPosition::ObjectPosition() {
  Center = new Position();
  Corner1 = new Position();
  Corner2 = new Position();
}

bool ObjectPosition::WithinImage() {
  return (Detected && Corner1->WithinImage() && Corner2->WithinImage());
}

std::string ObjectPosition::Print() {
  if(Detected)
  {
    return "C1: " + Corner1->Print() + " - C2: " + Corner2->Print() + " - Center: " + Center->Print();
  }
  else
  {
    return "No objected detected.";
  }
}
