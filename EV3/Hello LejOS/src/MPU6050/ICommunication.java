package MPU6050;

public interface ICommunication {
  int[] ReadBytes(int register, int length);
  void WriteBytes(int register, int[] buffer, int length);
}
