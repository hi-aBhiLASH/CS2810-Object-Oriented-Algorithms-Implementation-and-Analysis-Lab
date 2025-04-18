#include <bits/stdc++.h>
using namespace std;
#define int long long int
class Comparator
{
public:
    Comparator(int k)
    {
        flag = k;
    }
    bool operator()(int a, int b)
    {
        if (a > b)
        {
            if (flag == 1)
                return false;
            return true;
        }
        else
        {
            if (flag == 1)
                return true;
            return false;
        }
    }

private:
    int flag;
};

void sortrows(int l, int r, vector<int> &a, Comparator comparator)
{
    if (l == r)
        return;
    int mid = (l + r) / 2;
    sortrows(l, mid, a, comparator);
    sortrows(mid + 1, r, a, comparator);
    // merging(a,l,mid,r,comparator);
    {

        vector<int> c(r - mid, 0), b(mid - l + 1, 0);
        int s = 0;
        for (int i = l; i <= mid; i++)
        {
            b[s] = a[i];
            s++;
        }
        s = 0;
        for (int i = mid + 1; i <= r; i++)
        {
            c[s] = a[i];
            s++;
        }
        int j = 0, k = 0;
        int i;
        for (i = l; i <= r && j <= mid - l && k <= r - (mid + 1); i++)
        {
            if (!comparator(b[j], c[k])) // b[j]>c[k]
            // if(b[j]>c[k])
            {
                a[i] = c[k];
                k++;
            }
            else
            {
                a[i] = b[j];
                j++;
            }
        }
        if (j <= mid - l)
        {
            while (i <= r)
            {
                a[i] = b[j];
                j++;
                i++;
            }
        }
        else if (k <= r - (mid + 1))
        {
            while (i <= r)
            {
                a[i] = c[k];
                k++;
                i++;
            }
        }
    }
}

int countinversions(vector<int> &a, int l, int r)
{

    if (l == r)
    {
        return 0;
    }

    int mid = (l + r) / 2;
    int p = countinversions(a, l, mid);
    int q = countinversions(a, mid + 1, r);
    vector<int> c(r - mid, 0), b(mid - l + 1, 0);
    int s = 0;
    for (int i = l; i <= mid; i++)
    {
        b[s] = a[i];
        s++;
    }
    s = 0;
    for (int i = mid + 1; i <= r; i++)
    {
        c[s] = a[i];
        s++;
    }
    // aout(b);
    // aout(c);
    int count = 0;
    int j = l;
    for (int i = mid + 1; i <= r and j <= mid;)
    {
        if (b[j - l] <= c[i - mid - 1])
        {
            j++;
        }
        else
        {
            count += (mid - l + 1) - (j - l);
            i++;
        }
    }
    {
        int j = 0, k = 0;
        int i;
        for (i = l; i <= r && j <= mid - l && k <= r - (mid + 1); i++)
        {
            if (b[j] > c[k])
            {
                a[i] = c[k];
                k++;
            }
            else
            {
                a[i] = b[j];
                j++;
            }
        }
        if (j <= mid - l)
        {
            while (i <= r)
            {
                a[i] = b[j];
                j++;
                i++;
            }
        }
        else if (k <= r - (mid + 1))
        {
            while (i <= r)
            {
                a[i] = c[k];
                k++;
                i++;
            }
        }
    }
    return count + p + q;
}
//  by x-coordinate
bool sortbyX(pair<int, int> p1, pair<int, int> p2)
{
    return p1.first < p2.first;
}

