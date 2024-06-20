#!/bin/bash

# Compilar el servidor y el cliente
gcc -o server server.c -lpthread
gcc -o client client.c

# Iniciar el servidor en segundo plano
./server 8080 &
SERVER_PID=$!
echo "Servidor iniciado con PID $SERVER_PID"

# Dar tiempo al servidor para que inicie
sleep 2

# Función para ejecutar comandos del cliente
function run_client_command() {
    local command=$1
    echo "Ejecutando comando: $command"
    ./client 127.0.0.1 8080 "$command"
    echo
}

# Ejecutar los comandos necesarios
run_client_command "getInfo"
run_client_command "getNumberOfPartitions"
run_client_command "getCurrentKernelVersion"
run_client_command "sshdRunning"

# Detener el servidor
kill $SERVER_PID
echo "Servidor detenido"
