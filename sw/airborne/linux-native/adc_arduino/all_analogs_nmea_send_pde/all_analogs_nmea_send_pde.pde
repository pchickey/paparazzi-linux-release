
//int a0 = 0;
int a1 = 0;
int a2 = 0;
int a3 = 0;

int counter = 0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  
  //a0 = analogRead(0);            
  a1 = analogRead(1);
  a2 = analogRead(2);
  a3 = analogRead(3);

  //Serial.print("$ARD,A0," );                       
  //Serial.println(a0);      
  
  
  Serial.print("$A1," );                       
  Serial.println(a1);        
  Serial.print("$A2," );                       
  Serial.println(a2);    
  Serial.print("$A3," );                       
  Serial.println(a3);    
  
 // Serial.print("$ARD,SEQ,");
 // Serial.println(counter);
 // counter++;
 // delay(2);                     
}
