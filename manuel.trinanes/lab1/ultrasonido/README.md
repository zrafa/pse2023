
# Ultrasonido

## Conexiones
Utiliza el puerto D8 para el Trigger y D9 para el Echo del Ultrasonido.

## Funcionamiento
Pone en alto la señal del trigger hasta pasados 10us, donde la baja.
Espera hasta que el echo este en alto, para luego contar cuanto 10us pasan hasta que dicho echo este en bajo o que hayan pasado mas de 38.000us.
Y por ultimo, a dicho tiempo lo multiplica por 10 para obtener el numero en us, y lo divide por 100 para obtener una medida aproximada en cm, digo aproximada ya que los primeros 10cm son precisos pero luego se pierde dicha precision.


