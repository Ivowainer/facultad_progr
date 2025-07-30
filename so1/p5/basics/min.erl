-module(min).
-export([min/1, process_list/1]).

min([Hd]) -> Hd;
min([Hd | Tl]) ->
    Rest = min(Tl),
    if
        Hd < Rest -> Hd;
        true -> Rest
    end.

process_list([]) -> empty;                    % Lista vacía
process_list([Only]) -> {single, Only};       % Un elemento
process_list([H|T]) -> {head, H, tail, T}.

% min([5,3,8,1])
% → compara 5 con min([3,8,1])
%   → compara 3 con min([8,1])
%     → compara 8 con min([1])
%       → devuelve 1
%     → devuelve min(8,1) = 1
%   → devuelve min(3,1) = 1
% → devuelve min(5,1) = 1