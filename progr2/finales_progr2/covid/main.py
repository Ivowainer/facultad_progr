

def main():
    f = open('exit.txt', 'r')

    cant_personas_ofi = 0
    actual_ofi = 0

    dicc = {}
    i = 0
    
    for x in f:
        arr = x[:-1].split()

        """ Elimina las personas de baja prioridad """
        if arr[-1] == '0':
            arr[2] = "NADIE"
        
        """ Itera sobre todas las oficinas mientras guarda si está ocupada por al menos una persona. Cuando termina de recorrer las oficinas
        (que se da cuenta gracias al primer elif, porque la oficina cambió de numero), verifica si está ocupada, en caso de que no, agrega al diccionario el arr """
        if arr[1] == str(actual_ofi) and arr[2] != 'NADIE':  
            cant_personas_ofi +=1

        if arr[1] != str(actual_ofi):
            if cant_personas_ofi == 0:
                dicc[i] = "ACA"
                i+=1

            cant_personas_ofi = 0
            actual_ofi +=1
    
    print(dicc)



    f.close()

main()