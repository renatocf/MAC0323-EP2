/***********************************************/
/**  MAC 0323  -  Estrutura de Dados          **/
/**  IME-USP   -  Primeiro  Semestre de 2013  **/
/**  Turma 45  -  Yoshiharu Kohayakawa        **/
/**                                           **/
/**  Segundo   Exercício-Programa             **/
/**  Arquivo:  main.c                         **/
/**                                           **/
/**  Renato Cordeiro Ferreira        7990933  **/
/***********************************************/ 

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                               BIBLIOTECAS 
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
#include<stdarg.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/* Opções */
#include "getopt.h"

/* Módulos do cubo/esfera */
#include "Point.h"
#include "Dimension.h"

#include "queue.h"
#include "list.h"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                          ESTRUTURAS/MENSAGENS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* Opções da linha de comando */
typedef struct options {
    int N;   /* Número de pontos */
    int C;   /* Pontos na stdin (Parte I) */
    int D;   /* Número de dimensóes dos pontos */
    int L;   /* Pontos na stdin (Parte II) */
    int M;   /* Número de testes */
    float d; /* Distância entre pontos */
    int s;   /* Semente de números aleatórios */
    int v;   /* Verbosidade nível 1 */
    int V;   /* Verbosidade nível 2 */
    int h;   /* Ajuda */
} Options;

/* Mensagens */
char usage[] = "Uso: EP1 -N -D [-d] [-M] [-s] [-C] [-L] [-v] [-V]\n"
               "Digite -h para mais informações \n";
char error[] = "Erro: número de pontos requerido como argumento\n";
char help[]  = "LIMIAR DE CONEXIDADE PARA CERTOS GRAFOS GEOMÉTRICOS\n"
               "\n"
               "Lista de opções:\n"
               "* -N: número de pontos;\n"
               "* -D: número de dimensóes;\n"
               "* -d: distância para verificar conexidade (modo 1);\n"
               "* -M: número de rodadas para cálculo da 'densidade\n"
               "      normalizada crítica para conexidade' (modo 2);\n"
               "* -s: semente de números aleatórios;\n"
               "* -v: verbosidade 1;\n"
               "* -V: verbosidade 2;\n";

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                               PROTÓTIPOS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* Funções auxiliares */
int   receive_arguments (int argc, char **argv, Options *args);
point *random_points    (int N, int D, int vmode);
static int compare_distances(const void *p1, const void *p2);
point *get_points(int N, int verb_mode);

