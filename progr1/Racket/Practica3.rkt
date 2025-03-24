;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname Practica3) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define INITIALSTATE (circle 30 "solid" "red"))
(define MAINSCENE (empty-scene 400 400))

(define (changeColor state key)
  (cond
    [(key=? "n" key) (circle 30 "solid" "black")]
    [else INITIALSTATE]))

(define (circleDraw state)
  (place-image state 200 200 MAINSCENE))

(big-bang INITIALSTATE
  [to-draw circleDraw]
  [on-key changeColor])