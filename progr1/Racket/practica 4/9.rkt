;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |9|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define-struct Auto [año tip km/l])

(define (sacarPorcentaje km/l porcentaje)
  (/ (* porcentaje km/l ) 100))

(define (costo-viajeKmAux? year km/l)
  (cond
    [(and (> year 1) (< year 5)) (- km/l (sacarPorcentaje km/l 2))]
    [(and (> year 6) (< year 10)) (- km/l (sacarPorcentaje km/l 6))]
    [(and (> year 10) (< year 15)) (- km/l (sacarPorcentaje km/l 10))]
    [(> year 15) (- km/l (sacarPorcentaje km/l 15))]
    [else km/l])
)

(define (costo-viajeKmRecorriAux? km)
  (* 50 (round (/ km 100))))

(define (costo-viaje car km)
  (cond
    [(string=? "nafta" (Auto-tip car)) (+ (* (/ km (costo-viajeKmAux? (Auto-año car) (Auto-km/l car))) 19) (costo-viajeKmRecorriAux? km))]
    [(string=? "diesel" (Auto-tip car)) (+ (* (/ km (costo-viajeKmAux? (Auto-año car) (Auto-km/l car))) 17) (costo-viajeKmRecorriAux? km))]))

(round (costo-viaje (make-Auto 4 "nafta" 13) 450))