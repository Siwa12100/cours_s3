#!/bin/bash

host="127.0.0.1" # Remplacez par l'adresse IP de la cible que vous souhaitez scanner
ports=$(seq 0 1024) # Plage de ports à scanner (0 à 1024 dans ce cas)

for port in $ports
do
  (socat -v -t 1 TCP:$host:$port OPEN:/dev/null 2>/dev/null) && echo "Port $port ouvert"
done
