def selection_sort(arr):
    n = len(arr)

    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j

        if min_idx != i:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]

    return arr


def main():
    try:
        user_input = input("Введите последовательность чисел через пробел: ").strip()

        if not user_input:
            print("Строка не существует")
            return

        numbers = [int(x) for x in user_input.split()]

        sorted_numbers = selection_sort(numbers)

        print("Отсортированная последовательность:")
        print(*sorted_numbers)

    except ValueError:
        print("Ошибка: Вводите только целые числа!")


if __name__ == "__main__":
    main()