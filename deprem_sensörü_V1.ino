
#include <Arduino.h>
#include <TinyMPU6050.h>

unsigned long SimdikiZaman = 0;
unsigned long OncekiZaman = 0;
unsigned long aralik = 60001;
unsigned long aralikled = 60001;


float pos_offset = 10;
float neg_offset = -10;
long angle_x, angle_y, angle_z, offset_x, offset_y, offset_z;
MPU6050 mpu (Wire);

void setup() {

  // Initialization
  mpu.Initialize();

  // Calibration
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  Serial.println("Calibration complete!");
  Serial.println("Offsets:");
  Serial.print("AccX Offset = ");
  Serial.println(mpu.GetAccXOffset());
  Serial.print("AccY Offset = ");
  Serial.println(mpu.GetAccYOffset());
  Serial.print("AccZ Offset = ");
  Serial.println(mpu.GetAccZOffset());
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());
  
  pinMode(14,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(9, LOW);
    
  delay(1000);
  for(int i=0; i<200;i++){
   mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();
  }
  Serial.print("offset_x = ");
  Serial.print(offset_x);
  Serial.print("  /  offsetY = ");
  Serial.print(offset_y);
  Serial.print("  /  offsetZ = ");
  Serial.println(offset_z);
  
}

void loop() {
  mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();

 for(int i=0; i<5;i++){
  mpu.Execute();
  angle_x = mpu.GetAngX();
  angle_y = mpu.GetAngY();
  angle_z = mpu.GetAngZ();
 }

  Serial.print("AngX = ");
  Serial.print(angle_x - offset_x);
  Serial.print("  /  AngY = ");
  Serial.print(angle_y - offset_y);
  Serial.print("  /  AngZ = ");
  Serial.println(angle_z - offset_z);
  Serial.println("sensor çalısıyor");
  
  SimdikiZaman = millis();
  Serial.println(SimdikiZaman);
  
  if  (SimdikiZaman - OncekiZaman >= aralikled)
  {
    Serial.println("led sondu");
    OncekiZaman = SimdikiZaman;
    digitalWrite(13,LOW);   
  }
    
 if ( pos_offset < angle_x - offset_x || neg_offset > angle_x - offset_x || pos_offset < angle_y - offset_y || neg_offset > angle_y - offset_y || pos_offset < angle_z - offset_z || neg_offset > angle_z - offset_z){
      Serial.println("if e girildi");
  /*  
  mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();
  Serial.println("geldi");
  */
    delay(50);    
    while(1){
    SimdikiZaman = millis();
    Serial.println("while e girildi");
    Serial.println(SimdikiZaman);
    Serial.println(OncekiZaman);
    Serial.print("fark:  ");
    Serial.println(SimdikiZaman - OncekiZaman);
    Serial.println("-------------------");
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    delay(50);

    bool buton ;
    buton = digitalRead(2);
    if(buton == true){
    digitalWrite(9,LOW);
    digitalWrite(13,HIGH);
    Serial.println("butona basıldı bekleniyor...");
    delay(3000);
    OncekiZaman = SimdikiZaman;
    break;}
    
  if  (SimdikiZaman - OncekiZaman >= aralik)
  {
    Serial.println("süre doldu");
    OncekiZaman = SimdikiZaman;
    kalibre();
    break;
  }
  } 

 }  
}


  
void buton()
{
  Serial.println("butona girdi");
  bool buton ;
  buton = digitalRead(2);
  if(buton == true){
    digitalWrite(9,LOW);
    digitalWrite(13,HIGH);
    delay(3000);
    return;}
 }

 void kalibre()
 {
    // Initialization
  mpu.Initialize();

  // Calibration
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  Serial.println("Calibration complete!");
  Serial.println("Offsets:");
  Serial.print("AccX Offset = ");
  Serial.println(mpu.GetAccXOffset());
  Serial.print("AccY Offset = ");
  Serial.println(mpu.GetAccYOffset());
  Serial.print("AccZ Offset = ");
  Serial.println(mpu.GetAccZOffset());
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());
    
  delay(1000);
  for(int i=0; i<200;i++){
   mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();
  }
  Serial.print("offset_x = ");
  Serial.print(offset_x);
  Serial.print("  /  offsetY = ");
  Serial.print(offset_y);
  Serial.print("  /  offsetZ = ");
  Serial.println(offset_z);

 }
