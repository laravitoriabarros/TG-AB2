# Projeto de Teoria dos Grafos

![Badge em Desenvolvimento](https://img.shields.io/badge/STATUS-CONCLUÍDO-blue)


Projeto final da AB2 requerido para obtenção de nota na disciplina de Teoria dos Grafos, no curso de Ciência da Computação promovido pela Universidade Federal de Alagoas (UFAL).

Aluna: Lara Vitória Silva Santos Barros

---

## 💻 Algoritmos Implementados

- **Prim**   
- **Kruskal**  
- **Dijkstra**   
- **Floyd-Warshall**  
- **Kosaraju**

---

## ✅ Tecnologias Utilizadas

- [Compilador C++](https://sourceforge.net/projects/mingw/)
- [Make](https://samuel-nonoka.medium.com/instalando-makefile-no-windows-1d0021d2e0ce)
- [Bash (Git Bash no Windows ou terminal Linux)](https://git-scm.com/downloads)
- [VS CODE](https://code.visualstudio.com/)


---

## 💻 Como clonar
Para clonar este repositório na sua máquina, é só usar o comando no seu terminal:

```
git clone https://github.com/laravitoriabarros/TG-AB2.git
```

---

## 💻 Como testar

### Testes Automatizados:

Para verificar se os 4 algoritmos obrigatórios estão funcionando, primeiro navegue até a pasta Bat1:

```
cd testes/Bat1
```

Depois, execute o comando:

```
bash Bat1.sh
```
Para testar o quinto algoritmo é só seguir o mesmo passo a passo, a diferença é só que você estará indo para a pasta Bat2:

```
cd testes/Bat2
bash Bat2.sh
```

### Testes Manuais:

Para verificar se a saída de determinado algoritmo está igual ao gabarito, podemos usar os seguintes comandos tomando o algoritmo Dijkstra como exemplo:

```
cd testes/Bat2
./dijkstra.bin -f instances/exemp.mtx -i 1 > minha_saida.txt
diff -w minha_saida.txt sp/exemp.mtx
```

Se não retornar nada, significa que está correto. Caso tenha erro, irá aparecer no terminal as diferenças de resposta.

## 🛠️ Como Compilar

Navegue até a pasta de cada algoritmo e execute os comandos abaixo, usando o algoritmo prim como exemplo:

```
cd prim
make
```

Ou diretamente:

```
g++ -std=c++11 -o prim.bin prim.cpp
```
