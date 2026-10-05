#!/usr/bin/env python3
"""Optional local tests; the C program does not depend on Python."""

import argparse
from collections import Counter
import itertools
import math
from pathlib import Path
import random
import re
import subprocess
import sys


ROOT = Path(__file__).resolve().parent.parent
OPS = ('sa', 'sb', 'ss', 'pa', 'pb', 'ra', 'rb', 'rr', 'rra', 'rrb', 'rrr')
MODES = ('--simple', '--medium', '--complex', '--adaptive')


def simulate(values, operations):
    a, b = list(values), []
    for op in operations:
        assert op in OPS, f'invalid operation: {op!r}'
        if op in ('sa', 'ss') and len(a) > 1:
            a[0], a[1] = a[1], a[0]
        if op in ('sb', 'ss') and len(b) > 1:
            b[0], b[1] = b[1], b[0]
        if op == 'pa' and b:
            a.insert(0, b.pop(0))
        if op == 'pb' and a:
            b.insert(0, a.pop(0))
        if op in ('ra', 'rr') and a:
            a.append(a.pop(0))
        if op in ('rb', 'rr') and b:
            b.append(b.pop(0))
        if op in ('rra', 'rrr') and a:
            a.insert(0, a.pop())
        if op in ('rrb', 'rrr') and b:
            b.insert(0, b.pop())
    return a, b


class Suite:
    def __init__(self, args):
        self.push = str(args.push_swap.resolve())
        self.quick = args.quick
        self.checks = 0
        self.samples = {}

    def run(self, binary, args, stdin=b''):
        command = [binary, *map(str, args)]
        result = subprocess.run(command, input=stdin, capture_output=True, timeout=20)
        assert result.returncode >= 0, f'crashed: {command!r}\n{result.stderr!r}'
        return result

    def sorting(self, values, mode='--adaptive', arguments=None):
        args = arguments if arguments is not None else [mode, '--bench', *values]
        result = self.run(self.push, args)
        assert result.returncode == 0, f'{args!r}: status {result.returncode}, {result.stderr!r}'
        text = result.stdout.decode('ascii')
        assert not text or text.endswith('\n'), f'{args!r}: missing final newline'
        operations = text.splitlines()
        a, b = simulate(values, operations)
        assert a == sorted(values) and not b, f'{args!r}: final a={a!r}, b={b!r}'
        if list(values) == sorted(values):
            assert not operations, f'{args!r}: sorted input emitted moves'
        if '--bench' in args and values:
            self.benchmark(values, mode, operations, result.stderr.decode('ascii'))
        else:
            assert not result.stderr, f'{args!r}: unexpected stderr {result.stderr!r}'
        self.checks += 1
        return len(operations)

    def benchmark(self, values, mode, operations, report):
        n = len(values)
        inversions = sum(x > y for i, x in enumerate(values) for y in values[i + 1:])
        pairs = n * (n - 1) // 2
        disorder = inversions / pairs if pairs else 0
        percent = int(disorder * 10000 + 0.5)
        assert f'disorder: {percent // 100}.{percent % 100:02d}%' in report, report
        selected = mode
        if mode == '--adaptive':
            selected = '--simple' if disorder < .2 else '--medium' if disorder < .5 else '--complex'
            assert 'Adaptive / ' in report, report
        classes = {'--simple': 'O(n^2)', '--medium': 'O(n*sqrt(n))', '--complex': 'O(n*log(n))'}
        assert f'{selected[2:].title()} / {classes[selected]}' in report, report
        total = re.search(r'total_ops: (\d+)\n', report)
        assert total and int(total[1]) == len(operations), report
        counts = {op: int(number) for op, number in re.findall(r'\b(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr): (\d+)', report)}
        actual = Counter(operations)
        assert len(counts) == 11 and all(counts[op] == actual[op] for op in OPS), report
        if selected == '--simple':
            bound = n * n + 2 * n + 3
        elif selected == '--medium':
            width = math.isqrt(n - 1) + 1
            bound = n * math.ceil(n / width) + 2 * n * width + 2 * n
        else:
            bound = max(12, 2 * n * (n - 1).bit_length())
        assert len(operations) <= bound, f'{selected}: {len(operations)} > bound {bound}'

    def invalid_inputs(self):
        invalid = [
            [''], [' '], ['\t\n'], ['1', ''], ['1', '1'], ['0', '-0'], ['01', '+1'],
            ['2147483648'], ['-2147483649'], ['9' * 200], ['-' + '9' * 200],
            ['+'], ['-'], ['--1'], ['++1'], ['+-1'], ['1.0'], ['0x10'], ['1e2'],
            ['1,2'], ['1a'], ['a1'], ['1+2'], ['1-2'], ['1', '2', '3oops'],
            ['1 2 1'], ['1', '2', '\u00a0'],
        ]
        for args in invalid:
            result = self.run(self.push, args)
            assert result.returncode == 1 and result.stdout == b'' and result.stderr == b'Error\n', (
                f'{self.push} {args!r}: expected empty stdout, Error\\n, status 1; got {result!r}')
            self.checks += 1
        for args in (['--unknown'], ['--simple', '--medium', '1'], ['--bench', '--bench', '1'],
                     ['--adaptive', '--adaptive', '1'], ['1', '--bench'], ['--bench', 'x']):
            result = self.run(self.push, args)
            assert (result.returncode, result.stdout, result.stderr) == (1, b'', b'Error\n'), repr(result)
            self.checks += 1

    def execute(self):
        self.invalid_inputs()
        print(f'PASS invalid integers, duplicates, overflow and flags ({self.checks} checks)', flush=True)
        self.sorting([], arguments=[])
        self.sorting([], arguments=['--bench'])
        self.sorting([3, -2, 1], arguments=['3 -2 1'])
        self.sorting([3, -2, 1], arguments=['  3\t-2 ', '\n1\r'])
        self.sorting([-2147483648, 2147483647, 0], arguments=['-2147483648', '+2147483647', '-0'])
        self.sorting([1], arguments=['+' + '0' * 100 + '1'])
        for mode in MODES:
            for size in range(1, 5 if self.quick else 6):
                for values in itertools.permutations(range(size)):
                    self.sorting(list(values), mode)
        print('PASS exhaustive small permutations, benchmark counts and adaptive boundaries', flush=True)
        rng = random.Random(20260914)
        for size in (6, 10, 25, 100, 500):
            ordered = list(range(size))
            almost = ordered.copy()
            almost[-1], almost[-2] = almost[-2], almost[-1]
            cases = [ordered, ordered[::-1], ordered[1:] + ordered[:1], almost,
                     ordered[::2] + ordered[1::2]]
            cases += [rng.sample(range(-1000000, 1000000), size) for _ in range(3 if self.quick else 20)]
            for mode in MODES:
                counts = [self.sorting(values, mode) for values in cases]
                if size in (100, 500):
                    self.samples[size, mode] = (min(counts), max(counts))
        print('PASS random and structured inputs through 500 values; operation upper bounds', flush=True)
        for (size, mode), (low, high) in self.samples.items():
            print(f'  {size:3d} values {mode:10s}: {low}..{high} operations (includes sorted input)')
        print(f'PASS {self.checks} named-case checks; emitted operations verified by independent simulation')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--push-swap', type=Path, default=ROOT / 'push_swap')
    parser.add_argument('--quick', action='store_true')
    args = parser.parse_args()
    try:
        Suite(args).execute()
    except (AssertionError, subprocess.TimeoutExpired) as error:
        print(f'FAIL: {error}', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
