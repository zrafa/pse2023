# Serial Knight Rider y Ultrasonido

## Conexiones
Ultrasonido:
--> Echo: D9
--> Trigger: D8

Luces: De D2 a D7

## Funcionamiento
Intenta obtener del serial un char escrito por teclado, si no hay nada, se toma como un input 0 y continua con la ejecucion, si hay algo lo devuelve. Si lo retornado es U, se toma mide la distancia del ultrasonido y si es K se para o enciende el knight rider.
