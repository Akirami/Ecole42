#!/usr/bin/python3
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np


def print_error(s):
    print(s)
    exit()


class ImageProcessor:
    def load(self, path):
        im = mpimg.imread(path)
        w = im.shape
        print("Loading image of dimensions %d x %d." % (w[0], w[1]))
        return im

    def display(self, arr):
        imgplot = plt.imshow(arr)
        plt.show()


class ScrapBooker:
    def crop(self, array, dimensions, position=(0, 0)):
        x, y = position
        wh = array.shape
        h, w = dimensions
        posx, posy = position
        if h > wh[0] or w > wh[1]:
            print_error("Can't crop, dimensions out of range.")
        if posx + w > wh[0] or posy + h > wh[1]:
            print_error("Can't crop, positions out of range.")
        crop_img = array[y:y + h, x:x + w]
        np.resize(crop_img, (h, w))
        return crop_img

    def thin(self, array, n, axis):
        if n < 1:
            print_error("N is zero or below, invalid.")
        if not axis:
            if n > array.shape[0]:
                print_error("n too big for this img")
            arr = np.delete(array, list(range(0, array.shape[0], n)), axis=0)
        elif axis:
            if n > array.shape[1]:
                print_error("n too big for this img")
            arr = np.delete(array, list(range(0, array.shape[1], n)), axis=1)
        else:
            print_error("Axis out of range")
        return arr

    def juxtapose(self, array, n, axis=0):
        if n < 1:
            print_error("N is zero or below, invalid.")
        if not axis:
            arr = np.tile(array, (n, 1))
        elif axis:
            arr = np.tile(array, (n, 1, 1))
        else:
            print_error("Axis out of range")
        return arr

    def mosaic(self, array, dimensions):
        w, h = dimensions
        if w < 1 or h < 1:
            print_error("Wrong dimensions")
        arr = np.tile(array, (w, 1))
        arr = np.tile(arr, (h, 1, 1))

        return arr


if __name__ == "__main__":
    imp = ImageProcessor()
    arr1 = imp.load("./az.png")
    scrp = ScrapBooker()

    arr2 = scrp.crop(arr1, (150, 150), (80, 50))
    arr3 = scrp.thin(arr1, 4, 0)
    arr4 = scrp.juxtapose(arr1, 4, 1)
    arr5 = scrp.mosaic(arr1, (4, 3))

    imp.display(arr1)
    imp.display(arr2)
    imp.display(arr3)
    imp.display(arr4)
    imp.display(arr5)
