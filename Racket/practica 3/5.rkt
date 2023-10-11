;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |5|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define INITIALSTATE " ")

(define (drawBloc state)
  (place-image/align (text state 20 "indigo")
                   0 0 "left" "top" (empty-scene 800 60)))

(define (putLetter state key)
  (cond
    [(key=? "a" key) (string-append state "a")]
    [(key=? "d" key) (string-append state "d")]
    [(key=? " " key) (string-append state " ")]
    [(key=? "\b" key) (substring state 0 (- (string-length state) 1))]
    [else state]))

(big-bang INITIALSTATE
  [to-draw drawBloc]
  [on-key putLetter])