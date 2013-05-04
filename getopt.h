/***********************************************/
/**  MAC 0323  -  Estrutura de Dados          **/
/**  IME-USP   -  Primeiro  Semestre de 2013  **/
/**  Turma 45  -  Yoshiharu Kohayakawa        **/
/**                                           **/
/**  Primeiro  Exercício-Programa             **/
/**  Arquivo:  getopt.h                       **/
/**                                           **/
/**  Renato Cordeiro Ferreira        7990933  **/
/***********************************************/ 

#ifndef H_GETOPT_INCLUDED
#define H_GETOPT_INCLUDED

#define NONE -1 
/* Retorno padrão para argumento não encontrado */

extern char *optarg;
extern int optind, optopt;

char getopt(int argc, char **argv, char *optstring);
#endif
