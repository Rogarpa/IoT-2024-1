/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por:
  García Padrilla Rodrigo 
  Giron Jimenez Emmanuel
  Última modificación: 30-diciembre-2023
*/
void setup() {
  pinMode(13, INPUT);
  Serial.begin(115200);

}

void loop(){
  Serial.print(analogRead(13));
  Serial.print("\n");
  delay(250);
}