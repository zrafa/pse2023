# Sistema de control de planta química

Este programa cumple con los siguientes requisitos funcionales:

```
La consola del operador:
- si el operador presiona 'b', el motor se detiene.
- si el operador presiona 'n' el motor continua la marcha en la velocidad
  actual.

- si el operador presiona 'a' el servo se mueve a la izquierda (no al extremo
  izquierdo, sino que desde la posición actual hace un pequeño movimiento
  hacia la izquierda).
- si el operador presiona 'd' el servo se mueve a la derecha.

El knob controla la velocidad de un motor cc.

Se mantiene por software un real time clock que mantiene el tiempo
transcurrido. comenzando en 00:00:00 (hora:minutos:segundos) desde que
comenzó a ejecutarse el sistema desde el último reset.

Un led testigo parpadea. La frecuencia del parpadeo es proporcional a la
velocidad del motor. Mayor velocidad, mayor frecuencia. Cuando el motor está
detenido el led está apagado. Suponga que a minima velocidad el led parpadea a
1hz. y a maxima velocidad a 10hz.

Se reporta al operador el tiempo transcurrido desde el ultimo reset, la
velocidad del motor (en porcentaje sobre 100%), y el angulo al que apunta el
servo. Cada un segundo.

Ejemplo de salida recibida por el operador:
00:02:34. velocidad: 20 %. servo: 180 grados.
00:02:35. velocidad: 20 %. servo: 180 grados.
00:02:36. velocidad: 30 %. servo: 180 grados.
```

### Observacion

Aparentemente, el servo utilizado se posiciona en:
    - 0° cuando la duracion de la senial en alto (duty) es de 0.0005 
    - 180° cuando la duracion de la senial en alto es de 0.0022

## Alumno

- [@Santino Castagno](https://www.github.com/SantinoCastagno)
