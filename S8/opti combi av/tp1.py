def lecture_fichier(fichier):
    cpt=1
    length=0
    nbvar=0
    nbcloses=0
    matrice=[]
    tabtmp=[]
    i=0
    
    while(i<8+int(nbcloses)):

        if(cpt==6):
            ligne=fichier.readline()
            j=21
            while(ligne[j]!=" "):
                tabtmp.append(ligne[j])
                j+=1
            length=''.join(tabtmp)        
            tabtmp.clear()

        elif(cpt==8):
            ligne=fichier.readline()
            j=6
            while(ligne[j]!=" "):
                tabtmp.append(ligne[j])
                j+=1
            nbvar=''.join(tabtmp)
            j+=2
            tabtmp.clear()
            while(ligne[j]!=" "):
                tabtmp.append(ligne[j])
                j+=1
            nbcloses=''.join(tabtmp)
            tabtmp.clear()    

        elif(cpt<8):
            ligne=fichier.readline()

        else:
            ligne=fichier.readline()
            tabtmp.clear()   
            tab=[0]*int(length)        
            k=0
            cpt2=0
            while(ligne[k]!="0" or cpt2<2):
                if(ligne[k]=='-' or ligne[k].isnumeric()==1):
                    tabtmp.append(ligne[k])
                elif(ligne[k]==" " and cpt2<int(length)):
                    tab[cpt2]=''.join(tabtmp)
                    tabtmp.clear()
                    cpt2+=1
                k+=1
            matrice.append(tab)
            
        cpt+=1
        i+=1
    
    return int(length),int(nbvar),int(nbcloses),matrice



###########################################################
#                                                         #
#                           MAIN                          #
#                                                         #
###########################################################

fichier=open("uf20-01.cnf","r")
#fichier=open("uuf125-01.cnf","r")
length,nbvar,nbcloses,matrice=lecture_fichier(fichier)
fichier.close()

print("length = ",length)
print("nbvar = ",nbvar)
print("nbcloses = ",nbcloses)
print("matrice = ",matrice)