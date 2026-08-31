class Metrics:
    def __init__(self):
        self.comparisons = 0
        self.moves = 0


# ---------- MERGE SORT CLASICO (2 particiones) - O(n log n) ----------

def merge2(arr, lo, mid, hi, m):
    left = arr[lo:mid + 1]
    right = arr[mid + 1:hi + 1]
    i = j = 0
    k = lo
    while i < len(left) and j < len(right):
        m.comparisons += 1
        if left[i] <= right[j]:
            arr[k] = left[i]; i += 1
        else:
            arr[k] = right[j]; j += 1
        k += 1
        m.moves += 1
    while i < len(left):
        arr[k] = left[i]; i += 1; k += 1; m.moves += 1
    while j < len(right):
        arr[k] = right[j]; j += 1; k += 1; m.moves += 1


def merge_sort2(arr, lo, hi, m):
    if lo >= hi:
        return
    mid = lo + (hi - lo) // 2
    merge_sort2(arr, lo, mid, m)
    merge_sort2(arr, mid + 1, hi, m)
    merge2(arr, lo, mid, hi, m)


# ---------- MERGE SORT MODIFICADO (3 particiones) ----------

def merge_sort3(arr, lo, hi, m):
    length = hi - lo + 1
    if length < 3:
        merge_sort2(arr, lo, hi, m)
        return
    third = length // 3
    mid1 = lo + third - 1
    mid2 = lo + 2 * third - 1
    merge_sort3(arr, lo, mid1, m)
    merge_sort3(arr, mid1 + 1, mid2, m)
    merge_sort3(arr, mid2 + 1, hi, m)
    merge2(arr, lo, mid1, mid2, m)   # une primeros 2 tercios
    merge2(arr, lo, mid2, hi, m)     # une resultado con el ultimo tercio


# ---------- QUICK SORT CLASICO (1 pivote, Lomuto) ----------

def partition1(arr, lo, hi, m):
    pivot = arr[hi]
    i = lo - 1
    for j in range(lo, hi):
        m.comparisons += 1
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
            m.moves += 1
    arr[i + 1], arr[hi] = arr[hi], arr[i + 1]
    m.moves += 1
    return i + 1


def quick_sort1(arr, lo, hi, m):
    if lo < hi:
        p = partition1(arr, lo, hi, m)
        quick_sort1(arr, lo, p - 1, m)
        quick_sort1(arr, p + 1, hi, m)


# ---------- QUICK SORT MODIFICADO (2 pivotes: primero y ultimo, 3 particiones) ----------

def quick_sort2(arr, lo, hi, m):
    if lo >= hi:
        return
    if arr[lo] > arr[hi]:
        arr[lo], arr[hi] = arr[hi], arr[lo]
        m.moves += 1
    p1, p2 = arr[lo], arr[hi]
    lt, gt, i = lo + 1, hi - 1, lo + 1
    while i <= gt:
        m.comparisons += 1
        if arr[i] < p1:
            arr[i], arr[lt] = arr[lt], arr[i]
            m.moves += 1
            lt += 1; i += 1
        else:
            m.comparisons += 1
            if arr[i] > p2:
                while i < gt:
                    m.comparisons += 1
                    if arr[gt] <= p2:
                        break
                    gt -= 1
                arr[i], arr[gt] = arr[gt], arr[i]
                m.moves += 1
                gt -= 1
                m.comparisons += 1
                if arr[i] < p1:
                    arr[i], arr[lt] = arr[lt], arr[i]
                    m.moves += 1
                    lt += 1
            i += 1
    lt -= 1; gt += 1
    arr[lo], arr[lt] = arr[lt], arr[lo]
    m.moves += 1
    arr[hi], arr[gt] = arr[gt], arr[hi]
    m.moves += 1
    quick_sort2(arr, lo, lt - 1, m)
    quick_sort2(arr, lt + 1, gt - 1, m)
    quick_sort2(arr, gt + 1, hi, m)
