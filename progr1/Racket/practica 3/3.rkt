;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |3|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define INITIALSTATE 11)
(define MAINSCENE (empty-scene 800 800))
(define DECREMENTINCREMENTSIZE 1)

(define (changeColor state)
  (cond
    [(and (> state 0) (< state 50)) (circle state "solid" "yellow")]
    [(and (> state 51) (< state 100)) (circle state "solid" "red")]
    [else (circle state "solid" "green")]))

(define (changeSizeIncr state)
  (cond
    [(> state (image-width MAINSCENE)) INITIALSTATE]
    [else (+ state DECREMENTINCREMENTSIZE)]))

(define (changeSizeDecr state)
  (cond
    [(< state 1) 100]
    [else (- state DECREMENTINCREMENTSIZE)]))

(define (keyChange state key)
  (cond
    [(key=? "d" key) (* state 10)]
    [else state]))

(define (stopSize state)
  (cond
    [(> state 110) #true]
    [(< state 10) #true]
    [else #false]))

(define (drawCircle state)
  (place-image (changeColor state)
               400 400
               MAINSCENE))

(big-bang INITIALSTATE
  [to-draw drawCircle]
  [on-tick changeSizeIncr]
  [stop-when stopSize]
  [on-key keyChange])
