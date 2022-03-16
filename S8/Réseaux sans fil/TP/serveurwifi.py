import os, sys
import socket
import stat
import subprocess
from bluetooth import *

HOST=""
FILENAME="recu"
FILECMD=""
PORT=50008


# Executer en super user (sudo)
# @param le dernier nombre de l'adresse ip  
# @return execute le fichier recu


# Execution du fichier recu
def execute(filename):
    st=os.stat(filename)
    os.chmod(filename, st.st_mode | stat.S_IEXEC) #donne les droits au fichier de s'executer

    pid=os.fork()
    if(pid==0):
        os.system(filename)
    else:
        os.wait()


def main():

# Initialisation Wifi ESSID 'RPI'
    print ("Reçois un fichier en Wifi et une cmd a executer en Bluetooth")
    print ("Initialisation du Wifi :\n")


#partie I
# partie serveur wifi

    print ("En attente d'un fichier")
    print("Ouverture serveur Wifi :")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as serveur:
        serveur.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        serveur.bind((HOST, PORT))
        serveur.listen(1)

        while True:
            conn,addr=serveur.accept()
            print("Connection from", addr)
                
            FILENAME=conn.recv(256)
                
            print ("Le nom du fichier : " + str(FILENAME))

            #lecture du fichier reçu et ecriture dans le nouveau fichier
            with conn, open(FILENAME, "wb") as fic:
                data=conn.recv(1024)
                while data:
                    fic.write(data)
                    data=conn.recv(1024)
            break
                
        print ("Fichier recu")
        print ("Fermeture du serveur wifi\n")        


	# Réception de la commande à exécuter
        print ("Attente de la commande en Wifi")
        print ("Initialisation du Wifi :")

        serveur.listen(1)
        while True:
            conn,addr=serveur.accept()
            print("Connection from", addr)
            FILECMD = conn.recv(256)
            print ("La commande à exécuter : " + str(FILECMD))
            
            break
        
        print ("Fermeture de la Wifi")
        
        serveur.shutdown(socket.AF_INET)
        serveur.close()
                

	# Execution de la commande
    print ("Exécution de la commande\n")
    execute(FILECMD)
        

if __name__ == "__main__":
    main()