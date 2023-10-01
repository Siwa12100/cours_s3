#!/bin/bash

# Vérifier si l'agent SSH est activé
if [ -n "$SSH_AUTH_SOCK" ]; then
    echo "[Script Siwa initSshAgent.sh] : Agent SSH bien activé préalablement."
else
    echo "[Script Siwa initSshAgent.sh] : L'agent SSH n'est pas activé, pensez à le faire dans le fichier de configuration du shell."
    exit 1
fi

# Fonction pour ajouter une clé privée à l'agent SSH
function add_key_to_agent {
    ssh-add "$1"
    echo "Clé privée ajoutée à l'agent SSH : $1"
}

# Si l'option -g est passée en paramètre
if [ "$1" == "-g" ]; then
    echo "[Script Siwa initSshAgent.sh] : Exécution du script en mode github."
    shift # Supprimer l'option -g des paramètres
    while IFS= read -r -d $'\0' key_file; do
        add_key_to_agent "$key_file"
    done < <(find "$HOME/.ssh" -maxdepth 1 -type f -name '*github*' -not -name '*.pub' -print0)
elif [ $# -eq 0 ]; then
    echo "[Script Siwa initSshAgent.sh] : Exécution du script sans aucun paramètre."
else
    # Si des chemins vers des clés privées sont passés en paramètres
    for key_file in "$@"; do
        if [[ "$key_file" != *.pub ]]; then
            add_key_to_agent "$key_file"
        fi
    done
fi



