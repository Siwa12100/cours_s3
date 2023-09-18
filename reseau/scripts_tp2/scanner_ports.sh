#!/bin/bash

# Vérifie s'il y a un argument passé en ligne de commande
if [ $# -eq 1 ]; then
  host="$1" # Utilise l'adresse IP passée en argument
else
  host="localhost" # Utilise localhost par défaut si aucun argument n'est passé
fi

echo "Ports ouverts de la machine ayant l'IP $host"

ports=$(seq 0 1024) # Plage de ports à scanner (0 à 1024 dans ce cas)

for port in $ports
do
  (socat -v -t 1 TCP:$host:$port OPEN:/dev/null 2>/dev/null) && {
    service_name=$(grep -w "$port/tcp" /etc/services | awk '{print $1}')
    if [ -n "$service_name" ]; then
      echo "Port $port ouvert : $service_name"
    else
      echo "Port $port ouvert"
    fi
  }
done


