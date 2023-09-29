import subprocess
import os
# 给定的两个列表
list_size = [2000]
list_n = [1, 2, 3, 4, 5, 6, 7, 8]

# 执行 random_matrix 可执行文件并将 size 作为参数
def run_random_matrix(size):
    command = ['./random_matrix', str(size)]
    subprocess.run(command, check=True)

# 执行 lu 可执行文件并将 size, n 作为参数，输出重定向至 output.txt 文件
def run_lu(size, n):
    command = ['cargo', 'run', str(size), "lu_input.txt", str(n)]
    with open('output.txt', 'a') as f:

        f.write(f'size = {size}, number of threads = {n}\n')
        subprocess.run(command, check = False, stdout = f )
        f.write('\n\n')


# 对每个 n 和 m 进行运算

for size in list_size:
    run_random_matrix(size)
    for n in list_n:
        run_lu(size, n)