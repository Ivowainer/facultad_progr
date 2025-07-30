-module(par_impar).
-export[es_par/1].

es_par(Num) ->
    (Num rem 2) == 0.