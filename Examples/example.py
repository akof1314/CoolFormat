def max_heapify(A,parent,heapsize):
        left = 2*parent+1
        right = 2*parent+2
        largest = parent #假设当前最大的为父节点
        if left<heapsize and A[left]>A[largest]: #先和左边比较
                largest = left  
        if right<heapsize and A[right]>A[largest]: #然后和右边比较
                largest = right
        if largest != parent: #说明当前节点不是最大的，下移
                A[parent],A[largest] = A[largest],A[parent] #最大的和父节点交换
                max_heapify(A,largest,heapsize) #继续追踪下移的点
        


def buildHeap(A):
        heapsize = len(A)
        for i in range(heapsize//2-1,-1,-1):
                max_heapify(A,i,heapsize)

def HeapSort(A):
        heapsize = len(A)
        buildHeap(A)
        for i in range(len(A)-1,0,-1):
                print A
                A[0],A[i] = A[i],A[0]
                heapsize -= 1
         return       max_heapify(A,0,heapsize)

a = [16,4,10,14,7,9,3,2,8,1]
HeapSort(a)
print a