/* Funções para os modos de funcionamento 1 e 2 */
float euclidean_minimum_spanning_tree(point *p, int N, int vmode);
int check_connectivity(point *p, int N, float d, int vmode);

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                  MAIN
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
int main(int argc, char **argv)
{
    /** VARIÁVEIS *****************************************************/
        int i;         /* Contador auxiliar para laços               */
        float d;       /* Menor aresta que gera um grafo conexo      */
        float dp = 0;  /* Limiar de conexidade para um único grafo   */
        float cp = 0;  /* Média dos dp para 'M' elementos gerados    */
        int func_err;  /* Retorno de sucesso/erro das funções        */
        int vmode = 0; /* Verbosidade do programa (-v ou -V)         */
        point *Points; /* Vetor de pontos D-dimensionais             */
        
        /* Struct com argumentos da linha de comando */
        Options args = { 0, 0, 1, 0, 0, 0, 314159265, 0, 0 }; 

    /** ARGUMENTOS ****************************************************/
        func_err = receive_arguments(argc, argv, &args);
        if(func_err) return EXIT_FAILURE;
        
        if(args.h == 1)
        {
            printf("\n%s\n", help);
            return EXIT_SUCCESS;
        }
        
        if(args.N == 0 && args.C == 0 && args.L == 0) 
        {
            printf("\n%s%s\n", error, usage);
            return EXIT_FAILURE;
        }
        
        vmode = args.v + args.V;
    
    /** PONTOS ALEATÓRIOS *********************************************/
        set_seed(args.s); /* Semente de números aleatórios */
        if(args.C || args.L)
        {
            Points = get_points(args.N, vmode);
            if(Points == NULL) return EXIT_FAILURE;
        }
        
    /** MODO 1: CONEXIDADE ********************************************/
        if(args.d > 0) 
        {
            /* Gera pontos aleatoriamente se não vierem da stdin */
            if(!args.C) Points = random_points(args.N, args.D, vmode);
            
            func_err = check_connectivity
                (Points, args.N, args.d, vmode);
            if(func_err) 
                printf("Grafo não é conexo para d = %g\n", args.d);
            else 
                printf("Grafo é conexo para d = %g\n", args.d);
            
            free(Points);
        }
        
    /** MODO 2: DENSIDADE NORMALIZADA CRÍTICA *************************/
        if(args.M > 0)
        {
            if(args.L) args.L = 1;
            for(i = 0; i < args.M; i++) 
            {
                /* Gera pontos aleatóriamente */
                if(!args.L) Points = random_points(args.N, args.D, vmode);
                
                /* Calcula a árvore de custo mínimo */
                d = euclidean_minimum_spanning_tree (Points, args.N, vmode);
                
                /* Densidade normalizada crítica */
                dp = d*d*(args.N/log(args.N)); cp += dp;
                if(vmode) printf("%d: d*(p) = %g\n", i, dp);
                
                free(Points);
            }
            cp /= args.M; /* Limiar de conexidade */
            printf("Limiar de conexiade c*(p) = %f", dp);
        }
    
    return EXIT_SUCCESS;
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                 FUNÇÕES  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
point *get_points(int N, int verb_mode)
{
    point *Points = NULL, a; 
    List p; Link aux;
    int i = 0; 
    float x, y;
    
    char *format = (char *) malloc((3*N+1)*sizeof(*format));
    strcpy(format, "aaa");
    format[0] = 'a';
    for(i = 0; i < N-1; i++) strcat(format, "%g ");
    format[3*N] = '\0';
    printf("ok\n");
    for(i = 0; i < 3*N+1; i++) printf("%c\n", format[i]);
    free(format);
    
    /* Lista de pontos recebidas da stdin */
/*    p = list_init(); N = 0;
    for(N = 0; scanf("%g %g", &x, &y) != EOF; N++)
        { a.x = x; a.y = y; list_insert(p, a); }
    if(N == 0) return NULL;
    
    aux = list_first(p);
    Points = (point *) malloc(N * sizeof(*Points));
    
    \% Cria vetor a partir da lista ligada %\
    for(i = 0; i < N; i++, aux = list_next(aux)) 
    {
        Points[i] = list_remove(p, aux);
        if(verb_mode) 
            printf("%d: %f %f\n", i, Points[i].x, Points[i].y);
    }
    
    list_free(p); free(format)*/;
    return Points;
}

point *random_points (int N, int D, int vmode)
{
    int i = 0;
    /* Gera vetor com pontos aleatórios */
    point *Points = (point *) malloc(N * sizeof(*Points));
    
    set_dimension(D);
    for(i = 0; i < N; i++) 
    {
        Points[i] = randPoint();
        if(vmode) { printf("%d: ", i); print_point(Points[i]); }
    }
    return Points;
}

float euclidean_minimum_spanning_tree(point *p, int N, int vmode)
{
    float *distances = (float *) malloc((N*(N-1)/2) * sizeof(*distances));
    int l = 0, r = N*(N-1)/2 - 1, q = (l+r)/2;
    int i, j, k = 0, connected = 0; float dp;
    
    for(i = 0; i < N; i++)
        for(j = i+1; j < N; j++)
            distances[k++] = distance(p[i], p[j]);
    
    qsort(distances, N*(N-1)/2, sizeof(float), compare_distances);
    
    while(l < r)
    {
        dp = distances[q];
        connected = check_connectivity(p, N, dp, vmode);
        (connected) ? (r = q-1) : (l = q+1); q = (l+r)/2;
    }
    printf("d*(p): %g\n", dp);
    
    free(distances);
    return dp;
}

static int compare_distances(const void *p1, const void *p2)
{
    float P1 = *(float *) p1; float P2 = *(float *) p2;
    if(P1 < P2) return -1;
    if(P1 > P2) return 1;
    return 0;
}

int check_connectivity(point *p, int N, float d, int vmode)
{
    /** VARIÁVEIS *****************************************************/
        int i;           /* Batedor para percorrer vetor de pontos   */
        point now;       /* Ponto de conexões a serem checadas       */
        float dis;       /* Auxiliar de distância entre pontos       */
        int count = 0;   /* Total de conexões encontradas            */
        int scount = 0;  /* Número parcial de conexões               */
        Queue connected; /* Lista de pontos conectados               */
    
        connected = queueInit();
        queuePut(connected, p[0]);
    
    /** CHECA CONECTIVIDADE *******************************************/
        while(!queueEmpty(connected))
        {
            now = queueGet(connected);
            for(i = 0; i < N; i++)
            { 
                scount = 0; dis = distance(now, p[i]);
                if(dis < d && !eq(now,p[i]) )
                    { scount++; queuePut(connected, p[i]); }
            }
            if((count += scount) == N-1) break;
        }
    
    /** LIBERAÇÂO DE VARIÁVEIS/RETORNO ********************************/
        queueFree(connected); 
        if(count == N-1) return EXIT_SUCCESS;
        return EXIT_FAILURE;
}

int receive_arguments(int argc, char **argv, Options *args)
    /* Recebe os argumentos da linha de comando e os 
     * armazena na struct correspondente */
{
    char opt; /* int i = 0; */
    while((opt = getopt(argc, argv, "CD:LN:M:s:d:vVh")) != NONE)
    {
        switch(opt)
        {
            case 'N':
                args->N = atoi(optarg); break;
            case 'C':
                args->C = 1; break;
            case 'D':
                args->D = atoi(optarg); break;
            case 'L':
                args->D = 1; break;
            case 'M':
                args->M = atoi(optarg); break;
            case 'd':
                args->d = atof(optarg); break;
            case 's':
                args->s = atoi(optarg); break;
            case 'v':
                args->v = 1; break;
            case 'V':
                args->v = 1; args->V = 2; break;
            case 'h':
                args->h = 1; break;
            case '?':
                printf("Argumento -%c desconhecido\n", optopt);
                return EXIT_FAILURE;
        }
    } /* while */
    return EXIT_SUCCESS;
}
