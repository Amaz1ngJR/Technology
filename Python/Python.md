c++
```c++
int n = 100, m = 100, a = 50;
vector<int> v1(n);
cout<< v1.size();
vector<vector<int>>v2(m, vector<int>(n, 1));
while(a > 0)
  break;
for (int i = 0; i < n; i++) 
  for (int j = m; j >= 0; --j) 
    if (i < j && i < a) //&& || !
      return false; //true
```
python
```python
n = 100
m = 100
a = 50
v1 = [0] * n
print(len(v1))
v2 = [[1] * n for _ in range(m)]
while a > 0 :
  break
for i in range(n):
  for j in range(m, -1, -1):
    if i < j and i < a: # and or not
      return False # True
```
