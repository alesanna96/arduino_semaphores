#define pirA 2 //incrocio A
#define redA 7
#define yellowA 8
#define greenA 9

#define pirB 3 //incrocio B
#define redB 11
#define yellowB 12
#define greenB 13

#define on HIGH
#define off LOW

void setup() {
 pinMode(redA, OUTPUT);
 pinMode(yellowA, OUTPUT);
 pinMode(greenA, OUTPUT);
 pinMode(pirA, INPUT);

 digitalWrite(redA, on);
 digitalWrite(yellowA, off);
 digitalWrite(greenA, off);

 pinMode(redB, OUTPUT);
 pinMode(yellowB, OUTPUT);
 pinMode(greenB, OUTPUT);
 pinMode(pirB, INPUT);

 digitalWrite(redB, on);
 digitalWrite(yellowB, off);
 digitalWrite(greenB, off);

 Serial.begin(9600); //Initialize serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pirA) == HIGH & digitalRead(pirB) == LOW)
  { 
    Serial.println("Motion has been detected in A!");
    //siccome i semafori partono tutti e due da rosso questa parte si può lasciare così
    delay(1000); // aspetta 1 sec prima di cambiare status
    digitalWrite(redA, off);//appena il pir rileva la macchina in coda il semaforo passa da rosso a verda
    digitalWrite(greenA,on);
    delay(5000); // il verde rimane 5 secondi, giusto per fare una prova    
    digitalWrite(greenA, off);
    digitalWrite(yellowA,on);
    delay(2000);//il giallo rimane 3 secondi
    digitalWrite(yellowA,off);
    digitalWrite(redA, on);//il semaforo torna rosso
    }
   else if (digitalRead(pirB) == HIGH & digitalRead(pirA) ==LOW)
  { 
    Serial.println("Motion has been detected in B!");
    delay(1000); // aspetta 1 sec prima di cambiare status
    digitalWrite(redB, off);//appena il pir rileva la macchina in coda il semaforo passa da rosso a verda
    digitalWrite(greenB,on);
    delay(5000); // il verde rimane 5 secondi, giusto per fare una prova    
    digitalWrite(greenB, off);
    digitalWrite(yellowB,on);
    delay(2000);//il giallo rimane 3 secondi
    digitalWrite(yellowB,off);
    digitalWrite(redB, on);//il semaforo torna rosso
    }
    else if (digitalRead(pirB) == HIGH & digitalRead(pirA) == HIGH){
      //se arrivano due macchine allo stesso tempo dai precedenza ad A per 5 secondi, poi fai cambiare a B
      delay(1000); // aspetta 1 sec prima di cambiare status
    digitalWrite(redA, off);//appena il pir rileva la macchina in coda il semaforo passa da rosso a verda
    digitalWrite(greenA,on);
    delay(5000); // il verde rimane 5 secondi, giusto per fare una prova    
    digitalWrite(greenA, off);
    digitalWrite(yellowA,on);
    delay(2000);//il giallo rimane 3 secondi
    digitalWrite(yellowA,off);
    digitalWrite(redA, on);//il semaforo torna rosso
    digitalWrite(redB, off);//appena il pir rileva la macchina in coda il semaforo passa da rosso a verda
    digitalWrite(greenB,on);
    delay(5000); // il verde rimane 5 secondi, giusto per fare una prova    
    digitalWrite(greenB, off);
    digitalWrite(yellowB,on);
    delay(2000);//il giallo rimane 3 secondi
    digitalWrite(yellowB,off);
    digitalWrite(redB, on);//il semaforo torna rosso
    }
      
    delay(1000);//aspetta 1 secondi per la prossima lettura del pir
}
