# Graficos-por-Computador
FUNCIONES PRINCIPALES
?	Visualizar la ayuda
ESC	Finalizar la ejecución de la aplicación
F,f	Carga de objeto desde un fichero *.obj
TAB	Seleccionar siguiente objeto (de entre los cargados)
SUPR	Eliminar objeto seleccinado
CTRL + +	Reducir el volumen de visualización
CTRL + -	Incrementar volumen de visualización
TRANFORMACIONES
Las transformaciones se realizan mediante la teclas especiales (flechas, AvPag, RePag...),pero mediante la teclas normales se controla el tipo de elemento que se quiere transformar, el tipo de transformación que se quiere realizar y el sistema de referencia en el que se realiza la transformación. Todos ellos tendrán un valor de inicialización por defecto, pero se podrán modificar con las siguientes teclas:

 Tipo de transformación
M,m	Activar traslación
B,b	Activar rotación
T,t	Activar escalado
Sistema de referencia (modos excluyentes entre si).
G,g	Activar transformaciones en el sistema de referencia del mundo (transformaciones globales)
L,l	Activar transformaciones en el sistema de referencia local del objeto (objeto 3D, ccámara o luces) )
Elemento a transformar (en todo momento se debe estar en algun modo. Son excluyentes entre si):
O,o	Aplicar transformaciones al objeto seleccionado (valor por defecto) (desactiva cámara y luz)
K,k	Aplicar transformaciones a la cámara actual (desactiva objeto y luz)
A,a	Aplicar transformaciones a la luz selecionada (desactiva objeto y camara)
UP	Trasladar +Y; Escalar + Y; Rotar +X
DOWN	Trasladar -Y; Escalar - Y; Rotar -X
RIGHT	Trasladar +X; Escalar + X; Rotar +Y
LEFT	Trasladar -X; Escalar - X; Rotar -Y
AVPAG	Trasladar +Z; Escalar + Z; Rotar +Z
REPAG	Trasladar -Z; Escalar - Z; Rotar -Z
+	Escalar + en todos los ejes (solo objetos)
-	Escalar -  en todos los ejes (solo objetos)
CTRL + (Z,z)	Deshacer