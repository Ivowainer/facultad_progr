;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname Rectas) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;;Ejercicio 4. En este programa pretendemos simular el trazado de líneas en el plano.
;
;;Las siguientes constantes definen el plano sobre el cual
;;se podrán trazar rectas,
;;de a una a la vez, es decir cuando se hace un click sobre un punto
;;se elimina del plano la recta actual (si hubiera una)
;;y se dibuja un punto donde se hizo click
;;para comenzar con el trazado de una nueva recta.
;
;
;(define ALTO 500)
;(define ANCHO 800)
;(define FONDO (empty-scene ANCHO ALTO))
;
;
;(define(interpretar s)
;       (place-image FONDO))
;
;
;
;(define-struct estado [p1 p2 e])
;; estado es (posn, posn , Natural)
;; donde p1 representa la posición del primer punto
;;       p2 la posición del segundo punto
;;        e es alguno de los valores: 0,1 o 2 que indica cuántos puntos
;;       hay marcados en la imagen
;;          0 : ningún punto
;;          1 : 1 punto
;;          2 : 2 puntos unidos por una recta 
;
;
;
;
;; punto: posn -> Image
;; dado un punto en el plano, dibuja una "x" en las coordenadas
;; del punto dado sobre la imagen FONDO. 
;
;(define (punto p)
;  (place-image (text "x" 20 "blue") (posn-x p) (posn-y p) FONDO))
;
;
;; linea : posn posn -> Image
;; dados dos puntos, traza una línea azul entre ambos puntos
;; sobre la imagen FONDO. 
;(define (linea p1 p2)
;  (add-line FONDO (posn-x p1) (posn-y p1) (posn-x p2) (posn-y p2) "blue"))














(require 2htdp/image)
(require 2htdp/universe)

(define ALTO 500)
(define ANCHO 800)
(define FONDO (empty-scene ANCHO ALTO))
;; estado es (posn, posn , Natural)
;; donde p1 representa la posición del primer punto
;;       p2 la posición del segundo punto
;;       e es alguno de los valores: 0,1 o 2 que indica cuántos puntos hay marcados en la imagen
;;          0 : ningún punto
;;          1 : 1 punto
;;          2 : 2 puntos unidos por una recta 
(define-struct estado [p1 p2 e])
(define INITIALSTATE (make-estado (make-posn 0 0) (make-posn 0 0) 0))

;; punto: posn -> Image
;; dado un punto en el plano, dibuja una "x" en las coordenadas
;; del punto dado sobre la imagen FONDO. 
;
(define (punto p)
  (place-image (text "x" 20 "blue") (posn-x p) (posn-y p) FONDO))

;; linea : posn posn -> Image
;; dados dos puntos, traza una línea azul entre ambos puntos
;; sobre la imagen FONDO. 
(define (linea p1 p2)
  (add-line FONDO (posn-x p1) (posn-y p1) (posn-x p2) (posn-y p2) "blue"))

(define (drawRecta state)
  (cond
    [(= (estado-e state) 1) (punto (estado-p1 state))]
    [(= (estado-e state) 2) (linea (estado-p1 state) (estado-p2 state))];; verificamos si un punto del estado es mayor a 0
    [else FONDO]));; verificamos si los dos puntos del estado son mayores a 0

(define (clickPoint state x y event)
  (if (string=? event "button-down")
      (cond
        [(= (estado-e state) 0) (make-estado (make-posn x y) (make-posn 0 0) 1)]
        [(= (estado-e state) 1) (make-estado (estado-p1 state) (make-posn x y) 2)]
        [(= (estado-e state) 2) INITIALSTATE])
      state)
)

(big-bang INITIALSTATE
  [to-draw drawRecta]
  [on-mouse clickPoint])

