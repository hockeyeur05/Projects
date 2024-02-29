import pandas as pd
import matplotlib.pyplot as plt
FILE = "intraday_5min_IBM.csv"
file = pd.read_csv(FILE)
file.describe()
X = file['timestamp']
Y = file['close']


### functions
def n_voisins(x,n,file) :
    X = file['timestamp']
    Y = file['close']
    nb_points = file.count()[0]
    if((x-n >= 0) and (x+n <= nb_points)) :
        for i in range (2*n+1) :
            voisins.append((X[x+i],Y[x+i]))
    return voisins

def max(liste):
    maxi = liste[0]
    for i in range(len(liste)):
        if (liste[i]>maxi):
            maxi = liste[i]
    return maxi

def min(liste):
    mini = liste[0]
    for i in range(len(liste)):
        if (liste[i]<mini):
            mini = liste[i]
    return mini


def benef(entree,sortie) :
    return sortie - entree

def high(file,entree,sortie):
    points_max = file.count()[0]
    assert(entree>=0 and sortie <=points_max)
    L = []
    for k in range(sortie-entree):
        L.append(file['close'][k+entree])
    return max(L)

def minimum(file,entree,sortie):
    points_max = file.count()[0]
    assert(entree>=0 and sortie <=points_max)
    pts = []
    for k in range(sortie - entree):
        pts.append(file['close'][k+entree])
    return min(pts)




def fibonacci(file,entree,sortie) :
    max = high(file,entree,sortie)
    mini = minimum(file,entree,sortie)
    fib = [0,23.6,38.2,50,61.8,76.4]
    traces = [fibo/100*(max-mini) + mini for fibo in fib]
    X = file['timestamp']
    Y = file['close']
    plt.plot(X,Y)
    for trace in traces :
        plt.plot([entree,sortie],[trace,trace],linestyle = '--',linewidth=2)
    plt.show()
###
fibonacci(file,0,file.count()[0])










