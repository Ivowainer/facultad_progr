def leer_archivo():
    f = open('exit.txt')

    s = f.readlines()
    return s

def main():
    coords = leer_archivo()
    rows_length = len(coords)
    cols_length = len(coords[0][:-1])

    row = 0
    col = 0
    valor_actual = 0

    while row < rows_length and col < cols_length - 1 and coords[row][col] != '2':
        col+=1

        while row < rows_length and coords[row][col] != '1' and coords[row][col] != '2':
            row += 1

        if row >= rows_length or coords[row][col] == '1':
            row = 0

    if row == 0 and col == cols_length - 1:
        print("No se ha encontrado el objetivo")
        return
    
    print("Se ha encontrado en la posición", row, ",", col)
        
        

    
        

main()