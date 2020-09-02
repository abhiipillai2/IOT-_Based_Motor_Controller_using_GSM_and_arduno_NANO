//this program is deveoped by Abhijith S Pillai || not allowed copy or edit || this program is property of Atom Developers inc. 2020


#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial MySim(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2// 10 11 for uno
////
  
  String number = "+918129605783";//sender phone number
  String SMS;
  String message;
  bool flag = false;
////
#define relayOutput 5//relay output pin
//
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  MySim.begin(9600);
  Serial.println("Initializing..."); 
  delay(1000);
  delay(16000);
  MySim.println("AT+CMGF=1"); // Configuring TEXT mode
  //
                                                            delay(1000);
                                                            MySim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
                                                            delay(1000);
                                                            SMS = "hello ! all good ready to go :)";
                                                            MySim.println(SMS);
                                                            delay(100);
                                                            MySim.println((char)26);// ASCII code of CTRL+Z
                                                            delay(1000);
                                                            MySim.println("AT+CNMI=1,2,0,0,0");
  //
  delay(1000);
  MySim.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relayOutput,OUTPUT);
  //initial conditions
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(relayOutput,LOW);
  
  }

void loop()
{

          //for SMS Update only
          //delay(200);
          //MySim.println("AT+CMGF=1");
          //delay(200);
          MySim.println("AT+CNMI=1,2,0,0,0");
          delay(200);
          message=MySim.readString();
          delay(200);
          Serial.println(message);
          delay(200);
                    if (message.indexOf("on")>=0 ||message.indexOf("ON")>=0||message.indexOf("On")>=0)
                      {       
                        //relay operation
                              digitalWrite(LED_BUILTIN, HIGH);
                              digitalWrite(relayOutput, HIGH);
                              //msg operation           
                                              if(flag)
                                              {
                                                Serial.println("all ready started");
                                              }
                                              else{
                                                delay(5000);
                                                            MySim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
                                                            delay(1000);
                                                            SMS = "motor is ON now";
                                                            MySim.println(SMS);
                                                            delay(100);
                                                            MySim.println((char)26);// ASCII code of CTRL+Z
                                                            delay(1000);
                                                            MySim.println("AT+CNMI=1,2,0,0,0");
                                                            delay(1000); 
                                                            flag= true; 
                                              }
                                                             
                              
                      }
                     
                      else if(message.indexOf("off")>=0 ||message.indexOf("OFF")>=0||message.indexOf("Off")>=0)
                      {
                        //relay operation 
                              digitalWrite(LED_BUILTIN, LOW);
                              digitalWrite(relayOutput, LOW);
                                                             //msg operation
                                                             if(flag)
                                                             {
                                                              delay(5000);
                                                              MySim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
                                                              delay(1000);
                                                              SMS = "motor is OFF now";
                                                              MySim.println(SMS);
                                                              delay(100);
                                                              MySim.println((char)26);// ASCII code of CTRL+Z
                                                              delay(1000);
                                                              MySim.println("AT+CNMI=1,2,0,0,0");
                                                              delay(1000);
                                                              flag = false;
                                                             }
                                                            else{
                                                              Serial.println("alredy stop");
                                                            }
                                                                                      
                      }
              
              delay(250);                                                         
}
