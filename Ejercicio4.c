#include <stdio.h>
#include <stdlib.h>

/*
 Formato de entrada:
   m
   t1 v1
   t2 v2
   ...
   tm vm

 Donde:
   ti ∈ {0,1}  (0=tuerca, 1=tornillo)
   vi es el "tamaño" (entero) de esa pieza

 El programa separa las piezas en dos arreglos (tuercas y tornillos).
 Requisito: debe haber la misma cantidad de tuercas que de tornillos.
*/

/* 
 * Prototipos sugeridos de funciones auxiliares
 * --------------------------------------------
 * Estas NO están implementadas, solo son guías:
 *
 * int partir_tuercas(int tuercas[], int bajo, int alto, int tornilloPivote);
 *   -> Reorganiza las tuercas comparándolas con un tornillo pivote.
 *
 * int partir_tornillos(int tornillos[], int bajo, int alto, int tuercaPivote);
 *   -> Reorganiza los tornillos comparándolos con una tuerca pivote.
 *
 * La idea: usarlas de forma recursiva, estilo quicksort.
 */

/*
 * FUNCIÓN PRINCIPAL A IMPLEMENTAR
 *
 * Objetivo: reordenar ambos arreglos (tuercas y tornillos) de manera que
 *           al final ambos queden en el mismo orden.
 *
 * Reglas:
 * - Solo se permite comparar tuerca vs tornillo.
 * - No está permitido comparar tuerca vs tuerca ni tornillo vs tornillo.
 *
 */
void intercambiar( int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partir_tuercas(int tuercas[], int bajo, int alto, int tornilloPivote){

    int i=bajo;
    for(int j=bajo; j<alto; j++){
        if(tuercas[j]<tornilloPivote){
            intercambiar(&tuercas[i], &tuercas[j]);
            i++;   
          } else if(tuercas[j]==tornilloPivote){

            intercambiar(&tuercas[j],&tuercas[alto]);
            j--;
          }
    }

    intercambiar(&tuercas[i],&tuercas[alto]);
    return i;

}

int partir_tornillos(int tornillos[], int bajo, int alto, int tuercaPivote) {
    int i = bajo;
    for(int j = bajo; j< alto; j++) {
        if (tornillos[j] < tuercaPivote) {
            intercambiar(&tornillos[i], &tornillos[j]);
            i++;
        } else if(tornillos[j]==tuercaPivote){
            intercambiar(&tornillos[j], &tornillos[alto]);
            j--;
        }
    }
    intercambiar(&tornillos[i + 1], &tornillos[alto]);
    return(i + 1);
    return -1;
}

void emparejar_recursivo(int tuercas[], int tornillos[], int bajo, int alto){

    if(alto>=bajo) return;

    int indicePivote=partir_tuercas(tuercas, bajo, alto, tornillos[alto]);
    partir_tornillos(tornillos, bajo, alto, tuercas[indicePivote]);
    emparejar_recursivo(tuercas, tornillos, bajo, indicePivote-1);
    emparejar_recursivo(tuercas, tornillos, indicePivote+1,alto);


}

void emparejar_tuercas_y_tornillos(int tuercas[], int tornillos[], int n) {
    // Escribe aquí tu función
    //
    // Sugerencia: define una función recursiva como:
    // void emparejar_recursivo(int tuercas[], int tornillos[], int bajo, int alto);
    //
    // Dentro de ella puedes llamar a:
    //   int indicePivote = partir_tuercas(tuercas, bajo, alto, tornillos[alto]);
    //   partir_tornillos(tornillos, bajo, alto, tuercas[indicePivote]);
    //
    // Y luego hacer llamadas recursivas en los subarreglos.
    if(n<=0) return;

    emparejar_recursivo(tuercas, tornillos, 0, n-1);

}



/* Imprime un arreglo lineal */
void imprimir_arreglo(const char *etiqueta, int arr[], int n) {
    printf("%s: ", etiqueta);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int m;  // número total de pares provistos en la entrada

    printf("Ingrese el numero total de piezas (tuercas + tornillos):\n");
    if (scanf("%d", &m) != 1 || m <= 0) {
        fprintf(stderr, "Error: m inválido.\n");
        return 1;
    }

    int *tuercas   = (int *)malloc(m * sizeof(int));
    int *tornillos = (int *)malloc(m * sizeof(int));
    if (!tuercas || !tornillos) {
        fprintf(stderr, "Error: memoria insuficiente.\n");
        free(tuercas); free(tornillos);
        return 1;
    }

    int n_tuercas = 0, n_tornillos = 0;

    printf("\nEscriba primero el tipo de pieza: 0 si es una TUERCA, y 1 si es un TORNILLO \n");
    printf("Después escriba el tamaño (un numero entero).\n");
    printf("Ejemplo: 0 15 -> tuerca de tamaño 15\n");

    for (int i = 0; i < m; i++) {
        int tipo, valor;
        printf("Pieza %d:\t", i+1);
        if (scanf("%d %d", &tipo, &valor) != 2) {
            fprintf(stderr, "Error: entrada inválida en la línea %d.\n", i + 2);
            free(tuercas); free(tornillos);
            return 1;
        }
        if (tipo == 0) {           // tuerca
            tuercas[n_tuercas++] = valor;
        } else if (tipo == 1) {    // tornillo
            tornillos[n_tornillos++] = valor;
        } else {
            fprintf(stderr, "Error: tipo debe ser 0 (tuerca) o 1 (tornillo).\n");
            free(tuercas); free(tornillos);
            return 1;
        }
    }

    if (n_tuercas != n_tornillos) {
        fprintf(stderr, "Error: cantidad desigual de tuercas (%d) y tornillos (%d).\n",
                n_tuercas, n_tornillos);
        free(tuercas); free(tornillos);
        return 1;
    }

    int n = n_tuercas; // número de parejas

    // Llamada a la función a implementar
    emparejar_tuercas_y_tornillos(tuercas, tornillos, n);

    // Mostrar resultados como dos arreglos lineales
    printf("\nResultado de su emparejamiento:\n");
    imprimir_arreglo("Tuercas", tuercas, n);
    imprimir_arreglo("Tornillos", tornillos, n);

    free(tuercas);
    free(tornillos);
    return 0;
}
