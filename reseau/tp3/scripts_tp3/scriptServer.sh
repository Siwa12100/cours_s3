#!/bin/bash


# Cas où le --script manque : 
# ===========================


# si l'option n'est pas présente, on lance de nouveau le script sur le port passé 
# en paramètre, mais avec l'option --script en plus
# On utilise le fork pour lancer un processus fils à chaque nouvelle connexion qui entre...
if [ "$1" != "--script" ]; then
    socat TCP-LISTEN:"$1",fork,reuseaddr EXEC:"$0 --script"
fi



# Cas où le --script est bien mentionné : 
# =======================================

# On inspecte les arguments passés en paramètres au script 
case "$@" in
        # Si on a bien le --script on fait : 
    	'--script')
        # On lit la première ligne de la requête et on la met dans la variable requete
        read premiereLigneRequete

        # On récupère le premier mot de ligne 
        verificationGet=$(echo "$premiereLigneRequete" | cut -d ' ' -f 1)

        # Si ce n'est pas get, on fait : 
        if ! echo "$verificationGet" | grep -q "GET"; then
            echo -e -n "HTTP/1.1 501 Not Found\r\n"
            echo -e -n "Content-Length: 15\r\n"
            echo -e -n "Connection: close\r\n"
            echo -e -n "Content-Type: text/plain\r\n"
            echo -e -n "\r\n"

            echo "[ Erreur 501 ]: La requête n'a rien trouvé..."

        else
            # Si le get est bien présent : 
            # On récupère le second string de la première ligne 
            fichierNom=$(echo "$premiereLigneRequete" | cut -d ' ' -f 2)

            # Si il est à la racine du dossier courant, c'est index.html 
            if [ "$fichierNom" = "/" ]; then
                fichierNom="/index.html"
            fi

            # On rajoute le chemin jusqu'au fichier....
            fichierNom="./www-test/${fichierNom}"

            # On regarde si le fichier existe avant de le lire
            # S'il existe : 
            if [ -f "$fichierNom" ]; then
                # Si le fichier est bien lisible : 
				if [ -r "$fichierNom" ]; then
                    # On utilise le file pour connaitre le type de fichier étudié 
					mime=$(file -L --brief --mime-type $fichierNom)
					echo -e -n "HTTP/1.1 $1 OK\r\n"
					echo -e -n "Content-Length: $(wc -c < $fichierNom)\r\n"
					echo -e -n "Connection: close\r\n"
                    # On spécifie bien le type de fichier 
					echo -e -n "Content-Type: $mime\r\n"
					echo -e -n "\r\n"

                    # On affiche le contenu du fichier....
					cat $fichierNom

				else 
                    # S'il existe mais qu'il n'est pas lisible : 
					echo "[ Erreur 403 ] : Accès au fichier refusé..."
				fi

                # Sinon, c'est qu'il n'existe même pas....
            else
                echo -e -n "HTTP/1.1 404 Not Found\r\n"
                echo -e -n "Content-Length: 15\r\n"
                echo -e -n "Connection: close\r\n"
                echo -e -n "Content-Type: text/plain\r\n"
                echo -e -n "\r\n"
                echo "[ Erreur 404 ] : fichier introuvable..."
            fi
        fi
        ;;
esac
