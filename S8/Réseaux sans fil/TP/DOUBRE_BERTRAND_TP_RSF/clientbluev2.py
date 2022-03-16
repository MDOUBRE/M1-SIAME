#!/usr/bin/env python3

from bluetooth import *
import socket as sok
import subprocess as sub
import sys
import time as t

ADDR = ""
IP = "192.168.0.33"  # Adresse IP du client
HOST = "192.168.0.32" # Adresse IP du serveur
PORT = 50008


# Prend en paramètre le fichier à envoyer et à exécuter
def main(filename):
    print ("Envoie d'un fichier en Wifi et éxecution par Bluetooth\n")


    ################################################
    #   Exe des commandes de config du bluetooth   #
    ################################################
    os.system("sudo bluetoothctl discoverable on")
    os.system("sudo bluetoothctl pairable on")
    os.system("sudo bluetoothctl agent on")
    os.system("sudo bluetoothctl default-agent")


    ################################################
    #         Partie client wifi Ad-Hoc :          #
    ################################################
    print ("\nEnvoi du fichier en Wifi\nOuverture client Wifi :")

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

    print ("Fichier envoyé\nFermeture client wifi")


    ################################################
    #             Partie serveur wifi :            #
    ################################################
    print ("\nEn attente de l'adresse mac Bluetooth du client\nOuverture serveur Wifi :")

    with sok.socket(sok.AF_INET, sok.SOCK_STREAM) as server:
        server.bind(("", PORT))
        server.listen(1)

        while True:
            print("En attente du serveur")
            conn, addr = server.accept()
            print("Connection from", addr)
            ADDR = conn.recv(1024)
            break

    print ("réception de l'adresse mac Bluetooth du client\nFermeture serveur wifi")


    ################################################
    #           Partie client bluetooth :          #
    ################################################
    print ("\nEnvoi de la commande à exécuter\nAssociation Bluetooth :")

    # Connection bluetooth : reception de l'adresse Bl du serveur
    sokClient=BluetoothSocket(L2CAP)
    tmp = str(ADDR)
    print ("Adresse Bluetooth du serveur : " + tmp[2:len(tmp)-1])
    sokClient.connect((tmp[2:len(tmp)-1], 7))

    # Envoi de la commande via bluetooth
    sokClient.send("./"+filename.split('/')[-1])

    # fermeture de la socket client
    sokClient.close()

    print ("Dissociation Bluetooth")


if __name__ == "__main__":
    main(sys.argv[1])