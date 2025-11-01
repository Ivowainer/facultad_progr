-module(mult).
-export([multiplicar/2]).


multiplicar(Num, 1) -> Num;
multiplicar(Num, Cant) -> Num + multiplicar(Num, Cant-1).