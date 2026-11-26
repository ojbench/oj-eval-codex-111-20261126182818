# Solution

`src.hpp` implements the required global `strtok` function without includes,
standard-library calls, or global variables. A function-local static pointer
stores the remaining input. Each call builds a delimiter lookup table, skips
leading delimiters, and returns the next nonempty token, replacing its trailing
delimiter with a null byte. A non-null input resets the continuation pointer.
Rebuilding the table supports changing delimiters between calls; unsigned byte
indices support characters with the high bit set.

For a call scanning k input bytes with d delimiter bytes, time is O(k + d + 256)
and auxiliary space is O(256). Across calls, each input byte is scanned only a
constant number of times, apart from revisiting the terminating null byte.

## Local validation

- Compiled the provided driver with C++17 and verified the sample output.
- Compared return values, pointer offsets, and all buffer bytes with POSIX
  `strtok_r` on edge cases and 20,000 deterministic randomized inputs.
- Covered empty input, empty delimiters, delimiter-only input, repeated and
  trailing delimiters, changing delimiter sets, restarting with another string,
  repeated calls after exhaustion, and non-ASCII bytes.
- Passed AddressSanitizer and UndefinedBehaviorSanitizer.

Run the regression tests from the repository root:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g tests/strtok_test.cpp -o /tmp/problem111-test
/tmp/problem111-test
```

The advertised `data_test` directory was not present in the supplied data.
