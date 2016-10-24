#ifndef COMSTATE_H
#define	COMSTATE_H

#include "State.h"
#include "MessageDataProtocol.h"

class ComState : public State {
public:
  ComState(MessageDataProtocol* serialProtocol);
  State* View();
  virtual ~ComState();

private:
  void Print();
  State* Control();
  MessageDataProtocol* _SerialProtocol;
};

#endif	/* COMSTATE_H */

