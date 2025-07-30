-module(invertir).
-export([invertir_list/1]).

invertir_list(List) -> invertir_list(List, []).

invertir_list([], Acc) -> Acc;
invertir_list([Hd | Td], NewList) ->
    invertir_list(Td, [ Hd | NewList ]).

