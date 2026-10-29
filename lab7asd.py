def shell_sort(arr: list[int]) -> list[int]:
    n = len(arr)
    gap = n // 2

    while gap > 0:
        for i in range(gap, n):
            current_value = arr[i]
            j = i
            while j >= gap and arr[j - gap] > current_value:
                arr[j] = arr[j - gap]
                j -= gap

            arr[j] = current_value

        gap //= 2

    return arr


if __name__ == "__main__":
    raw_input = input("Введите последовательность чисел через пробел: ")
    numbers = [int(x) for x in raw_input.split()]

    print(f"Исходный массив:       {numbers}")
    shell_sort(numbers)
    print(f"Отсортированный массив: {numbers}")