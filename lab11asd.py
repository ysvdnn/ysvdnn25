def quick_sort(arr):
    if len(arr) <= 1:
        return arr

    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]

    return quick_sort(left) + middle + quick_sort(right)


def main():
    try:
        user_input = input("Введите последовательность чисел через пробел: ").strip()

        if not user_input:
            print("Строка не существует")
            return

        numbers = [int(x) for x in user_input.split()]

        sorted_numbers = quick_sort(numbers)

        print("Отсортированная последовательность:")
        print(*sorted_numbers)

    except ValueError:
        print("Ошибка: Вводите только целые числа!")


if __name__ == "__main__":
    main()
