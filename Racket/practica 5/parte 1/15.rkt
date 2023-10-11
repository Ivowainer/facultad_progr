;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |15|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define MAX 5)

(define (calcularDistancia? punto)
  (sqrt (+ (sqr (- (posn-x punto) 0)) (sqr (- (posn-y punto) 0))))
)

(define (cerca l)
  (cond
    [(empty? l) '()]
    [(< (calcularDistancia? (first l)) MAX) (cons (first l) (cerca (rest l)))]
    [else (cerca (rest l))])
)

(cerca (list (make-posn 3 5) (make-posn 1 2) (make-posn 0 1) (make-posn 5 6)))
