;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |1|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;; 1
(define (sumanat n1 n2)
  (if (= n2 0)
      n1
      (sumanat (add1 n1) (sub1 n2)))
)

(check-expect (sumanat 4 9) 13)

;; 2
(define (multiplicar n1 n2)
  (if (= n2 1)
      n1
      (sumanat n1 (multiplicar n1 (sub1 n2))))
)

(check-expect (multiplicar 3 3) 9)
(check-expect (multiplicar 5 9) 45)

;; 3
(define (powernat n1 n2)
  (if (= n2 1)
      n1
      (multiplicar n1 (powernat n1 (sub1 n2))))
)

(check-expect (powernat 4 2) 16)
(check-expect (powernat 3 2) 9)

;; 4
(define (sigma n f)
  (if (zero? n)
      n
      (sumanat (f n) (sigma (sub1 n) f)))
)

(check-expect (sigma 4 sqr) 30)
(check-expect (sigma 10 identity) 55)

;; 6
(define (intervalo n)
  (cond
    [(zero? n) '()]
    [else (cons n (intervalo (sub1 n)))])
)

(check-expect (intervalo 9) (list 9 8 7 6 5 4 3 2 1))
(check-expect (intervalo 5) (list 5 4 3 2 1))

;; 7
(define (factnat n)
  (if (= n 1)
      n
      (multiplicar n (factnat (sub1 n))))
)

(check-expect (factnat 4) 24)
(check-expect (factnat 5) 120)

;; 8
(define (fibnat n)
  (if (< n 2)
       n
       (sumanat (fibnat (sub1 n)) (fibnat (sub1 (sub1 n)))))
)

(check-expect (fibnat 8) 21)

;; 9
(define (list-fibonacci n)
  (cond
    [(zero? n) (list 1)]
    [else (cons (fibnat (add1 n)) (list-fibonacci (sub1 n)))])
)

(check-expect (list-fibonacci 4) (list 5 3 2 1 1))
(check-expect (list-fibonacci 0) (list 1))

;; 11
(define (componer f n x)
  (if (zero? n)
      x
      (componer f (sub1 n) (f x)))
)

(check-expect (componer sqr 2 5) 625)
(check-expect (componer add1 5 13) 18)

;; 12
(define (multiplos n m)
  (cond
    [(< n 1) '()]
    [(= n 1) (list m)]
    [else (cons (multiplicar n m) (multiplos (sub1 n) m))])
)

(check-expect (multiplos 4 7) (list 28 21 14 7))
(check-expect (multiplos 0 11) '())

;; 13
(define (g n f)
  (cond
    [(f n) #t]
    [(zero? n) #f]
    [else (g (sub1 n) f)])
)

(check-expect (g 3 negative?) #false)
(check-expect (g 7 even?) #true)

;; 14
(define (circulos m)
  (if (zero? m)
        (circle 1 "outline" "red")
      (place-image
       (circle (powernat m 2) "outline" "blue") (/ (multiplicar 2 (powernat m 2)) 2) (/ (multiplicar 2 (powernat m 2)) 2)
       (place-image
        (circulos (sub1 m)) (/ (multiplicar 2 (powernat m 2)) 2) (/ (multiplicar 2 (powernat m 2)) 2)
        (empty-scene (multiplicar 2 (powernat m 2)) (multiplicar 2 (powernat m 2)))))
   )
)

;; 15
(define (cuadrados m ang)
  (if (zero? m)
      (rotate ang (square 1 "outline" "blue"))
      (place-image
       (rotate ang (square (powernat m 2) "outline" "blue")) 100 100
       (place-image
        (cuadrados (sub1 m) (sumanat 20 ang)) 100 100
        (empty-scene 200 200)))
   )
)

(cuadrados 10 70)