#!/bin/bash

# Vérifie si le fichier Makefile existe dans le dossier courant
if [ -e "Makefile" ]; then
    clear
    echo "[Script Siwa makeC.sh] : Makefile bien trouvé."
    
    # Exécute la commande 'make' et capture la sortie
    make_output=$(make 2>&1)

    # Vérifie si la compilation a réussi (make retourne 0 en cas de succès)
    if [ $? -eq 0 ]; then
        echo "[Script Siwa makeC.sh] : Compilation effectuée, exécution :"
        echo "---"
        echo ""
        ./bin/exe
    else
        echo "[Script Siwa makeC.sh] : Erreurs à la compilation :"
        echo "---"
        echo ""
        echo "$make_output"
    fi
else
    # Si le fichier Makefile n'existe pas, affiche un message d'erreur
    current_dir=$(pwd)
    echo "[Script Siwa makeC.sh] : Makefile introuvable dans le dossier courant ($current_dir)."
fi
