import random
import matplotlib.pyplot as plt

def bubble_sort(n, A):
    comparisons = 0
    moves = 0
    for i in range(n-1):
        for j in range(n-1, i, -1):
            comparisons += 1
            if A[j] < A[j-1]:
                moves += 3  # Swap involves 3 moves (2 assignments + 1 comparison)
                A[j], A[j-1] = A[j-1], A[j]
    # Возвращаем сумму сравнений и перемещений
    return comparisons + moves

sizes = []
results = []

for n in range(10, 1010, 10):
    arr = [random.randint(0, n) for _ in range(n)]
    result = bubble_sort(n,arr)
    sizes.append(n)
    results.append(result)

plt.figure(figsize=(10, 6))
plt.plot(sizes, results, label="M_f + C_f (BubbleSort)", color="b")

plt.title("Зависимость M_ф + C_ф от n для метода BubbleSort")
plt.xlabel("Размер массива n")
plt.ylabel("M_f + C_f")
plt.grid(True)
plt.legend()

plt.show()
