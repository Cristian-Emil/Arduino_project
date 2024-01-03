void setup() {
  Serial.begin(9600);

  int temp = 28;

  if (temp == 28){
    Serial.println("Temperatura e OK");
  }

  if (temp <28){
    Serial.println("Temperatura e OK");
  }

  if (temp !=28){
    Serial.println("Temperatura e OK");
  }

  if (temp >= 28){
    Serial.println("Temperatura e OK");
  }
// sau putem pune conditia sa fie intre 2 parametrii - folosim && = si
  if ((temp >= 26) && (temp <30)){
    Serial.println("Temperatura e OK");
  }

// sau putem pune conditia sa fie unul din 2 parametrii - folosim || = sau
  if ((temp >= 26) || (temp <30)){
    Serial.println("Temperatura e OK");
  }
// sau avem conditia ca daca nu este ce trebuie folosim ELSE
  if (temp >= 32){
    Serial.println("Temperatura e OK");
  }
  else {
    Serial.println("Temperatura nu e OK");
  }

// sau avem conditia ca daca nu este ce trebuie folosim conditia 2 sau 3 sdi apoi ELSE
  if (temp >= 32){
    Serial.println("Temperatura e OK");
  }
  else if (temp == 30){
    Serial.println("Atunci este 'else if' ca varianta");
  }
  else {
    Serial.println("Temperatura nu e OK");
  }

}

void loop() {


}
