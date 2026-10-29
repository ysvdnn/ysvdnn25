def check_brackets(s: str) -> bool:
    brackets_map = {')': '(', '}': '{', ']': '['}
    opening_brackets = set(brackets_map.values())
    stack = []

    for char in s:
        if char in opening_brackets:
            stack.append(char)
        elif char in brackets_map:
            if not stack or stack[-1] != brackets_map[char]:
                return False
            stack.pop()

    return len(stack) == 0


def main():
    user_input = input("Введите строку: ").strip()

    if not user_input:
        print("Строка не существует")
        return

    if check_brackets(user_input):
        print("Строка существует")
    else:
        print("Строка не существует")


if __name__ == "__main__":
    main()