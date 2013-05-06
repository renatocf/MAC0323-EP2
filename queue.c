/***********************************************/
/**  MAC 0323  -  Estrutura de Dados          **/
/**  IME-USP   -  Primeiro  Semestre de 2013  **/
/**  Turma 45  -  Yoshiharu Kohayakawa        **/
/**                                           **/
/**  Primeiro  Exercício-Programa             **/
/**  Arquivo:  queue.c                        **/
/**                                           **/
/**  Renato Cordeiro Ferreira        7990933  **/
/***********************************************/ 

#include<stdio.h>
#include<stdlib.h>

#include "queue-internal.h"
/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                        FUNÇÕES DE USO EXTERNO   
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
Queue queueInit()
{
    Queue new_queue;
    
    /* Inicializa a nova fila */
    new_queue = (Queue) malloc(sizeof(*new_queue));
    new_queue->init = new_queue->end = NULL;
    
    /* Cria buffer, caso este não tenha sido inicializado */
    if(buffer == NULL) createBuffer();
    
    return new_queue;
}

int queueEmpty(Queue queue)
{
    if(queue->end == NULL) return 1;
    return 0;
}

void queuePut(Queue queue, Q_Item item)
{
    Link new_node;
    
    /* Checa disponibilidade do buffer */
    if(queueEmpty(buffer)) resizeBuffer();
    
    /* Cria novo nódulo da fila */
    new_node = getBufferNode(); 
    /* printf("getBufferNode\n"); */
    new_node->item = item;
    
    /* Inclui o novo nódulo na fila */
    new_node->next = NULL;
    
    if(queue->end == NULL) queue->end = new_node;
    else queue->init->next = new_node;
    
    queue->init = new_node;
}

Q_Item queueGet(Queue queue)
{
    Q_Item vestige;
    Link old_node;
    
    /* Tira o nódulo da fila */
    old_node = queue->end;
    queue->end = queue->end->next;
    
    /* Devolve o nódulo para o buffer */
    vestige = old_node->item;
    returnToBuffer(old_node);
    
    return vestige;
}

void queueFree(Queue queue)
{
    Link next_node;
    while(!queueEmpty(queue))
    {
        next_node = queue->end;
        queue->end = next_node->next;
        returnToBuffer(next_node);
    } 
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                        FUNÇÕES DE USO INTERNO   
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
static void createBuffer()
{
    int i = 0; /* Contador */
    
    /* Cria a fila 'buffer' */
    buffer = (Queue) malloc(sizeof(*buffer));
    
    /* Vetor de nódulos, com tamanho BUF_INIT_SIZE */
    buffer->end = (Link) malloc(BUF_INIT_SIZE * sizeof(*buffer->end));
    
    /* Nódulos apontam sequencialmente de um para outro */
    for(i = 0; i < BUF_INIT_SIZE-1; i++)
        buffer->end[i].next = &buffer->end[i+1];
    buffer->end[i].next = NULL;
    
    /* Arruma sinal para o fim da fila */
    buffer->init = &buffer->end[BUF_INIT_SIZE-1];
    buffer->init->next = NULL;
}

static Link getBufferNode()
{
    Link queue_node;
    
    /* Tira o nódulo da fila */
    queue_node = buffer->end;
    buffer->end = buffer->end->next;
    
    return queue_node;
}

static void returnToBuffer(Link node)
{
    /* Desassocia nódulo da fila antiga */
    node->next = NULL;
    
    /* Devolve nódulo ao buffer */
    if(queueEmpty(buffer)) buffer->end = node;
    else buffer->init->next = node;
    
    buffer->init = node;
}

static void resizeBuffer()
{
    int i;
    Queue new_buffer;
    new_buffer = (Queue) malloc(sizeof(*new_buffer));
    
    /* Dobra o tamanho do buffer */
    buf_size = 2*buf_size;
    new_buffer->end = 
        (Link) malloc(buf_size * sizeof(*new_buffer->end));
    
    /* Nódulos apontam sequencialmente de um para outro */
    for(i = 0; i < buf_size-1; i++)
        new_buffer->end[i].next = &new_buffer->end[i+1];
    new_buffer->init = &new_buffer->end[buf_size-1];
    
    /* Adicionamos os novos nódulos ao início da fila */
    if(queueEmpty(buffer)) buffer->end = new_buffer->end;
    else buffer->init->next = new_buffer->end;
    
    buffer->init = new_buffer->init;
    
    /* Arruma sinal para o fim da fila */
    buffer->init->next = NULL;
    
    /* Libera o ponteiro auxiliar 'new_buffer' */
    free(new_buffer); new_buffer = NULL;
}
