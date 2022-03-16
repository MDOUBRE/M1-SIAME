#!/usr/bin/env python3

from bluetooth import *
import os, sys
import socket as sok
import stat
import subprocess as sub

HOST = ""
FILENAME = "recu"
PORT = 50008

# Pour que le fichier fonctionne il faut l'exécuter avec les droits d'admin donc en sudo

################################################
#        Fct d'exécution de la commande :      #
################################################
def execute(fichier):
    st = os.stat(fichier)

    # permet de donner au fichier les droits de s'executer
    os.chmod(fichier, st.st_mode | stat.S_IEXEC)

    pid = os.fork()
    if pid == 0:
        os.system(fichier)
    else:
        os.wait()


################################################
#                      MAIN                    #
################################################
def main():
    print ("Reception d'un fichier par Wifi et d'instruction par Bluetooth\n")


    ################################################
    #   Exe des commandes de config du bluetooth   #
    ################################################
    os.system("sudo bluetoothctl discoverable on")
    os.system("sudo bluetoothctl pairable on")
    os.system("sudo bluetoothctl agent on")
    os.system("sudo bluetoothctl default-agent")

    # Récuperation de l'adresse Mac Bluetooth du serveur
    listAddr = sub.check_output("hciconfig".split(' '))
    index = listAddr.index(b"BD Address: ") + len (b"BD Address: ")
    addrMac = listAddr[index:(index+17)]


    ################################################
    #         Partie serveur wifi Ad-Hoc :         #
    ################################################
    print("\nEn attente d'un fichier\nOuverture du serveur Wifi :\n")

    with sok.socket(sok.AF_INET, sok.SOCK_STREAM) as serveur:
        serveur.bind((HOST, PORT))
        serveur.listen(1)

        while True:
            conn, addr = serveur.accept()
            print("Connection from", addr)

            FILENAME = conn.recv(256)
            print ("Fichier : " + str(FILENAME))

            # Lecture et ecriture du fichier receptionné dans un nouveau fichier f
            with conn, open(FILENAME, "wb") as f:
                data = conn.recv(1024)
                while data:
                    f.write(data)
                    data = conn.recv(1024)
            break

        print ("Fichier réceptionné\nFermeture du serveur wifi\n")


    ################################################
    #         Partie client wifi Ad-Hoc :          #
    ################################################
    print ("Envoi de l'adresse mac bluetooth\nOuverture du client wifi:")

    with sok.socket(sok.AF_INET, sok.SOCK_STREAM) as client :
        client.connect((addr[0], PORT))
        client.send((addrMac))

    print("Adresse bluetooth bien envoyé\nFermeture du client wifi\n")


    ################################################
    #           Partie serveur bluetooth :         #
    ################################################
    print ("Attente de la commande à exécuter\nAppareillage bluetooth")

    sokServer = BluetoothSocket(L2CAP)
    sokServer.bind(("",7))
    sokServer.listen(1)
    sokClient, address = sokServer.accept()
    data = str(sokClient.recv(1024))[2:-1]
    print ("Instruction reçue :  [%s]" % data)

    sokClient.close()
    sokServer.close()

    print ("Dissociation Bluetooth\n")

    print ("Exécution de l'instruction\n")
    execute(data)


if __name__ == "__main__":
    main()