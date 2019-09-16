#include <Arduino.h>

class BalancingControl{
    public:
        void Initialize();
        
        void SetPidPLevel(unsigned char);
        void SetPidILevel(unsigned char);
        void SetPidDLevel(unsigned char);
 
        unsigned char GetPidPLevel();
        unsigned char GetPidILevel();
        unsigned char GetPidDLevel();

        float pid_p_gain;
        float pid_i_gain;
        float pid_d_gain;
        float turning_speed;
        float max_target_speed;

    private:

};