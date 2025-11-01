;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |1|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define MAX 5)

;; 12
(define (pares l)
  (filter even? l))

;(pares (list 4 6 3 7 5 0))

;; 13
(define (cortasAux? word)
  (if (< (string-length word) 5)
      #true
      #false)
)

(define (cortas l)
  (filter cortasAux? l))

;(cortas (list "Lista" "de" "palabras" "sin" "sentido"))

;; 14
(define (mayores l n)
  (filter  (lambda (x) (> x n)) l)
)

; (mayores (list 1 2 3 4 5 6) 4)

;; 15
(define (distanciaPuntoOrigen? punto)
  (sqrt (+ (sqr (posn-x punto)) (sqr (posn-y punto)))))

(define (cercaAux? e)
  (if (< (distanciaPuntoOrigen? e) MAX)
      #true
      #false)
)

(define (cerca l)
  (filter cercaAux? l)
)

;(cerca (list (make-posn 3 5) (make-posn 1 2) (make-posn 0 1) (make-posn 5 6)))

;; 16
(define (positivos l)
  (filter positive? l)
)

;(positivos (list -5 37 -23 0 12))

;; 17
(define (eliminar l n)
  (filter (lambda (x) (not (= x n))) l)
)

;(eliminar (list 1 2 3 2 7 6) 2)

