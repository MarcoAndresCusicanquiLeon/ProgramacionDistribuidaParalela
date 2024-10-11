# se utiliza la formula area del circulo unitario:
# 2 * integral[-1,1] (sqrt(1-x^2)) dx = PI

import math
import multiprocessing as mp
from multiprocessing import Pool

def f(x):
    return math.sqrt(1-x**2)

def F(Start,l,r):
    cx=Start-1.0
    su=0
    for i in range(l,r+1):
        su+=f(cx)*DX
        cx+=DX
    return su

if __name__=='__main__':
    n_workers=mp.cpu_count()
    print("# trabajadores = {}".format(n_workers)) #se usa el maximo numero de trabajadores
    #se rompe la integral en 1 millon de segmentos:
    lim=1000000
    global DX
    DX=2/lim

    divi=lim//n_workers
    modu=lim%n_workers

    partition=[(0,0,divi-1)]

    st=divi
    for i in range(1,n_workers):
        en=st+divi-1
        if (i<=modu):
            en+=1
        partition.append((st*DX,st,en))
        st=en+1

    p=Pool()
    partial_sums=p.starmap(F,partition)
    PI=sum(partial_sums)*2
    print("PI = {:.18f}".format(PI))
