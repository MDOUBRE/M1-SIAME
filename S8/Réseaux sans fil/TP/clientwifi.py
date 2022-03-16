import socket
import sys
from bluetooth import *
import time
import subprocess

ADDR = ""
HOST = "192.168.0.32"
PORT = 50008
IP = "192.168.0.33"


# Prend en paramètre le fichier à envoyer et à executer
def main(filename):

    print ("Envoi d'un fichier et exécution de ce dernier en Wifi")
    print ("Initialisation du Wifi :\n")    

    list_addr = subprocess.check_output("arp -a".split(' '))
    
    # Envoi du fichier en Wifi    
    print ("\nEnvoi du fichier en Wifi")
    print ("Ouverture client Wifi :")
    
    # connexion du client avec le serveur
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client, \
         open(filename, "rb") as fic:
        client.connect((HOST, PORT))

        # Envoi du nom du fichier
        client.send(bytes(filename.split('/')[-1],'utf-8'))
        time.sleep(1)

		# envoi des données du fichier
        data=fic.read()
        while data:
            client.send(data)
            data=fic.read()
            
        print ("Fichier envoyé")
        print ("Fermeture client wifi") 
       

        # Envoi de la commande à exécuter en Wifi
        print ("\nEnvoi de la commande à exécuter en Wifi")
        print ("Ouverture du client Wifi :")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client :    
    #with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client, \
    #     open(filename, "rb") as fic:
        client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        client.connect((HOST, PORT))

        # Envoye du nom du fichier par le client en wifi
        client.send(bytes("./"+filename.split('/')[-1],'utf-8'))
        time.sleep(1)
            
    client.close()

    print ("Commande envoyée")
    print ("Fermeture du client wifi") 



if __name__ == "__main__":
    main(sys.argv[1])