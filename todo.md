# TODO

- afficher prompt				X
- recup input					X
- transfo tokens				X
	ATTENTION: add_redirection_token: vérifier pour les syntax error avec operator
- interpréter (expand, escape)
	PRESQUE OK: reste:
		
		! special expand '$?' !
		vérifier que les tableaux d'arguments se retrouvent pas
		avec des 'null' en plein milieu
		si on envoie une chaine vide à get_env_value() elle retourne
		automatique 'user42', à changer

- remplacer printf par ftprintf


questions :

à gérer ou pas ? sinon : error : unknown symbol

ls |> file.txt ? fichier vide
ls |>> file.txt ? fichier vide
ls <> file.txt ? output sur STDOUT file vide 
ls >| file.txt ? fonctionne

