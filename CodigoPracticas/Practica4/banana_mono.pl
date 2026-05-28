% --- ESTADO DEL MUNDO ---
% Representamos el estado como: estado(PosMono, PosMonoVertical, PosCaja, TieneBanana)
% PosMono y PosCaja pueden ser: 'puerta', 'ventana', 'centro'
% PosMonoVertical puede ser: 'suelo', 'sobre_caja'
% TieneBanana puede ser: 'no', 'si'

% --- MOVIMIENTOS VÁLIDOS (Acciones) ---

% Acción 1: Tomar la banana
% El mono puede tomar la banana si está sobre la caja en el centro y no la tiene aún.
mover(estado(centro, sobre_caja, centro, no),
      tomar,
      estado(centro, sobre_caja, centro, si)).

% Acción 2: Subirse a la caja
% El mono puede subir si está en el suelo en el mismo lugar que la caja.
mover(estado(Pos, suelo, Pos, Ban),
      subir,
      estado(Pos, sobre_caja, Pos, Ban)).

% Acción 3: Empujar la caja
% El mono puede empujar la caja de una Posición 1 a una Posición 2 si ambos están en la Posición 1 en el suelo.
mover(estado(Pos1, suelo, Pos1, Ban),
      empujar(Pos1, Pos2),
      estado(Pos2, suelo, Pos2, Ban)) :- 
    Pos1 \== Pos2.

% Acción 4: Caminar/Moverse solo
% El mono puede caminar de Pos1 a Pos2 si está en el suelo.
mover(estado(Pos1, suelo, PosCaja, Ban),
      caminar(Pos1, Pos2),
      estado(Pos2, suelo, PosCaja, Ban)) :- 
    Pos1 \== Pos2.

% Caso base: Si el estado actual ya muestra que el mono tiene la banana, el plan ha terminado.
solucion(estado(_, _, _, si), []).

% Caso recursivo: Encontrar una acción válida, ejecutarla y resolver el nuevo estado.
solucion(EstadoActual, [Accion | ListaAcciones]) :-
    mover(EstadoActual, Accion, EstadoSiguiente),
    solucion(EstadoSiguiente, ListaAcciones).