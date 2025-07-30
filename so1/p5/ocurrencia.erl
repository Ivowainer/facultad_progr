-module(ocurrencia).
-export([ocurrencia_list/3]).

ocurrencia_list([], Contador, Num) -> Contador;
ocurrencia_list([Hd | Tl], Contador, Num) ->
    if 
        Hd == Num -> ocurrencia_list(Tl, Contador+1, Num);
        true -> ocurrencia_list(Tl, Contador, Num)
    end.