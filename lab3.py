def find_numbers(x):
    result = []

    p3 = 1  # 3^0
    while p3 <= x:
        p5 = p3  # 3^K * 5^0
        while p5 <= x:
            p7 = p5  # 3^K * 5^L * 7^0
            while p7 <= x:
                result.append(p7)
                p7 *= 7
            p5 *= 5
        p3 *= 3

    result.sort()
    return result


def main():
    try:
        user_input = input("Введите число x: ").strip()

        if not user_input:
            print("Строка не существует")
            return

        x = int(user_input)

        if x < 1:
            print("Чисел в диапазоне от 1 до x нет")
            return

        numbers = find_numbers(x)

        print("Подходящие числа:")
        print(*numbers)

    except ValueError:
        print("Ошибка: Введите целое число!")


if __name__ == "__main__":
    main()