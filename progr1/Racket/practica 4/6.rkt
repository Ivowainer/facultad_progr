;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |6|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define MAINSCENE (empty-scene 800 400))
(define MOSCA (star 30 "solid" "red"))
(define INITIALSTATE (make-posn 400 200))
(define GAMMA 10)
(define DELTA 10)

(define (moveMosca state)
  (if (not (or (or (> (posn-x state) (image-width MAINSCENE)) (< (posn-x state) 0)) (or (> (posn-y state) (image-height MAINSCENE)) (< (posn-y state) 0))))
      (cond
        [(= (random 4) 0) (make-posn (+ (posn-x state) DELTA) (+ (posn-y state) DELTA))]
        [(= (random 4) 1) (make-posn (+ (posn-x state) DELTA) (- (posn-y state) DELTA))]
        [(= (random 4) 2) (make-posn (- (posn-x state) DELTA) (- (posn-y state) DELTA))]
        [(= (random 4) 3) (make-posn (- (posn-x state) DELTA) (+ (posn-y state) DELTA))]
        [else state])
      state)
)

(define (clickMoscaAux? state x y event)
  (if (and (or (< x (+ (posn-x state) GAMMA)) (< x (+ (posn-y state) GAMMA))) (or (< y (+ (posn-x state) GAMMA)) (< y (+ (posn-y state) GAMMA))))
      (make-posn -1 -1)
      state))

(define (clickMosca state x y event)
  (cond
    [(string=? event "button-down") (clickMoscaAux? state x y event)]
    [else state]))

(define (drawMosca state)
  (if (and (= (posn-x state) -1) (= (posn-y state) -1))
      (text "Atrapaste a la mosca" 24 "olive")
      (place-image
       MOSCA (posn-x state) (posn-y state)
       MAINSCENE)))

(big-bang INITIALSTATE
  [to-draw drawMosca]
  [on-tick moveMosca]
  [on-mouse clickMosca])