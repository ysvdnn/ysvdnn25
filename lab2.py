def check_brackets(expr):
    stack = []
    for char in expr:
        if char == '(':
            stack.append(char)
        elif char == ')':
            if not stack:
                return False
            stack.pop()
    return len(stack) == 0


def tokenize(expr):
    tokens = []
    i = 0
    n = len(expr)

    while i < n:
        ch = expr[i]

        if ch.isspace():
            i += 1
            continue

        # Число (целое или дробное через точку)
        if ch.isdigit() or ch == '.':
            num_str = ""
            dot_count = 0
            while i < n and (expr[i].isdigit() or expr[i] == '.'):
                if expr[i] == '.':
                    dot_count += 1
                    if dot_count > 1:
                        raise ValueError("Некорректное число (слишком много точек)")
                num_str += expr[i]
                i += 1
            if num_str == '.':
                raise ValueError("Некорректное число")
            tokens.append(float(num_str))
            continue

        # Операции и скобки
        if ch in '+-*/()':
            # Обработка унарного минуса (например, в начале выражения или после '(')
            if ch == '-' and (not tokens or tokens[-1] in ('(', '+', '-', '*', '/')):
                tokens.append(0.0)
            tokens.append(ch)
            i += 1
            continue

        raise ValueError(f"Недопустимый символ: '{ch}'")

    return tokens


def to_rpn(tokens):
    """Перевод выражения в обратную польскую запись (ОПЗ)."""
    priority = {'+': 1, '-': 1, '*': 2, '/': 2}
    output = []
    stack = []

    for token in tokens:
        if isinstance(token, float):
            output.append(token)
        elif token == '(':
            stack.append(token)
        elif token == ')':
            while stack and stack[-1] != '(':
                output.append(stack.pop())
            if not stack:
                raise ValueError("Ошибка в скобках")
            stack.pop()  # Убираем '('
        else:
            # Выталкиваем операции с большим или равным приоритетом
            while stack and stack[-1] in priority and priority[stack[-1]] >= priority[token]:
                output.append(stack.pop())
            stack.append(token)

    while stack:
        top = stack.pop()
        if top == '(':
            raise ValueError("Ошибка в скобках")
        output.append(top)

    return output


def eval_rpn(rpn):
    """Вычисление выражения в обратной польской записи через стек."""
    stack = []

    for token in rpn:
        if isinstance(token, float):
            stack.append(token)
        else:
            if len(stack) < 2:
                raise ValueError("Некорректное выражение (не хватает чисел для операции)")
            b = stack.pop()
            a = stack.pop()

            if token == '+':
                stack.append(a + b)
            elif token == '-':
                stack.append(a - b)
            elif token == '*':
                stack.append(a * b)
            elif token == '/':
                if b == 0:
                    raise ZeroDivisionError("Деление на ноль!")
                stack.append(a / b)

    if len(stack) != 1:
        raise ValueError("Некорректное выражение")

    return stack[0]


def calculate(user_input):
    expr = user_input.strip()

    if not expr:
        raise ValueError("Пустая строка")

    if not expr.endswith('='):
        raise ValueError("Выражение должно заканчиваться знаком '='")

    expr = expr[:-1].strip()  # Убираем '=' в конце

    if not expr:
        raise ValueError("Выражение перед '=' пустое")

    if not check_brackets(expr):
        raise ValueError("Скобки расставлены неверно")

    tokens = tokenize(expr)
    rpn = to_rpn(tokens)
    return eval_rpn(rpn)


def main():
    try:
        user_input = input("Введите выражение (в конце '='): ")
        result = calculate(user_input)

        # Если ответ целый (например, 5.0), выводим красиво как 5
        if result == int(result):
            print("Результат:", int(result))
        else:
            print("Результат:", result)

    except ZeroDivisionError as e:
        print("Ошибка:", e)
    except ValueError as e:
        print("Ошибка:", e)


if __name__ == "__main__":
    main()