#ifndef PORTCHECK_H
#define	PORTCHECK_H

#include <Check.h>
#include <Setting.h>
#include <ComController.h>
#include <SensorInfo.h>
#include <string>

class PortCheck : public Check, public SensorInfo, public Setting {
public:
  PortCheck(ComController* comController, int portCount);
  PortCheck(const PortCheck& orig);
  void Prepare();
  bool Test();
  std::string GetStatus();

private:
  ComController* _ComController;
  int _TargetCount;
  int _DeltaCount;

};

#endif	/* PORTCHECK_H */

