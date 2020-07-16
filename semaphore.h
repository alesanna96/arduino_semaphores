#ifndef ARDUINO_SEMAPHORES_SEMAPHORE_H
#define ARDUINO_SEMAPHORES_SEMAPHORE_H

/* ho definito il pir come struttura perchè altrimenti tenere previousread e
 * currentread in comune tra i semafori e i pir faceva casino.
 */


typedef struct {
    int red;
    int yellow;
    int green;
    int pir;
    int started_at;
} Semaphore;

void set_on_sem(Semaphore *sem);
void set_off_sem(Semaphore *sem);
int evaluate_condition(Semaphore *sem, volatile byte state);
void reset_sem(Semaphore *sem);
Semaphore *create_sem(int red, int yellow, int green, int pir);

#endif //ARDUINO_SEMAPHORES_SEMAPHORE_H
