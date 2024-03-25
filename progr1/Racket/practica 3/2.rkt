;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |2|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define INITIALSTATE 100)

(define (drawCircle state)
  (place-image (circle state "solid" "red")
               400 400
               (empty-scene 800 800)))

(define (changeSize state)
  (cond
    [(< state 1) 100]
    [else (- state 20)]))

(big-bang INITIALSTATE
  [to-draw drawCircle]
  [on-tick changeSize])
