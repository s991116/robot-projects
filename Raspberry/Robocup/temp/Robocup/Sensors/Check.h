
#ifndef CHECK_H
#define	CHECK_H

class Check {
public:
  virtual void Prepare() = 0;
  virtual bool Test() = 0;
};

#endif	/* CHECK_H */

