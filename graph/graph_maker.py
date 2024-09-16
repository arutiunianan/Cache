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

    #x = np.arange(lfu_array.size)
    #xnew = np.linspace (x. min (), x. max (), 200 ) 

    #spl = make_interp_spline (x, lfu_array, k = 3 )
    #lfu_y = spl(xnew)
    #spl = make_interp_spline (x, pca_array, k = 3 )
    #pca_y = spl(xnew)
    
    #plt.plot (xnew, lfu_y, label = "LFU")
    #plt.plot (xnew, pca_y, label = "PCA")

    plt.title('Ani Graph<3')
    plt.xlabel('Added elements')
    plt.ylabel('Hits number')
    plt.legend()
    plt.grid(True)
    plt.savefig('graph/graph.png')

    #plt.show()