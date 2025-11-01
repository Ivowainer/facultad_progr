;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |9|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (todos-verdaderos l)
  (cond
    [(empty? l) #true]
    [(boolean=? #false (first l)) #false]
    [else (todos-verdaderos (rest l))]))

(define (uno-verdadero l)
  (cond
    [(empty? l) #false]
    [(boolean=? #true (first l)) #true]
    [else (uno-verdadero (rest l))]))