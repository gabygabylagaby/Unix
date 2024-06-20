# Proyecto Final:

Write a service running a NET socket, max connections should be 30
it should receive the port as program argument
every client connection should be handled by a thread or fork
it should handle SIGINT signal (Ctrl+C)
the service will receive the following messages 
getInfo that should return a service name and the version
i.e. “Mike’s service, v0.1”
getNumberOfPartitions, should return number of partitions of the system
it can be implemented using bash scripting or calling directly to utilities, i.e. lsblk -l | grep part
getCurrentKernelVersion, should return the kernel version that the system is running
just the numerical par, you can use uname -r, it also can be though bash scripting or calling directly to uname utility
sshdRunning, should return true or false
it should be implemented using popen()
you can use one of these methods, or another one that could detect that sshd is running
ps ax|grep sshd
netstat -l |grep ssh
verify that sshd.pid file exists (/var/run/sshd.pid)
for getInfo, getNumberOfPartitions, and getCurrentKernelVersion, two of them can be implemented with bash scripting, the third one needs to be with popen or execv (or variations) if applicable.

## Explicacion en clases:
Vamos a tener un script de get info 
y otra maquina que tenga get kernel

y mi servicio dice que utiliza camel case entonces cuando el cliente se conecte, no va a reconocer.

' colaborador cesar-flores-jf '

definimos varias versiones:
- getInfo ->
-getKernelVersion ->

# Lo que realice:

## Instrucciones

### 1. Preparación del Entorno

1. Clona el repositorio o descarga el código fuente en tu máquina local.
2. Asegúrate de que tienes los archivos `server.c` y `client.c` en el mismo directorio.

### 2. Compilación del Código

Ejecuta el siguiente comando para compilar los archivos fuente del servidor y el cliente:

```sh
./test_service.sh
```

### Resultado

Unix/Proyecto final/Proyecto on  main [!?] via C v11.4.0-gcc on ☁️  
❯ ./test_service.sh

Servidor iniciado con PID 50109
Bind failed: Address already in use
Ejecutando comando: getInfo
Response: Gaby’s service, v0.1

Ejecutando comando: getNumberOfPartitions
Response: 2


Ejecutando comando: getCurrentKernelVersion
Response: 6.5.0-41-generic


Ejecutando comando: sshdRunning
Response: true

./test_service.sh: line 30: kill: (50109) - No such process
Servidor detenido
