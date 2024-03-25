;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |27|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define-struct alumno [nombre nota faltas])

(define (destacados l)
  (map alumno-nombre (filter (lambda (alumnox) (>= (alumno-nota alumnox) 9)) l))
)

;(destacados (list (make-alumno "Ada Lovelace" 10 20) (make-alumno "Carlos Software" 3.5 12)))

(define (condicion alumno)
  (cond
    [(>= (alumno-nota alumno) 8) 2]
    [(< (alumno-nota alumno) 6) 0]
    [else 1]))

;(condicion (make-alumno "Ada Lovelace" 10 20))

(define (exito l)
  (empty? (filter zero? (map condicion l)))
)

;(exito (list (make-alumno "Juan Computación" 5 13) (make-alumno "Carlos Software" 3.5 12) (make-alumno "Ada Lovelace" 10 20)))

