#!/bin/bash


# Vérifie si l'option --script a été passée en argument
if [ "$1" != "--script" ]; then
    socat TCP-LISTEN:"$1",fork,reuseaddr EXEC:"$0 --script"
fi




# Utilisation de "$*" pour traiter tous les arguments comme une seule chaîne
case "$@" in
    	'--script')

        read requete
        getVerif=$(echo "$requete" | cut -d ' ' -f 1)
        if ! echo "$getVerif" | grep -q "GET"; then
            echo -e -n "HTTP/1.1 501 Not Found\r\n"
            echo -e -n "Content-Length: 15\r\n"
            echo -e -n "Connection: close\r\n"
            echo -e -n "Content-Type: text/plain\r\n"
            echo -e -n "\r\n"
            echo "501 : Not Found"
        else
            fichier=$(echo "$requete" | cut -d ' ' -f 2)
            if [ "$fichier" = "/" ]; then
                fichier="/index.html"
            fi
            fichier="./www-test/${fichier}"

            # Vérifie si le fichier existe avant de le lire
            if [ -f "$fichier" ]; then
				if [ -r "$fichier" ]; then
					mime=$(file -L --brief --mime-type $fichier)
					echo -e -n "HTTP/1.1 $1 OK\r\n"
					echo -e -n "Content-Length: $(wc -c < $fichier)\r\n"
					echo -e -n "Connection: close\r\n"
					echo -e -n "Content-Type: $mime\r\n"
					echo -e -n "\r\n"
					cat $fichier
				else 
					echo "403 : forbidden"
				fi
            else
                echo -e -n "HTTP/1.1 404 Not Found\r\n"
                echo -e -n "Content-Length: 15\r\n"
                echo -e -n "Connection: close\r\n"
                echo -e -n "Content-Type: text/plain\r\n"
                echo -e -n "\r\n"
                echo "404 : Not Found"
            fi

			

        fi
        ;;

esac
