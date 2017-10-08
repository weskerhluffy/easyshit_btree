# XXX: https://www.hackerearth.com/practice/algorithms/sorting/merge-sort/practice-problems/algorithm/i-think-its-easy/
import sys
if __name__ == "__main__":
    primero=True
    for linea in sys.stdin:
        if primero:
            primero=False
            continue
        palabras = linea.strip().split()
        palabras.sort(key=lambda x:len(x))
        print(" ".join(palabras))
