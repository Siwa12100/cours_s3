#!/bin/sh

if [ $1 != "--script"]; then 
    socat TCP-LISTEN:2000 , reuseaddr , fork SYSTEM:"./server.sh --script"
fi


while read line; do 
    if [grep "GET" "$line"]; then

        fichier = $(cut -d ' ' -f 2 "$line")
        if ["$fichier" -e]; then
            if [$"fichier" -r]; then

            echo "[Temporaire] : Passage par ici....."

            else 
                echo "[Erreur 403] : Le fichier spécifié est illisible."
        else
            echo "[Erreur 404] : Le fichier spécifié n'existe pas."
        fi

    else
        echo "[Erreur 501] : Pas de requête GET fournie." 
    fi
done 