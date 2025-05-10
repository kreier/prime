console.log([...new Array(9)]
    .map((_, i) => [...new Array(i + 1)]
        .map((_, j) => j + 1)
        .filter((k) => (i + 1) % k === 0)
    )
    .flat()
    .reduce((a, b) => a + b));
