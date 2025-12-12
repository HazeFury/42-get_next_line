*This project has been created as part of the 42 curriculum by marberge.*

___

<div align="center">
<br>
  <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTQPzuYKu7n0cWUYa5Kbg0_LrlEQAIURWeo9A&s" alt="42 Logo" width="400" />

  <br>
</div>

# get_next_line

![Language](https://img.shields.io/badge/Language-C-blue)
![Bonus](https://img.shields.io/badge/Bonus-Completed-success)
![Grade](https://img.shields.io/badge/Grade-125%2F100-brightgreen)

## 📝 Description

The goal of this project is to write a function that returns a line read from a file descriptor. While `printf` taught us about variadic arguments and buffering output, **get_next_line** focuses on the concept of **static variables**, **file descriptors**, and strict **memory management**.

This implementation is robust, memory-leak free (checked with Valgrind), and handles multiple file descriptors simultaneously (Bonus) while remaining performant even with huge files or buffer sizes.

## 🛠️ Instructions

### Requirements
This project is written in C and requires a compiler (gcc/clang) and the standard C libraries.

### Compilation
To compile the project, you must define the `BUFFER_SIZE` macro. This determines the size of the read calls.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

### Usage
To use get_next_line in your own project:

1. Include the header file in your code:

```C
#include "get_next_line.h"
```

2. Call the function in a loop to read a file line by line.

### Example

```c
int main(void)
{
    int  fd = open("text.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line); // IMPORTANT: The user is responsible for freeing the line
    }
    close(fd);
    return (0);
}
```

## ⚙️ Technical Choices & Algorithm

This section details the specific implementation choices made for this project, particularly regarding memory management and optimization to handle varying buffer sizes.

### The Data Structure: Hybrid Memory Approach
To balance performance, stability, and memory safety, this project uses two distinct memory areas.

1.  **The Static Stash (Data/BSS Segment)**
    * Defined as `static char stash[MAX_FD][BUFFER_SIZE + 1]`.
    * **Role:** Persistence. It stores the "leftover" characters from the previous read that belong to the next line.
    * **Why Static?** Unlike a pointer that requires manual freeing at the very end (risking "Still Reachable" leaks), a static array is automatically managed by the program's lifecycle in the BSS segment.

2.  **The Read Buffer (Heap Segment)**
    * Defined as `char *buffer = malloc(...)`.
    * **Role:** Temporary storage for the `read()` system call.
    * **Why Heap?** Allocating a large buffer (e.g., 10MB) on the Stack causes a **Stack Overflow**. Using `malloc` allows us to handle huge buffer sizes defined at compilation time.

### The Algorithm Flow
The function acts as a "Conductor" orchestrating data movement:

1.  **Allocation:** The `buffer` is allocated on the Heap.
2.  **Initialization:** If `stash` contains data from a previous call, it is loaded into the accumulator (`tmp`).
3.  **Reading Loop:**
    * Reads `BUFFER_SIZE` bytes from the FD.
    * **Optimization:** Scans the *newly read buffer* for a `\n` before joining.
    * Joins the buffer to `tmp`.
    * Breaks immediately if a `\n` is found.
4.  **Critical Cleanup:** The `buffer` is freed **immediately** after the loop, regardless of success or failure.
5.  **Extraction & Update:** `ft_trim_from_start` creates the return line, and `ft_resize_stash` cleans the static array for the next call.

### Justification & Challenges
Several architectural choices were driven by strict testing constraints (Francinette & Valgrind).

#### 1. The Stack Overflow vs. Heap Dilemma
**Why `malloc` the buffer?**
Initially, declaring `char buffer[BUFFER_SIZE]` on the stack worked for small buffers. However, testing with `-D BUFFER_SIZE=10000000` crashed the program (Stack Overflow). Moving the buffer to the Heap solved this but required strict "Owner Allocates, Owner Frees" logic to avoid leaks.

#### 2. The "2-Bytes Leak" (Ownership)
**Why free in the main function?**
When delegating `malloc` to a sub-function, edge cases (like immediate EOF) often resulted in the buffer being lost before being freed. By enforcing that `get_next_line` (the caller) always frees the buffer it allocated, we guarantee 0 leaks.

#### 3. Optimization (Timeouts)
**Why scan the buffer instead of the stash?**
On "Giant Line" tests, scanning the growing `stash` for `\n` at every iteration created $O(N^2)$ complexity, leading to timeouts. Scanning only the small, fixed-size `buffer` reduced this to linear complexity.

## 📚 Resources

### References
* `man 2 read`
* `man 3 malloc`
* [Valgrind User Manual](https://valgrind.org/docs/manual/quick-start.html)

### AI Usage Declaration
As required by the new subject guidelines, here is the detail of AI usage for this project:

* **Code Implementation:** The code was entirely written by the author (`marberge`). No AI-generated code was copy-pasted into the final project.
* **Debugging:** AI was used to analyze Valgrind logs, specifically to understand the difference between "Still Reachable" (static pointers) and "Definitely Lost" (mishandled mallocs).
* **Optimization:** AI helped identify the mathematical complexity causing timeouts in the `ft_strjoin` function.
* **Architecture:** AI was consulted to determine the best strategy to avoid Stack Overflows with large buffers (Heap vs Stack trade-offs).
* **README:** This README has been written by AI.


<br>

___

<p align="center">Made by ❤️ by marberge<p>