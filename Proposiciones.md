# Propuestas para diseñar AF en C
Cada propuesta presenta una manera de crear un automata finito representando sus componentes: un conjunto de estados, un alfabeto, una función o relación de transiciín dependiendo si el automata es determinista o no, indicar el estado inicial y el conjunto de estados de aceptación.   

- ## Proposicion 1 - Delta como Lista de Transiciones
La función de transición Δ se guarda como una lista donde cada elemento tiene el estado de origen, el símbolo y los estados a los que puede ir. Esto modela directamente cómo trabaja δ(q,a), ya que cada transición aparece guardada por separado dentro de la estructura. Por ejemplo, si δ(q0,a) = {q1,q2}, quiere decir que desde q0, al leer a, el autómata puede moverse a q1 o q2. Funciona para AFD y AFND por igual, dado que el conjunto destino puede tener uno o más estados. Cada transición ocupa su propio lugar en la lista, lo que la hace fácil de entender e implementar.

Ahora bien, cuando se necesita consultar una transición hay que recorrer la lista hasta dar con el estado y símbolo que se buscan. Por eso, el tiempo que tarda la búsqueda depende de cuántas transiciones haya guardadas.

- ## Proposicion 2 - Delta Indexado por Estado
Se sugiere que las transiciones se agrupen en una lista de acuerdo al estado que lo compone, con una estructura como elemento que contiene al estado y una lista enlazada, con el símbolo y la salida correspondiente como datos. La lista de estados corresponde a los estados del automata y cualquiera de sus sublistas sirve como el alfabeto y, con su ubicación como contexto, se puede saber los *deltas*. Esto permite buscar de manera más ordenada a la salida de una determinada transición, recorriendo primero por el estado pedido y luego, una vez se encuentra el estado, por el caracter.  

También el conjunto de estados de aceptación no aparece explicitamente pero cada estado guarda la información por su cuenta con una bandera. Si se quiere saber el conjunto se debe recorrer la listas de estados y revisar cuales son de aceptación.  

El automata en sí es el padre de la lista principal. Este además tiene el nombre del estado inicial y una bandera que indica si el automata es determinista o no.

- ## Proposicion 3 - Delta como Matriz Dispersa
los estados y símbolos se usan como índices para armar la matriz que representa Δ. A cada par de estado y símbolo le corresponde una celda con los estados destino de esa combinación puntual. Tomando q0 y el símbolo a como índice 0, alcanza con ir directo a esa celda para obtener δ(q0,a), sin ningún paso intermedio. Esto es lo que la diferencia de la lista: no hace falta buscar nada, cada transición ya tiene su lugar fijo dentro de la estructura. Conociendo los índices, el acceso es inmediato. No importa cuántas transiciones tenga el autómata, llegar a una en particular siempre cuesta lo mismo.

Eso la vuelve bastante más práctica en situaciones donde el autómata maneja una cantidad grande de transiciones, ya que el tiempo de consulta no crece con la cantidad de elementos guardados.
- ## Proposicion 4 - Delta Funcional
Se propone usar un AST para representar todos los conjuntos que forman al automata. Un conjunto de estados, otro conjunto de caracteres para formar el alfabeto y el conjunto de estados de aceptación.  

Mientras que para las tranciciones se crea un arreglo con el tamaño guardado. Este tiene de elementos a los *deltas*. Usando una estructura que indica el estado y el símbolo junto al conjunto de destinaciones correspondientes.  

Esta proposición es la más directa en cuando se trata de representar al automata en base a su definición y compocición.

- ## Proposicion 5 - Estados Compuestos para Determinización  

- ## Proposicion que utilizaremos
