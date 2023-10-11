;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |28|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (calcularDist? punto)
  (sqrt (+ (sqr (posn-x punto)) (sqr (posn-y punto)))))

(define (sumdist l)
  (if (empty? l)
      0
      (+ (calcularDist? (first l)) (sumdist (rest l))))
)

(sumdist (list (make-posn 3 4) (make-posn 0 4) (make-posn 12 5)))