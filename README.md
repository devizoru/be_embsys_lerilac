# be_embsys_lerilac

Pour lancer le programme : 
Brancher les diodes, résistance et capteur comme sur le schéma électrique schema_elec.jpg
Se connecter en SSH sur la carte
Activer les ports I2C
Lancer le programme : /home/user/hw /dev/i2c-1

La led rouge clignote si la température est supérieure à 20°C, la verte clignote sinon.
La led bleue clignote pour signifier que le programme fonctionne.
On peut également lire les valeurs avec précision sur le terminal
