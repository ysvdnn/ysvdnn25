def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    result = []
    i = 0
    j = 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    result.extend(left[i:])
    result.extend(right[j:])

    return result


def main():
    try:
        user_input = input("Введите последовательность чисел через пробел: ").strip()

        if not user_input:
            print("Строка не существует")
            return

        numbers = [int(x) for x in user_input.split()]

        sorted_numbers = merge_sort(numbers)

        print("Отсортированная последовательность:")
        print(*sorted_numbers)

    except ValueError:
        print("Ошибка: Вводите только целые числа!")


if __name__ == "__main__":
    main()
