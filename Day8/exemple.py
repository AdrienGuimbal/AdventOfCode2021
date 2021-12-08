with open('input.txt') as inp:
    digits = [set() for x in range(10)]
    total = 0
    
    for line in inp:
        encoded, result = line.strip().split('|')
        encoded = encoded.split()
        result = result.split()

        # All digits will be stored as sets
        for digit in encoded:
            if len(digit) == 2:
                digits[1] = set(digit)
            elif len(digit) == 3:
                digits[7] = set(digit)
            elif len(digit) == 4:
                digits[4] = set(digit)
            elif len(digit) == 7:
                digits[8] = set(digit)

        # Group digits with other digits of the same length
        # e.g (0, 6, 9) and (2, 3, 5)
        digit_lengths = {}
        for digit in encoded:
          digit_lengths[len(digit)] = digit_lengths.get(len(digit), []) + [set(digit)]
        
        # Find 9
        for digit in digit_lengths[6]:
          if digit | digits[4] != digits[8]:
            digits[9] = digit | digits[4]
        
        digit_lengths[6].remove(digits[9])

        # Find 0 and 6
        for digit in digit_lengths[6]:
          if digit | digits[1] != digits[8]:
            digits[0] = digit
          else:
            digits[6] = digit
        
        # Find 5
        for digit in digit_lengths[5]:
          if digit | digits[1] == digits[9]:
            digits[5] = digit

        digit_lengths[5].remove(digits[5])

        # Find 2 and 3
        for digit in digit_lengths[5]:
          if digit | digits[1] == digit:
            digits[3] = digit
          else:
            digits[2] = digit
        
        # Convert encoded digits to regular digits
        # Add resulting number to the total
        num_result = ''
        for digit in result:
          num_result += str(digits.index(set(digit)))
        total += int(num_result)

    print(f'Part 2: {total}')
