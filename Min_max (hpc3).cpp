#include <bits/stdc++.h>
#include <omp.h>
using namespace std;


template <typename T>
class ParallelReduction{
    vector<T> arr;

    public:
    ParallelReduction(const vector<T>& inputArr) : arr(inputArr) {}

    T sum(){
        T sum = 0;

        #pragma omp parallel for reduction(+:sum)
        for(size_t i = 0; i<arr.size(); i++){
            sum += arr[i];
        }

        return sum;
    }

    T arr_min(){
        T minElement = numeric_limits<T>::max();

        #pragma omp parallel for reduction(min: minElement)
        for(size_t i = 0; i<arr.size(); i++){
            minElement = min(minElement, arr[i]);
        }

        return minElement;
    }

    T arr_max(){
        T maxElement = numeric_limits<T>::min();

        #pragma omp parallel for reduction(max: maxElement)
        for(size_t i=0; i<arr.size(); i++){
            maxElement = max(maxElement, arr[i]);
        }

        return maxElement;
    }

    double avg(){
        T sumValue = sum();
        return static_cast<double>(sumValue)/arr.size();
    }
};

int main(){
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ParallelReduction<int> pr(arr);

    int sum = pr.sum();
    cout << "Sum: "<< sum << endl;

    int min = pr.arr_min();
    cout << "Min: " << min << endl;

    int max = pr.arr_max();
    cout << "Max: " << max << endl;

    double avg = pr.avg();
    cout << "Average: "<< avg << endl;

    return 0;
}