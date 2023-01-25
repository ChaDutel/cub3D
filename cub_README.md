*** general ***
- nom d'exécutable 'cub3D'
- chaque touche (WASD ou ZQSD) doit faire quelque chose (mouvement, rotation du personnage)
- lancer avec plusieurs arguements (nb) et s'assurer que ça n'altère pas le grogramme ni ne créer d'erreurs non gérées
- ne doit rien faire si d'autres touches sont actionnées
- ne doit pas bug si la map est modifiée
- (close bien quand on lique sur la croix, ou en appyant sur échappe (ou autre touche configurée comme telle))
- vérifier que la fenêtre se size bien et sous le bon format

 *** parsing ***
 - message Error\n suivit d'un message explicite en cas d'erreur
 - se termine en .cub
 - pas de duplication d'éléments
 - vérifier qu'il y ait un mur (1) tout autour
 - vérifier qu'il n'y ait que 6 caractères différents '01NSEW'
 - les identifiants des élements/textures ne sont que : NO, EA, SO, WE, F, C. Ils doivent être devant leur path.
 - vérifier que le path des textures est valide
 - les instructions (identifiants avec leur path) peuvent être séparrées entre elles d'espaces ou/et de nouvelles lignes vides, mais doivent être avant/au-dessus de la map
 - la couleur des textures doit être entre 0-255 RGB (red green blue)

 *** tests ***
 - check_extension : s'il n'y a pas d'arguments, si le nom est trop court, s'il se termine en .cub (s'il est trop grand ou avec des chiffres?)