// by y-coordinate
bool sortbyY(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second < p2.second;
}
int distance_square(pair<int, int> rs1, pair<int, int> rs2)
{
    int x = rs1.first - rs2.first;
    int y = rs1.second - rs2.second;

    int ans = x * x + y * y;

    return (ans);
}
pair<pair<int, int>, pair<int, int>> recursion(vector<pair<int, int>> &Px)
{
    if ((Px.size()) <= 3)
    {
        if (Px.size() == 2)
        {
            return {Px[0], Px[1]};
        }
        else
        {
            int a = distance_square(Px[0], Px[1]);
            int b = distance_square(Px[1], Px[2]);
            int c = distance_square(Px[0], Px[2]);

            if (a < b && a < c)
            {
                return {Px[0], Px[1]};
            }
            else if (b < a && b < c)
            {
                return {Px[1], Px[2]};
            }
            else
            {
                return {Px[0], Px[2]};
            }
        }
    }

    vector<pair<int, int>> Lx, Rx;
    for (int i = 0; i < (Px.size()) / 2; i++)
    {

        Lx.push_back(Px[i]);
    }

    for (int i = (Px.size()) / 2; i < Px.size(); i++)
    {

        Rx.push_back(Px[i]);
    }

    auto a = Lx.back().first;
    auto point_1 = recursion(Lx);
    auto point_2 = recursion(Rx);

    int left = distance_square(point_1.first, point_1.second);
    int right = distance_square(point_2.first, point_2.second);

    pair<pair<int, int>, pair<int, int>> min_pair;

    if (left < right)
    {
        min_pair = point_1;
    }
    else if (right < left)
    {
        min_pair = point_2;
    }
    else
    {
        if (min(point_1.first, point_1.second) < min(point_2.first, point_2.second))
        {
            min_pair = point_1;
        }
        else
        {
            min_pair = point_2;
        }
    }
    int delta_square = min(left, right);
    vector<pair<int, int>> S;

    for (int i = 0; i < Px.size(); i++)
    {
        if ((Px[i].first - a) * (Px[i].first - a) <= delta_square)
        {
            S.push_back(Px[i]);
        }
    }
    sort(S.begin(), S.end(), sortbyY);


    for (int i = 0; i < S.size(); i++)
    {
        for (int j = i + 1; j < min(i + 8, (int)S.size()); j++)
        {
            int d = distance_square(S[i], S[j]);
            if (d < delta_square)
            {
                delta_square = d;
                min_pair = make_pair(S[i], S[j]);
            }
            else if (d == delta_square)
            {
                if (min(min_pair.first, min_pair.second) > min(S[i], S[j]))
                {
                    min_pair = make_pair(S[i], S[j]);
                }
            }
        }
    }

    return min_pair;
}

pair<pair<int, int>, pair<int, int>> closestpair(vector<pair<int, int>> &Coord)
{

    vector<pair<int, int>> Px = Coord;
    vector<pair<int, int>> Py = Coord;

    sort(Px.begin(), Px.end(), sortbyX);
    sort(Py.begin(), Py.end(), sortbyY);

    return recursion (Px) ;
}

int32_t main()
{
    string s;
    vector<vector<int>> matrix;

    while (1)
    {
        cin >> s;
        if (s == "END")
        {
            break;
        }
        else if (s == "CREATE_2D")
        {
            int n;
            cin >> n;
            matrix.assign(n, vector<int>(n, 0));
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cin >> matrix[i][j];
                }
            }
        }
        else if (s == "SORT_2D")
        {
            string s1;
            cin >> s1;
            int flag = 1; // flag=1 tells needs to be sorted in ascending order.push_back(matrix[i][j]);
            if (s1 == "ascending")
            {
                flag = 1;
            }
            else
                flag = 0;
            int n = matrix.size();
            Comparator comparator(flag);
            for (int i = 0; i < matrix.size(); i++)
            {
                // vector<int>&a=matrix[i];
                sortrows(0, n - 1, matrix[i], comparator);
            }
        }
        else if (s == "INVERSION_2D")
        {
            vector<int> a;
            int count = 0;
            int n = matrix.size();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    a.push_back(matrix[i][j]);
                }
            }

            cout << countinversions(a, 0, n * n - 1) << endl; // n*n-1
        }
        else if (s == "DISPLAY_2D")
        {
            int n = matrix.size();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
        }
        else if (s == "CLOSEST_2D")
        {
            int si;
            cin >> si;
            vector<pair<int, int>> points;
            vector<int> x(si, 0), y(si, 0);
            for (int i = 0; i < si; i++)
            {
                int v, b;
                cin >> v >> b;
                points.push_back(make_pair(v, b));
            }
            pair<pair<int, int>, pair<int, int>> a = closestpair(points);
            int i;
            for (i = 0; i < points.size(); i++)
            {
                if (points[i].first == a.first.first && points[i].second == a.first.second)
                {
                    break;
                }
            }
            int j;
            for (j = 0; j < points.size(); j++)
            {
                if (points[j].first == a.second.first && points[j].second == a.second.second)
                {
                    break;
                }
            }
            cout << points[min(i, j)].first << " " << points[min(i, j)].second << " " << points[max(i, j)].first << " " << points[max(i, j)].second << endl;
        }
    }
}