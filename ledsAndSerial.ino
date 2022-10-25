#define numOfValsRec 5
#define digitsPerValRec 1

int valsRec[numOfValsRec];
int stringLenght = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String recievedString;

bool sNew;

int led1,led3,led4,led5,led2;

int pins[5] = {26, 25, 24, 23, 22};

void setup() {
  Serial.begin(9600);
  for(int i=0; i<5; i++){
    digitalWrite(pins[i], LOW);
  }
}

void loop() {
  receiveData();

  if(sNew){
    for(int i=0; i<5; i++){
      if (valsRec[i] == 1){digitalWrite(pins[i], HIGH);}else{digitalWrite(pins[i],LOW);}
      Serial.print(int(valsRec[i]));
      valsRec[i] = 0;
    }
    Serial.println();
    sNew = false;
  }
  
}


void receiveData() {
  int i = 0;
  while (Serial.available()) {
   char c = Serial.read();
   
    if (c == '$') {
      counterStart = true;
      sNew = true;
    }
    if (counterStart == true )
    {
      if (counter < stringLenght)
      {
        recievedString = String(recievedString + c);
        counter++;
      }
      if (counter >= stringLenght) {
        counter = 0; counterStart = false;

        for(int i=0; i<numOfValsRec; i++){
          int num = (i*digitsPerValRec)+1;
          valsRec[i] = recievedString.substring(num, num + digitsPerValRec).toInt();
          //Serial.print(valsRec[i]);
        }
        //Serial.println();
        recievedString = "";
      }
    }
  }
}
