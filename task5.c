#include "ODE_SOLVER_HEADER.h"

// calculate a PSTH using PRC
#define TASK_NAME task5
#define TASK_NAME_STR "task5"

/// @brief Give a GABA impluse and find the next spike time
/// @param s Neuron
/// @return spike time, -1 if no spike within 50ms
double GABA_tspk(State s) {
    double dt = 0.025;
    int n = 2000; // in 50ms time limit
    s.GPe_stim = 1;
    s.Str_stim = 1;
    for (int j = 0; j < n; j++) {
        if (f(&s, dt)) {
            return s.time;
        }
        s.GPe_stim = 0;
        s.Str_stim = 0;
    }
    return -1;
}

void TASK_NAME(double W_GPe, double W_Str, double tau, const char* HCN) {
    double dt = 0.025;
    int N = 401;
    int n = 40e3;
    double I[N];   
    double t_spk0[N], t_spk2[N]; // GABA will be delivered at anytime between t_spk0[k] and t_spk2[k]
    double t_GABA[N][n], t_spk1[N][n];  

    #define PATH "/ocean/projects/mth240008p/jjian/"
    char file[64];
    
    if (strcmp(HCN, "som") == 0) {
        strcpy(file, PATH "g_HCN_som.bin"); 
    } else if (strcmp(HCN, "den") == 0) {
        strcpy(file, PATH "g_HCN_den.bin"); 
    } else {
        strcpy(file, PATH "g_HCN_zero.bin"); 
    }

    printf(file);

    double g_HCN[N];
    size_t N0;
    read_binary_file(file, g_HCN, &N0); // we expect N0 == N

    // To store all initial states to be tested
    State **s1 = (State **)malloc(N * sizeof(State *));
    for (int k = 0; k < N; k++) {
        s1[k] = (State *)malloc(n * sizeof(State));
    }

    // Load parameter
    #pragma acc kernels
    for (int k = 0; k < N; k++) {   
        I[k] = -70. + .1 * k;  
    }

    #pragma acc parallel loop // doesn't work with #pragma acc kernels
    for (int k = 0; k < N; k++) {  
        State s = init_state();    
        // choose your GABA parameters: 
        s.W_GPe = W_GPe;
        s.tau_GABA_som = tau;
        s.W_Str = W_Str;
        s.tau_GABA_den = tau;
        s.I_app = I[k];
        s.g_HCN_den = g_HCN[k]; // load your GABA
        
        // run 1 sec for init
        #pragma acc loop seq // necessary
        for (int i = 0; i < n; i++) {
            f(&s, dt);
        }

        // find the first spike t_spk0[k] 
        for (int i = 0; i < n; i++) {
            if (f(&s, dt)) {
                break;
            }
        }
        t_spk0[k] = s.time; 
        
        // find the second spike t_spk2[k] 
        for (int i = 0; i < n; i++) {    
            s1[k][i] = s;
            if (f(&s, dt)) {
                break;
            }
        }
        t_spk2[k] = s.time; 
        //printf("I[k] = %f, t_spk0 = %f, t_spk2 = %f\n", I[k], t_spk0[k], t_spk2[k]);
    }

    // it has to be a separate loop
    #pragma acc parallel loop collapse(2)    
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < n; i++) { 
            t_GABA[k][i] = s1[k][i].time;  
            t_spk1[k][i] = GABA_tspk(s1[k][i]);
            //printf("k = %d, i = %d\n", k, i);
        }
    }

    for (int k = 0; k < N; k++) {
        free(s1[k]);
    }
    free(s1);
    
    // output file    
    strcpy(file, PATH TASK_NAME_STR "_t_GABA.bin");
    write_binary_file(file, NULL, 0);
    for (int i = 0; i < N; i++) {
        append_binary_file(file, t_GABA[i], n);
    }
    
    strcpy(file, PATH TASK_NAME_STR "_t_spk1.bin");
    write_binary_file(file, NULL, 0);
    for (int i = 0; i < N; i++) {
        append_binary_file(file, t_spk1[i], n);
    }

    strcpy(file, PATH TASK_NAME_STR "_I.bin");
    write_binary_file(file, I, N);

    strcpy(file, PATH TASK_NAME_STR "_t_spk2.bin");
    write_binary_file(file, t_spk2, N);

    strcpy(file, PATH TASK_NAME_STR "_t_spk0.bin");
    write_binary_file(file, t_spk0, N); 
    
}

int main(int argc, char *argv[]) {
    struct timeval start_time, stop_time, elapsed_time; // timers
    gettimeofday(&start_time, NULL); // Unix timer

    char HCN_str[8] = "zero";
    double W_GPe = 0, W_Str = 0, tau = 0;

    // e.g. -GPe 0.1 -tau 5 -HCN som
    // Loop through command-line arguments
    for (int i = 1; i + 1 < argc; i++) {
        if (strcmp(argv[i], "-GPe") == 0) {
            W_GPe = strtod(argv[i + 1], NULL);  
        } else if (strcmp(argv[i], "-Str") == 0) {
            W_Str = strtod(argv[i + 1], NULL);
        } else if (strcmp(argv[i], "-tau") == 0) { 
            tau = strtod(argv[i + 1], NULL);
        } else if (strcmp(argv[i], "-HCN") == 0) {
            strncpy(HCN_str, argv[i + 1], sizeof(HCN_str) - 1);
            HCN_str[sizeof(HCN_str) - 1] = '\0';  
        }
    }

    printf(TASK_NAME_STR " begins \n");
    TASK_NAME(W_GPe, W_Str, tau, HCN_str);
    printf(TASK_NAME_STR " finishes \n");
    
    gettimeofday(&stop_time, NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
    printf("Total time was %f seconds.\n", elapsed_time.tv_sec + elapsed_time.tv_usec * 1e-6);
    return 0;
}