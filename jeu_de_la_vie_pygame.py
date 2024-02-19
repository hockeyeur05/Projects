import numpy as np
import random as rd
from time import sleep
import pygame as py
from pygame.locals import *
from pygame import display
##
py.init()
largeur = 1080
hauteur = 1080
fenetre = py.display.set_mode((largeur,hauteur))
fenetre.fill((255,255,255))
m=60
n=60
### classe
class carre:
    def __init__(self,x,y,couleur,taille):
        self.x=x
        self.y=y
        self.couleur=couleur
        self.taille=taille
    def affiche(self):
        py.draw.polygon(fenetre, self.couleur, [(self.x,self.y), (self.x+self.taille,self.y),(self.x+self.taille,self.y+self.taille),(self.x,self.y+self.taille)])

## quadrillage
def quadrillage(fenetre,m,n,hauteur,largeur):
    carre1 = largeur // n
    carre2 = hauteur // m
    y=0
    x=0
    while y <= hauteur:
        py.draw.line(fenetre,(0,0,0),(0,y),(largeur,y))
        y+= carre2
    while x <= largeur:
        py.draw.line(fenetre,(0,0,0),(x,0),(x,hauteur))
        x+= carre1
## fonctions


def M_to_py(M,carre,fenetre,hauteur,largeur):
    (m,n)=np.shape(M)
    carre1 = largeur // n
    carre2 = hauteur // m
    carre.taille = largeur // n
    carre.couleur=(0,0,0)
    for i in range(m):
        for j in range(n):
            carre.x,carre.y = j*carre1,i*carre2
            if M[i][j]==1:
                carre.affiche()
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
## matrice de depart
M=alea(m,n)
#croix
# M=np.zeros((m,n))
# L=[(30,29),(29,30),(30,30),(31,30),(30,31)]
# for i in range(m):
#     for j in range(n):
#         for ele in L:
#             (a,b)=ele
#             M[a][b]=1
## boucle principale
continuer= True
c=0
while continuer == True:
    d=0
    fenetre.fill((255, 255, 255))
    quadrillage(fenetre,m,n,hauteur,largeur)
    for event in py.event.get():
        if event.type == QUIT:
            continuer = False
    keys = py.key.get_pressed()
    if keys[py.K_RETURN]:
        c+=1
        fentre= M_to_py(M,carre(100,100,(0,0,0),10),fenetre,hauteur,largeur)
        M=evolution(M)
        py.display.update()
        sleep(0.1)
py.quit()
print(c)

