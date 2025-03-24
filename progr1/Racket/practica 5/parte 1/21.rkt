;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |21|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (signos l)
  (cond
    [(empty? l) '()]
    [(positive? (first l)) (cons 1 (signos (rest l)))]
    [(negative? (first l)) (cons -1 (signos (rest l)))]
    [(= (first l) 0) (cons 0 (signos (rest l)))]
    [else (signos (rest l))]))

(signos (list 45 32 -23 0 12))