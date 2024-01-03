void setup() {
  Serial.begin(9600);

  Serial.println("Hello1");
  Serial.println("Hello2");
  Serial.println("Hello3");
  Serial.println("Hello4");
  Serial.println("Hello5");

// sau putem sa utilizam functia "for" ca sa facem o bucla si sa scriem de 5 ori
  for (int i = 1; i<6; i++){
    Serial.println("Hello"+i);
  }
// putem sa folosim si bucla "while"  
  int i = 1;
  while (i<6){
    Serial.println("Hello"+i);
    i++;
  }

}

void loop() {

}
