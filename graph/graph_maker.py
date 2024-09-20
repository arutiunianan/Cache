import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline, BSpline
from pathlib import Path
import sympy as sp
import sys
 
if __name__ == '__main__':

    lfu = open(sys.argv[1], 'r') #'lfu_in.txt'
    pca = open(sys.argv[2], 'r') #'pca_in.txt'

    lfu_array = np.array(lfu.read().split()).astype(int)
    pca_array = np.array(pca.read().split()).astype(int)

    plt.plot(lfu_array, label = "LFU")
    plt.plot(pca_array, label = "PCA")

    plt.title('Ani Graph<3')
    plt.xlabel('Added elements')
    plt.ylabel('Hits number')
    plt.legend()
    plt.grid(True)
    plt.savefig('graph/graph.png')

    #plt.show()