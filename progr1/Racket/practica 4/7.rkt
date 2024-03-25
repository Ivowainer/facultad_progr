;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |7|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define MAINSCENE (empty-scene 1400 400))
(define-struct Auto [pos vel])
(define INITIALSTATE (make-Auto 0 1))
(define DELTA-VEL 3)

(define (changeVelocity state key)
  (cond
    [(key=? "up" key) (make-Auto (Auto-pos state) (+ (Auto-vel state) DELTA-VEL))]
    [(key=? "down" key) (make-Auto (Auto-pos state) (- (Auto-vel state) DELTA-VEL))]
    [else state]))

(define (moveCar state)
  (make-Auto (+ (Auto-pos state) (Auto-vel state)) (Auto-vel state)))

(define (drawCar state)
  (place-image
   (circle 20 "solid" "red") (Auto-pos state) (/ (image-height MAINSCENE) 2)
   MAINSCENE))

(big-bang INITIALSTATE
  [to-draw drawCar]
  [on-tick moveCar]
  [on-key changeVelocity])