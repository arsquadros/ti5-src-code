import general


def __rec_fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    elif n > 1:
        return __rec_fib(n - 1) + __rec_fib(n - 2)
    else:
        return -1


def fib(n):
    return __rec_fib(n - 1)
