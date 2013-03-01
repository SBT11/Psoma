PSoma - README file
===================


NOTES:
	All output and configuration files are text files and can be opend/edited using MS Notepad (or equivalent)
	File and folder addresses are given here with their relative path, full paths can be used most of the time. Also, please note that '../a_folder' corresponds to the parent folder of 'a_folder'
	An exemple execution is given in a separate file named 'example.txt'


For any questions: jeremie.pinoteau@upmc.fr


French Version :
================
PSoma est un programme C++ utilisant la librairie standard pour de modéliser la
réponse de méchanorécepteurs humains à une stimulation par des points de Braille.
Cette version du code comprend 3 sous-sections:
- un model très (très) simpliste de bras (pas d'accélération/d'inertie, pas d'erreur de
  position) pour imposer les déplacements au doigt
- un model de doigt artificiel composé de plusieur capteurs
- un model de type Leaky-Integrate and Fire des méchanorecepteurs SA-I
La grande majorité des paramètres de ces modèles peuvent être modifiés dans des fichiers de configuration sans avoir à modifier le code.

Organisation des fichiers:
==========================
Répertoires:
- bin* (bin, bin_Debug ou bin_Release)	contient l'executable une fois le programme compilé
- buildfiles*				contient les fichiers temporaires de compilation
- config				contient les fichiers de configuration
- data					contient les fichiers de sortie du programme (cf. section dédiée: 'Fichiers de Sortie')
- log					contient les fichiers logs du programme (pas utilisé pour l'instant)
- net					contient les fichiers de configuration des réseaux dans le programme
- scripts				contient des scripts MATLAB pour l'analyse des données
- src					contient les fichiers source du programme


Compilation:
=============
Windows:
La méthode la plus simple consiste à télécharger et installer l'IDE 'codeblocks'
('codeblocks-12.11mingw-setup.exe' sur http://www.codeblocks.org/downloads/26) puis
d'y importer le projet (fichier .cbp). Vous pourrez alors compiler le projet 
(aka. build project) depuis l'interface. (si codeblocks vous demande un choix de compilateur, choisissez celui par default - qui devrait ressembler à: GNU-GCC).

Vous pouvez aussi choisir un autre IDE que 'codeblocks' tel que 'QTcreator',
'Visual Studio (express) C++' ou 'eclipse' qui sont plus lourds. Dans ce cas il faudra 
créer un nouveau projet console vide et y importer le contenu du répertoire 'src'.
Finalement, vous devriez aussi pouvoir compiler le programme directement par ligne de 
commande (si vous savez comment faire sous windows).

Execution de l'application:
===========================
L'exécution s'effectue à partir du répertoire 'bin*'. Si vous utilisez un IDE, il doit 
pouvoir le lancer directement pour vous (mais il faudra peut etre préciser de bien le 
lancer à partir de ce répertoire).

!!! Si vous souhaitez le lancer à partir d'un autre répertoire, il faudra placer le 
ficher de configuration principal 'psoma.conf' à l'adresse '../config/psoma.conf' du 
lieu d'exécution du programme. Vous devrez aussi en modifier le contenu pour s'assurer 
que le programme puisse trouver les autres fichers de configuration. !!!

Fichiers de configuration:
==========================
Le fichier de configuration principal est: 'psoma.conf' et il doit impérativement se 
trouver dans le répertoire '../config/' (par rapport au répertoire d'exécution). Dans ce 
fichier se trouve les adresses des autres fichiers de configuration. Ces fichiers 
contiennent les valeurs des paramètres des différents modèles.

Chaque paramètre est accompagné d'un bref descriptif. Voici les points importants qui 
pourraient vous intéresser:
- les paramètres des capteurs et des méchanorécepteurs sont dans 'config/psoma_mr.conf'
- pour changer le nombre et la position des capteurs il faut éditer le fichier 'net/fingertip_layout.pos'. Si le nombre de capteurs est modifié, il faut aussi changer le nombre de méchanorécepteurs ('config/psoma_mr.conf'), ainsi que la connectivité entre les capteurs et les méchanorécepteurs ('net/sensor2mr.net').
- les paramètres concernant le mouvement du bras sont dans 'config/arm.conf'. Dans ce fichier vous pouvez notamment donner le fichier de trajectoire (eg. 'net/arm.trj') et le nombre de répétitions pour la trajectoire.
- le fichier de stimuli est décrit dans 'config/psoma.conf' (paramètre: 'sti_netFile'). Ledit fichier décrit la position des point Braille.

Il vous est déjà fourni trois fichiers de trajectoires et deux fichiers de stimuli afin de faciliter votre analyse.
- Trajectoire:
	- 'net/arm_AZ.trj' permet de lire facilement l'ensemble des caractères Braille contenus dans 'net/stimuli_AZ.pos'
	- 'net/arm_oneLine.trj' permet de faire un passage au-dessus d'une courte ligne en Y=0 à la vitesse de 30mm/s. On pourra l'utiliser avec 'net/stimuli_oneDot.pos' pour avoir la réponse à un passage au dessus d'un point Braille
	- 'net/arm_SEP.trj' permet d'explorer séquentiellement l'espace autour du point (0,0,0) à vitesse 60mm/s, afin de faire un SEP du stimulus qui s'y trouve (eg. 'net/stimuli_oneDot.pos')

Fichiers de Sortie:
===================
The système sauvegarde ses sorties dans quatre types de fichiers différents. On peut changer le nom/l'adresse de ces fichiers dans 'config/psoma.conf':
- 'data/traj.dat'	sauvegarde la trajectoire suivie par le bras sous forme de matrice: time(ms) | x(mm) | y(mm) | z(mm) | vx(mm/s) | vy(mm/s) | vz(mm/s) | repetition index | trajectory segment index
- 'data/mat.dat'	sauvegarde le signal des 'capteurs analogiques': time(ms) | capteur 1 | capteur 2 | ... etc
- 'data/LIF_spike.dat'	sauvegarde l'activité des méchanorécepteurs: time(ms) | neuron index
- 'data/LIFdynamics/MR*.dat'	sauvegarde les dynamiques internes de chaque neurone: time(ms) | intensity I | membrane potential v | threshold potential vt | spike (1=yes, 0=no)
