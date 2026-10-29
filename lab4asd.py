def comb_sort(arr: list[int]) -> list[int]:
    n = len(arr)
    gap = n
    shrink_factor = 1.247
    swapped = True

    while gap > 1 or swapped:
        gap = int(gap / shrink_factor)
        if gap < 1:
            gap = 1

        swapped = False

        for i in range(0, n - gap):
            if arr[i] > arr[i + gap]:
                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                swapped = True

    return arr


def main():
    try:
        user_input = input("Введите последовательность чисел через пробел: ").strip()

        if not user_input:
            print("Строка не существует")
            return

        numbers = [int(x) for x in user_input.split()]

        sorted_numbers = comb_sort(numbers)

        print("Отсортированная последовательность:")
        print(*sorted_numbers)

    except ValueError:
        print("Ошибка: Вводите только целые числа!")


if __name__ == "__main__":
    main()