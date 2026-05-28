% Caso base: Mover 1 disco del origen al destino
hanoi(1, Origen, Destino, _, _) :-
    escribir_movimiento(Origen, Destino).

% Caso recursivo: Mover N discos
hanoi(N, Origen, Destino, Auxiliar, Contador) :-
    N > 1,
    M is N - 1,
    % Paso 1: Mover N-1 discos del Origen al Auxiliar usando el Destino
    hanoi(M, Origen, Auxiliar, Destino, Contador),
    % Paso 2: Mover el disco grande restante al Destino
    escribir_movimiento(Origen, Destino),
    % Paso 3: Mover los N-1 discos del Auxiliar al Destino usando el Origen
    hanoi(M, Auxiliar, Destino, Origen, Contador).

% Predicado auxiliar para imprimir el movimiento en pantalla
escribir_movimiento(Origen, Destino) :-
    write('Mover disco desde la torre '), write(Origen),
    write(' hasta la torre '), write(Destino), nl.

% Predicado principal para iniciar el juego de forma más cómoda
resolver_hanoi(N) :-
    write('Pasos para resolver las Torres de Hanoi con '), write(N), write(' discos:'), nl,
    hanoi(N, 'A', 'C', 'B', _).