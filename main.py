import numpy as np
import matplotlib.pyplot as plt


def check_multiply() -> None:
    sizes = [10, 100, 200, 300, 500, 1000]
    for size in sizes:
        matrix1 = np.loadtxt(f"data/matrix1.{size}.txt")
        matrix2 = np.loadtxt(f"data/matrix2.{size}.txt")
        result = np.dot(matrix1, matrix2)
        file_result = np.loadtxt(f"data/res.{size}.txt")
        print(f"Проверка для размера: {size}")
        if np.array_equal(result, file_result):
            print("Результаты совпадают")
        else:
            print("Результаты не совпадают")


def plot_graph():
    with open('data/res_time.txt', 'r') as file:
        sizes, times = zip(*[map(int, line.strip().split('-')) for line in file])
    plt.plot(sizes, times)
    plt.title('Время умножения')
    plt.xlabel('Размер матрицы')
    plt.show()


if __name__ == '__main__':
    check_multiply()
    plot_graph()