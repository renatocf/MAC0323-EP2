/***********************************************/
/**  MAC 0323  -  Estrutura de Dados          **/
/**  IME-USP   -  Primeiro  Semestre de 2013  **/
/**  Turma 45  -  Yoshiharu Kohayakawa        **/
/**                                           **/
/**  Primeiro  Exercício-Programa             **/
/**  Arquivo:  queue-internal.h               **/
/**                                           **/
/**  Renato Cordeiro Ferreira        7990933  **/
/***********************************************/ 

#ifndef H_QUEUE_INTERNAL_INCLUDED
#define H_QUEUE_INTERNAL_INCLUDED
#include "queue.h"

#define BUF_INIT_SIZE 3000

/* Define os nódulso da fila e os links para eles */
typedef struct node *Link;
typedef struct node {
    Q_Item item;
    Link next;
} Node;

/* Define a estrutura de fila 'Queue' */
struct queue {
    Link init;
    Link end;
};

/* Cria buffer para uso da biblioteca */
static Queue buffer;
static int buf_size = BUF_INIT_SIZE/2;

/* Funções de manipulação do buffer */
static void createBuffer();
static Link getBufferNode();
static void returnToBuffer(Link node);
static void resizeBuffer();
#endif
