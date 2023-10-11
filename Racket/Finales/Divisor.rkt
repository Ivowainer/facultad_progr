;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname Divisor) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;Ejercicio 1. Diseñe una función divisores,
;que dado un número natural n calcule una lista
;con los divisores de n.
;Definir la función sin utilizar ninguna función sobre listas,
;salvo los constructores de listas y
;sin hacer recursión sobre listas.

(define (divisor? n div)
  (cond
    [(= div 1) (list div)]
    [(zero? (remainder n div)) (cons div (divisor? n (sub1 div)))]
    [else (divisor? n (sub1 div))])
)

(define (divisores n)
  (divisor? n n)
)

(divisores 12)