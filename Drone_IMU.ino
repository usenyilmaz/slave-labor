#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_HMC5883_U.h>

//each sensor class instances
MPU6050 mpu;//gyro + acc
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified();//barometer
Adafruit_HMC5883_Unified hmc = Adafruit_HMC5883_Unified();//magnetic field

//Sensor data storage variables
float temperature, pressure, altitude;
sensors_event_t hmcData;

/*------------------------------------------------------------*/
void SensorInit() {
  Serial.begin(115200);//Seriaal, ESP8266 standardized
  Wire.begin(); // I2C initiation

  //Initialize MPU6050
  mpu.initialize();
    if (!mpu.testConnection()) {
      Serial.println("MPU6050 connection failed");
      while (1);}
  Serial.println("MPU6050 initialized");

  // Initialize BMP180
    if (!bmp.begin()) {
      Serial.println("BMP180 initialization failed");
      while (1);}
  Serial.println("BMP180 initialized");

  // Initialize HMC5883L
    if (!hmc.begin()) {
      Serial.println("HMC5883L initialization failed");
      while (1);}
  Serial.println("HMC5883L initialized");
}

void ReadSensor() {
  //MPU data as accelerometer and gyrometer readings
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
  //2^16/(Sensitivity range(+2)-(-2))=16384.0 
  //same idea for gyroscope 250 degree sensitivity
  //physical value= (sensor value)/sensitivity

  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;
  float gx_dps = gx / 131.0;
  float gy_dps = gy / 131.0;
  float gz_dps = gz / 131.0;

  Serial.print("MPU6050: ");
  Serial.print("Ax: "); Serial.print(ax_g); Serial.print(" g ");
  Serial.print("Ay: "); Serial.print(ay_g); Serial.print(" g ");
  Serial.print("Az: "); Serial.print(az_g); Serial.print(" g ");
  Serial.print("Gx: "); Serial.print(gx_dps); Serial.print(" dps ");
  Serial.print("Gy: "); Serial.print(gy_dps); Serial.print(" dps ");
  Serial.print("Gz: "); Serial.print(gz_dps); Serial.println(" dps");

  sensors_event_t event;
  bmp.getEvent(&event);
  if (event.pressure) {
    pressure = event.pressure;
    bmp.getTemperature(&temperature);
    //altitude = bmp.pressureToAltitude(pressure);
    Serial.print("BMP180: ");
    Serial.print("Temperature: "); Serial.print(temperature); Serial.print(" C ");
    Serial.print("Pressure: "); Serial.print(pressure); Serial.print(" hPa ");}
    //Serial.print("Altitude: "); Serial.print(altitude); Serial.println(" m");}
  else {Serial.println("BMP180: Error reading pressure data");}


  if (hmc.getEvent(&hmcData)) {
    Serial.print("HMC5883L: ");
    Serial.print("X: "); Serial.print(hmcData.magnetic.x); Serial.print(" uT ");
    Serial.print("Y: "); Serial.print(hmcData.magnetic.y); Serial.print(" uT ");
    Serial.print("Z: "); Serial.print(hmcData.magnetic.z); Serial.println(" uT");
  } else {
  Serial.println("HMC5883L: Error reading magnetometer data");
  }

}
