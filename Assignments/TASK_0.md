# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?

Pour ajouter un avion il faut appuyer sur la touche 'c'

Comment faire pour quitter le programme ?

Pour quitter le programme on peut appuyer soit sur la touche 'X' soit sur la touche 'Q' du clavier.

A quoi sert la touche 'F' ?

La touche 'F' permet d'intervertir entre le mode pleine écran et le mode fenêtré.

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?

L'avion boucle dans une animation où il arrive puis repart.

Quelles informations s'affichent dans la console ?

Dasn la console on voit lorsqu'un avion atterrit avec le message "AIRPLANE_NAME is now landing...", quand il communique avec l'aéroport "now servicing AIRPLANE_NAME..." et "done servicing AIRPLANE_NAME" quand il finit et enfin "AIRPLANE_NAME lift off" quand il décolle.

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

Ils font le même parcours mais attendent dans les airs tant qu'il n'y a plus de place dans l'aéroport.

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

### TowerSimulation

C'est la classe qui s'occupe de représenter la simulation, elle permet de modifié le comportement de la simulation avec des fonctions-membres qui modifie l'éxécution du programme

### Waypoint

Cette classe représente une position dans la simulation, et elle permet de savoir si cette position est sur le sol ou dans les airs ou encore dans un terminals

### Point2D & Point3D

Ces deux structures représentent les coordonnées (x, y) pour Point2D et (x, y, z) pour Point3D, cela permet de mieux passer de la 3D à la 2D.

### AirportType

Cette classe représente un type d'aéroport avec ses différentes informations.

### AircraftType

Cette structure représente un type d'avion et permet de composer différents avions.

### Runway

Cette structure représente la distance entre relative entre l'aéroport et un Point3D, cela permet de savoir si une position est éloigné ou non de l'aérotport

---

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.

### Tower

Cette classe représente la tour de contrôle dans un aéroport et donne les informations et les instructions à suivre pour les avions.

Pour cette classe il y a 3 fonctions-membres public :

- Le constructeur qui permet de créer l'objet

- WaypointQueue get_intructions(Aircraft& aircraft); elle sert a savoir ce que l'avion aircraft peux faire, si il peut atterrir ou non

- void arrived_at_terminal(const Aircraft& aircraft); elle permet de faire aller l'avion dans un terminal

#### Terminal

Cette classe représente un terminal pour les avions, elle possèdes des positions et l'avion courrant.

Pour cette classe il y a 7 fonctions-membres public :

- Le constructor qui permet de créer l'objet

- bool in_use() const; elle permet de savoir si ce terminal est utilisé ou non

- bool is_servicing() const; permet de savoir si ce terminal est entrain d'être utilisé par l'avion courrant

- void assign_craft(const Aircraft& aircraft); permet d'associé un avion courrant au terminal

- void start_service(const Aircraft& aircraft); permet de commencer le service pour l'avion en paramètre
  
- void finish_service(); permet de finir le service de l'avion courrant et d'être de nouveau libre

- void move() override; permet de faire progresser le service en cours.

### Airport

Cette classe représente l'aéroport.

Il y a 4 fonctions-membres public :

- Le constructeur qui permet de créer l'objet

- Tower& get_tower(); qui renvoie la tour de contrôle de l'aérotport

- void display() const override; qui affiche l'aéroport

- void move() override; qui permet d'éxécuter pour chaques terminaux leur fonction-membre move

### Aircraft

Cette classe représente les avions et permets de stocker toutes leurs données.

Il y a 5 fonctions-membres :

- Le constructeur qui permet de créer l'objet

- const std::string& get_flight_num() const; qui renvoie le numéro de vol de l'avion

- float distance_to(const Point3D& p) const; qui renvoie la distance entre l'avion et le point

- void display() const override; qui affiche l'avion

- void move() override; effectue l'animation de l'avion, si celui est dans les airs il se déplace (soit vers l'aéroport soit de manière aléatoire dans les airs) sinon il se déplace vers sa destination dans l'aéroport

Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.
Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?

La classe Waypoint est impliquée dans la génération du chemin d'un avion avec les fonctions void Aircraft::move() override; et WaypointQueue Tower::get_instructions(Aircraft& aircraft).

Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?

Le conteneur choisi est deque.

Expliquez les intérêts de ce choix.

Car on peut à la fois ajouter et retirer en tête et en queue ce qui permet de gérer un ordre d'arriver et de sortie.

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.

Dans la fonction inline void AircraftType::init_aircraft_types();

Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

```c++
inline void init_aircraft_types()
{
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .02f, .1f, .02f, MediaPath { "concorde_af.png" } }; // concorde speed is x2
}
```

2) Identifiez quelle variable contrôle le framerate de la simulation.

La variable qui calcule le framerate de la simulation est GL::ticks_per_sec

Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.

```c++
void TowerSimulation::create_keystrokes() const
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_random_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('i', []() { GL::up_framerate(); });
    GL::keystrokes.emplace('k', []() { GL::down_framerate(); });
}
```

Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\

Le programme plante car on divise par 0.

Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

La variable qui contrôle le temps de débarquement des avions est SERVICE_CYCLES.

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\

Dans la fonction WaypointQueue Tower::get_instruction(Aircraft& aircraft).

Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?

Car cela provoquerai des problèmes avec tous les conteneurs dans lequelle est l'avion.

A quel endroit de la callstack pourriez-vous le faire à la place ?\

On pourrait le faire dans la fonction void GL::timer(const int step) qui parcours la move_queue qui contient tous les avions

Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

on doit mettre void DynamicObject::move() en bool DynamicObject::move() pour renvoyer true si l'on peut détruire l'objet dans void GL::timer(const int step).

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.

```c++
    Displayable(const float z_) : z { z_ } { display_queue.emplace_back(this); }
```

Il faut également penser à le supprimer de cette liste avant de le détruire.

```c++
    virtual ~Displayable()
    {
        display_queue.erase(std::find(display_queue.begin(), display_queue.end(), this));
    }
```

Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

Car tous les DynamicObject ne sont pas détruit.

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

On peut le faire avec le conteneur std::map.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

Car la fonction-membre std::pair<WaypointQueue, size_t> Airport::reserve_terminal(Aircraft& aircraft); est privée et que la classe Tower est _friend_ avec la classe Airport les deux classes peuvent donc accéder au champs/fonctions-membres protected/private.

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?

Nous ne sommes pas passé par référence car dans la fonction turn on modifie direction.

Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

Oui, on pourrait lors du passage par la méthode Point3D::cap_length(float f) renvoyer un nouveau Point3D et la rendant donc const?

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
