#!/usr/bin/env python3

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

# === === #

    print ("Envoie un fichier en Wifi et l'éxecute en Bluetooth")
    print ("Initialisation du Wifi :")
    print ()
    print ("Initialisation du Bluetooth :")
    print ()
    # Execution des commandes permettant la configuration du bluetooth
    os.system("sudo bluetoothctl discoverable on")
    os.system("sudo bluetoothctl pairable on")
    os.system("sudo bluetoothctl agent on")
    os.system("sudo bluetoothctl default-agent")


    # --- Recuperation de l'adresse Ip du serveur --- #
    list_addr = subprocess.check_output("arp -a".split(' '))
    #addrHost = list_addr[list_addr.index(b"192.168.0.3"):(list_addr.index(b"192.168.0.3")+12)]

# === === #

    # Partie Client Wifi Ad-Hoc

    print ()
    print ("Envoie le fichier en Wifi")
    print ("Ouverture client Wifi :")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client, \
         open(filename, "rb") as f:
        client.connect((HOST, PORT))

        # Envoye du nom du fichier par le client en wifi
        client.send(bytes(filename.split('/')[-1],'utf-8'))

        time.sleep(1)

        data = f.read()
        while data:
            client.send(data)
            data = f.read()

    print ("Fichier envoyer")
    print ("Fermeture client wifi")

    # Partie serveur wifi :

    print ()
    print ("Reçois l'adresse mac Bluetooth du client")
    print ("Ouverture serveur Wifi :")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.bind(("", PORT))
        server.listen(1)

        while True:
            print("En attente de connection de la part du serveur")
            conn, addr = server.accept()
            print("Connection from", addr)
            ADDR = conn.recv(1024)
            break

    print ("Adresse mac bluetooth du client recu")
    print ("Fermeture serveur wifi")


# === === #

    #Partie Client Bluetooth

    print ()
    print ("Envoie la cmd à executer")
    print ("Bluetooth apprareillage :");

    # Connection bluetooth : reception de l'adresse Bl du serveur
    client_socket=BluetoothSocket(L2CAP)
    tmp = str(ADDR)
    print ("Adresse Bluetooth du serveur : " + tmp[2:len(tmp)-1])
    client_socket.connect((tmp[2:len(tmp)-1], 7))


    # Envoye de la commande en bluetooth au serveur
    client_socket.send("./"+filename.split('/')[-1])

    print ("Commande envoyé")

    client_socket.close()

    print ("Fermeture du Bluetooth")



if __name__ == "__main__":
    main(sys.argv[1])