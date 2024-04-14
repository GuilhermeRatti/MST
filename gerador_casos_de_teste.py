import random
import string

def randomword(length):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for _ in range(length))

# Example usage:
numero_pontos = 50000
numero_dimensoes = 10
tamanho_id = 23 #23 chars
nome_arquivo_saida = "testes_50k.txt"
 
pontos_registrados = dict()

for i in range(numero_pontos):
    id_ponto = randomword(tamanho_id)
    if id_ponto in pontos_registrados.keys():
        i-=1
    else:
        pontos_registrados.update({id_ponto : [random.uniform(-100.0,100.0) for k in range(numero_dimensoes)]})


with open(f"dados_teste/{nome_arquivo_saida}","w") as f:
    for key in pontos_registrados:
        f.write(f"{key}")
        for val in pontos_registrados[key]:
            f.write(f",{val}")
        f.write("\n")