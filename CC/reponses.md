---
lang      : fr
title     : Contrôle de connaissances SE207 "SystemC"
date      : 25 juin 2019
---

# Instructions

Ce contrôle de connaissances est strictement individuel.
Vous devez modifier ce fichier pour y inclure vos réponses puis l'ajouter à votre dépôt dans un dossier `CC` à la racine de ce dernier.

- Seules les parties entre *`---`* sont à modifier.

- Laissez une ligne vide avant et après chaque *`---`*.

# Questions

### Question 1

En SystemC, pour représenter une donnée sur 13bits vous pouvez utiliser l'un des types suivants:

- **`sc_bv<13>`**
- **`sc_lv<13>`**
- **`sc_uint<13>`**
- **`sc_int<13>`**

1. Expliquez brièvement la difference entre ces types.
2. Quels critères vous feraient choisir un type plutôt qu'un autre ?

---

### Réponse 1.1
**`sc_bv<13>`** : c'est un vecteur de 13 bits. il ne peut  contenir que des 0 ou 1. il n'est pas possible de faire des opérations arithmetiques avec lui.

**`sc_lv<13>`** : c'est un vecteur logique de 13 bits. il ne peut  contenir que 4 valeurs: 0,1, X ou Z. Il n'est pas possible de faire des opérations arithmetiques avec lui.

**`sc_int<13>`** : c'est un entier signé de 13 bits. Il est possible de faire des opérations arithmetiques avec lui.

**`sc_uint<13>`** : c'est un entier non signé de 13 bits. Il est possible de faire des opérations arithmetiques avec lui.

### Réponse 1.2
Si on veut représener un bus logique dont les éléments sont 0 ou 1, il faudrait utiliser un **`sc_bv<13>`**. Si le bus peut contenir des bits de haute impedance ou inconnus à un certain moment, il faudrait utiliser le **`sc_lv<13>`**.

Si ce bus logique est utilisé pour faire des **operations arithmetiques** souvent, il faudrait utiliser des **`sc_uint<13>`** ou **`sc_int<13>`** selon le cas. Par exemple, un compteur devrait être représenté par un **`sc_uint<13>`**

---

### Question 2

Les notions de signal et d'affectation différée sont des notions importantes pour un simulateur évènementiel.

1. Expliquez brièvement à quoi correspondent ces notions et dans quels cas il est indispensable de les utiliser.
2. Expliquez comment elles sont mises en œuvre en SystemC.

---

### Réponse 2.1
Une affectation  différée est celle qui est prise en compte à la fin de chaque cycle d'horloge dans le cadre de la logique sequentielle.

Il est indispensable de les utiliser lorsque l'on modelise du matériels avec de la logique sequentielle.

### Réponse 2.2
Un signal est représentée par le type templaté `sc_signal<T>` où T est soit un type basique de `C++`, un type de SystemC ou un type contenant une surcharge des opérateurs `==`, `=`, `<<` et avec une methode pour la représenter.

Le type `sc_signal<T>` contient trois méthodes particulières pour modéliser de la logique sequentielle:

- `read()` : Pour lire la valeur courante du signal
- `write(T t)` : Pour modifier la valeur du signal. Cette valeur sera prise en compte lors de l'appel de update 
- `update()`: Pour mettre à jour la valeur tu signal et informer si elle a changée

Ce type contient un pointeur de type `sc_event` pour informer que sa valeur à changée lors de l'appel à update.

---


### Question 3

Nous voulons modéliser un système synchrone dont la sortie **`Q`** produit cycliquement la séquence suivante:

**
`0,1,2,3,4,3,2,1,0,1,2,3,4,5,6,7`
**



Composée des phases suivants:

1. incrémente de `0` à `4`,
2. décrémente de `4` à `0`,
3. incrémente de `0` à `7`...

Avec les caractéristiques suivantes:

- la sortie **`Q`** est sur 3 bits,
- elle évolue à chaque front montant d'une horloge **`clk`**,
- un signal de remise à zéro **`nrst`** actif sur niveau bas permet de réinitialiser la séquence,


1. Écrire le code de deux module SystemC reproduisant ce comportement:

   1. le premier contiendra un **`SC_THREAD`**,
   2. le second contiendra une ou plusieurs **`SC_METHOD`**.

---

