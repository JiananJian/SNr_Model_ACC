#!/bin/bash
TASK_NAME=task5

module load cuda/11.7.1

echo "#!/bin/bash" > "${TASK_NAME}.job"
echo "#SBATCH -N 1" >> "${TASK_NAME}.job"
echo "#SBATCH -p GPU-shared" >> "${TASK_NAME}.job"
echo "#SBATCH --gpus=v100:1" >> "${TASK_NAME}.job"
echo "#SBATCH -t 60" >> "${TASK_NAME}.job"
echo "#SBATCH -A mth240008p" >> "${TASK_NAME}.job"
echo "./${TASK_NAME}.out" >> "${TASK_NAME}.job" $@

sbatch "${TASK_NAME}.job"
squeue -u jjian
