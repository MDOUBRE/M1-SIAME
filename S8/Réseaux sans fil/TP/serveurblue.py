#!/usr/bin/env python3

import os, sys
import socket
import stat
import subprocess
from bluetooth import *

HOST = ""
PORT = 50008

FILENAME = "recu"

# Executer en super user (sudo)
# @param le dernier nombre de l'adresse ip
# @return execute le fichier recu


# Execution du fichier recu
def execute(filename):
    st = os.stat(filename)
    os.chmod(filename, st.st_mode | stat.S_IEXEC) #donne les droits au fichier de s'executer

    pid = os.fork()
    if pid == 0:
        os.system(filename)
    else:
        os.wait()


def main():

# Initialisation Wifi ESSID 'Blop'
    print ("Reçois un fichier en Wifi et une cmd a executer en Bluetooth")
    print ("Initialisation du Wifi :")
    print ()

# Initialisation Bluetooth

    print ("Initialisation du Bluetooth :")
    print ()

    os.system("sudo bluetoothctl discoverable on")
    os.system("sudo bluetoothctl pairable on")
    os.system("sudo bluetoothctl agent on")
    os.system("sudo bluetoothctl default-agent")

    print ()

    # --- Recuperation de l'adresse Mac Bluetooth du serveur --- #
    list_addr = subprocess.check_output("hciconfig".split(' '))
    index = list_addr.index(b"BD Address: ") + len (b"BD Address: ")
    addrMac = list_addr[index:(index+17)]



#partie I
# partie serveur wifi

    print ("En attente d'un fichier")
    print("Ouverture serveur Wifi :")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as serveur:
        serveur.bind((HOST, PORT))
        serveur.listen(1)

        while True:
            conn, addr = serveur.accept()
            print("Connection from", addr)

            FILENAME = conn.recv(256)

            print ("Le nom du fichier : " + str(FILENAME))

            #lecture du fichier reçu et ecriture dans le nouveau fichier
            with conn, open(FILENAME, "wb") as f:
                data = conn.recv(1024)
                while data:
                    f.write(data)
                    data = conn.recv(1024)
            break

        print ("Fichier recu")
        print ("Fermeture du serveur wifi")
        print ()


    #partie II
    # partie client wifi :

    print ("Envoie son adresse mac bluetooth")
    print ("Ouverture client wifi:")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client :
        client.connect((addr[0], PORT))
        client.send((addrMac))

    print("Adresse bluetooth bien envoyé")
    print ("Fermeture du client wifi")

    print ()


    # Partie bluetooth

    print ("Attente de la commande en Bluetooth")
    print ("Bluetooth appareillage :")

    server_socket = BluetoothSocket(L2CAP)
    server_socket.bind(("",7))
    server_socket.listen(1)
    client_socket, address = server_socket.accept()
    data = client_socket.recv(1024)
    tmp = str(data)
    data = tmp[2:len(tmp)-1]
    data = str(data)
    print ("Commande Reçu :  [%s]" % data)

    client_socket.close()
    server_socket.close()

    print ("Fermeture du Bluetooth")


    print ("Exécution de la commande");
    print ()

    execute(data)




if __name__ == "__main__":
    main()