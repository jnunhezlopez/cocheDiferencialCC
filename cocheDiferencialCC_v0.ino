#include <SoftwareSerial.h>

//Fecha: 08/09/2021
//Autor: Javier Núñez López
//Descripción: Accionamiento de los motores de CC montados en el chasis del coche
//, los motores llevan un encóder para controlar los giros (velocidad, posición)
//La salida lógica del encóder se controla por interrupciones.
//Para el control de los motores se utiliza la biblioteca de adafruit v1 (según
// su documentación ya está obsoleta).
//para arduino mega los pines 18 y 19 permiten interrupción
#define pinIzda 18
#define pinDcha 19
#include <AFMotor.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
class PID
{
  public:
    PID(float K, float Ki, float Kd);
    int hazControl(float valoractual, float consigna);
    void SetK(float K);
    void SetKi(float Ki);
    void SetKd(float Kd);
    float GetK();
    float GetKi();
    float GetKd();
  private:
    float cK, cKi, cKd;
    float crT, ceT, cpT, cqT, cyT, cuT;
    float cMax_uT=255, cMin_uT=0;
    float ceT_1=0.0, cpT_1=0.0;
    float cM;
    float cconsigna;
};
//*********************    PID     *****************
//float rT, eT, pT, qT, yT, uT;
//float Max_uT=255, Min_uT=75;
//float eT_1=0.0, pT_1=0.0;
//float K=5.0, Ki=3.0, Kd=8.0;
//float M;
float consigna, uTd, uTi;
PID ruedaDcha (5.0,0.5,8.0);
PID ruedaIzda (5.0,0.5,8.0);
//float medida;
//*********************PANTALLA LCD*****************
LiquidCrystal_I2C lcd(0x27,16,2); 
//*********************CONTROL VELOCIDAD*************
int intervalo=500;//tiempo en el que se calcula la velocidad
unsigned long ultimaactualizacion=0;
int contantdcha=0;
int contantizda=0;
float veldcha;
float velizda;
unsigned long intervaloControl=50, ultimoControl=0;
//*********************CONTADORES GIRO*************
int cIzda=0;
int cDcha=0;
//*********************MOTORES DE LAS RUEDAS**************
AF_DCMotor motordcha(3);
AF_DCMotor motorizda(4);
//*********************MAQUINA DE ESTADOS**************
char modo='S';
float parametro;
//**************************************************
//*********************BLUETOOTH**************
SoftwareSerial ConexionBT (50,51);
//**************************************************
void setup() {
  //inicio del puerto serie
  Serial.begin(38400);
  ConexionBT.begin(38400);
  //inicio de la pantalla LCD
  lcd.init();
  //inicio de los motores
  motordcha.setSpeed(255);
  motordcha.run(RELEASE);
  motorizda.setSpeed(255);
  motorizda.run(RELEASE);
  //inicio de las interrupciones
  attachInterrupt(digitalPinToInterrupt(pinIzda), ctaIzda, RISING);
  attachInterrupt(digitalPinToInterrupt(pinDcha), ctaDcha, RISING);  
}

void loop() {
  leeBT();
  leeSerial();  
  calcVels(millis(),'N');
  if (modo != 'S')
    imprimeLCD("Dcha:" + String(veldcha),"Izda:" + String(velizda));
  switch (modo){
    case 'D':
      cDcha=0;
      while(cDcha<parametro){
        motordcha.run(FORWARD);
        Serial.println(cDcha);
      }
      motordcha.run(RELEASE);
      modo='S';
      break;
    case 'I':
      cIzda=0;
      while(cIzda<parametro){
        motorizda.run(FORWARD);
        Serial.println(cIzda);
      }
      motorizda.run(RELEASE);
      modo='S';    
      break;        
    case 'B':
      cIzda=0;
      cDcha=0;
      while(cIzda<parametro && cDcha<parametro){
        motorizda.run(FORWARD);
        motordcha.run(FORWARD);
        Serial.println(cIzda);
        Serial.println(cDcha);
      }
      motorizda.run(RELEASE);
      motordcha.run(RELEASE);            
      modo='S';    
      break;   
    case 'W':
      lcd.display();
      motordcha.setSpeed(parametro);
      //motorizda.setSpeed(parametro);    
      motordcha.run(FORWARD);
      //motorizda.run(FORWARD);
      break;     
    case 'Q':
      lcd.display();
      motorizda.setSpeed(parametro);    
      motorizda.run(FORWARD);
      break;        
    case 'C':
      lcd.display();
      if (millis()-ultimoControl > intervaloControl)
      {
        ultimoControl = millis();
        //PID(veldcha,consigna);     
        uTi=ruedaIzda.hazControl(velizda,consigna); 
        uTd=ruedaDcha.hazControl(veldcha,consigna);
      }
      motorizda.setSpeed(uTi);
      motorizda.run(FORWARD);
      motordcha.setSpeed(uTd);
      motordcha.run(FORWARD);
      break;           
    case 'S':
      motordcha.run(RELEASE);
      motorizda.run(RELEASE);
      lcd.noDisplay();
      lcd.noBacklight();
      break;      
  }
}
void ctaIzda()
{
  cIzda++;
}
void ctaDcha()
{
  cDcha++;
}
void calcVels(unsigned long tactual, char serie)
{
  unsigned int intervaloreal;
  float cte;
  if (tactual- ultimaactualizacion > intervalo)
  {
    intervaloreal = tactual-ultimaactualizacion;
    cte = 3000/intervaloreal; //60/20*1000/intervalo, para convertir la velocidad en r.p.m    
    veldcha = (cDcha-contantdcha);
    velizda = (cIzda-contantizda);
    ultimaactualizacion = tactual;
    contantdcha=cDcha;
    contantizda=cIzda;
    if (serie == 'S')
    {
      Serial.println("Velocidades:  derecha izquierda ");
      Serial.print("               ");
      Serial.print(veldcha);
      Serial.print("     ");
      Serial.println(velizda);
      Serial.print("Intervalo real:");
      Serial.println(intervaloreal);
    }
  }
}
void configuraBT()
{
  if (Serial.available())
    ConexionBT.write(Serial.read());
  if (ConexionBT.available())
    Serial.write(ConexionBT.read());
}
