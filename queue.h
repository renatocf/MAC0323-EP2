/***********************************************/
/**  MAC 0323  -  Estrutura de Dados          **/
/**  IME-USP   -  Primeiro  Semestre de 2013  **/
/**  Turma 45  -  Yoshiharu Kohayakawa        **/
/**                                           **/
/**  Primeiro  Exercício-Programa             **/
/**  Arquivo:  queue.h                        **/
/**                                           **/
/**  Renato Cordeiro Ferreira        7990933  **/
/***********************************************/ 

#ifndef H_QUEUE_INCLUDED
#define H_QUEUE_INCLUDED

/* Bibliotecas */
#include "queue-item.h"

/* Define a estrutura de fila 'Queue' */
typedef struct queue *Queue;

/* Protótipos */
Queue  queueInit  (void);
Q_Item queueGet   (Queue);
void   queueFree  (Queue);
int    queueEmpty (Queue);
void   queuePut   (Queue, Q_Item);

#endif
