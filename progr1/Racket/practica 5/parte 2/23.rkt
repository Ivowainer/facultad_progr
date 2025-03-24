;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |23|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (calcularArea? e)
  (if (> (image-width e) (image-height e))
   (* (image-width e) (image-height e))
   0)
)

(define (saa l)
  (foldr + 0 (map calcularArea? l))
)

(saa (list (circle 20 "solid" "red")
              (rectangle 40 20 "solid" "blue")
              (rectangle 10 20 "solid" "yellow")
              (rectangle 30 20 "solid" "green")))