# SNr_Model_ACC
An SNr model written in C with OpenACC directives for GPU computing.

To use PSC resources
Step 1. Create an ACCESS account at https://allocations.access-ci.org/
Step 2. Request an Explore ACCESS Project
Step 3. Exchange ACCESS Credits against PSC resources: PSC Bridges-2 GPU for computing and PSC Ocean for storage
Step 4. Check out the PSC user guide at https://www.psc.edu/resources/bridges-2/user-guide/

My PSC username is jjian. My PSC project name is mth240008p.
I use WinSCP to log onto jjian@bridges2.psc.edu and use the PuTTY session within WinSCP to access the SSH.
The current latest availible nvc compiler version is nvc 22.9-0.

To run a program
Step 1. Upload the source codes to "/jet/home/jjian/".
Step 2. Run command line "./run.sh task4". It compiles task4.c and submits the job. 
Step 3. The output is stored in "/ocean/projects/mth240008p/jjian".
Step 4. Download the output files to the local folder.
Step 5. Run "task4.m" in Matlab to visualize the data.
