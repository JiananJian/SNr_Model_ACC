# SNr_Model_ACC  
An SNr model written in C with OpenACC directives for GPU computing.  

To use PSC resources  
Step 1. Create an ACCESS account at "https://allocations.access-ci.org/".  
Step 2. Request an Explore ACCESS Project by submitting a grant proposal.  
Step 3. Exchange ACCESS Credits against PSC resources: PSC Bridges-2 GPU for computing and PSC Ocean for storage.  
Step 4. Check out the PSC user guide at "https://www.psc.edu/resources/bridges-2/user-guide/".  

My PSC username is jjian. My PSC project name is mth240008p. My ACCESS-CI project name is MTH240038.  
I use WinSCP to log onto jjian@bridges2.psc.edu and use the PuTTY session within WinSCP to access the SSH.  
The current latest availible nvc compiler version is 22.9-0. The correspondent latest cuda version is 11.7.1.  

To run the program  
Step 1. Upload the source codes to "/jet/home/jjian/".  
Step 2. Run command line "./run.sh task4". It compiles "task4.c" and submits the job. This program calculates the steady-state firing rate as a function of the depolarizating current and the HCN conductance either on soma or on dendrite.   
Step 3. The outputs "task4_*.bin" are stored in "/ocean/projects/mth240008p/jjian".  
Step 4. Download the output files to the local folder.  
Step 5. Run "task4.m" in Matlab to visualize the data and generate three binary files "g_HCN_*.bin". These files give the HCN conductances that match experimental results.   
Step 6. Upload "g_HCN_*.bin" to "/jet/home/jjian/".  
Step 7. Compile "task5.c" with the command line "nvc -acc -Minfo=accel -o task5v2.out task5v2.c".  
Step 8. Run command line "./run_task5.sh -GPe 0.1 -tau 5 -HCN den". This calculates the first post-stimulus spike-times. Use options -GPe or -Str followed by their GABA conductance, use option -tau followed by their time constance, use option -HCN followed by -som or -den or -non to select HCN channel locations.  
Step 9. The outputs "task5_*.bin" are stored in "/ocean/projects/mth240008p/jjian".  
Step 10. Download the output files to the local folder.  
Step 11. Run "task5.m" in Matlab to visualize the data.  

********************* task9 ****************  
task5 saves the entire first-spike PSTH timespike data. task9 does the same calculation but only saves the histogram counts.   
Run "nvc -acc -Minfo=accel -o task9.out task9.c" to compile the program.  
Run "./run_task9.sh -GPe 0.030476 -tau 8.384470 -HCN zero -o task9a1" to caluclate the first-spike PSTH.   
The output is an array saved in "/ocean/projects/mth240008p/jjian/task9a1_c.bin".  
The array has 101 elements. The first 100 elements are the histogram counts in each bin [0, 0.5], ..., to [49.5, 50]. The last element is the total number of trials. 
  

Run "task9_job.mat" in matlab. It generates a shell program "run_task9v3.sh".  
Run "chmod +x run_task9v3.sh" to make it executable.  
Run "./run_task9v3.sh" to caluclate a list of first-spike PSTH with parameters from "tau_values.m".   
Download the files "/ocean/projects/mth240008p/jjian/task9a*_c.bin" to the local folder.   
Run "task9.m" in matlab and save the data into matlab data format with the propriate name such as "GPe_den.m".     
Edit line 2-4 of "task9_job.mat" for different experiment conditions, repeat the program and generate "GPe_den.m",  "GPe_som.m",  "GPe_zero.m", "Str_den.m",  "Str_som.m", and "Str_zero.m".  
Run "task9p2.mat" in matlab and visualized the histograms.


