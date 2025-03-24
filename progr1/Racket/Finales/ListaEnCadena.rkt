;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname ListaEnCadena) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;Ejercicio 3.
;
;Para resolver este ejercicio, en las funciones que se trabajen sobre listas
;se pide que utilice foldr, map y filter.
;No puede utilizar recursión sobre listas.

;Diseñe una función lista-en-cadena, que dada una lista de números l elimine de la misma los números que no están entre 0 y 100, y 
;construya con los restantes una cadena de la forma "[x1, .. , xn]", donde cada xi es un número de la lista.
;
;Por ejemplo:
;
;    (check-expect (lista-en-cadena (list 23 -4 100 0 45 120)) "[23,45]")
;
;Presente al menos dos ejemplos más en su diseño.

;dada una lista de números l elimine de la misma los números que no están entre 0 y 100, y 
;construya con los restantes una cadena de la forma "[x1, .. , xn]

(define (lista-en-cadenaAux? x)
  (string-append (number->string x)",")
)

(define (modifyStringLastFirst str)
  (string-append "["(substring str 0 (sub1 (string-length str)))"]")
)

(define (lista-en-cadena l)
  (modifyStringLastFirst (foldr string-append "" (map lista-en-cadenaAux? (filter (lambda (x) (and (> x 0) (< x 100))) l))))
)

(check-expect (lista-en-cadena (list 23 -4 100 0 45 120)) "[23,45]")
(check-expect (lista-en-cadena (list 100 100 1 100)) "[1]")
(check-expect (lista-en-cadena (list 1 2 3 4 5 6 7)) "[1,2,3,4,5,6,7]")