```{.cpp}

// En utilisant un SC_THREAD
SC_MODULE(SeqThread) {
  sc_in<bool> clk;
  sc_in<bool> nrst;
  sc_out<sc_uint<3>> Q;

  SC_CTOR(SeqThread){
    SC_THREAD(loop);
    sensibility<<clk.pos();
    reset_is(nrst,false);
  }

  void loop(){
    Q==0;
    for(;;){
      for(int i=0; i<4; i++){
        wait();
        Q++;
      }
      for(int i=0; i<4; i++){
        wait();
        Q--; 
      }
      for(int i=0; i<8; i++){
        wait();
        Q++;
      }
    }
  }

}

// En utilisant une ou plusieurs SC_METHOD
SC_MODULE(SeqMethod) {
  sc_in<bool> clk;
  sc_in<bool> nrst;
  sc_out<sc_uint<3>> Q;

  boolean was_4 = false;
  boolean was_0 = false;

  SC_CTOR(SeqMethod){
    SC_METHOD(function);
    sensibility<<clk.pos();
    reset_is(nrst,false);
  }

  void function(){
    if(!nrst){
      Q = 0;
      was_4 = false;
      was_0 = false;
    }
    else {
      if (was_4 && !was_0){
        Q--;
        if (Q==1){
          was_0 = true;
        }
      }
      else
        Q++;
        if (Q==3 && !was_4){
          was_4 = true;
        }
        if (Q == 7){
          was_4 = false;
          was_0 = false;
        }
    }
  }

}

```

---


### Question 4

1. Expliquez pourquoi les **`SC_THREAD`** contiennent souvent une boucle infinie ?
   * Que se passe-t-il si cette boucle n'existe pas ?
2. Que se passe-t-il par contre si une boucle infinie existe dans une **`SC_METHOD`** ?
   * Que se passe-t-il si la fonction **`wait()`** est appelée dans cette boucle infinie ?


---

### Réponse 4.1

Un **`SC_THREAD`** ne correspond pas à un thread du Système d'exploitation. C'est le simulateur evenementiel qui gere son execution, donc il ne bloque pas l'execiution . Un **`SC_THREAD`** contient une boucle car elle est active en permanence.

Sans boucle, une fois que la function appelée par le **`SC_THREAD`** finisse son éxécution, elle ne sera plus appelée. 

### Réponse 4.2
Un **`SC_METHOD`** ne peut pas contenir une boucle infinie car elle est exécutée du début à la fin. Elle bloquerait donc le système dans ce cas.

C'est pourquoi il est interdit d'appeler la méthode `wait()`. Le faire déclencherait une erreur.

---

### Question 5

Pour modéliser deux calculs effectués par des blocs matériels synchrones nous utilisons deux `SC_THREAD` sensibles au front d'un signal d'horloge `clk`.
Pour les synchroniser nous utilisons un `sc_mutex`.

1. Donnez, **dans les grandes lignes**, un exemple de code illustrant ce fonctionnement.

2. Ce modèle est-il synchrone avec l'horloge `clk` ?

3. Donnez, **toujours dans les grandes lignes**, un exemple de code pour modéliser la même fonctionnalité au niveau RTL ?

4. Comparez ces deux modèles du point de vue des ressources nécessaires à la simulation.


---

### Réponse 5.1

```{.cpp}

sc_signal<bool> b;
sc_mutex m;
boolean b = true;

void thread1(){
  for(;;){
    m.lock();
      b != b;
      wait();
    m.unlock();
    wait()
  }
}

void thread2(){
  for(;;){
    m.lock();
      b != b;
      wait();
    m.unlock();
    wait()
  }
}

...
```

### Réponse 5.2
Ce modele n'est pas synchrone avec l'horloge clk car dès qu'un thread libère un mutex, l'autre va le prendre sans prendre en compte le front de l'horloge.

### Réponse 5.3

```{.cpp}
// second code (rtl)

sc_signal<bool> b;
sc_mutex m;
boolean b = true;

boolean is_mine1 = false;
boolean is_mine2 = false;

void function1(){
  boolean comp;
  if ( comp = m.n_lock()){
    if (comp){
      is_mine1 = comp;
    }
  }
  else {
    if (is_mine1){
      is_mine1 = false;
      m.unlock()
    }
  }
}

void function2(){
  boolean comp;
  if ( comp = m.n_lock()){
    if (comp){
      is_mine2 = comp;
    }
  }
  else {
    if (is_mine2){
      is_mine2 = false;
      m.unlock()
    }
  }
}
...
```


---

