#Noe Lozano Mendoza, Diana Olivas, Steffan Canul, Jenny Bacab
import numpy as np
import math 

def bublesorting(list1):
  n=len(list1)-1
  for i in range(n):
    for j in range(0, n-i):
      if list1[j+1]<list1[j]:
        list1[j], list1[j+1] = list1[j+1], list1[j]
  return list1

def selectionsorting(list1):
  n = len(list1)
  for i in range(n):
    m = i
    for j in range(i+1, n):
      if list1[j] < list1[m]:
        m=j
    list1[i], list1[m] = list1[m], list1[i]
  return list1

def insertionsort(list1):
  n= len(list1)
  for i in range(n):
    v = list1[i]
    j = i-1
    while j >= 0 and v < list1[j]:
      list1[j+1] = list1[j]
      j -= 1
    list1[j+1] = v 
  return list1 

def sequential_search(anyList, elementSearched):
    for i in range(len(anyList)):
        if elementSearched == anyList[i]:
            return i

    return -1

def binary_search(anyList, elementSearched):
    l = 0
    r = len(anyList) - 1

    while l <= r and elementSearched >= anyList[l] and elementSearched <= anyList[r]:
        m = math.floor((l + r) / 2)
        if elementSearched == anyList[m]:
            return m
        elif elementSearched < anyList[m]:
            r = m - 1
        else:
            l = m + 1

    return -1

def interpolation_search(anyList, elementSearched):
    l = 0
    r = len(anyList) - 1

    while l <= r and elementSearched >= anyList[l] and elementSearched <= anyList[r]:
        m = math.floor( ((elementSearched - anyList[l]) * (r - l)) / (anyList[r] - anyList[l]) )
        if elementSearched == anyList[m]:
            return m
        elif elementSearched < anyList[m]:
            r = m - 1
        else:
            l = m + 1

    return -1

def main():
    #Bubble Sorting
  print("First, we will bubble sort an array")
  bli = np.random.randint(-100,100,6)
  print("The list is:", bli)  
  print("After the Bubble Sorting:", bublesorting(bli)) 
  print("\n")

  #Selection Sorting
  print("Second, the Selection Sorting")
  sli = np.random.randint(-100,100,6)
  print("The list is:", sli)  
  print("After the Selection Sorting:", selectionsorting(sli))
  print("\n")

  #Insertion Sorting
  print("Now, we will finish with the Insertion Sorting")
  ili=np.random.randint(-100,100,6)
  print("The list is:", ili)  
  print("After the Insertion Sorting:", insertionsort(ili))  
  print("\n")

  #Sequential search
  print("We generate a numbers list to search sequentially")
  listSS = [2, 50, 78, 10, 7, 90, 45]
  print("The list is:", listSS) 
  print("Searched element: ", 10)
  print("When the value exists in the list return it: ", sequential_search(listSS, 10)) 
  print("When not so: ", sequential_search(listSS, 100)) 
  print("\n")

  #Binary Search
  print("We generate a numbers list to binary search test")
  listBS = [10,14,19,26,27,31,33,35,42,44]
  print("The list is:", listBS)
  print("Searched element: ", 33)
  print("When the value exists in the list return index value: ", binary_search(listBS, 31)) 
  print("When not so: ", binary_search(listBS, 5)) 
  print("\n")

  #Interpolation Search
  print("We generate a numbers list to interpolation search test")
  listIS = [10,14,19,26,27,31,33,35,42,44]
  print("The list is:", listIS) 
  print("Searched element: ", 26)
  print("When the value exists in the list return index value: ", interpolation_search(listIS, 26)) 
  print("When not so: ", interpolation_search(listIS, 50)) 
  print("\n")
  
main()