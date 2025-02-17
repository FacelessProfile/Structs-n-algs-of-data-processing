import random
import matplotlib.pyplot as plt

def select_sort(arr):
    comparisons = 0
    swaps = 0
    n = len(arr)
    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            comparisons += 1
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
        swaps += 3
    return comparisons + swaps

sizes = []
results = []

for n in range(10, 1010, 10):
    arr = [random.randint(0, n) for _ in range(n)]
    result = select_sort(arr)
    sizes.append(n)
    results.append(result)

plt.figure(figsize=(10, 6))
plt.plot(sizes, results, label="M_f + C_f (SelectSort)", color="b")

plt.title("Зависимость M_ф + C_ф от n для метода SelectSort")
plt.xlabel("Размер массива n")
plt.ylabel("M_f + C_f")
plt.grid(True)
plt.legend()

plt.show()
