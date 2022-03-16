Readme :

Package intallé : - sudo apt-get install bluetooth bluez-utils blueman bluez
		  - pip3 install bluez


Modification d'un fichier pour le wifi afin de pouvoir créer un réseau ad-hoc: 

sudo nano /etc/dhcpcd.conf
Écrire à la fin du fichier :  
denyinterfaces wlan0


Commande pour configurer notre machine en wifi ad-hoc :
sudo iwconfig wlan0 mode ad-hoc essid 'Blop' channel 1
sudo ip link set wlan0 up
sudo ip addr add 192.168.0.33/24 dev wlan0

Rappel:
Client ip: 192.168.0.33
Server ip: 192.168.0.32


Bluetooth les commandes pour préparer sa machine:
sudo bluetoothctl :
	- discoverable on
	- pairable on
	- agent on
	- default-agent



