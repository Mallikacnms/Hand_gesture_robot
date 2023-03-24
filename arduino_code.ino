#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

long timer = 0;

int AD1 = 3;  // Right
int AD2 = 4;  // Right
int AD3 = 5;  // Left
int AD4 = 6;  // Left

double xAn;
double yAn;
double zAn;

void setup() {
  
  pinMode(AD1, OUTPUT);
  pinMode(AD2, OUTPUT);
  pinMode(AD3, OUTPUT);
  pinMode(AD4, OUTPUT);

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
  Serial.begin(9600);
}

void loop() {

  mpu6050.update();
//
//  delay(100);
//  
  xAn = mpu6050.getAngleX();
  yAn = mpu6050.getAngleY();
  zAn = mpu6050.getAngleZ();
//
  if(millis() - timer > 1000){
//    
   Serial.println("=======================================================");
    
    Serial.print("angleX : ");Serial.print(xAn);
    Serial.print("\tangleY : ");Serial.print(yAn);
    Serial.print("\tangleZ : ");Serial.println(zAn);
    Serial.println("=======================================================\n");
    timer = millis();
  }
  

  if ((zAn < -25)) // forward 
  
  {
    digitalWrite(AD1, HIGH);
    digitalWrite(AD2, HIGH);
    digitalWrite(AD3, LOW);
    digitalWrite(AD4, LOW);
    Serial.println("0011");
    
  }
  else if (zAn > 40) // backwards
  {
    digitalWrite(AD1, LOW);
    digitalWrite(AD2, LOW);
    digitalWrite(AD3, HIGH);
    digitalWrite(AD4, HIGH);
    Serial.println("1100");
  }
  else if (yAn > -40) // left
  {
    digitalWrite(AD1, LOW);
    digitalWrite(AD2, HIGH);
    digitalWrite(AD3, HIGH);
    digitalWrite(AD4, HIGH);
    Serial.println("1000");
  }
  else if (yAn < -120) // right 
  {
    digitalWrite(AD1, HIGH);
    digitalWrite(AD2, LOW);
    digitalWrite(AD3, HIGH);
    digitalWrite(AD4, HIGH);
    Serial.println("0100");
  }
  else
  {
    digitalWrite(AD1, HIGH);
    digitalWrite(AD2, HIGH);
    digitalWrite(AD3, HIGH);
    digitalWrite(AD4, HIGH);
    Serial.println("0000");     
  }

}
