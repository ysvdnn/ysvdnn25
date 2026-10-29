def radix_sort(arr: list[int]) -> list[int]:
    if not arr:
        return arr

    max_val = max(arr)
    exp = 1

    while max_val // exp > 0:
        buckets = [[] for _ in range(10)]

        for num in arr:
            digit = (num // exp) % 10
            buckets[digit].append(num)

        arr.clear()
        for bucket in buckets:
            arr.extend(bucket)

        exp *= 10

    return arr


if __name__ == "__main__":
    raw_input = input("Введите последовательность целых чисел через пробел: ")
    numbers = [int(x) for x in raw_input.split()]

    print(f"Исходный массив:       {numbers}")
    radix_sort(numbers)
    print(f"Отсортированный массив: {numbers}")