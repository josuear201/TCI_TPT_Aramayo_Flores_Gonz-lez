# Propuestas para diseñar AF en C
Cada propuesta presenta una manera de crear un automata finito representando sus componentes: un conjunto de estados, un alfabeto, una función o relación de transiciín dependiendo si el automata es determinista o no, indicar el estado inicial y el conjunto de estados de aceptación.   

- ## Proposicion 1 - Delta como Lista de Transiciones


- ## Proposicion 2 - Delta Indexado por Estado
Se sugiere que las transiciones se agrupen en una lista de acuerdo al estado que lo compone, con una estructura como elemento que contiene al estado y una lista enlazada, con el símbolo y la salida correspondiente como datos. La lista de estados corresponde a los estados del automata y cualquiera de sus sublistas sirve como el alfabeto y, con su ubicación como contexto, se puede saber los *deltas*. Esto permite buscar de manera más ordenada a la salida de una determinada transición, recorriendo primero por el estado pedido y luego, una vez se encuentra el estado, por el caracter.  

También el conjunto de estados de aceptación no aparece explicitamente pero cada estado guarda la información por su cuenta con una bandera. Si se quiere saber el conjunto se debe recorrer la listas de estados y revisar cuales son de aceptación.  

El automata en sí es el padre de la lista principal. Este además tiene el nombre del estado inicial y una bandera que indica si el automata es determinista o no.

- ## Proposicion 3 - Delta como Matriz Dispersa


- ## Proposicion 4 - Delta Funcional


- ## Proposicion 5 - Estados Compuestos para Determinización



- ## Proposicion que utilizaremos
