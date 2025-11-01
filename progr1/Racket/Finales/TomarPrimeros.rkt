;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname TomarPrimeros) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;Ejercicio 2. Diseñe una función tomar-primeros,
;que dado un predicado f, un natural n y
;una lista l de elementos de cierto tipo X,
;devuelva una lista con los primeros n elementos de l
;que satisfacen f.
;Definir la función sin utilizar ninguna función sobre listas,
;salvo los constructores y selectores de listas, y el predicado empty?.

;devuelva una lista con los primeros n elementos de l
;que satisfacen f.
(define (tomar-primeros f n l)
  (cond
    [(or (empty? l) (zero? n)) '()]
    [(f (first l)) (cons (first l) (tomar-primeros f (sub1 n) (rest l)))]
    [else (tomar-primeros f n (rest l))])
)

(check-expect (tomar-primeros negative? 3 (list 1 -2 3 -4 -5 -6 -8 7)) (list -2 -4 -5))
(check-expect (tomar-primeros empty? 2 (list '() (list 2 1 3) '() '() '() '())) (list '() '()))
(check-expect (tomar-primeros positive? 1 (list 1 2 3 4 5 6 7)) (list 1))