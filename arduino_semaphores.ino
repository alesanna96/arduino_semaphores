// tensione 5V
#define pir_a 2 // crossroad A
#define red_a 7
#define yellow_a 8
#define green_a 9

#define pir_b 3 // crossroad B
#define red_b 11
#define yellow_b 12
#define green_b 13

/*
#define pir_ped -1 // crossroad pedestrians: high priority
#define lights_ped {-1, -1, -1}
*/

#include "semaphore.h"

void setup() {
  
 pinMode(red_a, OUTPUT);
 pinMode(yellow_a, OUTPUT);
 pinMode(green_a, OUTPUT);

 pinMode(red_b, OUTPUT);
 pinMode(yellow_b, OUTPUT);
 pinMode(green_b, OUTPUT);
 
 pinMode(pir_a, INPUT);
 pinMode(pir_b, INPUT);
 
 Serial.begin(9600);
};



/*  definisci i semafori: ogni volta che bisogna aggiungere un semaforo regolare,
 *  si cambia DIM, si aggiungono i led e il pir nella sezione setup e si aggiunge una riga
 *  di inizializzazione richiamando create_sem. Tutto il resto dello sketch rimane identico.
 */
#define DIM 2

Semaphore *sem_a = create_sem(red_a, yellow_a, green_a, pir_a);
Semaphore *sem_b = create_sem(red_b, yellow_b, green_b, pir_b);

Semaphore *sem_vett[DIM] = {sem_a, sem_b};

void loop(){
  int prova = LOW;
  Serial.print(prova);
  prova = not prova;
  Serial.print(prova);
  Serial.print(prova == HIGH);
  int i, j;

  // aggiorna lo stato di tutti i semafori
  for(i = 0; i < DIM; i++){
    sem_vett[i]->state = posedge_pir(sem_vett[i]->pir, sem_vett[i]->state);
  }
  /* controlla tutti i semafori in ordine
   *  valuta la condizione per cui il semaforo deve funzionare in 3 modi:
   *  è passato troppo tempo o no: evaluate_time da semaphore.h
   *  c'è qualcuno davanti al semaforo: lo stato è HIGH
   *  non ci sono semafori con più alta priorità davanti: il ciclo controlla in ordine, 
   *  e se un semaforo agisce, c'è un break che lo interrompe. Da ciò consegue che
   *  i semafori sono mutualmente escludenti e che verranno attivati in ordine.
   */
  int entered = LOW; // flag che controlla se ho azionato almeno un semaforo
  for(i = 0; i < DIM; i++){
    if(evaluate_time(sem_vett[i]) && sem_vett[i]->state){ // condizione di entrata del semaforo i-esimo
      for (j = 0; j < DIM; j++){ // tieni rossi tutti i semafori che non siano quello giusto
          if(i != j) {
            set_off_sem(sem_vett[i]); 
          }
      }
      set_on_sem(sem_vett[i]); // accendi il semaforo giusto
      entered = HIGH; // segnala che sei entrato in un semaforo
      break; // interrompi il ciclo, puoi eseguire solo un semaforo alla volta
    }
  }
  
  if(entered == LOW){ // se non sei entrato in nessun semaforo, serve un reset
    for(i = 0; i < DIM; i++){ // riporta tutti i semafori alla condizione iniziale
      reset_sem(sem_vett[i]); 
    }
  }
  
}
