#!/bin/bash

# Ce script permet d'écrire en une seule fois les 3 commandes :
# - git add .
# - git cmmit -m "..." 
# - git push

# Le but étant de gagner du temps lors du travail sur du code et d'éviter de 
# toujours devoir rentrer ces 3 commandes à la suite. 

# Il est préférable de passer en paramètre du script le message à mettre dans le 
# commit, mais si ce n'est pas fait, il message par défaut est utilisé. 

# On vérifie qu'un message est bien passé, sinon on en met un par défaut 
if [ -z "$1"]
    then 
        msg="commit de $USER avec le script gitSend sans msg défini."
    else
        msg="$1"
fi

# On essaye le git add 
if git add . 
    then
        # On essaye le commit 
        if git commit -m "$msg" 
            then
                # On essaye le push
                if git push
                    then

                        echo -n "--> push bien réalisé !"
                    else 
                        echo -n " --> soucis pendant le push..."
                fi

            else 
                echo -n "--> soucis pendant le commit..."
        fi
    else
        echo -n "--> soucis pendant le add..."
fi 