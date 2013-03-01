PSoma - README file
===================


NOTES:
	All output and configuration files are text files and can be opend/edited using MS Notepad (or equivalent)
	File and folder addresses are given here with their relative path, full paths can be used most of the time. Also, please note that '../a_folder' corresponds to the parent folder of 'a_folder'
	An exemple execution is given in a separate file named 'example.txt'


For any questions: jeremie.pinoteau@upmc.fr


French Version :
================
PSoma est un programme C++ utilisant la librairie standard pour de mod�liser la
r�ponse de m�chanor�cepteurs humains � une stimulation par des points de Braille.
Cette version du code comprend 3 sous-sections:
- un model tr�s (tr�s) simpliste de bras (pas d'acc�l�ration/d'inertie, pas d'erreur de
  position) pour imposer les d�placements au doigt
- un model de doigt artificiel compos� de plusieur capteurs
- un model de type Leaky-Integrate and Fire des m�chanorecepteurs SA-I
La grande majorit� des param�tres de ces mod�les peuvent �tre modifi�s dans des fichiers de configuration sans avoir � modifier le code.

Organisation des fichiers:
==========================
R�pertoires:
- bin* (bin, bin_Debug ou bin_Release)	contient l'executable une fois le programme compil�
- buildfiles*				contient les fichiers temporaires de compilation
- config				contient les fichiers de configuration
- data					contient les fichiers de sortie du programme (cf. section d�di�e: 'Fichiers de Sortie')
- log					contient les fichiers logs du programme (pas utilis� pour l'instant)
- net					contient les fichiers de configuration des r�seaux dans le programme
- scripts				contient des scripts MATLAB pour l'analyse des donn�es
- src					contient les fichiers source du programme


Compilation:
=============
Windows:
La m�thode la plus simple consiste � t�l�charger et installer l'IDE 'codeblocks'
('codeblocks-12.11mingw-setup.exe' sur http://www.codeblocks.org/downloads/26) puis
d'y importer le projet (fichier .cbp). Vous pourrez alors compiler le projet 
(aka. build project) depuis l'interface. (si codeblocks vous demande un choix de compilateur, choisissez celui par default - qui devrait ressembler �: GNU-GCC).

Vous pouvez aussi choisir un autre IDE que 'codeblocks' tel que 'QTcreator',
'Visual Studio (express) C++' ou 'eclipse' qui sont plus lourds. Dans ce cas il faudra 
cr�er un nouveau projet console vide et y importer le contenu du r�pertoire 'src'.
Finalement, vous devriez aussi pouvoir compiler le programme directement par ligne de 
commande (si vous savez comment faire sous windows).

Execution de l'application:
===========================
L'ex�cution s'effectue � partir du r�pertoire 'bin*'. Si vous utilisez un IDE, il doit 
pouvoir le lancer directement pour vous (mais il faudra peut etre pr�ciser de bien le 
lancer � partir de ce r�pertoire).

!!! Si vous souhaitez le lancer � partir d'un autre r�pertoire, il faudra placer le 
ficher de configuration principal 'psoma.conf' � l'adresse '../config/psoma.conf' du 
lieu d'ex�cution du programme. Vous devrez aussi en modifier le contenu pour s'assurer 
que le programme puisse trouver les autres fichers de configuration. !!!

Fichiers de configuration:
==========================
Le fichier de configuration principal est: 'psoma.conf' et il doit imp�rativement se 
trouver dans le r�pertoire '../config/' (par rapport au r�pertoire d'ex�cution). Dans ce 
fichier se trouve les adresses des autres fichiers de configuration. Ces fichiers 
contiennent les valeurs des param�tres des diff�rents mod�les.

Chaque param�tre est accompagn� d'un bref descriptif. Voici les points importants qui 
pourraient vous int�resser:
- les param�tres des capteurs et des m�chanor�cepteurs sont dans 'config/psoma_mr.conf'
- pour changer le nombre et la position des capteurs il faut �diter le fichier 'net/fingertip_layout.pos'. Si le nombre de capteurs est modifi�, il faut aussi changer le nombre de m�chanor�cepteurs ('config/psoma_mr.conf'), ainsi que la connectivit� entre les capteurs et les m�chanor�cepteurs ('net/sensor2mr.net').
- les param�tres concernant le mouvement du bras sont dans 'config/arm.conf'. Dans ce fichier vous pouvez notamment donner le fichier de trajectoire (eg. 'net/arm.trj') et le nombre de r�p�titions pour la trajectoire.
- le fichier de stimuli est d�crit dans 'config/psoma.conf' (param�tre: 'sti_netFile'). Ledit fichier d�crit la position des point Braille.

Il vous est d�j� fourni trois fichiers de trajectoires et deux fichiers de stimuli afin de faciliter votre analyse.
- Trajectoire:
	- 'net/arm_AZ.trj' permet de lire facilement l'ensemble des caract�res Braille contenus dans 'net/stimuli_AZ.pos'
	- 'net/arm_oneLine.trj' permet de faire un passage au-dessus d'une courte ligne en Y=0 � la vitesse de 30mm/s. On pourra l'utiliser avec 'net/stimuli_oneDot.pos' pour avoir la r�ponse � un passage au dessus d'un point Braille
	- 'net/arm_SEP.trj' permet d'explorer s�quentiellement l'espace autour du point (0,0,0) � vitesse 60mm/s, afin de faire un SEP du stimulus qui s'y trouve (eg. 'net/stimuli_oneDot.pos')

Fichiers de Sortie:
===================
The syst�me sauvegarde ses sorties dans quatre types de fichiers diff�rents. On peut changer le nom/l'adresse de ces fichiers dans 'config/psoma.conf':
- 'data/traj.dat'	sauvegarde la trajectoire suivie par le bras sous forme de matrice: time(ms) | x(mm) | y(mm) | z(mm) | vx(mm/s) | vy(mm/s) | vz(mm/s) | repetition index | trajectory segment index
- 'data/mat.dat'	sauvegarde le signal des 'capteurs analogiques': time(ms) | capteur 1 | capteur 2 | ... etc
- 'data/LIF_spike.dat'	sauvegarde l'activit� des m�chanor�cepteurs: time(ms) | neuron index
- 'data/LIFdynamics/MR*.dat'	sauvegarde les dynamiques internes de chaque neurone: time(ms) | intensity I | membrane potential v | threshold potential vt | spike (1=yes, 0=no)
