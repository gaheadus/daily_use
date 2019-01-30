/*
常用算法
参考
参考：大话数据结构,程杰,清华大学出版社, 2011.06
数据结构与算法分析新视角,周幸妮,2016
*/
//交换排序
//(1)冒泡排序(Bubble Sort)
//冒泡排序：指定数值小的元素在前、数值大的元素在后，元素之间两两比较，逆序则交换两个元素的位置，。
//第一趟，全部n个元素两两相互比较，从arr[0]开始，arr[0]、arr[1]比较，逆序则交换位置，arr[1]、arr[2]比较，逆序则交换位置，…，最后，arr[n-2]、arr[n-1]比较，逆序则交换位置；一趟完成后，最大元素就冒泡到最后的位置arr[n-1]了。
//第二趟，前n-1个元素两两相互比较，从arr[0]开始，arr[0]、arr[1]比较，逆序则交换位置，arr[1]、arr[2]比较，逆序则交换位置，…，最后，arr[n-3]、arr[n-2]比较，逆序则交换位置；一趟完成后，次大元素就冒泡到最后的位置arr[n-2]了。
//第三趟，…
void BubbleSort(){
    int i,j,temp;
    int change=0;//检测一次排序中是否发生交换，若无交换，则序列有序，仅需一趟排序
    for(i=n-1;i>=0&&change==0;i--){
        change=1;
        for(j=0;j<i;j++){
            if(a[j]>a[j+1]){
                change=0;
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}
//时间复杂度：O(n2)
//代码参考：《数据结构与算法分析新视角,周幸妮,2016》- 7.3交换排序、《大话数据结构.程杰》- 9.3 冒泡排序

//(2)快速排序(Quick Sort)
//快速排序是对冒泡排序的一种改进，基本思路是将待排序序列分成两部分，其中一部分的记录都比另一部分的记录小，随后分别对这两部分再分成两部分，使一部分的记录都小于另一部分，如此反复最终使整个序列有序。
//参考：《数据结构与算法分析新视角,周幸妮,2016》- 7.3交换排序
QuickSort(array[100],100,0,99);

void QuickSort(int *arr, int n, int low, int high){
int pivotloc;
if(low<high){
    pivotloc=Partition_1(arr,low,high);
    QuickSort(arr,n,low,pivotloc-1);
    QuickSort(arr,n,pivotloc+1,high);
}
}

int Partition_1(int arr[], int low, int high){
    int pivotloc=arr[low], temp;
    while(low<high){
        while(low<high && arr[high]>=pivotloc)
            --high;
        if(arr[high]<pivotloc){ //判断是low==high、还是arr[high]<pivotloc引起while终止，low==high引起while终止不
            temp=arr[low];  //需要交换、直接跳出外层while，arr[high]<pivotloc引起while终止才需要交换。
            arr[low]=arr[high];
            arr[high]=temp;
        }

        while(low<high && arr[low]<=pivotloc)
            ++low;
        if(arr[low]>pivotloc){ //判断是low==high、还是arr[low]>pivotloc引起while终止，low==high引起while终止不
            temp=arr[low];  //需要交换、直接跳出外层while，arr[low]>pivotloc引起while终止才需要交换。
            arr[low]=arr[high];
            arr[high]=temp;
        }

    }
}
//时间复杂度：O(nlogn)
//代码参考：《数据结构与算法分析新视角,周幸妮,2016》- 7.3交换排序


//选择排序
//(3)简单选择排序(Selection Sort)
//选择排序的基本思想是每一趟在所有记录中选择最小的记录放入有序序列中，如此反复就能够实现无序序列的有序化。
//相对于冒泡排序来说，简单选择排序效率更高一些，因为冒泡排序每一轮的每一次比较后，如果发现前面的数比后面的数大，就要立即进行数据交换，而选择排序则每一轮最多进行一次数据交换。冒泡排序数据交换次数平均要比选择排序多。参考：《数据结构与算法分析新视角,周幸妮,2016》- 7.4选择排序
//选择排序：根据位置选择元素(指定位置，选择元素)。指定位置arr[0]存放最小元素、指定位置arr[1]存放次小元素、指定位置arr[2]存放再次小元素、…。
//指定位置arr[0]存放最小元素，第一趟，从数组中去查找最小元素，找到最小元素后，将其放到位置arr[0]；
//指定位置arr[1]存放次小元素，第二趟，从数组中去查找次小元素，找到次小元素后，将其放到位置arr[1]；
//第三趟，…
//代码：
void SelectionSort(int *a, int n){
    int i,j,loc,temp;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++){
            if(a[j]<a[i])
                loc=j; //记录某一趟比较中最小元素所在位置
        }

        if(i!=loc){ //最后只进行一次位置交换
            temp=a[i];
            a[i]=a[loc];
            a[loc]=a[i];
        }
    }
}
//时间复杂度：O(n2)
//代码参考《大话数据结构.程杰》- 9.4 简单选择排序


//(4)堆排序(Heap Sort)
//未完


//插入排序
//(5)直接插入排序(Insertion Sort)
//代码参考：《大话数据结构.程杰》- 9.5直接插入排序、《数据结构与算法分析新视角,周幸妮,2016》- 7.2插入排序
void InsertSort(int *a, int n){
    int i,j,temp;
    for(i=1;i<n;++i){
        if(a[i]<a[i-1]){
            temp=a[i]; //哨兵
            for(j=i-1;temp<a[j]&&j>=0;--j) //查找插入位置
                a[j+1]=a[j];
            a[j+1]=temp;
        }
    }
}
//时间复杂度：O(n2)

//(6)希尔排序(Shell Sort)
//代码参考：《数据结构与算法分析新视角,周幸妮,2016》- 7.2插入排序、《大话数据结构.程杰》- 9.6希尔排序、
//《数据结构(C,第2版)严蔚敏》-8.2.3 希尔排序
void ShellSort(int *a, int n){
    int k,dlta[3]={5,3,1};
    for(k=0;k<3;++k)
        ShellInsert(arr,n,dlta[k]);
}

void ShellInsert(int *arr,int n, int dk){
    int i,j,k,temp;
    for(k=0;k<dk;k++){
        for(i=k+dk;i<n;i=i+dk){
            if(arr[i]<arr[i-dk]){
                temp=arr[i];
                for(j=i-dk;j>=0&&temp<arr[j];j=j-dk)
                    arr[j+dk]=arr[j];
                arr[j+dk]=temp;
            }
        }
    }
}
//时间复杂度：O(nlog2n)



//归并排序
//(7)归并排序(Merge Sort)
//参考：《数据结构(C,第2版)严蔚敏》-8.5归并排序、《大话数据结构.程杰》-9.8归并排序
void Merge(int *r, int *t, int low, int mid, int high){//将有序序列r[low…mid]和t[mid+1...high]归并为有序序列r[low...high]
    int i=low,j=mid+1,k=low;
    while(i<=mid&&j<=high)
        if(r[i]<r[j])
            t[k++]=r[i++];
        else
            t[k++]=r[j++];

    while(i<=mid)
        t[k++]=r[i++];
    while(j<=high)
        t[k++]=r[j++];
}

void MSort(int *r,int *t, int low, int high){//r[low...high]归并后放入t[low...high]
    int s[NUM];

    if(low==high)
        t[low]=r[low];
    else{
        mid=(low+high)/2;
        MSort(r,s,low,mid);
        MSort(r,s,mid+1,high);
        Merge(s,t,low,mid,high);
    }
}

void MergeSort(int r[NUM]){
    MSort(r[NUM],r[NUM],0,NUM-1);
}
时间复杂度：O(nlog2n)



//分配排序
//(8)桶排序(Bucket Sort)
//代码参考：《数据结构与算法分析新视角,周幸妮,2016》- 7.6分配排序 - 7.6.1桶排序

//(9)基数排序(Radix Sort)
//代码参考：《数据结构与算法分析新视角,周幸妮,2016》- 7.6分配排序 - 7.6.2基数排序
//          《数据结构(C,第2版)严蔚敏》-8.6基数排序
//基数排序详解--https://blog.csdn.net/u011948899/article/details/78027838
//基数排序分为两类：
//第一类：最低位优先法，简称LSD法：先从最低位开始排序，再对次低位排序，直到对最高位排序后得到一个有序序列；具体过程如下图所示：
//初始数组序列为：15,25,105,78,34,21,32,41，按照个位数大小依次入桶；
//将桶中数依次倒出，对于同一个桶中的数按先进先出顺序倒出，结果为：21,41,32,34,15,25,105,78，再按十位数大小依次入桶；
//将桶中数依次倒出，结果为：105,15,21,25,32,34,41,78，再按百位上数大小依次入桶，没有百位的数则按百位为0入桶；
//将桶中数倒出，结果为：15,21,25,32,34,41,78,105
//Java实现代码如下：
public void radixSort(int[] A,int n){
        int max = A[0];
        for(int i = 1 ;i < n;i++){
            if(max < A[i])
                max = A[i];
        }
        double d = Math.pow(10, String.valueOf(max).length());
        
        int k = 1;
        int[][] t = new int[10][n];  //桶
        int[] num = new int[n];  //记录每个桶中存入数的个数
        while(k < d){
            for(int a : A){
                int m = (a / k) % 10;
                t[m][num[m]] = a;
                num[m]++;
            }
            int c = 0;
            for(int i = 0; i < n; i++){
                if(num[i] != 0){
                    for(int j = 0;j < num[i];j++){
                        A[c++] = t[i][j];
                    }
                }
                num[i] = 0;
            }
            k = k * 10;
        }
        
    }
//时间复杂度：O(d(n+rd))

//第二类：最高位优先法，简称MSD法：先从最高位开始排序，再逐个对各分组按次高位进行子排序，循环直到最低位。
//仍以序列：15,25,105,78,34,21,32,41为例，从最高位百位依次入桶，只有105有百位，其他百位按0算；检测每个桶中的数据。当桶中的元素个数多于1个的时候，要对这个桶递归进行下一位的分组。
//Java代码实现：
public class MSDSort {
    public int[] sort(int[] A, int n){
        int max = A[0];
        for(int i = 1 ;i < n;i++){
            if(max < A[i])
                max = A[i];
        }
        int maxL = String.valueOf(max).length();  //获取数组中最长元素长度
        
        int k = new Double(Math.pow(10, maxL - 1)).intValue();
        int[][] t = new int[10][n];  //桶
        int[] num = new int[n];      //记录每个桶中存入数的个数
        
        for(int a : A){              //按最高位入桶
            int m = (a / k) % 10;
            t[m][num[m]] = a;
            num[m]++;
        }
        int c = 0;
        for(int i = 0; i < n; i++){
            if(num[i] == 1){        //如果桶中只有一个数则直接取出
                A[c++] = t[i][0];
            }else if(num[i] > 1){   //如果桶中不止一个数，则另存如数组B递归
                int[] B = new int[num[i]]; 
                for(int j = 0;j < num[i];j++){
                    B[j] = t[i][j];
                    sort(B,num[i]);   //递归方法
                }
            }
        }
        return A;
    }

    public static void main(String[] args) {
        RadixSort r = new RadixSort();
        int[] A = {12,1,23,123,34};
        r.sort(A, A.length);
        for(int a : A){
            System.out.println(a);
        }
 
    }
}
//时间复杂度：O(d(n+rd))





