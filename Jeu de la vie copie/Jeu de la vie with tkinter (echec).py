import tkinter as tk
import numpy as np
import random as rd
import matplotlib.pyplot as plt
import copy
from time import sleep
import pygame as py
## quadrillage
def quadrillage(canvas,m,n,hauteur,largeur):
    carre1 = largeur // n
    carre2 = hauteur // m
    y=0
    x=0
    while y <= hauteur:
        canvas.create_line((0,y),(largeur,y))
        y+= carre2
    while x <= largeur:
        canvas.create_line((x,0),(x,hauteur))
        x+= carre1
## fonctions
def remplissage_quadrillage(n):
    M=np.zeros((n,n))
    for i in range(n):
        for j in range(n):
            M[i][j]=j+1
    return M

def convert(x,y):
    i,j=x//largeur,y//hauteur
    return i,j


def appuie(event):
    i,j=convert(event.x,event.y)

def M_to_tk(M,m,n,hauteur,largeur):
    carre1 = largeur // n
    carre2 = hauteur // m
    (m,n)=np.shape(M)
    for i in range(m):
        for j in range(n):
            x,y = j*carre1,i*carre2
            if M[i][j]==1:
                canvas.create_rectangle((x, y),(x + cote, y + cote), fill=couleur_carre, outline=couleur_fond)
    return fenetre



def alea(m,n):
    M=np.zeros((m,n))
    for i in range(m):
        for j in range(n):
            M[i][j]=rd.randint(0,1)
    return M


def vois(M,i,j):
    res=[]
    (m,n)=np.shape(M)
    (a,b)=(i,j)
    if a>0:
        res.append((a-1,b))
    if b>0:
        res.append((a,b-1))
    if a<n-1:
        res.append((a+1,b))
    if b<m-1:
        res.append((a,b+1))
    if a>0 and b>0:
        res.append((a-1,b-1))
    if a>0 and b<n-1:
        res.append((a-1,b+1))
    if a<n-1 and b<n-1:
        res.append((a+1,b+1))
    if a<n-1 and b>0:
        res.append((a+1,b-1))
    return res

def compte_voisins(M,i,j):
    c=0
    (m,n)=np.shape(M)
    voisins = vois(M,i,j)
    for voisin in voisins :
        (a,b)=voisin
        if M[a][b]==1:
            c+=1
    return c


# def evolution_case(M,i,j):
#     nouveau=[]
#     degage=[]
#     c = compte_voisins(M,i,j)
#     if c<2 and M[i][j]==1:
#         degage.append((i,j))
#     if c>3 and M[i][j]==1:
#         degage.append((i,j))
#     if c==3 and M[i][j]==0:
#         nouveau.append((i,j))
#
#     return nouveau,degage

# def traite_case(M,i, j):
#     """Fait une étape de l'automate pour la case de coordonnées (i, j)
#     en retournant la nouvelle valeur de la case du tableau"""
#     n = compte_voisins(M,i, j)
#     if M[i][j] == 0:
#         # si case morte
#         if n == 3:
#             M[i][j]=1
#
#         else:
#             M[i][j]=0
#     else:
#         # si case vivante
#         if n in [2, 3]:
#             M[i][j]=1
#         else:
#             M[i][j]=0
#     return M[i][j]

def pre_evolution(M):
    (m,n)=np.shape(M)
    nouveaux=[]
    degages=[]
    for i in range(m):
        for j in range(n):
            c = compte_voisins(M,i,j)
            if c<2 and M[i][j]==1:
                degages.append((i,j))
            if c>3 and M[i][j]==1:
                degages.append((i,j))
            if c==3 and M[i][j]==0:
                nouveaux.append((i,j))
    return nouveaux,degages

def evolution(M):
    nouveaux,degages = pre_evolution(M)
    for nouveau in nouveaux:
        (i,j)=nouveau
        M[i][j]=1
    for degage in degages:
        (a,b) = degage
        M[a][b]=0
    return M


# def M_bin(M):
#     (m,n)=np.shape(M)
#     for i in range(m):
#         for j in range(n):
#             if M[i][j]>1:
#                 M[i][j]=1
#     return M


# def somme(liste,m,n):
#     res= np.zeros((m,n))
#     n=len(liste)
#     for k in range(n):
#         res+=liste[k]
#     return res




# def evolution_matrice(M):
#     l=[]
#     (m,n)=np.shape(M)
#     for i in range(m):
#         for j in range(n):
#             M[i][j]=evolution_case(M,i,j)
#             l.append(M)
#     return M_bin(somme(l,m,n))

# def evolve(M):
#     (a,b)=np.shape(M)
#     for i in range(a):
#         for j in range(b):
#             M[i][j]=traite_case(M,i,j)
#     return M


def etape(event):
    """Fait une étape du jeu de la vie en modifiant la variable globale tableau"""
    global M
    M_res = copy.deepcopy(M)
    for i in range(nb_colonne):
        for j in range(nb_ligne):
            M_res=evolution_matrice(M)
    M = M_res
###
# M=alea(nb_ligne,nb_colonne)
# fenetre = tk.Tk()
# fenetre.geometry("1080x720")
# fenetre.title("jeu de la vie")
# fenetre.minsize(400,400)
# canvas = tk.Canvas(fenetre,width = largeur,height = hauteur)
# canvas.grid()
# canvas.bind("<Button-1>", evolution_case)
# fenetre.bind("n", etape)
# quadrillage()
# fenetre.mainloop()
## matrice de depart

M = np.array([[0,0,0,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,1,0,0,0],[0,0,1,1,1,0,0],[0,0,0,1,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,0,0]])
##
# d=0
# while d < iterations:
#     plt.imshow(M)
#     plt.show()
#     M=evolution(M)
#     d+=1
#     sleep(1)
##
largeur = 1080
hauteur = 720
cote=20
nb_colonne = largeur//cote
nb_ligne = hauteur//cote
couleur_fond = 'black'
couleur_carre = 'white'
iterations = 10

fenetre = tk.Tk()
fenetre.title("Jeu de la vie")
canvas = tk.Canvas(fenetre, bg=couleur_fond, width=largeur, height=hauteur)
canvas.grid()
quadrillage(canvas,60,60,hauteur,largeur)
fenetre.config(background=couleur_fond)
## boucle principale
d=0
fenetre=(M_to_tk(M,canvas,60,60,hauteur,largeur))
#quadrillage(fenetre,60,60,hauteur,largeur)
fenetre.mainloop()
while d <= iterations:
    M = evolution(M)
    fenetre=(M_to_tk(M,canvas,60,60,hauteur,largeur))
    fenetre.mainloop()
    d+=1
    sleep(1)




