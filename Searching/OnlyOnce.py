
def OnlyOnce(A, min, max):
    i = (min + max) / 2
    if A[i] != A[i + 1] and A[i] != A[i - 1]:
        return A[i]
    elif A[i] == A[i + 1]:
        if i % 2 == 0:
            return OnlyOnce(A, i + 1, max)
        else:
            return OnlyOnce(A, min, i - 1)
    else:
        if i % 2 == 0:
            return OnlyOnce(A, min, i - 1)
        else:
            return OnlyOnce(A, i + 1, max)

filename = input("Enter a filename: ")
if len(filename) == 0:
    filename = "practice.txt"

a = open(filename, 'r').read()
a = a.strip()
a = a[1:-1].split(',')

print(OnlyOnce(a, 0, len(a) - 1))
