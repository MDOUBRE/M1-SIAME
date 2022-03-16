#!/usr/bin/env python3

import os, sys
import socket as sok
import stat
import subprocess as sub

HOST=""
FILENAME="recu"
FILECMD=""
PORT=50008

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
    print ("Reception d'un fichier et de la commande d'exécution par Wifi\n")


    ################################################
    #         Partie serveur wifi Ad-Hoc :         #
    ################################################
    print("En attente d'un fichier\nOuverture du serveur Wifi :")

    with sok.socket(sok.AF_INET, sok.SOCK_STREAM) as serveur:
        serveur.setsockopt(sok.SOL_SOCKET, sok.SO_REUSEADDR, 1)
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

        print ("Attente de la commande en Wifi\nInitialisation du Wifi :")

        serveur.listen(1)
        while True:
            conn,addr=serveur.accept()
            print("Connection from", addr)
            FILECMD = conn.recv(256)
            print ("La commande à exécuter : " + str(FILECMD))

            break

        print ("Fermeture de la Wifi\n")

        serveur.shutdown(sok.AF_INET)
        serveur.close()


    print ("Exécution de la commande\n")
    execute(FILECMD)


if __name__ == "__main__":
    main()