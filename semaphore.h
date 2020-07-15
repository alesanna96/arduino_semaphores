#ifndef ARDUINO_SEMAPHORES_SEMAPHORE_H
#define ARDUINO_SEMAPHORES_SEMAPHORE_H

/* ho definito il pir come struttura perchè altrimenti tenere previousread e
 * currentread in comune tra i semafori e i pir faceva casino.
 */

typedef struct {
  int pin;
  int previous_read;
  int current_read;
} Pir;

typedef struct {
    int red;
    int yellow;
    int green;
    Pir pir;
    int started_at;
    int state;
} Semaphore;

void set_on_sem(Semaphore *sem);
void set_off_sem(Semaphore *sem);
int evaluate_time(Semaphore *sem);
void reset_sem(Semaphore *sem);
int posedge_pir(Pir pir, int state);
Semaphore *create_sem(int red, int yellow, int green, int pir);

#endif //ARDUINO_SEMAPHORES_SEMAPHORE_H
