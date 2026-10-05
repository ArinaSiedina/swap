# push_swap

C implementation of the supplied **Push_swap, version 1.1** subject: four
sorting strategies, initial disorder measurement, and benchmark reporting. No external library or libft is required.

## Learners and contributions

The subject requires exactly two learners. Complete this table with the actual
logins and contributions before submission; the entries below are placeholders.
The `login` author fields in the C headers also need the real authors' details.

| Learner login | Actual contribution |
| --- | --- |
| TODO: first login | TODO: describe work completed and reviewed |
| TODO: second login | TODO: describe work completed and reviewed |

AI assistance was used to generate the initial implementation, documentation,
and local tests. Both learners should review the code and be able to explain
every strategy, its invariants, and its complexity during the defense.

## Build and run

Use a Linux/macOS shell with a C compiler and Make. On Windows, run these commands
in **WSL: Ubuntu**, from this project directory:

```sh
make
./push_swap 3 2 1
./push_swap --simple "4 1 3 2"
./push_swap --medium 4 67 3 87 23
./push_swap --complex --bench 4 67 3 87 23
./push_swap --bench --adaptive 4 67 3 87 23 > moves.txt 2> bench.txt
```

The first integer is the top of stack A. Stack B starts empty. The output is a
list of allowed operations, one per line, which leaves A in ascending order and
B empty. Already sorted input emits no operations.

`--adaptive` is the default. `--simple`, `--medium`, and `--complex` force their
respective strategies for every input size and disorder level. All strategies
share a constant-size base case for up to five integers.

`--bench` writes the initial disorder as a percentage with two decimal places,
the requested/selected strategy and operation complexity, total operations,
and counts of all eleven operation types to **stderr**. Without this flag,
successful sorting writes nothing to stderr. Combined operations count once.

Options must precede the integers. `--bench` and one strategy flag can appear
in either order. Unknown, repeated, or conflicting options are errors. Integers
may be separate arguments, whitespace-separated quoted groups, or a mixture.
ASCII whitespace and a single leading `+` or `-` are accepted. Empty arguments,
whitespace-only arguments, malformed integers, values outside
`[-2147483648, 2147483647]`, and numerical duplicates are rejected.

Errors produce exactly `Error\n` on stderr and exit status 1. Validation finishes
before sorting, so invalid arguments cannot produce a partial operation stream.
No arguments, or recognized flags without integers, produce no output and exit
successfully. A zero or one-element input has disorder zero.

## Strategies and operation bounds

Each value receives its rank among the input integers, from 0 to n-1. This
preserves ordering while allowing radix sorting of negative numbers and the
full signed integer range. The original values remain available for checking.

Complexity below counts **emitted push_swap operations**, as required by the
subject. It does not claim the same bound for the C program's analysis work.

| Selector | Method | Operation upper bound | Auxiliary space |
| --- | --- | --- | --- |
| `--simple` | Minimum extraction with shortest rotations | O(n²) | O(n) |
| `--medium` | Fixed rank buckets of width ceil(sqrt(n)) | O(n sqrt(n)) | O(n) |
| `--complex` | Stable binary LSD radix sort of ranks | O(n log(n)) | O(n) |
| `--adaptive` | Select one of the above from initial disorder | Bound of selected method | O(n) |

**Simple:** bring the minimum of A to its top using the shorter rotation
direction, then push it to B. Repeat until the remaining A is sorted or has
three elements. Sort that small remainder and return B to A. Extracted minima
are in descending order in B, so returning them restores ascending order.
Each extraction needs at most n/2 rotations; at most n extractions and 2n pushes
give an O(n²) upper bound. Sorted remainders stop extraction early.

**Medium:** let k = ceil(sqrt(n)). Scan the remaining A once for each successive
rank bucket, pushing the bucket's values to B and rotating past the others.
There are ceil(n/k) scans, each of at most n operations. This forms contiguous
buckets on B, with the highest bucket on top. Bring B's maximum to the top with
the shorter rotation direction and push it to A; repeat. On the circular stack,
the current highest bucket stays contiguous and touches the top, possibly
wrapping across the bottom. Its next maximum is reachable in at most k rotations.
Removing that bucket exposes the next bucket. The return phase therefore costs
at most n(k+1) operations. Together, O(n²/k + nk) = O(n sqrt(n)). The algorithm
deliberately preserves bucket boundaries, making this bound independent of the
input order.

**Complex:** process rank bits from least significant to most significant.
For each bit, push zero-bit ranks to B and rotate one-bit ranks in A; return B
to A. The two pushes preserve the zero group's relative order, and rotations
preserve the one group's relative order. Each pass stably partitions on one
more bit. At most ceil(log2(n)) passes, each with at most 2n operations, sort the
input in O(n log(n)) operations.

**Adaptive:** before any operation, count inversions (pairs i < j with a[i] >
a[j]) and divide by n(n-1)/2. The exact, unrounded ratio selects the strategy:

| Initial disorder | Selected method | Reason |
| --- | --- | --- |
| Less than 0.2 | Simple | Exploit sorted remainders with straightforward extraction |
| At least 0.2, less than 0.5 | Medium | Bound movement using square-root rank buckets |
| At least 0.5 | Complex | Use a predictable logarithmic number of full passes |

These thresholds are specified by the subject. Rounded benchmark percentages
are for display only. Sorted input returns immediately after strategy selection.
The shared two-to-five-element base case uses at most 12 operations and does not
change any asymptotic bound. The algorithms aim to keep operation counts small;
they do not guarantee globally shortest sequences.

Both stacks use preallocated circular arrays. Swap, push, rotate, and reverse
rotate each take constant CPU time without further allocation. The arrays use
O(n) memory. Input duplicate detection, rank assignment, inversion measurement,
and repeated min/max searches use O(n²) CPU work overall; this is distinct from
the operation bounds above. Radix generation adds O(n log(n)) CPU work. Both
allocations are released on success and on argument errors.

## Files and local validation

- Submission sources: `*.c`, `push_swap.h`, `Makefile`, and this README.
- `.build/*.o` and `push_swap` are generated build artifacts.
- `tests/test_push_swap.py` is optional local infrastructure, not a dependency
  of the C program. It requires Python 3 only when running tests.

```sh
make test
python3 tests/test_push_swap.py --quick
norminette
make clean     # remove generated object files
make fclean    # also remove the executable
make re        # rebuild push_swap
```

Tests independently simulate emitted operations, exhaustively cover all
permutations through five integers in every strategy, exercise structured and
seeded random inputs through 500 integers, verify disorder/strategy/count
reporting, check conservative operation bounds, and test malformed input.
Failures identify the input and actual result.

The supplied PDF is the requirements reference. Relevant implementation entry
points are `parse.c`, `measure.c`, `sort.c`, `sort_simple.c`, `sort_medium.c`,
`sort_complex.c`, and `operations.c`.
