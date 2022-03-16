#!/usr/bin/env python3

import socket as sok
import subprocess as sub
import sys
import time as t

IP = "192.168.0.33"  # Adresse IP du client
HOST = "192.168.0.32" # Adresse IP du serveur
PORT = 50008


# Prend en paramètre le fichier à envoyer et à exécuter
def main(filename):
    print ("Envoie d'un fichier en Wifi et éxecution par Bluetooth\n")


    ################################################
    #         Partie client wifi Ad-Hoc :          #
    ################################################
    print ("Envoi du fichier en Wifi\nOuverture client Wifi :")

    with sok.socket(sok.AF_INET, sok.SOCK_STREAM) as client, \
        open(filename, "rb") as f:
        client.connect((HOST, PORT))

        # Envoi du nom du fichier
        client.send(bytes(filename.split('/')[-1],'utf-8'))
        t.sleep(1)

        # Envoi du contenu du fichier
        data = f.read()
        while data:
            client.send(data)
            data = f.read()

    print ("Fichier envoyé\nFermeture du client wifi\n")

    print ("Envoi de la commande à exécuter en Wifi\nOuverture du client Wifi :")

    with sok.socket(sok.AF_INET, sok.SOCK_STREAM) as client :
        client.setsockopt(sok.SOL_SOCKET, sok.SO_REUSEADDR, 1)
        client.connect((HOST, PORT))

        # Envoi de la commande
        client.send(bytes("./"+filename.split('/')[-1],'utf-8'))
        t.sleep(1)

    client.close()

    print ("Commande envoyée\nFermeture du client wifi")


if __name__ == "__main__":
    main(sys.argv[1])