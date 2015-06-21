enum class CommandType 
{ 
	SET_MotorA_P = 1,
	SET_MotorA_I = 2,
	SET_MotorA_D = 3,

	SET_MotorB_P = 4,
	SET_MotorB_I = 5,
	SET_MotorB_D = 6,

	SET_MotorA_Speed = 7,
	SET_MotorB_Speed = 8,

	GET_MotorA_Speed = 9,
	GET_MotorB_Speed = 10,

	GET_MotorA_Distance = 11,
	GET_MotorB_Distance = 12,

	SET_Motor_Running = 13,

	GET_Calculation_Time = 14,

	SET_Measure_Mode = 15,

	GET_Measurement = 16,

	TestEcho = 255 
};
