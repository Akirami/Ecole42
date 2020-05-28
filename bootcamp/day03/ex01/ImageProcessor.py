#!/usr/bin/python3
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np


class ImageProcessor:
    def load(self, path):
        im = mpimg.imread(path)
        w = im.shape
        print("Loading image of dimensions %d x %d." % (w[0], w[1]))
        return im

    def display(self, arr):
        imgplot = plt.imshow(arr)
        plt.show()


if __name__ == "__main__":
    imp = ImageProcessor()
    arr = imp.load("./az.png")

    print(arr)

    imp.display(arr)
