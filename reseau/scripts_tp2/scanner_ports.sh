#!/bin/bash

# Si il y a bien un argument de passé en ligne de commande 
if [ $# -eq 1 ]; then
  # Alors l'ip que l'on va ping est celle passée en paramètre 
  host="$1"
else
  # Si aucune ip de passée en paramètre, on exécute le script sur notre machine 
  host="localhost" 
fi
# On commance par afficher l'ip de la machine à qui on va scanner les ports 
echo "Ports ouverts de la machine ayant l'IP $host"
# On défini la liste des ports que l'on va scanner
ports=$(seq 0 1024) # Plage de ports à scanner (0 à 1024 dans ce cas)
# Pour chaque pour dans la liste, on va effectuer des actions 
for port in $ports
do
  # On commence par essayer d'établir une connexion avec le port via soccat 
  (socat -v -t 1 TCP:$host:$port OPEN:/dev/null 2>/dev/null) && {
    # Si on a réussit, on récupère le nom du service associé à ce port 
    # On récupère dans /etc/services les lignes avec écrit port/tcp 
    # Et dans ces lignes ci on prend le premier mot avec le awk 
    service_name=$(grep -w "$port/tcp" /etc/services | awk '{print $1}')
    # Si la variable contenant le nom du service est non nulle, on l'affiche 
    if [ -n "$service_name" ]; then
      echo "Port $port ouvert : $service_name"
    else
    # Sinon on fait un affiche ne mentionnant pas le service associé au port 
      echo "Port $port ouvert"
    fi
  }
done


