# Deterministic Universal Turing Machine
Ce projet a pour but de mettre en place un programme permettant de simuler une DTM en utilisant un fichier décrivant la
machine a simuler.

Le projet a été testé et compilé sur des machines Windows 8.1, Windows 10, Ubuntu 19.04.
La compilation se fait en utilisant le compilateur g++, un script build.sh est mis à disposition afin de compiler le 
programme, en sortie un exécutable nommé UTM(.exe pour Windows) sera utilisé afin d’exécuter le programme.

## Getting Started
UTM [Options]… TM_FILE_DESCRIPT… INPUT…

-	Options : il y’a 3 types d’options possibles :
o	-steps : affichera chaque étape de transition.
o	-state : affichera l’état final.
o	-tape : affichera le contenu de la tape.

-	TM_FILE_DESCRIPT (Obligatoire) : le nom du fichier d’extension .tm qui contiendra la description de la machine de 
	turing à simuler.

-	INPUT (Obligatoire) : l’input à fournir en entrée à la machine de turing simulé.

