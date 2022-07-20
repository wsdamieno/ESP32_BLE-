void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //always use the same speed
}

int i=0; 

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("Je suis à la position : %d \n", i);

  delay(1000); // wait 1 second between two consecutive printing
  i++;
} 
