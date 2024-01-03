void setup() {
  // Inițializare port serial cu o viteză de transmisie de 9600 bps
  Serial.begin(9600);
}

void loop() {
  // Variabilă pentru a stoca o valoare
  int valoare = analogRead(A0);

  // Afișează valoarea pe portul serial
  Serial.print("Valoarea citită: ");
  Serial.println(valoare);

  // O pauză de 1 secundă între citiri
  delay(1000);
}
