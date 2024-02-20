# Genetic-algorithm
Genetic Algorithm for the traveling salesman problem, for "Programming Paradigms" course in University. 

INFORMACION SOBRE COMO CORRER PROGRAMA:

Al compilar los files y correr el exe con el argv "-h" el programa devuelve el formato que debe recibir:

    -u umbral -cantGen cantidad generaciones -csv archivoCsv -tipoSalida tipoDeArchivoSalida
    
    •umbral es un numero entre 0 y 1, representa el porcentaje de cambio minimo con el cual debe seguir iterando la reproduccion.
    •cantGen es un entero, representa la cantidad maxima de iteraciones de reproduccion que deben ocurrir si no se alcanza el umbral.
    •csv es el nombre del archivo csv, debe estar en la misma carpeta que el programa
    •tipoSalida puede ser 1, 2 o 3. representa los 3 formatos de salida que se especifican en la web del tp.
Pueden estar en distinto orden pero necesariamente los 4 argumentos con sus identificadores (almenos que se pase solamente -h)

Ejemplo: ./tp2main -u 0.005 -cantGen 100 -csv miCsv.csv -tipoSalida 2
