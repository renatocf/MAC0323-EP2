point randPoint()
{
    int D = get_dimension();
    int i; float S = 0, R, K; 
    
    /* Vetor de ponto D-dimensional */
    point new = malloc(D * sizeof(float));
    
    do {
        for(S = 0, i = 0; i < D; i++)
        {
            new[i] = 2 * (1.0*rand()/RAND_MAX) - 1;
            S += (new[i] * new[i]);
        }
        
        K = sqrt(-2.0 * log(S)/S); R = sqrt(2*S);
        for(i = 0; i < D; i++) new[i] *= K/R;
        
    } while(S >= 1 || S == 0); 
    
    return new;
}
