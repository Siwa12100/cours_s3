#!/bin/bash

# Activer l'agent SSH
eval $(ssh-agent -s)

# Fonction pour ajouter une clé privée à l'agent SSH
function add_key_to_agent {
    ssh-add "$1"
    echo "Clé privée ajoutée à l'agent SSH : $1"
}

# Si des chemins vers des clés privées sont passés en paramètres
if [ $# -gt 0 ]; then
    for key_file in "$@"; do
        if [[ "$key_file" != *.pub ]]; then
            add_key_to_agent "$key_file"
        fi
    done
else
    # Si aucun chemin n'est passé en paramètre, parcourir le dossier ~/.ssh/
    ssh_dir="$HOME/.ssh"
    if [ -d "$ssh_dir" ]; then
        for key_file in "$ssh_dir"/*; do
            if [[ "$key_file" != *.pub ]]; then
                add_key_to_agent "$key_file"
            fi
        done
    else
        echo "Le dossier ~/.ssh/ n'existe pas."
        exit 1
    fi
fi




# ===================================
# eval $(ssh-agent -s)

# if ! ssh-add "$1" 
#     then
#         for cle in "~/.ssh/*"
#             do 
#                 echo "$cle"
#                 if ! grep '.pub' 
#                     then 
#                         echo " bonne clé : $cle " 
#                 fi
#             done
#     fi