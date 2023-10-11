;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |8|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/universe)
(require 2htdp/image)

(define MAINSCENE (empty-scene 800 60))
(define-struct Text [s color tam])
(define INITIALSTATE (make-Text "saf" "red" 20))

(define (putLetter state key)
  (cond
    [(key=? "f1" key) (make-Text (Text-s state) "indigo" (Text-tam state))]
    [(key=? "f2" key) (make-Text (Text-s state) "red" (Text-tam state))]
    [(key=? "f3" key) (make-Text (Text-s state) "blue" (Text-tam state))]
    [(key=? "f4" key) (make-Text (Text-s state) "orange" (Text-tam state))]

    [(key=? "up" key) (make-Text (Text-s state) (Text-color state) (+ (Text-tam state) 5))]
    [(key=? "down" key) (make-Text (Text-s state) (Text-color state) (- (Text-tam state) 5))]
    
    [(key=? "a" key) (make-Text (string-append (Text-s state) "a") (Text-color state) (Text-tam state))]
    [(key=? "d" key) (make-Text (string-append (Text-s state) "d") (Text-color state) (Text-tam state))]
    [(key=? "\b" key) (make-Text (substring (Text-s state) 0 (- (string-length (Text-s state)) 1)) (Text-color state) (Text-tam state))]
    [(key=? " " key) (make-Text (string-append (Text-s state) " ") (Text-color state) (Text-tam state))]
    [else state])
)

(define (drawBloc state)
  (place-image/align (text (Text-s state) (Text-tam state) (Text-color state))
                   0 0 "left" "top" MAINSCENE))

(big-bang INITIALSTATE
  [to-draw drawBloc]
  [on-key putLetter])