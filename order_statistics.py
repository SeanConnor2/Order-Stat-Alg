"""
Part 1 of CSC 382 Project
Implement Order Statistics Algorithm
Authors: Nora Elattar, Sean Connor, and Matthew Henschke
"""

# libraries used
from random import randint
import time

# function that will compute the value at kth index in arr
def order_statistics(arr, k):
    sublists = [arr[j: j + 5] for j in range(0, len(arr), 5)]  # generate all sublists
    medians = []  # medians array
    for list in sublists:
        # add the median of every sublist to medians
        medians.append(sorted(list)[len(list) // 2])
    # if the total number of medians is less than five, we can get the median of all medians
    if len(medians) <= 5:
        pivot = sorted(medians)[len(medians) // 2]  # pivot is median of medians
    else:
        # recursion call to continue to find the median of medians
        pivot = order_statistics(medians, len(medians) // 2)

    # partition step
    low = [i for i in arr if i < pivot]
    high = [j for j in arr if j > pivot]

    # get position of pivot in arr
    pos = len(low)

    if k < pos:
        return order_statistics(low, k)
    elif k > pos:
        return order_statistics(high, k - pos - 1)
    else:
        return pivot  # we found the kth value








# method to generate n random numbers in range 1 - N
def generateArray(N, n):
    arr = set()
    while len(arr) < n:
        arr.add(randint(1, N))
    return list(arr)





# driver code
if __name__ == "__main__":
    sample_sizes = [100,300,500, 1000, 2000, 4000]
    pop_sizes = [5000, 8000, 10000]


    for n in sample_sizes: # iterate through all n values
        print("n:", n)
        arr = []
        for N in pop_sizes:# iterate through all N values
            arr = generateArray(N, n) # generate array
            for j in range(5): # pick k five times for each N value
                i = randint(1, n)
                start = time.time()
                order_statistics(arr, i - 1 )
                end = time.time()
                runtime = (end - start) * 1000 # get runtime of order statistics function in
                print("N = {}, i = {}, Order statistics algorithm took {:.2f} milliseconds  ".format(N, i, runtime))

            arr = [] # reset array
        print("\n")




