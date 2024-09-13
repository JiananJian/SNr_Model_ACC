#include "ODE_SOLVER_HEADER.h"

/// @brief Calculate the firing rate of a neuron
/// @param s Neuron 
/// @return firing rate in Hz, 0 if less than 1Hz
double calc_rate(State *restrict s) {
    double dt = 0.025;
    int n;

    // run 1 sec for init
    n = 40e3;
    for (int i = 0; i < n; i++) {
        f(s, dt);
    }

    // we expect at least 2 spikes within 2 sec if the rate is at least 1 Hz
    n = 80e3;
    int count = 0;
    #define count_max 2
    double tspk[count_max];
    for (int i = 0; i < n; i++) {
        if (f(s, dt)) {
            tspk[count] = s->time;
            count++;
        }
        if (count == count_max) {
            double r = 1e3 / (tspk[1] - tspk[0]);
            return r;
        }
    }
    return 0;
}

// task1 - task3 combined
// find the relationship between the firig rate and I_app, g_HCN
#define TASK_NAME task4
#define TASK_NAME_STR "task4"

void TASK_NAME() {
    int m = 301, n = 401;
    double g[m], I[n], r0[n], r1[m][n], r2[m][n];

    // load parameter space
    #pragma acc kernels 
    {
        for (int i = 0; i < m; i++) {
            g[i] = pow(2, -10. + 0.05 * i);
        }

        for (int j = 0; j < n; j++) {
            I[j] = -70. + .1 * j;
        }
    }
    
    // calculate rates
    #pragma acc kernels
    {
        for (int j = 0; j < n; j++) {
            State s = init_state(); 
            s.I_app = I[j];
            r0[j] = calc_rate(&s);
            // printf("I = %f, r = %f \n", I[j], r[j]);
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                State s = init_state(); 
                s.I_app = I[j];
                s.g_HCN_som = g[i];
                r1[i][j] = calc_rate(&s);  
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                State s = init_state(); 
                s.I_app = I[j];
                s.g_HCN_den = g[i];
                r2[i][j] = calc_rate(&s);  
            }
        }
    }
    
    // output file    
	const char path[] = "/ocean/projects/mth240008p/jjian/";
    char file[64];

    strcpy(file, path);
    strcat(file, TASK_NAME_STR "_g.bin");
    write_binary_file(file, g, m);

    strcpy(file, path);
    strcat(file, TASK_NAME_STR "_I.bin");
    write_binary_file(file, I, n);

    strcpy(file, path);
    strcat(file, TASK_NAME_STR "_r0.bin");
    write_binary_file(file, r0, n);
    
    strcpy(file, path);
    strcat(file, TASK_NAME_STR "_r1.bin");
    write_binary_file(file, NULL, 0);
    for (int i = 0; i < m; i++) {
        append_binary_file(file, r1[i], n);
    }

    strcpy(file, path);
    strcat(file, TASK_NAME_STR "_r2.bin");
    write_binary_file(file, NULL, 0);
    for (int i = 0; i < m; i++) {
        append_binary_file(file, r2[i], n);
    }
}

int main() {
    struct timeval start_time, stop_time, elapsed_time; // timers
    gettimeofday(&start_time, NULL); // Unix timer

    printf(TASK_NAME_STR " begins \n");
    TASK_NAME();
    printf(TASK_NAME_STR " finishes \n");
    
    gettimeofday(&stop_time, NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
    printf("Total time was %f seconds.\n", elapsed_time.tv_sec + elapsed_time.tv_usec * 1e-6);
    return 0;
}