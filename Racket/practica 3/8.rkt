;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |8|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define FONDO (empty-scene 800 500))
(define STAR (star 20 "solid" "red"))

(define (drawStarOnClickAux? x y state)
  (if (or (or (> x (image-width state)) (< x 0)) (or (> y (image-height state)) (< y 0)))
      state
      (place-image STAR x y state))
)
(define (drawStarOnClick state x y event)
  (cond
    [(string=? "button-down" event) (drawStarOnClickAux? x y state)]
    [else state]))

(define (drawBackground state)
  state)

(define (drawStarKey state key)
  (cond
    [(key=? key "\b") FONDO]
    [else state]))

(big-bang FONDO
  [to-draw drawBackground]
  [on-mouse drawStarOnClick]
  [on-key drawStarKey])