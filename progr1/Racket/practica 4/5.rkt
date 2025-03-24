;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |5|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define MAINSCENE (empty-scene 800 400))
(define INITIALSTATE (make-posn 400 200))

(define (moveCircle state key)
  (cond
    [(key=? "up" key) (make-posn (posn-x state) (- (posn-y state) 20))]
    [(key=? "down" key) (make-posn (posn-x state) (+ 20 (posn-y state)))]
    [else state]))

(define (drawCircle state)
  (place-image
   (circle 30 "solid" "red") (posn-x state) (posn-y state)
   MAINSCENE))


(big-bang INITIALSTATE
  [to-draw drawCircle]
  [on-key moveCircle])