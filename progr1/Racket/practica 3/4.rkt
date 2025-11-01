;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |4|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define MAINSCENE (empty-scene 800 800))
(define INITIALSTATE (/ (image-height MAINSCENE) 2))
(define DELTA 20)

(define (borderObjectDown state)
  (cond
    [(and (< state (image-height MAINSCENE)) (> state 0)) (+ state DELTA)]
    [else state]))
(define (borderObjectUp state)
  (cond
    [(and (< state (image-height MAINSCENE)) (> state 0)) (- state DELTA)]
    [else state]))

(define (changePosition state key)
  (cond
    [(key=? key "down") (borderObjectDown state)]
    [(key=? key "up") (borderObjectUp state)]
    [(key=? key " ") INITIALSTATE]
    [else state]))

(define (drawCircle state)
  (place-image
   (circle 40 "solid" "red") (/ (image-width MAINSCENE) 2) state
   MAINSCENE))

(big-bang INITIALSTATE
  [to-draw drawCircle]
  [on-key changePosition])