### Bibliothèques
import numpy as np
import pygame as py
from pygame.locals import *
from pygame import display

from random import randint,random

import time as tm
### Paramètres

rayon = 10
noir = (0,0,0)
bordx = 800
bordy = 800
max_v = 5
max_vois = 10
fenetre = py.display.set_mode((bordx,bordy))
fenetre.fill((255,255,255))
pop = 20
bord = min(bordx,bordy)

### classes
class Boid:
    taille = bord//2

    def __init__(self,position = None,vitesse = None):
        self.pos = (position if position is not None else np.random.uniform(-Boid.taille,Boid.taille,2))
        self.v = (vitesse if vitesse is not None else np.random.uniform(-max_v,max_v,2))
        vitesse = np.linalg.norm(self.v)
        self.vitesse = vitesse
        self.position = (self.pos[0],self.pos[1])

    def draw(self):
        py.draw.circle(fenetre,noir,self.pos.round(2)+Boid.taille, rayon)

    def distance(self,other):
        return np.linalg.norm(self.pos-other.pos)

    def vit(self):
        return np.linalg.norm(self.v)

    def vitesse(self,value):
        self.v = self.v * value / self.vitesse

    def angle_mort(self,other):
        M1 = self.v - self.pos
        M2 = other.v - other. pos
        cos_angle = np.dot(M1,M2) / (np.linalg.norm(M1) * np.linalg.norm(M2) )
        return np.arccos(cos_angle) > (3/4) * np.pi

    def voisins(self,population,seuil):
        """ renvoie la liste des voisins triée en fonction de la distance """
        l_vois = []
        for other in population:
            if self != other:
                if self.distance(other) < seuil and self.angle_mort(other) == False:
                    l_vois.append(other)
        return sorted(l_vois,key = self.distance)

    def direction(self):
        return np.arctan2(self.v[1],self.v[0]) # sa direction est l'angle entre vx et vy

    def separation(self,population):
        voisins = self.voisins(population,50)[:max_vois]
        return sum (self.pos - other.pos for other in voisins)

    def aligne(self,population):
        voisins = self.voisins(population,200)[:max_vois]
        vitesses = sum(other.v for other in voisins)
        n = len(voisins)
        if n > 0:
            return vitesses / n - self.v
        else:
            return 0

    def rapproche(self,population):
        voisins = self.voisins(population,200)[:max_vois]
        vitesses = sum(other.pos for other in voisins)
        n = len(voisins)
        if n > 0:
            return vitesses / n - self.pos
        else:
            return 0

    def centripete(self):
        return -self.pos

    def noise(self):
        return np.random.uniform(-max_v,max_v,2)

    def interaction(self,population):
        self.v += (
            self.separation(population) / 100
            + self.aligne(population) / 80
            + self.rapproche(population) / 500
            + self.centripete() / 2000)
           # + self.noise() )

        if self.vitesse  > 20:
            self.vitesse = 20

        self.pos += self.v

        if (np.abs(self.pos) > Boid.taille).any():
            for i,coord in enumerate(self.pos):
                if (diff:= coord + Boid.taille) < 10:
                    self.pos[i] = -Boid.taille + 10 + diff
                    self.v[i] *= -1
                if (diff := Boid.taille + 10 - coord) < 10:
                    self.pos[i] = Boid.taille - 10 - diff
                    self.v[i] *= -1
        tm.sleep(0.0001)
        return self

###
population = []
for i in range(pop):
    #new_boid = boid((randint(50,bordx-50),randint(50,bordy-50)),randint(-max_v*100,max_v*100)/100)
    new_boid = Boid()
    population.append(new_boid)


###
continuer = True
while continuer == True:
    #affichage de la fenêtre
    fenetre.fill((255, 255, 255))

    #arrêt de la simulation si on le souhaite
    for event in py.event.get():
        if event.type == QUIT:
            continuer = False

    # affichage des boids
    for boid in population:
        boid.interaction(population)
        boid.draw()
    py.display.flip()
py.quit()







