#include <stdlib.h>

#define WAIT 500
#define THRESH 5000

void set_on_sem(Semaphore *sem){ // passa il semaforo da rosso a verde
    digitalWrite(sem->red, LOW);
    digitalWrite(sem->yellow, LOW);
    digitalWrite(sem->green, HIGH);
};

void set_off_sem(Semaphore *sem){ // passa il semaforo da verde a rosso
    int was_green = digitalRead(sem->green);
    digitalWrite(sem->green, LOW);
    if (was_green){ // se il semaforo prima era verde, devo farlo diventare giallo
        digitalWrite(sem->yellow, HIGH);
        delay(WAIT);
        digitalWrite(sem->yellow, LOW);
    }
    digitalWrite(sem->red, HIGH);
};

/* valuta il tempo trascorso: se non ho usato prima il semaforo sem,
 * o se sono dopo un reset, started_at vale -1. Quindi, inizializzo started_at
 * e non lo tocco più fino a che non ci sarà un altro reset. Calcolo il tempo
 * attuale, poi lo sottraggo al tempo iniziale: se è minore della threshold
 * ritorno TRUE perchè significa che il semaforo può agire, altrimenti FALSE.
 */

int evaluate_condition(Semaphore *sem, volatile byte state){
    unsigned long int current;
    if(state){
      if(sem->started_at < 0) {
          sem->started_at = millis();
      }
      current = millis();
      return (current - sem->started_at < THRESH);
    } else {
      return LOW;
    }
};

void reset_sem(Semaphore *sem){ // riporta il semaforo alla condizione iniziale: luce rossa, nessuna macchina davanti, tempo iniziale mai settato, pir mai letto
    digitalWrite(sem->red, HIGH);
    digitalWrite(sem->yellow, LOW);
    digitalWrite(sem->green, LOW);
    sem->started_at = -1;
};

Semaphore *create_sem(int red, int yellow, int green, int pir){ // alloca la variabile semaforo, serve solo una volta
    Semaphore *sem = (Semaphore *) malloc(sizeof(Semaphore));
    sem->red = red; 
    sem->yellow = yellow; 
    sem->green = green; 
    sem->pir = pir;
    reset_sem(sem);
    return sem;
};
