"""
Part 2 of Project:
Implement Median Filtering Procedure using Order Statistics Algorithm
Authors: Nora Elattar, Sean Connor, and Matthew Henschke
"""
#libraries used
from PIL import Image
import numpy
from order_statistics import order_statistics

#median filtering algorithm
def median_filter(data, filter_size):
    temp = []
    indexer = filter_size // 2
    data_final = []
    data_final = numpy.zeros((len(data),len(data[0])))
    for i in range(len(data)):

        for j in range(len(data[0])):

            for z in range(filter_size):
                if i + z - indexer < 0 or i + z - indexer > len(data) - 1:
                    for c in range(filter_size):
                        temp.append(0)
                else:
                    if j + z - indexer < 0 or j + indexer > len(data[0]) - 1:
                        temp.append(0)
                    else:
                        for k in range(filter_size):
                            temp.append(data[i + z - indexer][j + k - indexer])

            # This is the part where we will implement the order statistics algorithm
            if len(temp) == len(set(temp)):
                data_final[i][j] = order_statistics(temp, len(temp) // 2) # apply order statistics when pixel values are distinct
            else:
                data_final[i][j] = sorted(temp)[len(temp) // 2 ] # the pixel values are not distinct
            temp = []



    return data_final


if __name__ == "__main__":
    img = Image.open("boat.jpg").convert("L")
    filter = int(input("Please enter a dimension"))
    arr = numpy.array(img)
    removed_noise = median_filter(arr, filter)
    img = Image.fromarray(removed_noise)
    img.show()




