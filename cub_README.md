# general
- nom d'exécutable 'cub3D'   GOOD
- chaque touche (WASD ou ZQSD) doit faire quelque chose (mouvement, rotation du personnage)
- lancer avec plusieurs arguements (nb) et s'assurer que ça n'altère pas le grogramme ni ne créer d'erreurs non gérées   GOOD
- ne doit rien faire si d'autres touches sont actionnées
- ne doit pas bug si la map est modifiée
- (close bien quand on clique sur la croix, ou en appyant sur échap (ou autre touche configurée comme telle))
- vérifier que la fenêtre se size bien et sous le bon format

 # parsing
 - message Error\n suivit d'un message explicite en cas d'erreur   GOOD
 - se termine en .cub   GOOD
 - pas de duplication d'éléments   GOOD
 - vérifier qu'il y ait un mur (1) tout autour
 - vérifier qu'il n'y ait que 6 caractères différents '01NSEW'   GOOD
 - les identifiants des élements/textures ne sont que : NO, EA, SO, WE, F, C. Ils doivent être devant leur path.  GOOD
 - vérifier que le path des textures est valide
 - les instructions (identifiants avec leur path) peuvent être séparrées entre elles d'espaces ou/et de nouvelles lignes vides, mais doivent être avant/au-dessus de la map   GOOD
 - la couleur des textures doit être entre 0-255 RGB (red green blue)

 # tests
 - check_extension : s'il n'y a pas d'arguments, si le nom est trop court, s'il se termine en .cub (s'il est trop grand ou avec des chiffres?).

 - pre_parsing :

 - split_config :	remplir la structure t_config avec les elements desquels on enlève les '\n' et que l'on met dans l'ordre: NO SO EA WE F C et copier la map en elevant les '\n'.

 - parse_elem : couleurs : verifier nb < 0 et > 255, bien 3 nb separres par des virgules, espaces entre, autre valeurs !!!!espace derniere lettre

 - parse_map : check s'il y a exactement 1 player et si la map est bien entourée de murs ('1').


 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!PARSING: check si les paths ne sont pas des directory !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!AFFICHAGE:  check si ce qu'on veut afficher sort de l'ecran

 # exec
 - mouvements du personnage
 - rotation du personnage
 - collision avec les murs
 - affichage de la map:
    1. raycast
    2. fix fisheye
    3. afficher le background floor/ceiling
    3. afficheres les textures pour peindre la map