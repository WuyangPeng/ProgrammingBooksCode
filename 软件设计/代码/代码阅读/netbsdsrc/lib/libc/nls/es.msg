$set 1
$ EPERM
1 Operaci?n no permitida
$ ENOENT
2 Fichero o directorio no existente
$ ESRCH
3 Proceso inexistente
$ EINTR
4 Llamada del sistema interrumpida
$ EIO
5 Error de E/S
$ ENXIO
6 Dispositivo no configurado
$ E2BIG
7 La lista de argumentos es demasiado amplia
$ ENOEXEC
8 Error en el formato del ejecutable 
$ EBADF
9 Descriptor de fichero incorrecto
$ ECHILD
10 No hay procesos hijo 
$ EDEADLK
11 Se ha evitado bloqueo del recurso
$ ENOMEM
12 No se pudo asignar la memoria pedida
$ EACCES
13 Permiso denegado
$ EFAULT
14 Direcci?n incorrecta
$ ENOTBLK
15 Se necesita un dispositivo de bloques
$ EBUSY
16 Dispositivo ocupado
$ EEXIST
17 El fichero ya existe
$ EXDEV
18 Enlace entre dispositivos
$ ENODEV
19 Operaci?n inadecuada para este dispositivo
$ ENOTDIR
20 No es un directorio
$ EISDIR
21 Es un directorio
$ EINVAL
22 Argumento inadecuado
$ ENFILE
23 Hay demasiados ficheros abiertos en el sistema
$ EMFILE
24 Hay demasiados ficheros abiertos
$ ENOTTY
25 IOCTL inapropiado para el dispositivo
$ ETXTBSY
26 Fichero de texto ocupado
$ EFBIG
27 Fichero demasiado grande
$ ENOSPC
28 No queda espacio libre en el dispositivo
$ ESPIPE
29 B?squeda ilegal
$ EROFS
30 Fichero del sistema de s?lo lectura
$ EMLINK
31 Demasiados enlaces
$ EPIPE
32 Canal (pipe) roto
$ EDOM
33 El argumento num?rico est? fuera de rango
$ ERANGE
34 El resultado es demasiado grande
$ EAGAIN, EWOULDBLOCK
35 El recurso est? temporalmente no disponible
$ EINPROGRESS
36 Operaci?n actualmente en proceso
$ EALREADY
37 La operaci?n ya estaba realiz?ndose
$ ENOTSOCK
38 Se ha intentado realizar una operaci?n de socket en algo que no es un socket
$ EDESTADDRREQ
39 Se necesita una direcci?n de destino
$ EMSGSIZE
40 Mensaje demasiado largo
$ EPROTOTYPE
41 Tipo err?neo de protocolo para el socket
$ ENOPROTOOPT
42 Protocolo no disponible
$ EPROTONOSUPPORT
43 Protocolo no contemplado
$ ESOCKTNOSUPPORT
44 Tipo de socket no contemplado
$ EOPNOTSUPP
45 Operaci?n no contemplada
$ EPFNOSUPPORT
46 Familia de protocolos no contemplada
$ EAFNOSUPPORT
47 Familia de direcciones no contemplada por la familia de protocolos
$ EADDRINUSE
48 La direcci?n ya est? en uso
$ EADDRNOTAVAIL
49 No se pudo asignar la direcci?n pedida
$ ENETDOWN
50 La red no funciona
$ ENETUNREACH
51 No se puede acceder a la red
$ ENETRESET
52 La conexi?n a la red se interrumpi? al reinicializar
$ ECONNABORTED
53 La conexi@@@n se ha abortado debid a problemas en el software
$ ECONNRESET
54 El interlocutor ha reinicializado la comunicaci?n
$ ENOBUFS
55 No queda espacio en el almacenamiento intermedio
$ EISCONN
56 El socket ya estaba conectado
$ ENOTCONN
57 El socket no est? conectado
$ ESHUTDOWN
58 No se puede enviar tras la desconexi?n del socket
$ ETOOMANYREFS
59 Demasiadas referencias: no se puede unir
$ ETIMEDOUT
60 El tiempo de conexi?n ha expirado
$ ECONNREFUSED
61 Conexi?n rehusada
$ ELOOP
62 Demasiados niveles de enlaces simb?licos
$ ENAMETOOLONG
63 Nombre de fichero demasiado largo
$ EHOSTDOWN
64 La m?quina est? ca?da
$ EHOSTUNREACH
65 No hay ruta hasta la m?quina
$ ENOTEMPTY
66 Directorio no vac?o
$ EPROCLIM
67 Demasiados procesos
$ EUSERS
68 Demasiados usuarios
$ EDQUOT
69 Cuota de disco sobrepasada
$ ESTALE
70 Manejador de fichero NFS inv?lido
$ EREMOTE
71 Camino con demasiados niveles
$ EBADRPC
72 La estructura de la RPC es err?nea
$ ERPCMISMATCH
73 La versi?n de la RPC es err?nea
$ EPROGUNAVAIL
74 La RPC no est? accesible
$ EPROGMISMATCH
75 Versi?n err?nea del programa
$ EPROCUNAVAIL
76 Procedimiento err?neo para el programa
$ ENOLCK
77 No hay cerrojos disponibles
$ ENOSYS
78 Funci?n no realizada
$ EFTYPE
79 Tipo de fichero o formato inapropiado
$set 2
$ SIGHUP
1 Bloqueo del sistema
$ SIGINT
2 Interrupci?n
$ SIGQUIT
3 Terminaci?n
$ SIGILL
4 Instrucci?n ilegal
$ SIGTRAP
5 Depuraci?n
$ SIGABRT
6 Llamada de aborto
$ SIGEMT
7 EMT trap
$ SIGFPE
8 Excepci?n de coma flotante
$ SIGKILL
9 Asesinato
$ SIGBUS
10 Error en el bus
$ SIGSEGV
11 Fallo de segmentaci?n
$ SIGSYS
12 Llamada al sistema err?nea
$ SIGPIPE
13 Canal (pipe) roto
$ SIGALRM
14 Alarma del reloj
$ SIGTERM
15 Terminado
$ SIGURG
16 Condici?n urgente de E/S
$ SIGSTOP
17 Detenido (se?al)
$ SIGTSTP
18 Detenido
$ SIGCONT
19 Continuado {continuando}
$ SIGCHLD
20 Proceso hijo finalizado
$ SIGTTIN
21 Detenido (entrada tty)
$ SIGTTOU
22 Detenido (salida tty)
$ SIGIO
23 E/S posible {permisible}
$ SIGXCPU
24 Se ha sobrepasado el tiempo l?mite de la CPU
$ SIGXFSZ
25 Se ha sobrepasado el l?mite de longitud de fichero
$ SIGVTALRM
26 Temporizador virtual expirado
$ SIGPROF
27 Perfilador expirado
$ SIGWINCH
28 Cambios en el tama?o de la ventana
$ SIGINFO
29 Petici?n de informaci?n
$ SIGUSR1
30 Se?al definida por el usuario n? 1
$ SIGUSR2
31 Se?al definida por el usuario n? 2
