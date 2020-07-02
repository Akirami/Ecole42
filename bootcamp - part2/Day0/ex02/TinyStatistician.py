#!/usr/bin/python3

import math

class TinyStatistician:
    def mean(self, arr):
        if len(arr) > 0:
            total = 0.0
            for x in arr:
                if (isinstance(x, float) or isinstance(x, int)):
                    total += float(x)
                else:
                    return None
        else:
            return None
        return total / float(len(arr))

    def median(self, a):
        arr = a
        arr.sort()
        if len(arr) > 0:
            for x in arr:
                if (isinstance(x, float) or isinstance(x, int)):
                    z = (len(arr) + 1) / 2
                    if z % 1 == 0:
                        return arr[int(z) - 1]
                    else:
                        return (arr[int(z) - 1] + arr[int(z)]) / 2
                else:
                    return None
        else:
            return None

    def quartiles(self, a, c):
        arr = a
        arr.sort()
        if len(arr) > 0:
            if c == 25:
                for x in arr:
                    if (isinstance(x, float) or isinstance(x, int)):
                        z = (len(arr) + 3) / 4
                        if z % 1 == 0:
                            return arr[int(z - 1)]
                        elif z % 1 == 0.25:
                            return (3 * arr[int(z - 1)] + arr[int(z)]) / 4
                        elif z % 1 == 0.75:
                            return (arr[int(z - 1)] + (arr[int(z)] * 3)) / 4
                    else:
                        return None
            if c == 75:
                for x in arr:
                    if (isinstance(x, float) or isinstance(x, int)):
                        z = (3 * len(arr) + 1) / 4
                        if z % 1 == 0:
                            return arr[int(z - 1)]
                        elif z % 1 == 0.25:
                            return (3 * arr[int(z - 1)] + arr[int(z)]) / 4
                        elif z % 1 == 0.75:
                            return (arr[int(z - 1)] + (arr[int(z)] * 3)) / 4
        else:
            return None
    def var(self, a):
        arr = a
        arr.sort()
        moy = self.mean(a)
        v = 0.0
        for k in arr:
            v += (float(k) - float(moy))**2
        return(v / len(arr))

    def std(self, data):
        n = len(data)
        if n <= 1:
            return None
        moy = self.mean(data)
        sd = 0.0
        for el in data:
            sd += (float(el) - moy)**2
        return math.sqrt(sd / float(n - 1))

if __name__ == "__main__":
    tstat = TinyStatistician()
    a = [4, 2, 5, 8, 6]   
    print(tstat.mean(a))
    print(tstat.median(a))
    print(tstat.quartiles(a, 25))
    print(tstat.quartiles(a, 75))
    print(tstat.var(a))
    print(tstat.std(a))



