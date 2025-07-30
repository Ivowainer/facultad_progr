-module(delete_dup).
-export([delete_dup_list/1, already_in_list/2]).

already_in_list(List, Num) -> 
    case List of
        [] -> false;
        [Hd | Td] -> 
            if 
                Hd == Num -> true;
                true -> already_in_list(Td, Num)
            end
    end.

delete_dup_list(List) -> 
    Result = delete_dup_list(List, []),
    lists:reverse(Result).

delete_dup_list(List, NewList) ->
    case List of 
        [] -> NewList;
        [Hd | Td] -> 
            case already_in_list(NewList, Hd) of
                true -> delete_dup_list(Td, NewList);
                false -> delete_dup_list(Td, [ Hd | NewList ])
            end
    end.