;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |4|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/universe)

(define (distancia punto1 punto2)
  (sqrt (+ (sqr (- (posn-x punto2) (posn-x punto1))) (sqr (- (posn-y punto2) (posn-y punto1)))))
)

(distancia (make-posn 4 2) (make-posn 8 4))

