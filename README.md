# Sudoku Solver

A constraint-based Sudoku solver written in C. The program uses logical elimination techniques to solve a hardcoded puzzle without backtracking.

## Project Structure

| File | Description |
|------|-------------|
| `main.c` | Entry point — initializes the puzzle and runs the solve loop |
| `sudoku.h` | Header file with struct definitions and function declarations |
| `setup.c` | Puzzle creation, grid initialization, and core update logic |
| `checkRows.c` | Row-based single-candidate detection |
| `boxSingles.c` | Box-based single-candidate detection and box/square setup |
| `solvedSquare.c` | Marks a square as solved when only one possibility remains |

## Data Structures

### `Square`
Represents a single cell in the 9×9 grid.
- `number` — the solved value (0 if unsolved)
- `possible[9]` — bitmask array; `1` means the number is eliminated
- `solvable` — count of remaining possibilities
- `row`, `column` — grid coordinates
- `box` — pointer to the containing 3×3 box

### `Box`
Represents one of the nine 3×3 sub-grids.
- `squares[9]` — pointers to the nine cells in this box
- `possible[9]` — eliminated candidates for the box
- `numbers`, `solvable` — bookkeeping counters

### `Soduku`
Top-level container holding:
- `squares` — the 9×9 grid as `Square***`
- `boxes` — array of nine `Box*` pointers

## How It Works

1. **Initialization** — `setUpPuzzle()` allocates the grid, assigns each cell to a box, and runs `updateSoduku` / `updateBoxes` for every pre-filled cell to propagate initial constraints.

2. **Solve loop** — `checkPuzzle()` is called repeatedly until the puzzle is solved or no more progress can be made. Each call tries three strategies in order:

   | Strategy | Function | Description |
   |----------|----------|-------------|
   | Naked single | `solvedSquare()` | A cell has exactly one remaining candidate |
   | Box single | `boxSingles()` | A candidate appears in only one cell of a 3×3 box |
   | Row single | `checkRows()` | A candidate appears in only one cell of a row |

3. **Propagation** — whenever a cell is solved, `updateSoduku()` eliminates that value from every cell in the same row and column, and `updateBoxes()` eliminates it from every cell in the same box.

## Building

Compile all `.c` files together with your C compiler:

```bash
gcc main.c setup.c checkRows.c boxSingles.c solvedSquare.c -o sudoku
./sudoku
```

## Puzzle Input

The puzzle is hardcoded in `createPuzzle()` inside `setup.c` as a 9×9 integer array. Use `0` for empty cells.

```c
int array[9][9] = {
    0,1,9,  0,0,2,  0,0,0,
    4,7,0,  6,9,0,  0,0,1,
    ...
};
```

To solve a different puzzle, replace the values in this array and recompile.

## Global Variables

| Variable | Purpose |
|----------|---------|
| `UNSOLVED` | Counts remaining unsolved cells; initialized to `81` |
| `SIZE_ROWS` | Grid height (9) |
| `SIZE_COLUMNS` | Grid width (9) |

## Limitations

- **No backtracking** — puzzles that require guessing (i.e., those not solvable by naked/hidden singles alone) will cause the solver to exit with `"didnt solve"`.
- **Single puzzle** — the input puzzle is hardcoded; there is no file or stdin input.
- **No memory cleanup** — allocated memory is not freed before exit.

## Example Output

```
------------------------------------
| 0 | 1 | 9 | 0 | 0 | 2 | 0 | 0 | 0 |
| 4 | 7 | 0 | 6 | 9 | 0 | 0 | 0 | 1 |
...
------------------------------------

(solved grid printed after)
```
