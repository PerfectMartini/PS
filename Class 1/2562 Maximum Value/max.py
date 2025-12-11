natural_numbers = [int(input()) for _ in range(9)]
maximum_value = max(natural_numbers)
maximum_value_index = natural_numbers.index(maximum_value) + 1
print(maximum_value)
print(maximum_value_index)
