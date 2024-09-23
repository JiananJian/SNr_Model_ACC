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
