# Basic Median String Search
This project implements branch and bound median string search in **C++** and some test cases. 


## Algorithm
**Aim:** Given an integer k and a set of DNA sequences we ask to find a k-mer
pattern that minimizes Total Distance(pattern, DNA) over all strings of that length under
Hamming distance. We call such a k-mer a median string for a set of DNA sequences. k must
be equals or less than 16, pattern must be of a length equal or less than 500 and the number
of DNA sequences must be equal or less than 100.

**Input:** A text file whose first line is an integer k following by a set of DNA sequences of the
same length.

**Output:** A text file containing the k-mer pattern that minimizes Total distance(pattern,
DNA) over all k-mers.

### Psuedocode
```
BranchAndBoundMedianStringSearch(DNA,t,n,l )
  s ← (1,…,1)
  bestDistance ← ∞
  i ← 1
  while i > 0
    if i < l
      prefix ← string corresponding to the first i nucleotides of s
      optimisticDistance ← TotalDistance(prefix,DNA)
      if optimisticDistance > bestDistance
        (s, i ) ← Bypass(s,i, l, 4)
      else
        (s, i ) ← NextVertex(s, i, l, 4)
  else
    word ← nucleotide string corresponding to s
    if TotalDistance(s,DNA) < bestDistance
      bestDistance ← TotalDistance(word, DNA)
      bestWord ← word
    (s,i ) ← NextVertex(s,i,l, 4)
  return bestWord


Bypass(a,i,L,k)           // a: array of digits
  for j ← i to 1          // i : prefix length
    if a[j] < k           // L: maximum length
      a[j] ← a[j] +1      // k : max digit value
      return(a,j)
  return(a,0)


NextVertex(a,i,L,k)       // a : the array of digits
  if i < L                // i : prefix length
    a[i+1] ← 1            // L: max length
    return (a,i+1)        // k : max digit value
  else
    for j ← l to 1
      if a[j] < k
        a[j] ← a[j] +1
        return(a,j)
  return(a,0)
```

## Compilation and Run
Makefile uses **Makefile** and **g++** as compiler. These packages should be installed into the system in order to run the project.
After navigating to the projects directory to compile the project execute
```
make
```
or
```
make build
```

After compilation, an example to run the project can be

```
make run in=input0.txt out=output0.txt
```
or
```
./medianSearch input0.txt output0.txt
```
