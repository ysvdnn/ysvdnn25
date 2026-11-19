def extract_runs(arr):
    if not arr:
        return []

    runs = []
    current_run = [arr[0]]

    for i in range(1, len(arr)):
        if arr[i] >= arr[i - 1]:
            current_run.append(arr[i])
        else:
            runs.append(current_run)
            current_run = [arr[i]]

    runs.append(current_run)
    return runs


def merge_two_runs(run1, run2):
    if run1 is None:
        return list(run2) if run2 is not None else []
    if run2 is None:
        return list(run1)

    result = []
    i = 0
    j = 0

    while i < len(run1) and j < len(run2):
        if run1[i] <= run2[j]:
            result.append(run1[i])
            i += 1
        else:
            result.append(run2[j])
            j += 1

    result.extend(run1[i:])
    result.extend(run2[j:])
    return result


def polyphase_sort(arr):
    if len(arr) <= 1:
        return arr

    runs = extract_runs(arr)
    if len(runs) == 1:
        return runs[0]

    # Вычисляем числа Фибоначчи для распределения серий по 2 лентам
    f1, f2 = 1, 1
    while f1 + f2 < len(runs):
        f1, f2 = f2, f1 + f2

    # Дополняем список серий пустыми ("фиктивными") сериями до числа Фибоначчи
    total_needed = f1 + f2
    dummy_count = total_needed - len(runs)
    all_runs = [None] * dummy_count + runs

    # Распределяем серии на две входные ленты (f2 и f1 штук), третья лента пустая
    tapes = [all_runs[:f2], all_runs[f2:], []]

    # Многофазное слияние: сливаем пока одна из входных лент не опустеет
    while sum(1 for t in tapes if len(t) > 0) > 1:
        empty_idx = next(i for i, t in enumerate(tapes) if len(t) == 0)
        in1, in2 = [i for i in range(3) if i != empty_idx]

        while tapes[in1] and tapes[in2]:
            r1 = tapes[in1].pop(0)
            r2 = tapes[in2].pop(0)

            if r1 is None and r2 is None:
                tapes[empty_idx].append(None)
            else:
                tapes[empty_idx].append(merge_two_runs(r1, r2))

    # Находим ленту, на которой осталась итоговая слитая серия
    for t in tapes:
        for run in t:
            if run is not None:
                return run

    return []


def main():
    try:
        user_input = input("Введите последовательность чисел через пробел: ").strip()

        if not user_input:
            print("Строка не существует")
            return

        numbers = [int(x) for x in user_input.split()]

        sorted_numbers = polyphase_sort(numbers)

        print("Отсортированная последовательность:")
        print(*sorted_numbers)

    except ValueError:
        print("Ошибка: Вводите только целые числа!")


if __name__ == "__main__":
    main()