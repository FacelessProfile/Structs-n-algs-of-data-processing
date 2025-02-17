import random
import matplotlib.pyplot as plt

# Функция для пузырьковой сортировки (BubbleSort)
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

# Функция для генерации случайного массива
def generate_random_array(n):
    return [random.randint(0, 1000) for _ in range(n)]

# Массивы для хранения значений Мф + Сф для разных n
n_values = list(range(10, 1001, 10))
bubble_sort_values = []

# Подсчитаем Мф + Сф для каждого n
for n in n_values:
    arr = generate_random_array(n)
    arr_copy = arr.copy()
    total_operations = bubble_sort(n, arr_copy)
    bubble_sort_values.append(total_operations)
    print(f"n = {n}, M_f + C_f = {total_operations}")  # Выводим значение для каждого n

# Построим график
plt.figure(figsize=(10, 6))
plt.plot(n_values, bubble_sort_values, label="BubbleSort", color='r')

plt.title('Зависимость M_f + C_f от размера массива n (для BubbleSort)')
plt.xlabel('Размер массива n')
plt.ylabel('M_f + C_f')
plt.legend()
plt.grid(True)
plt.show()
