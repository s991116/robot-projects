#ifndef COMSTATE_H
#define	COMSTATE_H

#include "State.h"
#include "SerialProtocol.h"

class ComState : public State {
public:
  ComState(SerialCommandProtocol* serialProtocol);
  State* View();
  virtual ~ComState();

private:
  void Print();
  State* Control();
  SerialCommandProtocol* _SerialProtocol;
};

#endif	/* COMSTATE_H */

